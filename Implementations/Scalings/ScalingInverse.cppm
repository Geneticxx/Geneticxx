module ScalingInverse;

namespace Geneticxx
{
    ScalingInverse::ScalingInverse()
    {
    }

    ScalingInverse::~ScalingInverse()
    {
    }

    Population* ScalingInverse::scale(Population* population)
    {
        for (int i = 0; i < population->getSize(); i++)
        {
            scale(population->getIndividual(i));
        }
        return population;
    }

    Individual* ScalingInverse::scale(Individual* individual) {
        double scaled = 0;
        for (int i = 0; i < individual->getObjectiveScore().size(); i++)
        {
            scaled += 1/individual->getObjectiveScore()[i];
        }
        individual->setFitness(scaled);
        return individual;
    }
}