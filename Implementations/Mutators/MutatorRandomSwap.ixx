export module MutatorRandomSwap;

export import MutationSchema;
import RandomIntFromRange;
import Genome1D;
import std;

namespace Geneticxx {
    /**
     * @class MutatorRandomSwap
     * @brief A mutation schema that performs a random swap between two values in a genome.
     *
     * This class defines a mutation operation that selects two random indices in a genome and swaps their values.
     */
    export class MutatorRandomSwap : public MutationSchema {
    private:
        /**
         * @brief Pointer to a random number generator for generating random integers.
         *
         * This utility is used to generate random indices for swapping values in the genome.
         */
        RandomIntFromRange* m_RandomNumbersGeneratorInt{};

    public:
        /**
         * @brief Constructor to initialize the mutation schema with a random number generator.
         *
         * This constructor initializes the mutation schema by accepting a random integer generator, which will
         * be used to select random indices for swapping values in the genome.
         *
         * @param genInt Pointer to the random integer generator.
         */
        MutatorRandomSwap(RandomIntFromRange* genInt);

        /**
         * @brief Destructor.
         *
         * The destructor cleans up resources. In this case, it relies on the smart pointer, so no additional
         * cleanup is required.
         */
        ~MutatorRandomSwap() override;

        /**
         * @brief Performs the mutation by swapping two random values in the genome.
         *
         * This method selects two random indices in the genome and swaps the values at those positions. If the two
         * selected indices are the same, it will ensure the second index is different before performing the swap.
         *
         * @param genome Pointer to the genome to mutate.
         */
        void mutate(Genome* genome) override;

        /**
         * @brief Validates the genome for mutation.
         *
         * This method ensures that the genome is valid for mutation. In this case, it checks that the genome has
         * at least two elements, as swapping requires multiple values.
         *
         * @param genome Pointer to the genome to validate.
         *
         * @return True if the genome is valid for mutation (i.e., has at least two elements), otherwise false.
         */
        bool validate(Genome* genome) const override;

        /**
         * @brief Clones the mutator.
         *
         * This method creates a new instance of the `MutatorRandomSwap` and copies the random number generator
         * for use in the cloned mutator.
         *
         * @return A pointer to the cloned mutation schema.
         */
        [[nodiscard]] MutationSchema* clone() const override;
    };
}
