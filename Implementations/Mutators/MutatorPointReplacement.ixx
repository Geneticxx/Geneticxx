export module MutatorPointReplacement;

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
    export class MutatorPointReplacement : public MutationSchema {
    private:
        /**
         * @brief Pointer to a random number generator for generating random integers.
         *
         * This utility is used to generate random integer values for mutation.
         */
        RandomIntFromRange* m_RandomNumbersGeneratorInt{};

        /**
         * @brief Pointer to a random number generator for generating random real numbers.
         *
         * This utility is used to generate random real values for mutation within the specified range.
         */
        RandomRealFromRange* m_RandomNumbersGeneratorReal{};

        /**
         * @brief The maximum value range for mutations.
         *
         * This specifies the upper bound for the random values that can be assigned during mutation.
         */
        double m_MaxValue;

        /**
         * @brief The minimum value range for mutations.
         *
         * This specifies the lower bound for the random values that can be assigned during mutation.
         */
        double m_MinValue;

        /**
         * @brief The index of the genome element to mutate.
         *
         * If a valid index is set, the mutation will happen at that index; otherwise, a random index will be selected.
         */
        int m_index;

    public:
        /**
         * @brief Constructor to initialize the mutation schema with random number generators.
         *
         * This constructor initializes the mutation schema by accepting random number generators for integer
         * and real number generation. The mutation range is set to default values (0.0 for min and 60.0 for max).
         *
         * @param genInt Pointer to the random integer generator.
         * @param genReal Pointer to the random real number generator.
         */
        MutatorPointReplacement(RandomIntFromRange* genInt, RandomRealFromRange* genReal);

        /**
         * @brief Constructor to initialize the mutation schema with a custom range for mutations.
         *
         * This constructor initializes the mutation schema with specified minimum and maximum values for mutation
         * and also accepts random number generators for integer and real number generation.
         *
         * @param genInt Pointer to the random integer generator.
         * @param genReal Pointer to the random real number generator.
         * @param minValue The minimum value for mutation.
         * @param maxValue The maximum value for mutation.
         */
        MutatorPointReplacement(RandomIntFromRange* genInt, RandomRealFromRange* genReal, double minValue,
                                double maxValue);

        /**
         * @brief Destructor.
         *
         * The destructor cleans up resources, though in this case, it relies on smart pointers for automatic cleanup.
         */
        ~MutatorPointReplacement() override;

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
         * @brief Gets the minimum value for mutation.
         *
         * This method returns the minimum value used to generate random mutation values.
         *
         * @return The minimum value for mutation.
         */
        double getMinVal() const;

        /**
         * @brief Sets the minimum value for mutation.
         *
         * This method allows setting the minimum value for generating random mutation values.
         *
         * @param minVal The new minimum value for mutation.
         *
         * @throws std::invalid_argument If the provided minimum value is greater than the maximum value.
         */
        void setMinVal(double minVal);

        /**
         * @brief Gets the maximum value for mutation.
         *
         * This method returns the maximum value used to generate random mutation values.
         *
         * @return The maximum value for mutation.
         */
        double getMaxVal() const;

        /**
         * @brief Sets the maximum value for mutation.
         *
         * This method allows setting the maximum value for generating random mutation values.
         *
         * @param maxVal The new maximum value for mutation.
         *
         * @throws std::invalid_argument If the provided maximum value is less than the minimum value.
         */
        void setMaxVal(double maxVal);

        /**
         * @brief Gets the index at which mutation will occur.
         *
         * This method returns the current index set for mutation. If no valid index is set, a random index will be used.
         *
         * @return The index for mutation.
         */
        int getIndex() const;

        /**
         * @brief Sets the index at which mutation will occur.
         *
         * This method allows specifying the index at which mutation will occur. If no index is set, a random index will be used.
         *
         * @param index The index for mutation.
         */
        void setIndex(int index);

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
