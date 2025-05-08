export module MutationSchema;

export import Genome;

import std;

namespace Geneticxx {
    /**
     * @class MutationSchema
     * @brief Class responsible for mutating genomes.
     *
     * The `MutationSchema` class defines an interface for applying mutations to genomes in a genetic algorithm.
     * It provides methods for cloning the mutation schema, applying mutation operations to genomes, and validating
     * whether the mutation is applicable to a given genome.
     */
export class MutationSchema {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived class objects.
     *
     * This virtual destructor ensures that the destructors of derived classes are called
     * when deleting an object through a base class pointer.
     */
    virtual ~MutationSchema() {}

    /**
     * @brief Creates a deep copy of the current mutation schema instance.
     *
     * This method is responsible for creating a new instance of the mutation schema,
     * which is a clone of the current one. It allows for duplicating the mutation logic
     * for different genome instances while maintaining their individual properties.
     *
     * @return A pointer to the cloned `MutationSchema` object.
     */
    [[nodiscard]] virtual MutationSchema *clone() const = 0;

    /**
     * @brief Applies a mutation operation to the given genome.
     *
     * This method performs the mutation operation on the provided genome. The exact
     * mutation behavior is determined by the specific implementation of this method
     * in derived classes. It modifies the genome according to the defined mutation rules.
     *
     * @param genome Pointer to the `Genome` object to be mutated.
     */
    virtual void mutate(Genome *genome) = 0;

    /**
     * @brief Checks if the mutation schema is valid for the given genome.
     *
     * This method determines if the mutation operation can be applied to the provided genome.
     * Some genomes may not be compatible with certain mutation operations, so this validation
     * ensures that mutation is only applied when appropriate.
     *
     * @param genome Pointer to the `Genome` object to validate.
     * @return `true` if the mutation schema is valid for the genome, `false` otherwise.
     */
    virtual bool validate(Genome *genome) const = 0;
};

}
