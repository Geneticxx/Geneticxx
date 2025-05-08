export module PhenomeIntVector;

export import Phenome1D;
import std;

namespace Geneticxx {
    /**
     * @class PhenomeIntVector
     * @brief A class representing a phenome as a vector of integer values.
     *
     * This class models a phenome where the data is stored as a vector (vector) of integers. It provides methods for
     * updating, cloning, and managing the phenome's data, including operations like accessing and modifying specific values
     * in the vector.
     */
    export class PhenomeIntVector : public Phenome1D {
    private:
        /**
         * @brief A vector of integer values representing the phenome's data.
         *
         * This vector holds the integer values that define the phenome.
         */
        std::vector<int> m_data;

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an empty phenome with no data.
         */
        PhenomeIntVector();

        /**
         * @brief Constructor to initialize the vector with a specific size.
         *
         * This constructor creates a phenome with the specified size. The data vector will be filled with default values (0).
         *
         * @param size The size of the phenome's data vector.
         */
        PhenomeIntVector(int size);

        /**
         * @brief Constructor to initialize the vector with a specific size and predefined data.
         *
         * This constructor creates a phenome with the specified size and initializes the data vector with the given values.
         *
         * @param size The size of the phenome's data vector.
         * @param data A vector of integers representing the initial data for the phenome.
         */
        PhenomeIntVector(int size, std::vector<int> data);

        /**
         * @brief Copy constructor.
         *
         * This constructor creates a new `PhenomeIntVector` by copying the data from another `PhenomeIntVector`.
         *
         * @param other The `PhenomeIntVector` to copy data from.
         */
        PhenomeIntVector(const PhenomeIntVector &other);

        /**
         * @brief Move constructor.
         *
         * This constructor creates a new `PhenomeIntVector` by moving the data from another `PhenomeIntVector`.
         *
         * @param other The `PhenomeIntVector` to move data from.
         */
        PhenomeIntVector(PhenomeIntVector &&other);

        /**
         * @brief Copy assignment operator.
         *
         * This operator assigns data from another `PhenomeIntVector` to the current instance.
         *
         * @param other The `PhenomeIntVector` to copy data from.
         * @return A reference to the current `PhenomeIntVector` object.
         */
        PhenomeIntVector& operator=(const PhenomeIntVector &other);

        /**
         * @brief Move assignment operator.
         *
         * This operator moves data from another `PhenomeIntVector` to the current instance.
         *
         * @param other The `PhenomeIntVector` to move data from.
         * @return A reference to the current `PhenomeIntVector` object.
         */
        PhenomeIntVector& operator=(PhenomeIntVector &&other) noexcept;

        /**
         * @brief Destructor.
         *
         * Cleans up the resources used by the `PhenomeIntVector` object.
         */
        ~PhenomeIntVector() override;

        /**
         * @brief Updates the phenome using data from a genome.
         *
         * This method updates the phenome's data vector by extracting values from the provided genome. The size of the genome
         * should match the size of the phenome's data vector.
         *
         * @param genome A pointer to the genome object that provides the data to update the phenome.
         */
        void updatePhenome(const Genome* genome) override;

        /**
         * @brief Creates a new instance of `PhenomeIntVector`.
         *
         * This method creates and returns a new `PhenomeIntVector` object, typically used for creating new phenomes.
         *
         * @return A pointer to the newly created `PhenomeIntVector` object.
         */
        Phenome* createNew() const override;

        /**
         * @brief Clones the current phenome.
         *
         * This method creates a new `PhenomeIntVector` that is a copy of the current one, including the same data.
         *
         * @return A pointer to the cloned `PhenomeIntVector` object.
         */
        Phenome* clone() const override;

        /**
         * @brief Retrieves the value at a specific position in the phenome's data vector.
         *
         * This method returns the value stored at the given position in the phenome's data vector.
         *
         * @param position The index of the value to retrieve.
         * @return The value at the specified position, wrapped in a `std::any` object.
         */
        std::any getValue(size_t position) const override;

        /**
         * @brief Sets the value at a specific position in the phenome's data vector.
         *
         * This method updates the value stored at the given position in the phenome's data vector.
         *
         * @param position The index of the value to set.
         * @param value The value to set at the specified position, wrapped in a `std::any` object.
         */
        void setValue(size_t position, std::any value) override;

        /**
         * @brief Retrieves the size of the phenome's data vector.
         *
         * This method returns the number of elements in the phenome's data vector.
         *
         * @return The size of the phenome's data vector.
         */
        int getSize() const override;

        /**
         * @brief Compares the current phenome to another phenome for equality.
         *
         * This method checks if the current phenome is equal to another phenome. This comparison is not implemented yet.
         *
         * @param other The phenome to compare with.
         * @return `true` if the phenomes are equal, `false` otherwise. (Currently returns `false` as it is not implemented.)
         */
        bool operator==(const Phenome *other) const override;
    };
}
