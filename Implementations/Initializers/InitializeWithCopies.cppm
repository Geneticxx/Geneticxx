module InitializeWithCopies;

namespace Geneticxx {
    InitializeWithCopies::InitializeWithCopies(int size, Individual *individual) {
        this->size = size;
        this->individual = std::unique_ptr<Individual>(individual);
    }

    InitializeWithCopies::~InitializeWithCopies() {
    }

    void InitializeWithCopies::initialize(std::vector<std::unique_ptr<Population> > *populations) {
        for (auto &pop: *populations) {
            if (size <= 0) return; //TODO throw exception?
            pop->resize(size);

            for (int i = 0; i < size; ++i) {
                pop->setIndividual(i, individual->clone());
            }
        }
    }

    void InitializeWithCopies::setIndividual(Individual *individual) {
        this->individual = std::unique_ptr<Individual>(individual);
    }
}
