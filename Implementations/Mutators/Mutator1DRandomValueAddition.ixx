
export module Mutator1DRandomValueAddition;

export import MutationSchema;
import RandomIntFromRange;
import RandomRealFromRange;
import Genome1D;
import std;

namespace Geneticxx {
    /**
     * @class Mutator1DRandomValueAddition
     * @brief A mutation schema that replaces a random value in the genome with a new randomly generated value.
     *
     * This class performs a mutation operation where it selects a random position in the genome and replaces the
     * value at that position with a new value randomly generated within a specified range.
     */
    export template<typename T> //TODO should only accept types representing reals
    class Mutator1DRandomValueAddition : public MutationSchema {
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

        T minValue = -1, maxValue = 1;
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
        Mutator1DRandomValueAddition(RandomIntFromRange* genInt, RandomRealFromRange* genReal)
            : m_RandomNumbersGeneratorInt{genInt}, m_RandomNumbersGeneratorReal{genReal}
        {

        }

        Mutator1DRandomValueAddition(RandomIntFromRange* genInt, RandomRealFromRange* genReal, T minValue, T maxValue)
            : m_RandomNumbersGeneratorInt{genInt}, m_RandomNumbersGeneratorReal{genReal}, minValue{minValue}, maxValue{maxValue}
        {

        }
        /**
         * @brief Destructor.
         *
         * The destructor cleans up resources. In this case, it relies on smart pointers, so no additional
         * cleanup is required.
         */
        ~Mutator1DRandomValueAddition() override = default;

        /**
         * @brief Clones the mutator.
         *
         * This method creates a new instance of the `Mutator1DRandomValueAddition` and copies the random number generators
         * as well as the mutation value range settings to the new instance.
         *
         * @return A pointer to the cloned mutation schema.
         */
        [[nodiscard]] MutationSchema* clone() const override
        {
            auto cloneMutator = new Mutator1DRandomValueAddition<T>(m_RandomNumbersGeneratorInt,
                m_RandomNumbersGeneratorReal, minValue, maxValue);
            return cloneMutator;
        }

        /**
         * @brief Performs the mutation by replacing a random value in the genome.
         *
         * This method selects a random position in the genome and replaces the value at that position with a new
         * value randomly generated within the specified range (from `m_MinValue` to `m_MaxValue`).
         *
         * @param genome Pointer to the genome to mutate.
         */
        void mutate(Genome* genomeBase) override
        {
            auto genome = dynamic_cast<Genome1D*>(genomeBase);
            int pos = m_RandomNumbersGeneratorInt->generate(0, static_cast<int>(genome->getSize()) - 1);
            genome->setValue(
                pos,
                std::any_cast<T>(genome->getValue(pos)) + m_RandomNumbersGeneratorReal->generate(minValue, maxValue)
            );
        }


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
        bool validate(Genome* genome) const override
        {
            return genome->getSize() > 0;
        }
    };
}
