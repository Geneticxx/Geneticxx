export module Genome;

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
    export class Genome {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * The virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~Genome() {
        }

        /**
         * @brief Creates a new Genome instance with default values.
         *
         * This method is intended to create a new genome object initialized with default values.
         *
         * @return std::unique_ptr to a new Genome instance.
         */
        virtual std::unique_ptr<Genome> createNew() const = 0;

        /**
         * @brief Creates a deep copy of the current Genome instance.
         *
         * This method creates a deep copy of the current genome instance, preserving its
         * internal data and structure.
         *
         * @return std::unique_ptr to the cloned Genome instance.
         */
        virtual std::unique_ptr<Genome> clone() const = 0;

        /**
         * @brief Returns the size (number of elements) of the genome.
         *
         * This method returns the number of elements present in the genome.
         *
         * @return Size of the genome, i.e., the number of elements in it.
         */
        virtual size_t getSize() const = 0;


        /**
         * @brief Compares two genomes and returns a similarity metric.
         *
         * This method computes a similarity metric between two genomes. The metric quantifies
         * how similar or different the two genomes are.
         *
         * @param other Pointer to another Genome instance.
         * @return Similarity metric as a double. Higher values may indicate more similarity.
         */
        virtual double distance(Genome *other) const = 0;


        /**
         * @brief Compares two genome instances for equality.
         *
         * This method compares the current genome with another genome to check if they are equal.
         *
         * @param other Pointer to another Genome instance.
         * @return True if the genomes are equal, false otherwise.
         */
        virtual bool operator==(Genome *other) const = 0;

    };
}
