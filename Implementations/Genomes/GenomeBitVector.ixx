export module GenomeBitVector;

import std;
import std.compat;
export import Genome1D;

//TODO reimplement this as a template specialization of genomeVector
namespace Geneticxx {
    /**
     * @class GenomeBitVector
     * @brief Represents a genome as a binary vector of bits.
     *
     * This class provides functionalities to create, manipulate, and compare genome bit vectors.
     * It also includes methods for cloning, copying, moving, and calculating the similarity between genomes.
     */
    export class GenomeBitVector : public Genome1D {
    private:
        /**
         * @brief Stores the binary representation of the genome.
         *
         * A vector of booleans where each element represents a bit (true = 1, false = 0) of the genome.
         */
        std::vector<bool> m_Bits{};

        /**
         * @brief Converts a binary sequence to its Gray code representation.
         * @param binary The binary sequence to convert.
         * @return The Gray code representation of the binary sequence.
         */
        static std::vector<bool> toGray(const std::vector<bool> &binary);

        /**
         * @brief Converts a Gray code sequence back to binary.
         * @param gray The Gray code sequence to convert.
         * @return The binary representation of the Gray code sequence.
         */
        static std::vector<bool> fromGray(const std::vector<bool> &gray);

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an empty genome bit vector.
         */
        GenomeBitVector();

        /**
         * @brief Copy constructor.
         *
         * @param other The genome to copy.
         *
         * Initializes the genome bit vector as a copy of the provided genome.
         */
        GenomeBitVector(const GenomeBitVector &other);

        /**
         * @brief Move constructor.
         *
         * @param other The genome to move.
         *
         * Initializes the genome bit vector by taking ownership of the resources from the provided genome.
         */
        GenomeBitVector(GenomeBitVector &&other) noexcept;

        /**
         * @brief Copy assignment operator.
         *
         * @param other The genome to copy.
         * @return Reference to the copied genome bit vector.
         */
        GenomeBitVector& operator=(const GenomeBitVector &other);

        /**
         * @brief Move assignment operator.
         *
         * @param other The genome to move.
         * @return Reference to the moved genome bit vector.
         */
        GenomeBitVector& operator=(GenomeBitVector &&other) noexcept;

        /**
         * @brief Destructor.
         *
         * Destroys the genome bit vector.
         */
        ~GenomeBitVector() override;

        /**
         * @brief Creates a new genome.
         *
         * @return Pointer to the newly created genome bit vector.
         */
        std::unique_ptr<Genome> createNew() const override;

        /**
         * @brief Clones the genome (deep copy).
         *
         * This method is useful during crossover operations.
         *
         * @return A new cloned genome bit vector.
         */
        std::unique_ptr<Genome> clone() const override;

        /**
         * @brief Compares two genomes.
         *
         * Returns a similarity metric (distance) between the current genome and another.
         * The similarity is based on the number of differing bits between the two genomes.
         *
         * @param other The genome to compare with.
         * @return A value representing the similarity between the two genomes, where 0 means identical.
         */
        double distance(Genome *otherBase) const override;

        /**
         * @brief Converts the genome to a phenome for fitness evaluation.
         *
         * This method is used to retrieve the value (phenotypic representation) at a specific position of the genome.
         *
         * @param position The position in the genome to retrieve.
         * @return The value at the given position, wrapped in std::any.
         */
        std::any getValue(size_t position) const override;

        /**
         * @brief Sets the value at a specific position in the genome.
         *
         * This method allows for modifying the value (bit) at the given position.
         *
         * @param position The position in the genome to modify.
         * @param value The new value to set at the given position.
         */
        void setValue(size_t position, std::any value) override;

        /**
         * @brief Returns the size of the genome (number of bits).
         *
         * @return The number of bits in the genome.
         */
        size_t getSize() const override;

        /**
         * @brief Compares two genomes for equality.
         *
         * This method checks if two genomes are identical based on their binary representation.
         *
         * @param other The genome to compare with.
         * @return True if the genomes are identical, false otherwise.
         */
        bool operator==(Genome *otherBase) const override;

        /**
        * @brief Sets the Gray code representation of the genome.
        * @param grayBits The Gray code bits to set.
        */
        void setGrayRepresentation(const std::vector<bool>& grayBits);

        /**
         * @brief Retrieves the Gray code representation of the genome.
         * @return The genome encoded in Gray code.
         */
        std::vector<bool> getGrayRepresentation() const;
    };
}
