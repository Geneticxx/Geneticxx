export module RandomRealFromRange;

export import Individual;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class RandomRealFromRange
     * @brief A base class for generating random real numbers within a specified range.
     *
     * This class defines the basic structure for generating random real numbers.
     * Derived classes should implement the `generate` method to produce random
     * real numbers within a given range.
     */
    export class RandomRealFromRange {
    protected:
        unsigned int m_seed; ///< The seed used for random number generation

        /**
         * @brief Constructor that initializes the random number generator with a seed.
         *
         * @param seed The seed for the random number generator. Defaults to 0.
         */
        explicit RandomRealFromRange(unsigned int seed = 0) : m_seed{seed} {
        }

    public:
        virtual ~RandomRealFromRange() {
        }

        /**
         * @brief Pure virtual function to generate a random real number within the given range.
         *
         * This function must be overridden in a derived class to generate a random
         * real number between the specified minimum and maximum values.
         *
         * @param min The minimum value of the range.
         * @param max The maximum value of the range.
         *
         * @return A random real number between min and max (inclusive).
         */
        virtual double generate(double min, double max) = 0;
    };

}
