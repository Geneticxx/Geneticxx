export module EvaluationKnapsack;

export import Evaluation;
export import Phenome1D;
import std;

namespace Geneticxx {
    /**
 * @class EvaluationKnapsack
 * @brief Evaluation class for assessing a phenome's similarity to a target value.
 *
 * This class evaluates a given phenome by comparing its values to a predefined target.
 * The evaluation returns a normalized score representing how well the phenome matches the expected pattern.
 */
    export class EvaluationKnapsack : public Evaluation {
    private:
        int values[10] = {1,2,3,4,5,6,7,8,9,10}; ///< values of the items used for evaluation.
        int weights[10] = {1,10,2,9,3,8,4,7,5,6}; ///< weights of the items
        int capacity = 20; ///< capacity of the knapsack

    public:
        /**
         * @brief Constructor initializing the evaluation with a specific target value.
         *
         * @param target The reference value against which the phenome is evaluated.
         */
        EvaluationKnapsack(int target);

        /**
         * @brief Destructor for `EvaluationKnapsack`.
         */
        ~EvaluationKnapsack() override;

        /**
         * @brief Evaluates the phenome and returns a fitness score.
         *
         * @param phenome Pointer to a `Phenome` object representing the solution.
         * @return A vector containing a single double value representing the fitness score.
         */
        std::vector<double> evaluate(const Phenome* phenome) override;
    };
}
