module CrossoverUniform;

namespace Geneticxx {
    CrossoverUniform::CrossoverUniform(RandomIntFromRange *genInt) : m_RandomNumbersGeneratorInt{genInt} {
    }

    CrossoverUniform::~CrossoverUniform() = default;

    std::vector<std::unique_ptr<Genome> > CrossoverUniform::crossover(Genome *parent1, Genome *parent2) {
        // Ensure that both parent genomes are of the same size
        if (parent1->getSize() != parent2->getSize()) {
            throw std::invalid_argument("Genomes must have the same size");
        }

        auto child1 = parent1->clone();
        auto child2 = parent2->clone();

        auto child1ptr = dynamic_cast<Genome1D*> (child1.get()); //TODO questionable casts
        auto child2ptr = dynamic_cast<Genome1D*> (child2.get());
        auto parent1ptr = dynamic_cast<Genome1D*> (parent1);
        auto parent2ptr = dynamic_cast<Genome1D*> (parent2);

        // Perform the uniform crossover for each gene position
        for (int i = 0; i < parent1->getSize(); i++) {
            if (m_RandomNumbersGeneratorInt->generate(0, 1) == 0) {
                // No need to change as cloned children already have these values
            } else {
                child1ptr->setValue(i, parent2ptr->getValue(i));
                child2ptr->setValue(i, parent1ptr->getValue(i));
            }
        }

        // Return the two children genomes
        std::vector<std::unique_ptr<Genome> > results;
        results.push_back(std::move(child1));
        results.push_back(std::move(child2));

        return std::move(results);
    }
}
