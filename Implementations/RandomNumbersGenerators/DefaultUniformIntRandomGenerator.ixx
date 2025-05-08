export module DefaultUniformIntRandomGenerator;

export import Individual;
import std;
import std.compat;
export import RandomIntFromRange;

namespace Geneticxx {
    /**
     * @class DefaultUniformIntRandomGenerator
     * @brief A random number generator that produces uniform integers within a specified range.
     *
     * This class uses the standard C++ random number generation facilities to produce random integers
     * between a specified minimum and maximum value. It utilizes a uniform integer distribution
     * to ensure each number within the range has an equal chance of being selected.
     */
    export class DefaultUniformIntRandomGenerator : public RandomIntFromRange {
        std::default_random_engine engine{}; ///< The random engine used to generate random numbers.
        std::uniform_int_distribution<> distribution{}; ///< The uniform integer distribution used to define the range.

    public:
        /**
         * @brief Constructor that initializes the random generator with a given seed.
         *
         * The constructor accepts a seed for the random number generator. If no seed is provided, a default
         * seed is generated using `std::random_device`. The random engine and distribution are also initialized.
         *
         * @param seed The seed value used to initialize the random engine (default is `std::random_device{}`).
         */
        explicit DefaultUniformIntRandomGenerator(unsigned int seed = std::random_device{}());

        /**
         * @brief Destructor for proper cleanup of the random generator.
         *
         * This virtual destructor ensures that any resources used by the `DefaultUniformIntRandomGenerator`
         * are properly cleaned up when an object of this type is destroyed. It overrides the base class destructor.
         */
        ~DefaultUniformIntRandomGenerator() override;

        /**
         * @brief Generate a random integer within the specified range.
         *
         * This method generates a random integer between the provided `min` and `max` values using a uniform
         * integer distribution. The distribution ensures that every integer within the range has an equal probability
         * of being selected.
         *
         * @param min The minimum value (inclusive) that can be generated.
         * @param max The maximum value (inclusive) that can be generated.
         * @return A randomly generated integer between `min` and `max`.
         */
        int generate(int min, int max) override;
    };
}
