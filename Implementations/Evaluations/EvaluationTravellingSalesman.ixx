export module EvaluationTravellingSalesman;

import Evaluation;
import Phenome1D;
import std;

namespace Geneticxx {
    /**
     * @class EvaluationTravellingSalesman
     * @brief Evaluation class for the Travelling Salesman Problem (TSP).
     *
     * This class calculates the total distance of a given route based on a predefined set of city coordinates.
     * It assumes that the route is closed, meaning the last city connects back to the first.
     */
    export class EvaluationTravellingSalesman : public Evaluation {
    private:
        int m_cols; ///< Number of coordinates (always 2 for 2D space).
        int m_rows; ///< Number of cities (destinations).
    public:


    private:
        double** m_array; ///< 2D array storing the coordinates of the cities.

    public:
        /**
         * @brief Default constructor initializing a predefined set of city coordinates.
         *
         * Initializes `m_rows` to 8 and sets up city coordinates in a fixed 2D space.
         */
        EvaluationTravellingSalesman();

        /**
         * @brief Constructor initializing the class with a custom set of city coordinates.
         *
         * @param rows Number of cities (destinations).
         * @param array Pointer to a dynamically allocated 2D array containing city coordinates.
         */
        EvaluationTravellingSalesman(int rows, double** array);

        /**
         * @brief Destructor for `EvaluationTravellingSalesman`.
         *
         * Releases dynamically allocated memory for city coordinates.
         */
        ~EvaluationTravellingSalesman() override;


        int getCols() const;

        void setCols(int m_cols);

        int getRows() const;

        void setRows(int m_rows);

        double *getCity(int index);
        /**
         * @brief Evaluates a given route and calculates its total travel distance.
         *
         * @param phenome Pointer to a Phenome object representing a proposed route.
         * @return A vector containing a single double value, which is the total route distance.
         * @throws std::invalid_argument if the number of cities in the phenome does not match `m_rows`.
         */
        std::vector<double> evaluate(const Phenome* phenome) override;
    };
}
