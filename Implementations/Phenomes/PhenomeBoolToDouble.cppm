module PhenomeBoolToDouble;

namespace Geneticxx {
    PhenomeBoolToDouble::PhenomeBoolToDouble() {
    }

    PhenomeBoolToDouble::PhenomeBoolToDouble(int size, unsigned int exponentSize, unsigned int mantissaSize) {
        m_exponentSize = exponentSize;
        m_mantissaSize = mantissaSize;
        m_data.resize(size);
        for (int i = 0; i < size; i++) {
            m_data[i] = 0;
        }
    }

    PhenomeBoolToDouble::PhenomeBoolToDouble(std::vector<double> m_data, unsigned int exponentSize, unsigned int mantissaSize) {
        m_exponentSize = exponentSize;
        m_mantissaSize = mantissaSize;
        this->m_data = m_data;
    }

    PhenomeBoolToDouble::PhenomeBoolToDouble(const PhenomeBoolToDouble &other) : m_data{other.m_data} {
    }

    PhenomeBoolToDouble::PhenomeBoolToDouble(PhenomeBoolToDouble &&other) : m_data{std::move(other.m_data)} {
    }

    PhenomeBoolToDouble &PhenomeBoolToDouble::operator=(const PhenomeBoolToDouble &other) {
        if (this != &other) {
            m_data = other.m_data;
        }
        return *this;
    }

    PhenomeBoolToDouble &PhenomeBoolToDouble::operator=(PhenomeBoolToDouble &&other) noexcept {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    PhenomeBoolToDouble::~PhenomeBoolToDouble() {
    }

    void PhenomeBoolToDouble::updatePhenome(const Genome *genomeBase) {
        auto genome = dynamic_cast<const Genome1D*>(genomeBase); //TODO check if it's the correct type
        // if (this->m_data.size() != genome->getSize()) {
        //     return;
        // }
        if (m_exponentSize == 0 || m_mantissaSize == 0 ) {
            throw std::invalid_argument("Neither m_exponentSize or m_mantissaSize can be 0.");
        }

        if (genome->getValue(0).type() == typeid(bool)) { // Check if the genome values are booleans
            int countDataIndex = 0;
            double value;
            unsigned long long int exponentValue;
            double mantissaValue;

            // Iterate through the genome in blocks of (m_exponentSize + m_mantissaSize) bits
            for (int i = 0; i < genome->getSize(); i += m_mantissaSize + m_exponentSize) {
                // Reset values for this group
                exponentValue = 0;
                mantissaValue = 0.0;

                // Process exponent bits (most significant bits)
                for (int j = 0; j < m_exponentSize; ++j) {
                    bool bit = std::any_cast<bool>(genome->getValue(i + j));
                    exponentValue = (exponentValue << 1) | (bit ? 1ULL : 0ULL);
                }

                // Process mantissa bits as fractional part.
                // Each bit j corresponds to a fractional value of 1/2^(j+1)
                double fraction = 0.5;
                for (int j = m_exponentSize; j < m_exponentSize + m_mantissaSize; ++j) {
                    bool bit = std::any_cast<bool>(genome->getValue(i + j));
                    if (bit) {
                        mantissaValue += fraction;
                    }
                    fraction *= 0.5;
                }

                // Combine the computed exponent and mantissa values.
                value = static_cast<double>(exponentValue) + mantissaValue;
                m_data[countDataIndex] = value;
                ++countDataIndex;
            }
        }
    }

    Phenome *PhenomeBoolToDouble::createNew() const {
        return new PhenomeBoolToDouble();
    }

    Phenome *PhenomeBoolToDouble::clone() const {
        auto clone = new PhenomeBoolToDouble();
        clone->m_data = this->m_data;
        return clone;
    }

    std::any PhenomeBoolToDouble::getValue(size_t position) const {
        return this->m_data[position];
    }

    void PhenomeBoolToDouble::setValue(size_t position, std::any value) {
        try {
            this->m_data[position] = std::any_cast<double>(value);
        }
        catch (const std::bad_any_cast &ex) {
            std::cout << "PhenomeBoolToDouble::setValue " << ex.what() << std::endl;
            throw;
        }
    }

    int PhenomeBoolToDouble::getSize() const {
        return m_data.size();
    }

    bool PhenomeBoolToDouble::operator==(const Phenome *other) const {
        return false; //TODO implementation
    }
}
