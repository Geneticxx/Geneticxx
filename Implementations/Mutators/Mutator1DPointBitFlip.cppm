module Mutator1DPointBitFlip;

namespace Geneticxx {
    Mutator1DPointBitFlip::Mutator1DPointBitFlip(RandomIntFromRange *genInt)
        : m_RandomNumbersGeneratorInt{genInt} {

    }


    Mutator1DPointBitFlip::~Mutator1DPointBitFlip() = default;

    void Mutator1DPointBitFlip::mutate(Genome *genome) {
        // flip the bit at a random index
        if (!validate(genome)) throw std::invalid_argument("Invalid genome");
        auto temp = dynamic_cast<Genome1D *>(genome);
        size_t index = m_RandomNumbersGeneratorInt->generate(0, temp->getSize() - 1);
        temp->setValue(index, !std::any_cast<bool>(temp->getValue(index)));

    }

    bool Mutator1DPointBitFlip::validate(Genome *genome) const {
        // For MutatorPointReplacement, no special validation requirements
        // This method can be expanded for more complex genomes
        return genome->getSize() > 0; // Example: genome must have at least one element
    }

    MutationSchema *Mutator1DPointBitFlip::clone() const {
        // Create a unique copy of the mutator
        auto cloneMutator = new Mutator1DPointBitFlip(m_RandomNumbersGeneratorInt);
        return cloneMutator;
    }
}
