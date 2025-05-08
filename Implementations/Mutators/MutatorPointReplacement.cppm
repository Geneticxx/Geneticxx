module MutatorPointReplacement;
import std.compat;

namespace Geneticxx {
    MutatorPointReplacement::MutatorPointReplacement(RandomIntFromRange *genInt, RandomRealFromRange *genReal)
        : m_RandomNumbersGeneratorInt{genInt}, m_RandomNumbersGeneratorReal{genReal}, m_MaxValue{60.0}, m_MinValue{0.0}, m_index(-1) {
        // Default rate is 1%
    }

    MutatorPointReplacement::MutatorPointReplacement(RandomIntFromRange *genInt, RandomRealFromRange *genReal, double minValue, double maxValue) : m_RandomNumbersGeneratorInt{genInt},
        m_RandomNumbersGeneratorReal{genReal}, m_MaxValue{maxValue}, m_MinValue{minValue}, m_index{-1} {
    }

    // MutatorPointReplacement::MutatorPointReplacement(double minValue, double maxValue, int index) : m_MutationRate{0.01}, m_Distribution{Distributions::UniformReal}, m_MaxValue{minValue}, m_MinValue{maxValue},
    //                                                                                                 m_index{index} {
    // }


    MutatorPointReplacement::~MutatorPointReplacement() = default;

    void MutatorPointReplacement::mutate(Genome *genome) {
        // Replace the value with a new random value
        auto temp = dynamic_cast<Genome1D *>(genome);
        if (m_index > -1 && m_index < genome->getSize()) {
            temp->setValue(
                m_index,
                m_RandomNumbersGeneratorReal->generate( // TODO: types should match genome vector type?
                    m_MinValue,
                    m_MaxValue)
            );
        } else {
            temp->setValue(
                m_RandomNumbersGeneratorInt->generate(0, genome->getSize() - 1),
                m_RandomNumbersGeneratorReal->generate( // TODO: types should match genome vector type?
                    m_MinValue,
                    m_MaxValue)
            );
        }
    }

    double MutatorPointReplacement::getMinVal() const {
        return m_MinValue;
    }

    void MutatorPointReplacement::setMinVal(double minVal) {
        if (minVal > m_MaxValue)
            throw std::invalid_argument("Minimum value must be less than the maximum value. Try setting maximum value first.");

        m_MinValue = minVal;
    }

    double MutatorPointReplacement::getMaxVal() const {
        return m_MaxValue;
    }

    void MutatorPointReplacement::setMaxVal(double maxVal) {
        if (maxVal < m_MinValue)
            throw std::invalid_argument("Maximum value must be greater than the minimum value.");

        m_MaxValue = maxVal;
    }

    int MutatorPointReplacement::getIndex() const {
        return m_index;
    }

    void MutatorPointReplacement::setIndex(int index) {
        m_index = index;
    }

    bool MutatorPointReplacement::validate(Genome *genome) const {
        // For MutatorPointReplacement, no special validation requirements
        // This method can be expanded for more complex genomes
        return genome->getSize() > 0; // Example: genome must have at least one element
    }

    MutationSchema *MutatorPointReplacement::clone() const {
        // Create a unique copy of the mutator
        auto cloneMutator = new MutatorPointReplacement(m_RandomNumbersGeneratorInt, m_RandomNumbersGeneratorReal);
        cloneMutator->m_MaxValue = m_MaxValue;
        cloneMutator->m_MinValue = m_MinValue;
        return cloneMutator;
    }
}
