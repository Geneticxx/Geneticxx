export module Phenome1D;

export import Genome1D;
export import Phenome;
import std;

namespace Geneticxx {
    /**
     * @class Phenome
     * @brief Class responsible for holding visible manifestation of genome after certain translation operation.
     *
     * The `Phenome` class represents the external expression or manifestation of a genome after it has undergone some transformation.
     * It provides methods to update the phenome based on a genome, as well as methods for manipulating its values and comparing phenomes.
     */
    export class Phenome1D : public Phenome {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        //virtual ~Phenome1D() {}

        /**
         * @brief Retrieves the value at a specific position within the phenome.
         *
         * This method fetches the value located at the specified index in the phenome.
         * The exact type of the returned value is currently generic (`std::any`) but could be
         * refined to return specific types as per the implementation's needs.
         *
         * @param position Index of the value to retrieve.
         * @return Value at the specified position as `std::any`.
         */
        virtual std::any getValue(size_t position) const = 0; // TODO: Change to return specific types

        /**
         * @brief Sets a value at a specific position within the phenome.
         *
         * This method assigns a new value to the phenome at the specified index.
         * The value to be set is generic (`std::any`) but could be changed to more specific types.
         *
         * @param position Index at which to set the value.
         * @param value The value to be set.
         */
        virtual void setValue(size_t position, std::any value) = 0; // TODO: Change to return specific types
    };
}
