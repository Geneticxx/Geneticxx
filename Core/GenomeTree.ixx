export module GenomeTree;

import Genome;
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
    export class GenomeTree : public Genome {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * The virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~GenomeTree() {
        }


    };
}
