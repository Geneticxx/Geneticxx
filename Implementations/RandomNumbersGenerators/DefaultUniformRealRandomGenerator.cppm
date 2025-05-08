module DefaultUniformRealRandomGenerator;

namespace Geneticxx {
    DefaultUniformRealRandomGenerator::DefaultUniformRealRandomGenerator(unsigned int seed) : RandomRealFromRange(seed), engine(seed), distribution(0, 1) {
    }

    DefaultUniformRealRandomGenerator::~DefaultUniformRealRandomGenerator() {
    };

    double DefaultUniformRealRandomGenerator::generate(double min, double max) {
        return distribution(engine, std::uniform_real_distribution<>::param_type(min, max)); // TODO: check if it is not creating excessive overhead
    }
}
