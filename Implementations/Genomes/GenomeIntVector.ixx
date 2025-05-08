export module GenomeVector;

export import Genome1D;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class GenomeVector
     * @brief Represents a genome stored as a vector of integers.
     *
     * This class provides functionalities to create, manipulate, and compare genomes represented by integer vectors.
     * It includes methods for cloning, copying, moving, and calculating the similarity between genomes.
     */
    export template <typename T>
    class GenomeVector : public Genome1D {
    private:
        /**
         * @brief The data representing the genome, stored as a vector of integers.
         *
         * Each integer in the vector represents a component of the genome.
         */
        std::vector<T> data{};

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an empty genome (empty integer vector).
         */
        GenomeVector()
        {

        }

        /**
         * @brief Constructor with specified size.
         *
         * Initializes the genome with a specified size. The vector will be filled with default values.
         *
         * @param size The number of integers in the genome.
         */
        GenomeVector(size_t size)
        {
            data.resize(size);
        }

        /**
         * @brief Constructor with specified data.
         *
         * Initializes the genome using a provided vector of integers.
         *
         * @param data A vector of integers representing the genome data.
         */
        GenomeVector(std::vector<T> data)
        {
            //size_t i = data.size();
            //i++;
            //this->data.resize(data.size());
            this->data = data;
        }

        /**
         * @brief Copy constructor.
         *
         * Initializes a new genome by copying the data from another genome.
         *
         * @param other The genome to copy.
         */
        GenomeVector(const GenomeVector& other) : data{other.data}
        {
            
        }

        /**
         * @brief Move constructor.
         *
         * Initializes a new genome by transferring ownership of the data from another genome.
         *
         * @param other The genome to move.
         */
        GenomeVector(GenomeVector&& other) noexcept : data{std::move(other.data)}
        {
            
        }

        /**
         * @brief Copy assignment operator.
         *
         * Assigns the data of another genome to the current genome.
         *
         * @param other The genome to copy.
         * @return Reference to the current genome.
         */
        GenomeVector& operator=(const GenomeVector& other)
        {
            if (this != &other) {
                data = other.data;
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         *
         * Transfers ownership of the data from another genome to the current genome.
         *
         * @param other The genome to move.
         * @return Reference to the current genome.
         */
        GenomeVector& operator=(GenomeVector&& other) noexcept
        {
            if (this != &other) {
                data = std::move(other.data);
            }
            return *this;
        }

        /**
         * @brief Destructor.
         *
         * Destroys the genome and frees the associated resources.
         */
        ~GenomeVector() override = default;

        /**
         * @brief Creates a new genome.
         *
         * @return Pointer to the newly created genome.
         */
        std::unique_ptr<Genome> createNew() const override
        {
            return std::make_unique<GenomeVector>();
        }

        /**
         * @brief Clones the genome (deep copy).
         *
         * This method creates a new genome that is a copy of the current genome.
         *
         * @return A new cloned genome.
         */
        std::unique_ptr<Genome> clone() const override
        {
            auto clone = new GenomeVector();
            clone->data = this->data;
            return std::unique_ptr<GenomeVector>(clone);
        }

        /**
         * @brief Compares two genomes.
         *
         * This method calculates a similarity metric (distance) between the current genome and another.
         *
         * @param other The genome to compare with.
         * @return A value representing the similarity between the two genomes, where 0 means identical.
         */
        double distance(Genome *otherBase) const override 
        {
            /* TODO this is commented, as this is effectively a specialization for numeric types
            auto other = dynamic_cast<Genome1D *>(otherBase);
            double distance = 0;
            if (this->data.size() == other->getSize()) {
                for (size_t i = 0; i < this->data.size(); i++) {
                    if (std::any_cast<T>(other->getValue(i)) > std::any_cast<T>(this->getValue(i))) {
                        distance += (std::any_cast<T>(other->getValue(i)) - std::any_cast<T>(this->getValue(i))) / std::any_cast<T>(other->getValue(i));
                    } else {
                        distance += (std::any_cast<T>(this->getValue(i)) - std::any_cast<T>(other->getValue(i))) / std::any_cast<T>(this->getValue(i));
                    }
                }
                distance /= this->data.size();
            } else {
                distance = 1;
            }
            return distance;*/
            return this == otherBase;
        }

        /**
         * @brief Converts the genome to a phenome for fitness evaluation.
         *
         * This method retrieves the value at a specific position in the genome.
         *
         * @param position The position in the genome to retrieve.
         * @return The value at the given position, wrapped in std::any.
         */
        std::any getValue(size_t position) const override
        {
            return this->data[position];
        }

        /**
         * @brief Sets the value at a specific position in the genome.
         *
         * This method modifies the value of the genome at a given position.
         *
         * @param position The position in the genome to modify.
         * @param value The new value to set at the given position.
         */
        void setValue(size_t position, std::any value) override
        {
            this->data.at(position) = std::any_cast<T>(value);
        }

        /**
         * @brief Returns the size of the genome (number of elements).
         *
         * @return The number of elements in the genome.
         */
        size_t getSize() const override
        {
            return this->data.size();
        }

        /**
         * @brief Compares two genomes for equality.
         *
         * This method checks if two genomes are identical based on their integer vector representation.
         *
         * @param other The genome to compare with.
         * @return True if the genomes are identical, false otherwise.
         */
        bool operator==(Genome *otherBase) const override
        {
            auto other = dynamic_cast<Genome1D *>(otherBase);
            if (this->data.size() == other->getSize()) {
                for (size_t i = 0; i < this->data.size(); i++) {
                    if (std::any_cast<T>(other->getValue(i)) != std::any_cast<T>(this->getValue(i))) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        
        }
    };
}
