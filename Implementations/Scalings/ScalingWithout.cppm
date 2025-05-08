module ScalingWithout;

namespace Geneticxx
{
    ScalingWithout::ScalingWithout()
    {
    }

    ScalingWithout::~ScalingWithout()
    {
    }

    Population* ScalingWithout::scale(Population* population)
    {
        for (int i = 0; i < population->getSize(); i++)
        {
            scale(population->getIndividual(i));
        }
        return population;
    }

    Individual* ScalingWithout::scale(Individual* individual) {
        double scaled = 0;
        for (int j = 0; j < individual->getObjectiveScore().size(); j++)
        {
            scaled += individual->getObjectiveScore()[j];
        }
        individual->setFitness(scaled);
        return individual;
    }
}