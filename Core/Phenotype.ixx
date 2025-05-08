export module Phenome;

export import Genome;
import std;

namespace Geneticxx {
    /**
     * @class Phenome
     * @brief Class responsible for holding visible manifestation of genome after certain translation operation.
     *
     * The `Phenome` class represents the external expression or manifestation of a genome after it has undergone some transformation.
     * It provides methods to update the phenome based on a genome, as well as methods for manipulating its values and comparing phenomes.
     */
    export class Phenome {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~Phenome() {
        }

        /**
         * @brief Updates the phenome using a given genome.
         *
         * This method updates the phenome based on the data contained in the provided genome.
         * The update mechanism can involve applying translation operations or any other transformation
         * defined by the specific phenome class implementation.
         *
         * @param genome Pointer to the `Genome` object used for updating the phenome.
         */
        virtual void updatePhenome(const Genome *genome) = 0;

        /**
         * @brief Creates a new instance of the phenome with default values.
         *
         * This method instantiates a new phenome object with the default properties. It allows
         * for creating fresh phenome instances to represent new individuals or objects in the population.
         *
         * @return Pointer to a newly created `Phenome` instance.
         */
        virtual Phenome* createNew() const = 0;

        /**
         * @brief Creates a deep copy of the current phenome instance.
         *
         * This method generates a deep copy of the current phenome, preserving its properties,
         * allowing independent modifications to the original and the copy.
         *
         * @return Pointer to the cloned `Phenome` instance.
         */
        virtual Phenome* clone() const = 0;

        /**
         * @brief Returns the size (number of values/elements) of the phenome.
         *
         * This method returns the number of elements or values that constitute the phenome.
         * The size is determined by the structure or representation of the phenome.
         *
         * @return The number of elements in the phenome.
         */
        virtual int getSize() const = 0;

        /**
         * @brief Compares two phenome instances for equality.
         *
         * This method compares the current phenome instance to another one and determines if they are identical.
         * The comparison could involve checking if all values in the phenome match.
         *
         * @param other Reference to another `Phenome` instance.
         * @return `true` if the phenomes are equal, `false` otherwise.
         */
        virtual bool operator==(const Phenome *other) const = 0;
    };
}
