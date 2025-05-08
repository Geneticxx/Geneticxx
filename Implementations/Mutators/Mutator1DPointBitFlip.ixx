export module Mutator1DPointBitFlip;

export import MutationSchema;
import RandomIntFromRange;
import RandomRealFromRange;
import Genome1D;
import std;

namespace Geneticxx {
    /**
     * @class MutatorPointReplacement
     * @brief A mutation schema that replaces a value in a genome with a new random value.
     *
     * This class defines a mutation operation that randomly replaces a value at a specific index (or a random index)
     * in a genome with a new value drawn from a specified range.
     */
    export class Mutator1DPointBitFlip : public MutationSchema {
    private:
        /**
         * @brief Pointer to a random number generator for generating random integers.
         *
         * This utility is used to generate random integer values for mutation.
         */
        RandomIntFromRange* m_RandomNumbersGeneratorInt{};

    public:
        /**
         * @brief Constructor to initialize the mutation schema with random number generators.
         *
         * This constructor initializes the mutation schema by accepting random number generators for integer
         * and real number generation. The mutation range is set to default values (0.0 for min and 60.0 for max).
         *
         * @param genInt Pointer to the random integer generator.
         */
        Mutator1DPointBitFlip(RandomIntFromRange* genInt);

        /**
         * @brief Destructor.
         *
         * The destructor cleans up resources, though in this case, it relies on smart pointers for automatic cleanup.
         */
        ~Mutator1DPointBitFlip() override;

        /**
         * @brief Clones the mutator.
         *
         * This method creates a new instance of the mutator and copies the relevant settings such as min and max values.
         *
         * @return A pointer to the cloned mutation schema.
         */
        [[nodiscard]] MutationSchema* clone() const override;

        /**
         * @brief Mutates the genome by replacing a value at a random index (or the specified index).
         *
         * This method performs the mutation by selecting an index (either randomly or specified by the `m_index` member)
         * and replacing the value at that index with a random value generated within the specified range.
         *
         * @param genome Pointer to the genome to mutate.
         */
        void mutate(Genome* genome) override;

        /**
         * @brief Validates the genome for mutation.
         *
         * This method ensures that the genome is valid for mutation (e.g., has at least one element).
         *
         * @param genome Pointer to the genome to validate.
         *
         * @return True if the genome is valid for mutation, otherwise false.
         */
        bool validate(Genome* genome) const override;
    };
}
