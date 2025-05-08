// ------ Population components ------

// Population
import PopulationSimple;

// Individual
import IndividualSimple;

// Genotype
import GenomeBitVector;

// Phenome
import Phenome1DNoTranslation;


// ------ Genetic algorithm components ------

// Genetic algorithm
import GeneticAlgorithmSimple;

// Initialization
import InitializeWithCopies;

// Crossover
import CrossoverUniform;
import CrossoverSinglePoint;

// Mutation
import Mutator1DPointBitFlip;

// Selection
import SelectorRoulette;

// Stopping criterion
import StoppingCriterionMaxGenerations;

// Replacement
import ReplacementFull;

// Evaluation
import EvaluationKnapsack;


// ------ Utility components ------

// Random numbers generator
import DefaultUniformIntRandomGenerator;
import DefaultUniformRealRandomGenerator;

// Dispatcher
import DispatcherMultiThreaded;
import DispatcherNoDispatch;

// Scaling
import ScalingWithout;

// History
import HistoryBasic;

// Statistics
import StatisticsBasic;

// ------   ------

import std;

using namespace Geneticxx;

int main(int argc, char *argv[]) {
//TODO sensible names
    std::vector<std::unique_ptr<Population> > aa;
    aa.push_back(std::make_unique<PopulationSimple>());

    auto *genInt = new DefaultUniformIntRandomGenerator();
    auto *genReal = new DefaultUniformRealRandomGenerator();

    auto phenomes = new Phenome1DNoTranslation<bool>();
    auto genes = new GenomeBitVector();
    genes->setGrayRepresentation({0,0,0,0,0,0,0,0,0,0,});
    phenomes->updatePhenome(genes);

    HistoryBasic *history = new HistoryBasic(new StatisticsBasic());
    auto geneticAlgorithm = std::make_unique<GeneticAlgorithmSimple>(
        // Create a new population using PopulationSimple
        &aa,

        // Define the evaluation method for fitness calculation
        new EvaluationKnapsack(20), //TODO

        // Specify the replacement schema for the population
        new ReplacementFull(),

        // Define the crossover operation
        new CrossoverSinglePoint(genInt),

        // Specify the mutation operation with parameters
        new Mutator1DPointBitFlip(genInt),

        // Define the fitness scaling method (scaling inverse - fitness is inversely proportional to objective score)
        new ScalingWithout(),

        // Specify the selection method for reproduction
        new SelectorRoulette(genReal),

        // Initialize the population with 100 copies of an IndividualSimple
        new InitializeWithCopies(
            100,
            // Define an individual with a phenome and genome
            new IndividualSimple(
                phenomes,
                genes)),
                //new GenomeIntVector({0, 1, 2, 3, 4, 5, 6, 7}))),

        // Define the stopping criterion (max 100 generations)
        new StoppingCriterionMaxGenerations(100),

        // Define a dispatcher for managing tasks (no dispatching in this case)
        new DispatcherMultiThreaded(),
        //new DispatcherNoDispatch(),

        genReal
    );
    geneticAlgorithm->attach(history);

    //geneticAlgorithm->addEvaluation(new EvaluationTravellingSalesman()); test if 2 evaluations work

    // Initialize the genetic algorithm
    geneticAlgorithm->initialize();

    // Evolve the algorithm until the stopping criterion is met

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    geneticAlgorithm->evolve();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    const Phenome* bestPhenome = history->getBestIndividual(0)->getPhenome();
    const auto castPhenome = dynamic_cast<const Phenome1D*>(bestPhenome);

    std::cout << "best objective scores: ";
    for (int i = 0; i < history->getBestObjectiveScores(0).size(); i++)
    {
        std::cout << history->getBestObjectiveScores(0)[i];
        if (i < history->getBestObjectiveScores(0).size() - 1) std::cout << " | ";
    }

    std::cout << std::endl << "best fitness: " << history->getBestFitness(0) << std::endl;
    std::cout << "generation in which it appeared: " << history->getBestGeneration() << std::endl;
    for (int i = 0; i < bestPhenome->getSize(); i++) {
        std::cout << std::any_cast<bool>(castPhenome->getValue(i));
        if (i < bestPhenome->getSize() - 1) std::cout << " | ";
    }

    // std::cin >> a;
    delete genInt;
    delete genReal;
    delete history;
    return 0;
}
