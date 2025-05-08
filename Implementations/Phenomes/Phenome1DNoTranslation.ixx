export module Phenome1DNoTranslation;

export import Phenome1D;
import std;
import std.compat;

namespace Geneticxx {

    export template<class T>
    class Phenome1DNoTranslation : public Phenome1D {
    private:
        /**
         * @brief A vector of double values representing the phenome's data.
         *
         * This vector holds the double values that define the phenome.
         */
        std::vector<T> m_data;

    public:
        Phenome1DNoTranslation()
        {

        }

        Phenome1DNoTranslation(std::vector<T> data)
        {
          m_data = data;
        }



        /**
         * @brief Copy constructor.
         *
         * This constructor creates a new `PhenomeBoolToDouble` by copying the data from another `PhenomeBoolToDouble`.
         *
         * @param other The `PhenomeBoolToDouble` to copy data from.
         */
        //PhenomeBoolToDouble(const PhenomeBoolToDouble &other);

        /**
         * @brief Move constructor.
         *
         * This constructor creates a new `PhenomeBoolToDouble` by moving the data from another `PhenomeBoolToDouble`.
         *
         * @param other The `PhenomeBoolToDouble` to move data from.
         */
        //PhenomeBoolToDouble(PhenomeBoolToDouble &&other);

        /**
         * @brief Copy assignment operator.
         *
         * This operator assigns data from another `PhenomeBoolToDouble` to the current instance.
         *
         * @param other The `PhenomeBoolToDouble` to copy data from.
         * @return A reference to the current `PhenomeBoolToDouble` object.
         */
        //PhenomeBoolToDouble& operator=(const PhenomeBoolToDouble &other);

        /**
         * @brief Move assignment operator.
         *
         * This operator moves data from another `PhenomeBoolToDouble` to the current instance.
         *
         * @param other The `PhenomeBoolToDouble` to move data from.
         * @return A reference to the current `PhenomeBoolToDouble` object.
         */
        //PhenomeBoolToDouble& operator=(PhenomeBoolToDouble &&other) noexcept;

        /**
         * @brief Destructor.
         *
         * Cleans up the resources used by the `PhenomeBoolToDouble` object.
         */
        ~Phenome1DNoTranslation() override = default;

        /**
         * @brief Updates the phenome using data from a genome.
         *
         * This method updates the phenome's data vector by extracting values from the provided genome. The size of the genome
         * should match the size of the phenome's data vector.
         *
         * @param genome A pointer to the genome object that provides the data to update the phenome.
         */
        void updatePhenome(const Genome* genomeBase) override
        {
            auto genome = dynamic_cast<const Genome1D*>(genomeBase); //TODO check if it's the correct type
            if (m_data.size() <= genome->getSize())
            {
                m_data.resize(genome->getSize());
            }
            for (size_t i = 0; i < m_data.size(); ++i) {
                m_data[i] = std::any_cast<T>(genome->getValue(i)); //TODO check cast correctness, otherwise fun crashes happen
            }

        }

        /**
         * @brief Creates a new instance of `PhenomeBoolToDouble`.
         *
         * This method creates and returns a new `PhenomeBoolToDouble` object, typically used for creating new phenomes.
         *
         * @return A pointer to the newly created `PhenomeBoolToDouble` object.
         */
        Phenome* createNew() const override
        {
            return new Phenome1DNoTranslation;
        }

        /**
         * @brief Clones the current phenome.
         *
         * This method creates a new `PhenomeBoolToDouble` that is a copy of the current one, including the same data.
         *
         * @return A pointer to the cloned `PhenomeBoolToDouble` object.
         */
        Phenome* clone() const override
        {
            auto temp = new Phenome1DNoTranslation(*this);
            temp->m_data = m_data;
            return temp;
        }

        /**
         * @brief Retrieves the value at a specific position in the phenome's data vector.
         *
         * This method returns the value stored at the given position in the phenome's data vector.
         *
         * @param position The index of the value to retrieve.
         * @return The value at the specified position, wrapped in a `std::any` object.
         */
        std::any getValue(size_t position) const override
        {
            return m_data[position];
        }

        /**
         * @brief Sets the value at a specific position in the phenome's data vector.
         *
         * This method updates the value stored at the given position in the phenome's data vector.
         *
         * @param position The index of the value to set.
         * @param value The value to set at the specified position, wrapped in a `std::any` object.
         */
        void setValue(size_t position, std::any value) override
        {
            m_data[position] = std::any_cast<T>(value); //TODO any cast again, check for type before casting or catch errors
        }

        /**
         * @brief Retrieves the size of the phenome's data vector.
         *
         * This method returns the number of elements in the phenome's data vector.
         *
         * @return The size of the phenome's data vector.
         */
        int getSize() const override
        {
            return m_data.size();
        }

        /**
         * @brief Compares the current phenome to another phenome for equality.
         *
         * This method checks if the current phenome is equal to another phenome. This comparison is not implemented yet.
         *
         * @param other The phenome to compare with.
         * @return `true` if the phenomes are equal, `false` otherwise. (Currently returns `false` as it is not implemented.)
         */
        bool operator==(const Phenome *other) const override
        {
            return false; //TODO check if type matches, then compare values
        }
    };
}