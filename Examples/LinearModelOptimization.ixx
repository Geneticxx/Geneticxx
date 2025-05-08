
// Population
import PopulationSimple;

// Individual
import IndividualSimple;

// Genotype
import GenomeVector;

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
import MutatorMultiplicative;
import MutatorReplacement;
import Mutator1DRandomValueAddition;

// Selection
import SelectorRoulette;

// Stopping criterion
import StoppingCriterionMaxGenerations;

// Replacement
import ReplacementFull;

// Evaluation
import Evaluation;


// ------ Utility components ------

// Random numbers generator
import DefaultUniformIntRandomGenerator;
import DefaultUniformRealRandomGenerator;

// Dispatcher
import DispatcherMultiThreaded;
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



namespace Geneticxx
{
    class EvaluationLinear : public Evaluation
    {
        std::vector<double> x = {4, -2, 3.5, 5, -11, -4.7};
        double y = 44;
    public:
        EvaluationLinear() = default;

        ~EvaluationLinear() override = default;
        std::vector<double> evaluate(const Phenome *phenomeBase) override
        {
            auto phenome = dynamic_cast<const Phenome1D*>(phenomeBase); // ideally this should be type checked earlier
            double result = 0;
            for (int i = 0; i < 6; i++)
            {
                result += x[i] * std::any_cast<double>(phenome->getValue(i)); // ideally this should be type checked earlier
            }
            std::vector<double> resultVector = {std::abs(y - result) + 0.000001};
            return resultVector;
        }
    };
}

using namespace Geneticxx;

int main(int argc, char *argv[]) {
//TODO sensible names
    std::vector<std::unique_ptr<Population> > populationVector;
    populationVector.push_back(std::make_unique<PopulationSimple>());

    auto *genInt = new DefaultUniformIntRandomGenerator();
    auto *genReal = new DefaultUniformRealRandomGenerator();

    auto phenomes = new Phenome1DNoTranslation<double>();
    auto genes = new GenomeVector<double>(6);
    for (int i = 0; i < 6; i++)
    {
        genes->setValue(i, 0.0);//genReal->generate(-2, 5));
    }
    phenomes->updatePhenome(genes);

    auto initializer = new InitializeWithCopies(100, new IndividualSimple(phenomes, genes));

    HistoryBasic *history = new HistoryBasic(new StatisticsBasic());

    auto geneticAlgorithm = std::make_unique<GeneticAlgorithmSimple>( //TODO change this to a steady-state algorithm
        // Create a new population using PopulationSimple
        &populationVector,

        // Define the evaluation method for fitness calculation
        new EvaluationLinear(), //TODO

        // Specify the replacement schema for the population
        new ReplacementFull(),

        // Define the crossover operation
        new CrossoverSinglePoint(genInt),

        // Specify the mutation operation with parameters
        //new MutatorMultiplicative<double>(genInt, genReal),
        new Mutator1DRandomValueAddition<double>(genInt, genReal),

        // Define the fitness scaling method (scaling inverse - fitness is inversely proportional to objective score)
        //new ScalingWithout(),
        new ScalingInverse(),

        // Specify the selection method for reproduction
        new SelectorRoulette(genReal),

        // Initialize the population with 100 copies of an IndividualSimple
        initializer,

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

    std::cout << "best objective scores: ";
    for (int i = 0; i < history->getBestObjectiveScores(0).size(); i++)
    {
        std::cout << history->getBestObjectiveScores(0)[i];
        if (i < history->getBestObjectiveScores(0).size() - 1) std::cout << " | ";
    }

    std::cout << std::endl << "best fitness: " << history->getBestFitness(0) << std::endl;
    std::cout << "generation in which it appeared: " << history->getBestGeneration() << std::endl;
    for (int i = 0; i < history->getBestIndividual(history->getBestGeneration(), history->getBestPopulationIndex(), 0)->getPhenome()->getSize(); i++) {
        std::cout << std::any_cast<double>(dynamic_cast<const Phenome1D*>(history->getBestIndividual(history->getBestGeneration(), history->getBestPopulationIndex(), 0)->getPhenome())->getValue(i));
        if (i < history->getBestIndividual(history->getBestGeneration(), history->getBestPopulationIndex(), 0)->getPhenome()->getSize() - 1) std::cout << " | ";
    }

    // std::cin >> a;
    delete genInt;
    delete genReal;
    delete history;
    return 0;
}
