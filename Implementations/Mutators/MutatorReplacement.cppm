module MutatorReplacement;
import std.compat;

namespace Geneticxx {
    MutatorReplacement::MutatorReplacement(RandomIntFromRange *genInt, RandomRealFromRange *genReal) : m_RandomNumbersGeneratorInt{genInt}, m_RandomNumbersGeneratorReal{genReal}, m_MaxValue{60.0}, m_MinValue{0.0} {
    }

    MutatorReplacement::MutatorReplacement(RandomIntFromRange *genInt, RandomRealFromRange *genReal, double minValue, double maxValue) : m_RandomNumbersGeneratorInt{genInt},
        m_RandomNumbersGeneratorReal{genReal}, m_MaxValue{maxValue}, m_MinValue{minValue}{
    }

    MutatorReplacement::~MutatorReplacement() = default;

    void MutatorReplacement::mutate(Genome *genomeBase) {
        auto genome = dynamic_cast<Genome1D*>(genomeBase);
        int pos = m_RandomNumbersGeneratorInt->generate(0, static_cast<int>(genome->getSize()) - 1);
        genome->setValue(
            pos,
            m_RandomNumbersGeneratorReal->generate( // TODO: types should match genome vector type?
                m_MaxValue, m_MinValue)
        );
    }

    double MutatorReplacement::getMinVal() const {
        return m_MinValue;
    }

    void MutatorReplacement::setMinVal(double minVal) {
        if (minVal > m_MaxValue)
            throw std::invalid_argument("Minimum value must be less than the maximum value. Try setting maximum value first.");

        m_MinValue = minVal;
    }

    double MutatorReplacement::getMaxVal() const {
        return m_MaxValue;
    }

    void MutatorReplacement::setMaxVal(double maxVal) {
        if (maxVal < m_MinValue)
            throw std::invalid_argument("Maximum value must be greater than the minimum value.");

        m_MaxValue = maxVal;
    }

    bool MutatorReplacement::validate(Genome *genome) const {
        // For MutatorReplacement, no special validation requirements
        // This method can be expanded for more complex genomes
        return genome->getSize() > 0; // Example: genome must have at least one element
    }

    MutationSchema *MutatorReplacement::clone() const {
        // Create a unique copy of the mutator
        auto cloneMutator = new MutatorReplacement(m_RandomNumbersGeneratorInt, m_RandomNumbersGeneratorReal);
        cloneMutator->m_MaxValue = m_MaxValue;
        cloneMutator->m_MinValue = m_MinValue;
        return cloneMutator;
    }
}
