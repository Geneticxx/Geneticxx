module SelectorTournament;

namespace Geneticxx {
    SelectorTournament::SelectorTournament() {
    }

    SelectorTournament::~SelectorTournament() {
    }

    std::vector<std::unique_ptr<Individual>> SelectorTournament::select(Population* population, size_t size) {
        //TODO finish tournament selector
        /*
        Population* transitionalPopulation = new Population(); // Create the transitional population

        // Divide the given population into m_subsetsNumber subsets
        std::vector<std::vector<Individual*>> dividedPopulations(m_subsetsNumber); // ??
        size_t populationSize = population->getSize();
        size_t subsetSize = populationSize / m_subsetsNumber;

        for (size_t i = 0; i < populationSize; ++i) {
            dividedPopulations[i % m_subsetsNumber].push_back(population->at(i)); // ??
        }

        // Iterate through each subpopulation
        for (const auto& subPopulation : dividedPopulations) {
            Individual* bestIndividual = nullptr;
            double bestFitness = std::numeric_limits<double>::max(); // Start with a very high fitness value

            // Find the individual with the lowest fitness in the subpopulation
            for (Individual* individual : subPopulation) {
                double fitness = individual->getFitness();
                if (fitness < bestFitness) {
                    bestFitness = fitness;
                    bestIndividual = individual;
                }
            }

            // Add the best individual to the transitional population
            transitionalPopulation->add(bestIndividual);
        }

        // Return the transitional population
        return transitionalPopulation;


        */
        // a temporary measure - previous code will be the final one after adjustments
        auto temp = population->getIndividual(0)->clone();
        std::vector<std::unique_ptr<Individual>> results;
        auto tt = std::unique_ptr<Individual>(temp);
        results.push_back(std::move(tt));
        return std::move(results);
    }
}



