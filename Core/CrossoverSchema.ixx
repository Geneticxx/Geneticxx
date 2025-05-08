export module CrossoverSchema;

export import Genome;
import std;
import std.compat;

namespace Geneticxx {
	/**
	 * @class CrossoverSchema
	 * @brief Class responsible for taking parent genomes and creating children genomes based on their values.
	 *
	 * This class defines the basic interface for performing crossover operations between
	 * two parent genomes to produce offspring genomes. Derived classes should implement
	 * the `crossover` method to define the specific crossover behaviour.
	 */
	export class CrossoverSchema {
	public:
		/**
		 * @brief Virtual destructor to ensure proper cleanup of derived class objects.
		 *
		 * The virtual destructor ensures that derived class destructors are called
		 * when deleting an object through a base class pointer.
		 */
		virtual ~CrossoverSchema() {
		}

		/**
		 * @brief Performs the crossover operation between two individuals and returns a new offspring.
		 *
		 * This method should be implemented in derived classes to define the specifics of
		 * the crossover operation. It produces a new genome based on the values of two parent genomes.
		 *
		 * @param parent1 First genome used in generating child genomes.
		 * @param parent2 Second genome used in generating child genomes.
		 *
		 * @return A vector of unique pointers to child genomes. This vector must contain at least one value.
		 *
		 * @note The implementation should ensure that at least one child genome is returned.
		 */
		[[nodiscard]] virtual std::vector<std::unique_ptr<Genome>> crossover(Genome* parent1, Genome* parent2) = 0;
	};
}
