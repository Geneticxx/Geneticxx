module DefaultUniformIntRandomGenerator;

namespace Geneticxx {
    DefaultUniformIntRandomGenerator::DefaultUniformIntRandomGenerator(unsigned int seed) : RandomIntFromRange{seed}, engine{seed}, distribution(0, 1) {
    }

    DefaultUniformIntRandomGenerator::~DefaultUniformIntRandomGenerator() {
    };

    int DefaultUniformIntRandomGenerator::generate(int min, int max) {
        return distribution(engine, std::uniform_int_distribution<>::param_type(min, max)); // TODO: check if it is not creating excessive overhead
    }
}
