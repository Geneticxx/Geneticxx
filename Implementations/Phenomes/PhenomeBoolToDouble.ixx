export module PhenomeBoolToDouble;

export import Phenome1D;
import std;

namespace Geneticxx {
    /**
     * @class PhenomeBoolToDouble
     * @brief A class representing a phenome as a vector of double values.
     *
     * This class models a phenome where the data is stored as a vector (vector) of doubles. It provides methods for
     * updating, cloning, and managing the phenome's data, including operations like accessing and modifying specific values
     * in the vector.
     */
    export class PhenomeBoolToDouble : public Phenome1D {
    private:
        /**
         * @brief A vector of double values representing the phenome's data.
         *
         * This vector holds the double values that define the phenome.
         */
        std::vector<double> m_data;
        unsigned int m_exponentSize;
        unsigned int m_mantissaSize;

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an empty phenome with no data.
         */
        PhenomeBoolToDouble();

        /**
     * @brief Constructor to initialize the phenome with a specific size.
     *
     * This constructor creates a phenome with the given size. The data vector will be initialized with default values (0).
     *
     * @param size The number of elements in the phenome's data vector.
     * @param exponentSize The number of bits allocated for the exponent in floating-point representation.
     * @param mantissaSize The number of bits allocated for the mantissa in floating-point representation.
     */
        PhenomeBoolToDouble(int size, unsigned int exponentSize = 12, unsigned int mantissaSize = 20);

        /**
         * @brief Constructor to initialize the phenome with predefined data.
         *
         * This constructor creates a phenome and initializes the data vector with the provided values.
         *
         * @param data A vector of doubles representing the initial values for the phenome.
         * @param exponentSize The number of bits allocated for the exponent in floating-point representation.
         * @param mantissaSize The number of bits allocated for the mantissa in floating-point representation.
         */
        PhenomeBoolToDouble(std::vector<double> data, unsigned int exponentSize = 12, unsigned int mantissaSize = 20);


        /**
         * @brief Copy constructor.
         *
         * This constructor creates a new `PhenomeBoolToDouble` by copying the data from another `PhenomeBoolToDouble`.
         *
         * @param other The `PhenomeBoolToDouble` to copy data from.
         */
        PhenomeBoolToDouble(const PhenomeBoolToDouble &other);

        /**
         * @brief Move constructor.
         *
         * This constructor creates a new `PhenomeBoolToDouble` by moving the data from another `PhenomeBoolToDouble`.
         *
         * @param other The `PhenomeBoolToDouble` to move data from.
         */
        PhenomeBoolToDouble(PhenomeBoolToDouble &&other);

        /**
         * @brief Copy assignment operator.
         *
         * This operator assigns data from another `PhenomeBoolToDouble` to the current instance.
         *
         * @param other The `PhenomeBoolToDouble` to copy data from.
         * @return A reference to the current `PhenomeBoolToDouble` object.
         */
        PhenomeBoolToDouble& operator=(const PhenomeBoolToDouble &other);

        /**
         * @brief Move assignment operator.
         *
         * This operator moves data from another `PhenomeBoolToDouble` to the current instance.
         *
         * @param other The `PhenomeBoolToDouble` to move data from.
         * @return A reference to the current `PhenomeBoolToDouble` object.
         */
        PhenomeBoolToDouble& operator=(PhenomeBoolToDouble &&other) noexcept;

        /**
         * @brief Destructor.
         *
         * Cleans up the resources used by the `PhenomeBoolToDouble` object.
         */
        ~PhenomeBoolToDouble() override;

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
         * @brief Creates a new instance of `PhenomeBoolToDouble`.
         *
         * This method creates and returns a new `PhenomeBoolToDouble` object, typically used for creating new phenomes.
         *
         * @return A pointer to the newly created `PhenomeBoolToDouble` object.
         */
        Phenome* createNew() const override;

        /**
         * @brief Clones the current phenome.
         *
         * This method creates a new `PhenomeBoolToDouble` that is a copy of the current one, including the same data.
         *
         * @return A pointer to the cloned `PhenomeBoolToDouble` object.
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