module StoppingCriterionMaxGenerations;

namespace Geneticxx
{
    StoppingCriterionMaxGenerations::StoppingCriterionMaxGenerations(size_t maxGenerations) {
        this->maxGenerations = maxGenerations;
    }

    StoppingCriterionMaxGenerations::~StoppingCriterionMaxGenerations() = default;

    size_t StoppingCriterionMaxGenerations::getMaxGenerations() const {
        return this->maxGenerations;
    }

    // void StoppingCriterionMaxGenerations::setMaxGenerations(size_t maxGenerations) {
    //     this->maxGenerations = maxGenerations;
    // }

    bool StoppingCriterionMaxGenerations::check(Population *population) {
        if (population->getIteration() < maxGenerations)
        {
            return false;
        }
        return true;
    }
}