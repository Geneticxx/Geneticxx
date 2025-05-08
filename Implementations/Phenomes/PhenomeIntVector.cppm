module PhenomeIntVector;

namespace Geneticxx {
    PhenomeIntVector::PhenomeIntVector() {
    }

    PhenomeIntVector::PhenomeIntVector(int size) {
        m_data.resize(size);
        for (int i = 0; i < size; i++) {
            m_data[i] = 0;
        }
    }

    PhenomeIntVector::PhenomeIntVector(int size, std::vector<int> m_data) {
        this->m_data = m_data;
    }

    PhenomeIntVector::PhenomeIntVector(const PhenomeIntVector &other) : m_data{other.m_data} {
    }

    PhenomeIntVector::PhenomeIntVector(PhenomeIntVector &&other) : m_data{std::move(other.m_data)} {
    }

    PhenomeIntVector &PhenomeIntVector::operator=(const PhenomeIntVector &other) {
        if (this != &other) {
            m_data = other.m_data;
        }
        return *this;
    }

    PhenomeIntVector &PhenomeIntVector::operator=(PhenomeIntVector &&other) noexcept {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    PhenomeIntVector::~PhenomeIntVector() {
    }

    void PhenomeIntVector::updatePhenome(const Genome *genomeBase) {
        auto genome = dynamic_cast<const Genome1D*>(genomeBase); //TODO check if it's the correct type
        if (this->m_data.size() != genome->getSize()) {
            return;
        }

        if (genome->getValue(0).type() == typeid(int)) //TODO change this
            for (int i = 0; i < genome->getSize(); i++) {
                m_data[i] = std::any_cast<int>(genome->getValue(i));
            }
    }

    Phenome *PhenomeIntVector::createNew() const {
        return new PhenomeIntVector();
    }

    Phenome *PhenomeIntVector::clone() const {
        auto clone = new PhenomeIntVector();
        clone->m_data = this->m_data;
        return clone;
    }

    std::any PhenomeIntVector::getValue(size_t position) const {
        return this->m_data[position];
    }

    void PhenomeIntVector::setValue(size_t position, std::any value) {
        try {
            this->m_data[position] = std::any_cast<int>(value);
        }
        catch (const std::bad_any_cast &ex) {
            std::cout << "PhenomeIntVector::setValue " << ex.what() << std::endl;
            throw;
        }
    }

    int PhenomeIntVector::getSize() const {
        return this->m_data.size();
    }

    bool PhenomeIntVector::operator==(const Phenome *other) const {
        return false; //TODO implementation
    }
}
