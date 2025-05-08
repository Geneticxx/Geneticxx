export module Evaluation;


export import Phenome;
import std;
import std.compat;


namespace Geneticxx {
	/**
 * @class Evaluation
 * @brief Class responsible for evaluating a phenome and returning a vector of values (min. 1).
 *
 * This class provides an interface for evaluating a phenome and returning a set of
 * objective scores. Derived classes should implement the `evaluate` method to define
 * the specific evaluation process.
 */
	export class Evaluation {
	public:
		/**
		 * @brief Virtual destructor to ensure proper cleanup of derived class objects.
		 *
		 * The virtual destructor ensures that derived class destructors are called
		 * when deleting an object through a base class pointer.
		 */
		virtual ~Evaluation() {
		}

		/**
		 * @brief Evaluate the given phenome.
		 *
		 * This method should be implemented in derived classes to evaluate a given
		 * phenome and return a vector of objective scores.
		 *
		 * @param phenome Phenome that is subjected to evaluation.
		 *
		 * @return A vector of objective scores. The vector must contain at least one score.
		 *
		 * @note The implementation should ensure that the returned vector has a minimum
		 *       of one value.
		 */
		virtual std::vector<double> evaluate(const Phenome *phenome) = 0;
	};
}
