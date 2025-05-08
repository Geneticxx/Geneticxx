module MutatorRandomSwap;

namespace Geneticxx {
    MutatorRandomSwap::MutatorRandomSwap(RandomIntFromRange *genInt) : m_RandomNumbersGeneratorInt{genInt} {
    }

    MutatorRandomSwap::~MutatorRandomSwap() = default;

    void MutatorRandomSwap::mutate(Genome *genomeBase) {
        // Replace the value with a new random value
        auto genome = dynamic_cast<Genome1D*>(genomeBase);
        if (validate(genome))
        {
            int target1 = m_RandomNumbersGeneratorInt->generate(0, static_cast<int>(genome->getSize()) - 1);
            int target2 = m_RandomNumbersGeneratorInt->generate(0, static_cast<int>(genome->getSize()) - 1);
            while (target1 == target2) {
                // ensure we're not swapping the same index
                target2 = m_RandomNumbersGeneratorInt->generate(0, static_cast<int>(genome->getSize()) - 1);
            }
            auto tempVal = genome->getValue(target1); //TODO if get value doesn't copy this can be replaced with std swap
            genome->setValue(target1, genome->getValue(target2));
            genome->setValue(target2, tempVal);
            return;
        }
        //TODO throw error or not? maybe it should be thrown in validate function?
    }

    bool MutatorRandomSwap::validate(Genome *genome) const {
        // This method can be expanded for more complex genomes
        return genome->getSize() > 1; // Example: genome must have at least two elements
    }

    MutationSchema *MutatorRandomSwap::clone() const {
        auto temp = new MutatorRandomSwap(m_RandomNumbersGeneratorInt);
        temp->m_RandomNumbersGeneratorInt = this->m_RandomNumbersGeneratorInt;
        return temp;
    }
}
