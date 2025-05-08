// ------ Population components ------

// Population
import PopulationSimple;

// Individual
import IndividualSimple;

// Genotype
import GenomeVector;

// Phenome
import PhenomeIntVector;


// ------ Genetic algorithm components ------

// Genetic algorithm
import GeneticAlgorithmSimple;

// Initialization
import InitializeWithCopies;

// Crossover
import CrossoverUniform;
import CrossoverSinglePoint;
import CrossoverOrder;

// Mutation
import MutatorRandomSwap;

// Selection
import SelectorRoulette;

// Stopping criterion
import StoppingCriterionMaxGenerations;

// Replacement
import ReplacementFull;

// Evaluation
//import ExampleEvaluation;
import EvaluationTravellingSalesman;
//import Evaluation;


// ------ Utility components ------

// Random numbers generator
import DefaultUniformIntRandomGenerator;
import DefaultUniformRealRandomGenerator;

// Dispatcher
import DispatcherNoDispatch;

// Scaling
import ScalingWithout;
import ScalingInverse;

// History
import HistoryBasic;

// Statistics
import StatisticsBasic;

// ------   ------

import std;

using namespace Geneticxx;

int main(int argc, char *argv[]) {
    /*                                    EXAMPLE ARRAY FOR TRAVELLING SALESMAN PROBLEM
    int rows = 8;
    auto array = new double*[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new double[2];
    }

    array[0][0] = 23;
    array[0][1] = 11;

    array[1][0] = 79;
    array[1][1] = 197;

    array[2][0] = 2;
    array[2][1] = -15;

    array[3][0] = -354;
    array[3][1] = -51;

    array[4][0] = 218;
    array[4][1] = 322;

    array[5][0] = 54;
    array[5][1] = -111;

    array[6][0] = 243;
    array[6][1] = -189;

    array[7][0] = -281;
    array[7][1] = 42;
*/
    std::vector<std::unique_ptr<Population> > aa;
    aa.push_back(std::make_unique<PopulationSimple>());

    auto *genInt = new DefaultUniformIntRandomGenerator();
    auto *genReal = new DefaultUniformRealRandomGenerator();

    HistoryBasic *history = new HistoryBasic(new StatisticsBasic());

    std::vector<int> tests = {0,1,2,3,4,5,6,7};
    auto phenomes = new PhenomeIntVector(8, tests);
    auto genes = new GenomeVector<int>(8);
    phenomes->setValue(0, genes->getValue(0));
    for (int i = 0; i < 8; i++)
    {
        int index = genInt->generate(0,7-i);
        genes->setValue(i, tests[index]);
        phenomes->setValue(i, genes->getValue(i));
        tests.erase(tests.begin() + index);
    }

    auto geneticAlgorithm = std::make_unique<GeneticAlgorithmSimple>(
        // Create a new population using PopulationSimple
        &aa,

        // Define the evaluation method for fitness calculation
        new EvaluationTravellingSalesman(),

        // Specify the replacement schema for the population
        new ReplacementFull(),

        // Define the crossover operation
        new CrossoverOrder<int>(genInt),

        // Specify the mutation operation with parameters
        new MutatorRandomSwap(genInt),
        //new MutatorPointReplacement(0, 100),

        // Define the fitness scaling method (scaling inverse - fitness is inversely proportional to objective score)
        new ScalingInverse(),
        //new ScalingWithout(),

        // Specify the selection method for reproduction
        new SelectorRoulette(genReal),

        // Initialize the population with 100 copies of an IndividualSimple
        new InitializeWithCopies(
            10,
            // Define an individual with a phenome and genome
            new IndividualSimple(
                phenomes,
                genes)),
                //new GenomeIntVector({0, 1, 2, 3, 4, 5, 6, 7}))),

        // Define the stopping criterion (max 100 generations)
        new StoppingCriterionMaxGenerations(100),

        // Define a dispatcher for managing tasks (no dispatching in this case)
        new DispatcherNoDispatch(),

        genReal
    );
    geneticAlgorithm->attach(history);

    //geneticAlgorithm->addEvaluation(new EvaluationTravellingSalesman()); test if 2 evaluations work

    // Initialize the genetic algorithm
    geneticAlgorithm->initialize();

    // Evolve the algorithm until the stopping criterion is met
    //geneticAlgorithm->evolve();
    geneticAlgorithm->step(100);


    // std::string a;
    for (int i = 0; i < history->getBestObjectiveScores(0).size(); i++)
    {
        std::cout << "best objective scores: " << history->getBestObjectiveScores(0)[i] << std::endl;
        if (i < history->getBestObjectiveScores(0).size() - 1) std::cout << " | ";
    }

    std::cout << "best fitness: " << history->getBestFitness(0) << std::endl;
    std::cout << "generation in which it appeared: " << history->getBestGeneration() << std::endl;
    for (int i = 0; i < history->getBestIndividual(history->getBestGeneration(), history->getBestPopulationIndex(), 0)->getPhenome()->getSize(); i++) {
        std::cout << std::any_cast<int>(dynamic_cast<const Phenome1D*>(history->getBestIndividual(history->getBestGeneration(), history->getBestPopulationIndex(), 0)->getPhenome())->getValue(i));
        if (i < history->getBestIndividual(history->getBestGeneration(), history->getBestPopulationIndex(), 0)->getPhenome()->getSize() - 1) std::cout << " | ";
    }

    // std::cin >> a;
    delete genInt;
    delete genReal;
    delete history;
    return 0;
}
