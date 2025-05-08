export module DefaultUniformRealRandomGenerator;

export import Individual;
import std;
import std.compat;
export import RandomRealFromRange;

namespace Geneticxx {
    /**
     * @class DefaultUniformRealRandomGenerator
     * @brief A random number generator that produces uniform real numbers within a specified range.
     *
     * This class uses the standard C++ random number generation facilities to produce random real numbers
     * between a specified minimum and maximum value. It utilizes a uniform real distribution to ensure each
     * number within the range has an equal chance of being selected.
     */
    export class DefaultUniformRealRandomGenerator : public RandomRealFromRange {
        std::default_random_engine engine{}; ///< The random engine used to generate random numbers.
        std::uniform_real_distribution<> distribution{}; ///< The uniform real distribution used to define the range.

    public:
        /**
         * @brief Constructor that initializes the random generator with a given seed.
         *
         * The constructor accepts a seed for the random number generator. If no seed is provided, a default
         * seed is generated using `std::random_device`. The random engine and distribution are also initialized.
         *
         * @param seed The seed value used to initialize the random engine (default is `std::random_device{}`).
         */
        explicit DefaultUniformRealRandomGenerator(unsigned int seed = std::random_device{}());

        /**
         * @brief Destructor for proper cleanup of the random generator.
         *
         * This virtual destructor ensures that any resources used by the `DefaultUniformRealRandomGenerator`
         * are properly cleaned up when an object of this type is destroyed. It overrides the base class destructor.
         */
        ~DefaultUniformRealRandomGenerator() override;

        /**
         * @brief Generate a random real number within the specified range.
         *
         * This method generates a random real number between the provided `min` and `max` values using a uniform
         * real distribution. The distribution ensures that every real number within the range has an equal probability
         * of being selected.
         *
         * @param min The minimum value (inclusive) that can be generated.
         * @param max The maximum value (inclusive) that can be generated.
         * @return A randomly generated real number between `min` and `max`.
         */
        double generate(double min, double max) override;
    };
}
