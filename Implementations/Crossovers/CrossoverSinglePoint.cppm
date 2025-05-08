module CrossoverSinglePoint;

namespace Geneticxx {
    CrossoverSinglePoint::CrossoverSinglePoint(RandomIntFromRange *genInt) : m_RandomNumbersGeneratorInt{genInt} {}

    CrossoverSinglePoint::~CrossoverSinglePoint() = default;

    std::vector<std::unique_ptr<Genome> > CrossoverSinglePoint::crossover(Genome *parent1, Genome *parent2) {
        auto child1 = parent1->clone();
        auto child2 = parent2->clone();

        // Determine the shorter genome size to avoid out-of-bounds access
        int shorter = parent1->getSize() > parent2->getSize() ? parent2->getSize() : parent1->getSize();

        // Generate a random crossover point
        int cut_point = m_RandomNumbersGeneratorInt->generate(0, shorter - 1);

        auto child1ptr = dynamic_cast<Genome1D*> (child1.get()); //TODO questionable casts
        auto child2ptr = dynamic_cast<Genome1D*> (child2.get());
        auto parent1ptr = dynamic_cast<Genome1D*> (parent1);
        auto parent2ptr = dynamic_cast<Genome1D*> (parent2);

        // Perform the crossover at the selected point
        for (int i = 0; i < cut_point; i++) {
            child1ptr->setValue(i, parent2ptr->getValue(i));
            child2ptr->setValue(i, parent1ptr->getValue(i));
        }

        // Return the two children genomes
        std::vector<std::unique_ptr<Genome>> results;
        results.push_back(std::move(child1));
        results.push_back(std::move(child2));

        return std::move(results);
    }
}
