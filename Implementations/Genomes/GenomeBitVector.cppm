module GenomeBitVector;

namespace Geneticxx {

    GenomeBitVector::GenomeBitVector() {
    }

    GenomeBitVector::GenomeBitVector(const GenomeBitVector &other) : m_Bits{other.m_Bits} {
    }

    GenomeBitVector::GenomeBitVector(GenomeBitVector &&other) noexcept
        : m_Bits{std::move(other.m_Bits)} {
    }

    GenomeBitVector& GenomeBitVector::operator=(const GenomeBitVector &other) {
        if (this != &other) {
            m_Bits = other.m_Bits;
        }
        return *this;
    }

    GenomeBitVector& GenomeBitVector::operator=(GenomeBitVector &&other) noexcept {
        if (this != &other) {
            m_Bits = std::move(other.m_Bits);
        }
        return *this;
    }

    GenomeBitVector::~GenomeBitVector() = default;

    std::vector<bool> GenomeBitVector::toGray(const std::vector<bool> &binary) {
        std::vector<bool> gray(binary.size());
        if (!binary.empty()) {
            gray[0] = binary[0];
            for (size_t i = 1; i < binary.size(); ++i)
                gray[i] = binary[i - 1] ^ binary[i]; // operator XOR
        }
        return gray;
    }

    std::vector<bool> GenomeBitVector::fromGray(const std::vector<bool> &gray) {
        std::vector<bool> binary(gray.size());
        if (!gray.empty()) {
            binary[0] = gray[0];
            for (size_t i = 1; i < gray.size(); ++i)
                binary[i] = binary[i - 1] ^ gray[i]; // operator XOR
        }
        return binary;
    }

    std::unique_ptr<Genome> GenomeBitVector::createNew() const {
        return std::make_unique<GenomeBitVector>();
    }

    std::unique_ptr<Genome> GenomeBitVector::clone() const {
        auto clone = new GenomeBitVector();
        clone->m_Bits = this->m_Bits;
        return std::unique_ptr<GenomeBitVector>(clone);
    }

    double GenomeBitVector::distance(Genome *otherBase) const {
        auto other = dynamic_cast<Genome1D *>(otherBase); //TODO throw on incorrect types
        double bitStringDistance = 0;
        if (this->m_Bits.size() == other->getSize()) {
            for (size_t i = 0; i < this->m_Bits.size(); i++) {
                if (std::any_cast<bool>(other->getValue(i)) > std::any_cast<bool>(this->getValue(i))) {
                    bitStringDistance += (std::any_cast<bool>(other->getValue(i)) - std::any_cast<
                        bool>(this->getValue(i))) / std::any_cast<bool>(other->getValue(i));
                }
                else {
                    bitStringDistance += (std::any_cast<bool>(this->getValue(i)) - std::any_cast<
                        bool>(other->getValue(i))) / std::any_cast<bool>(this->getValue(i));
                }
            }
            bitStringDistance /= this->m_Bits.size();
        }
        else {
            bitStringDistance = 1;
        }
        return bitStringDistance;
    }

    std::any GenomeBitVector::getValue(size_t position) const {
        if (position >= this->m_Bits.size()) {
            return false;
        }
        return this->m_Bits[position];
    }

    void GenomeBitVector::setValue(size_t position, std::any value) {
        m_Bits[position] = std::any_cast<bool>(value);
    }

    size_t GenomeBitVector::getSize() const {
        return m_Bits.size();
    }

    bool GenomeBitVector::operator==(Genome *otherBase) const {
        auto other = dynamic_cast<Genome1D *>(otherBase);
        if (this->m_Bits.size() == other->getSize()) {
            for (size_t i = 0; i < this->m_Bits.size(); i++) {
                if (std::any_cast<bool>(other->getValue(i)) != std::any_cast<bool>(this->getValue(i))) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    void GenomeBitVector::setGrayRepresentation(const std::vector<bool> &grayBits) {
        m_Bits = fromGray(grayBits);
    }

    std::vector<bool> GenomeBitVector::getGrayRepresentation() const {
        return toGray(m_Bits);
    }
}
