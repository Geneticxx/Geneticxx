export module Genome1D;

export import Genome;

import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class Genome
     * @brief Class responsible for holding data on which genome operators are executed.
     *
     * This class defines the interface for the Genome, which represents a genetic entity
     * in the context of a genetic algorithm. It provides methods for creating, cloning,
     * comparing, and manipulating genome data.
     */
    export class Genome1D : public Genome {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * The virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~Genome1D() {}

        /**
         * @brief Retrieves the value at a specific position in the genome.
         *
         * This method retrieves the value stored at the given position within the genome.
         *
         * @param position Index of the value to retrieve.
         * @return Value at the specified position as std::any, which can hold any data type.
         */
        virtual std::any getValue(size_t position) const = 0;

        /**
         * @brief Sets the value at a specific position in the genome.
         *
         * This method sets the value at a specific position in the genome.
         *
         * @param position Index at which to set the value.
         * @param value The value to be set. It is stored as an std::any type to accommodate different types.
         */
        virtual void setValue(size_t position, std::any value) = 0;

    };
}
