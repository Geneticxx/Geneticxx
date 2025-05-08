export module HistoryBasic;

import History;

import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class HistoryBasic
     * @brief A class that manages the history of statistics and population evaluations during an evolutionary process.
     *
     * This class tracks the best fitness, objective scores, and other related information for each generation. It stores
     * statistics and populations across generations and provides methods to access the best individuals, their phenomes,
     * and their scores.
     */
    export class HistoryBasic : public History {
    private:
        std::unique_ptr<Statistics> m_statisticsTotal;
        /**
         * @brief Stores statistics for each generation or population evaluations.
         *
         * A vector of statistics objects, where each element contains the statistics for a particular generation or population.
         */
        std::vector<std::vector<std::unique_ptr<Statistics>>> m_statistics;

        /**
         * @brief Stores the populations for each generation.
         *
         * A vector of unique pointers to population objects, each representing the population of a generation.
         */
        std::vector<std::vector<std::unique_ptr<Population>>> m_populations;

        /**
         * @brief Tracks the current index for statistics in the vector.
         *
         * This index is used to identify the position of the current statistics object in the `m_Statistics` vector.
         */
        int m_CurrentStatisticsIndex;

        /**
         * @brief Stores the fitness score of the best individual observed so far.
         *
         * This value is updated whenever a better fitness score is found in the current statistics.
         */
        double m_BestFitness;

        /**
         * @brief The generation where the best fitness was achieved.
         *
         * This value tracks the generation in which the best fitness score was observed.
         */
        int m_BestGeneration;

        /**
         * @brief The index of the population in the generation where the best fitness was achieved.
         *
         * This value tracks the population in the generation in which the best fitness score was observed.
         */
        int m_BestPopulationIndex;

    public:
        /**
         * @brief Constructor to initialize the history with initial statistics.
         *
         * This constructor initializes the history with the given statistics object. It also sets default values
         * for other member variables.
         *
         * @param statistics Pointer to the initial statistics object.
         */
        HistoryBasic(Statistics* statistics);

        /**
         * @brief Destructor.
         *
         * The destructor ensures proper cleanup of the `HistoryBasic` object. As `m_Statistics` and `m_Populations`
         * are managed by raw pointers and smart pointers respectively, they will be automatically cleaned up.
         */
        ~HistoryBasic() override;

        /**
         * @brief Updates the current statistics with information from the given population.
         *
         * This method updates the current statistics object with the data from the provided population.
         *
         * @param population Pointer to the current population object to be used for updating statistics.
         */
        void updateCurrentStatistics(Population* population, int index) override;

        /**
         * @brief Pushes the current statistics into the statistics history.
         *
         * This method stores the current statistics and updates the best fitness, objective score, generation,
         * and phenome index if necessary.
         */
        void pushStatistics() override;

        void clear() override;

        /**
         * @brief Retrieves the best fitness score for a given index.
         *
         * This method retrieves the best fitness score for the individual at the specified index in the best generation.
         *
         * @param index The index of the individual whose fitness score is to be retrieved.
         * @return The best fitness score for the individual at the specified index.
         */
        double getBestFitness(int index) const override;

        /**
         * @brief Retrieves the best objective scores for a given index.
         *
         * This method retrieves the objective scores for the individual at the specified index in the best generation.
         *
         * @param index The index of the individual whose objective scores are to be retrieved.
         * @return A vector of objective scores for the individual at the specified index.
         */
        std::vector<double> getBestObjectiveScores(int index) const override;

        /**
         * @brief Retrieves the generation in which the best fitness was observed.
         *
         * This method returns the generation where the best fitness score was achieved.
         *
         * @return The generation where the best fitness score was observed.
         */
        int getBestGeneration() const override;

        int getBestPopulationIndex() const override;
        /**
         * @brief Retrieves the phenome of an individual at a given generation and index.
         *
         * This method is currently not implemented, but it is intended to return the phenome of the individual
         * at the specified generation and index.
         *
         * @param generation The generation to which the individual belongs.
         * @param populationIndex The index of the population within the generation
         * @param index The index of the individual in the population.
         * @return A pointer to the phenome of the individual.
         */
        const Individual* getBestIndividual(int generation, int populationIndex, int index) const override;

        /**
         * @brief Retrieves the phenome of an individual at a given generation and index.
         *
         * This method is currently not implemented, but it is intended to return the phenome of the individual
         * at the specified generation and index.
         *
         * @param index The index of the individual in the best population of the best generation.
         * @return A pointer to the phenome of the individual.
         */
        const Individual* getBestIndividual(int index) const override;

        /**
         * @brief Retrieves the objective score of an individual at a given generation and index.
         *
         * This method is currently not implemented, but it is intended to return the objective score of the individual
         * at the specified generation and index.
         *
         * @param generation The generation to which the individual belongs.
         * @param index The index of the individual in the population.
         * @return The objective score of the individual.
         */
        std::vector<double> getObjectiveScore(int generation, int populationIndex, int index) const override;

        /**
         * @brief Retrieves the fitness score of an individual at a given generation and index.
         *
         * This method retrieves the fitness score for the individual at the specified generation and index.
         *
         * @param generation The generation to which the individual belongs.
         * @param index The index of the individual in the population.
         * @return The fitness score of the individual.
         */
        double getFitness(int generation, int populationIndex, int index) const override;

        /**
         * @brief Handles the evaluation process after it is completed.
         *
         * This method is a placeholder for handling actions that should take place after the evaluation of a generation
         * or population is done. Currently, it does not perform any actions.
         *
         * @param population A pointer to vector of unique pointers to population objects.
         * @return An integer status code (currently returns 0).
         */
        int evaluationDone(std::vector<std::unique_ptr<Population>> *population) override;

        /**
         * @brief Handles actions when a new generation starts.
         *
         * This method is a placeholder for handling actions that should take place when a new generation begins.
         * Currently, it does not perform any actions.
         *
         * @param population A pointer to vector of unique pointers to population objects.
         * @return An integer status code (currently returns 0).
         */
        int generationStart(std::vector<std::unique_ptr<Population>> *population) override;

        /**
         * @brief Handles actions when a generation finishes.
         *
         * This method updates the current statistics and pushes the new statistics after a generation is done.
         *
         * @param population A pointer to vector of unique pointers to population objects.
         * @return An integer status code (currently returns 0).
         */
        int generationDone(std::vector<std::unique_ptr<Population>> *population) override;
    };
}
