export module SelectorTournament;

import SelectionSchema;
import std;

namespace Geneticxx {
    /**
     * @class SelectorTournament
     * @brief A selection schema that selects individuals using a tournament-based method.
     *
     * This class implements the `SelectionSchema` interface and selects individuals by running a tournament
     * among subsets of individuals from the population. The best individual from each subset is selected.
     */
    export class SelectorTournament : public SelectionSchema {
    private:
        /**
         * @brief The number of subsets used in the tournament selection.
         *
         * This value determines how the population is divided into subsets for the tournament selection process.
         */
        unsigned int m_subsetsNumber;

    public:
        /**
         * @brief Default constructor for `SelectorTournament` class.
         *
         * Initializes the tournament selector with default parameters, such as the number of subsets for the tournament.
         */
        SelectorTournament();

        /**
         * @brief Destructor for `SelectorTournament` class.
         *
         * The destructor ensures proper cleanup of resources when the `SelectorTournament` object is destroyed.
         */
        ~SelectorTournament() override;

        /**
         * @brief Selects a subset of individuals from the population using the tournament selection method.
         *
         * This method divides the population into a number of subsets (`m_subsetsNumber`) and performs a tournament
         * in each subset. The best individual (based on fitness) from each subset is selected and returned in the results.
         *
         * @param population The population from which to select individuals.
         * @param size The number of individuals to select.
         * @return A vector containing the selected individuals as unique pointers.
         */
        std::vector<std::unique_ptr<Individual>> select(Population* population, size_t size) override;
    };
}
