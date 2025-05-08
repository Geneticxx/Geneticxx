export module RandomIntFromRange;

export import Individual;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class RandomIntFromRange
     * @brief A base class for generating random integers within a specified range.
     *
     * This class defines the basic structure for random number generation. Derived
     * classes should implement the `generate` method to produce random integers
     * within a given range.
     */
    export class RandomIntFromRange {
    protected:
        unsigned int m_seed; ///< The seed used for random number generation

        /**
         * @brief Constructor that initializes the random number generator with a seed.
         *
         * @param seed The seed for the random number generator.
         */
        explicit RandomIntFromRange(unsigned int seed) : m_seed{seed} {
        }

    public:
        virtual ~RandomIntFromRange() {
        }

        /**
         * @brief Pure virtual function to generate a random integer within the given range.
         *
         * This function must be overridden in a derived class to generate a random
         * integer between the specified minimum and maximum values.
         *
         * @param min The minimum value of the range.
         * @param max The maximum value of the range.
         *
         * @return A random integer between min and max (inclusive).
         */
        virtual int generate(int min, int max) = 0;
    };

}
