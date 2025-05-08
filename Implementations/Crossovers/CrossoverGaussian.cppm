module CrossoverGaussian;

namespace Geneticxx {
    CrossoverGaussian::CrossoverGaussian() {
    }

    CrossoverGaussian::~CrossoverGaussian() {
    }

    std::vector<std::unique_ptr<Genome> > CrossoverGaussian::crossover(Genome *parent1, Genome *parent2) { //TODO actual implementation
        auto child1 = parent1->clone();
        //child1->setGenome();
        std::vector<std::unique_ptr<Genome> > results;
        results.push_back(std::move(child1));
        return std::move(results);
    }
}
