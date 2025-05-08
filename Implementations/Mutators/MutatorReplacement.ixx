export module MutatorReplacement;

export import MutationSchema;
import RandomIntFromRange;
import RandomRealFromRange;
import Genome1D;
import std;

namespace Geneticxx {
    /**
     * @class MutatorReplacement
     * @brief A mutation schema that replaces a random value in the genome with a new randomly generated value.
     *
     * This class performs a mutation operation where it selects a random position in the genome and replaces the
     * value at that position with a new value randomly generated within a specified range.
     */
    export class MutatorReplacement : public MutationSchema {
    private:
        /**
         * @brief Pointer to a random number generator for generating random integers.
         *
         * This utility is used to generate random indices for selecting positions in the genome.
         */
        RandomIntFromRange* m_RandomNumbersGeneratorInt{};

        /**
         * @brief Pointer to a random number generator for generating random real values.
         *
         * This utility is used to generate new values that will replace the existing value in the genome.
         */
        RandomRealFromRange* m_RandomNumbersGeneratorReal{};

        /**
         * @brief Maximum value range for the mutation.
         *
         * This is the upper bound for the random values that will replace the existing values in the genome.
         */
        double m_MaxValue;

        /**
         * @brief Minimum value range for the mutation.
         *
         * This is the lower bound for the random values that will replace the existing values in the genome.
         */
        double m_MinValue;

    public:
        /**
         * @brief Constructor to initialize the mutation schema with a random number generator for integers and reals.
         *
         * This constructor initializes the mutation schema by accepting random integer and real number generators,
         * which will be used to select indices and generate values for mutation, respectively. It also sets default
         * min and max value ranges for mutation.
         *
         * @param genInt Pointer to the random integer generator.
         * @param genReal Pointer to the random real number generator.
         */
        MutatorReplacement(RandomIntFromRange* genInt, RandomRealFromRange* genReal);

        /**
         * @brief Constructor that sets the minimum and maximum value range for mutations.
         *
         * This constructor initializes the mutation schema with specified min and max value ranges for mutation.
         * It also accepts random number generators for integers and reals, which are used for selecting indices and
         * generating values for mutation.
         *
         * @param genInt Pointer to the random integer generator.
         * @param genReal Pointer to the random real number generator.
         * @param minValue The minimum value for the mutation.
         * @param maxValue The maximum value for the mutation.
         */
        MutatorReplacement(RandomIntFromRange* genInt, RandomRealFromRange* genReal, double minValue, double maxValue);

        /**
         * @brief Destructor.
         *
         * The destructor cleans up resources. In this case, it relies on smart pointers, so no additional
         * cleanup is required.
         */
        ~MutatorReplacement() override;

        /**
         * @brief Clones the mutator.
         *
         * This method creates a new instance of the `MutatorReplacement` and copies the random number generators
         * as well as the mutation value range settings to the new instance.
         *
         * @return A pointer to the cloned mutation schema.
         */
        [[nodiscard]] MutationSchema* clone() const override;

        /**
         * @brief Performs the mutation by replacing a random value in the genome.
         *
         * This method selects a random position in the genome and replaces the value at that position with a new
         * value randomly generated within the specified range (from `m_MinValue` to `m_MaxValue`).
         *
         * @param genome Pointer to the genome to mutate.
         */
        void mutate(Genome* genome) override;

        /**
         * @brief Gets the minimum value for mutation.
         *
         * This method returns the current minimum value used for generating mutation values.
         *
         * @return The minimum value used for mutation.
         */
        double getMinVal() const;

        /**
         * @brief Sets the minimum value for mutation.
         *
         * This method sets the minimum value used for generating mutation values. If the new minimum value is greater
         * than the current maximum value, an exception is thrown.
         *
         * @param minVal The new minimum value for mutation.
         *
         * @throws std::invalid_argument If `minVal` is greater than the maximum value.
         */
        void setMinVal(double minVal);

        /**
         * @brief Gets the maximum value for mutation.
         *
         * This method returns the current maximum value used for generating mutation values.
         *
         * @return The maximum value used for mutation.
         */
        double getMaxVal() const;

        /**
         * @brief Sets the maximum value for mutation.
         *
         * This method sets the maximum value used for generating mutation values. If the new maximum value is less
         * than the current minimum value, an exception is thrown.
         *
         * @param maxVal The new maximum value for mutation.
         *
         * @throws std::invalid_argument If `maxVal` is less than the minimum value.
         */
        void setMaxVal(double maxVal);

        /**
         * @brief Validates the genome for mutation.
         *
         * This method ensures that the genome is valid for mutation. In this case, it checks that the genome has at
         * least one element to mutate.
         *
         * @param genome Pointer to the genome to validate.
         *
         * @return True if the genome is valid for mutation (i.e., has at least one element), otherwise false.
         */
        bool validate(Genome* genome) const override;
    };
}
