export module Dispatcher;

export import Calculator;
export import Evaluation;
export import Population;
import std;

namespace Geneticxx {
	/**
	 * @class Dispatcher
	 * @brief Class responsible for executing evaluations on the population.
	 *
	 * This class defines the interface for handling the dispatching logic that
	 * connects a population to an evaluation process. Derived classes should
	 * implement the `dispatch` method to define the specific dispatching behaviour.
	 */
	export class Dispatcher {
	public:
		/**
		 * @brief Virtual destructor to ensure proper cleanup of derived class objects.
		 *
		 * The virtual destructor ensures that derived class destructors are called
		 * when deleting an object through a base class pointer.
		 */
		virtual ~Dispatcher() {
		};

		/**
		 * @brief Handle the dispatching logic for the population and evaluation.
		 *
		 * This method should be implemented in derived classes to handle the dispatching
		 * logic that connects a population with a set of evaluations. It ensures that the
		 * population is properly evaluated by the given evaluation objects.
		 *
		 * @param population Pointer to the Population object that will be evaluated.
		 * @param evaluation Pointer to a vector of unique pointers to Evaluation objects
		 *        that will be used to evaluate the population.
		 */
		virtual void dispatch(Population *population, std::vector<std::unique_ptr<Evaluation> > *evaluation) = 0;
	};
}
