export module CrossoverOrder;

import CrossoverSchema;
import DefaultUniformIntRandomGenerator;
import Genome1D;
import std;

namespace Geneticxx {
    export template <class T>
    class CrossoverOrder : public CrossoverSchema {
    private:
        RandomIntFromRange* m_RandomNumbersGeneratorInt; /**< Utility for generating random numbers */
    public:
        CrossoverOrder(RandomIntFromRange* genInt)
        {
            m_RandomNumbersGeneratorInt = genInt;
        }

        ~CrossoverOrder() override
        {

        }

        std::vector<std::unique_ptr<Genome> > crossover(Genome *parent1, Genome *parent2) override
        {
            if (parent1->getSize() != parent2->getSize() || parent1->getSize() < 2) throw;
            size_t size = parent1->getSize();
            size_t point1 = m_RandomNumbersGeneratorInt->generate(1, size-1);
            auto child1 = parent1->clone();
            auto child2 = parent2->clone();
            int iter1 = 0;
            int iter2 = 0;

            auto child1ptr = dynamic_cast<Genome1D*> (child1.get()); //TODO questionable casts
            auto child2ptr = dynamic_cast<Genome1D*> (child2.get());
            auto parent1ptr = dynamic_cast<Genome1D*> (parent1);
            auto parent2ptr = dynamic_cast<Genome1D*> (parent2);

            for (int i = point1; i < size; i++)
            {
                for (int k = 0; k < point1; k++)
                {
                    if (std::any_cast<T>(parent2ptr->getValue(iter1)) == std::any_cast<T>(parent1ptr->getValue(k)))
                    {
                        iter1++;
                        k = -1;
                    }
                }
                child1ptr->setValue(i, parent2ptr->getValue(iter1));
                iter1++;
                for (int k = 0; k < point1; k++)
                {
                    if (std::any_cast<T>(parent1ptr->getValue(iter2)) == std::any_cast<T>(parent2ptr->getValue(k)))
                    {
                        iter2++;
                        k = -1;
                    }
                }
                child2ptr->setValue(i, parent1ptr->getValue(iter2));
                iter2++;
            }

            for (int i = 0; i < size; i++)
            {
                for (int j = i+1; j < size; j++)
                {
                    if (std::any_cast<T>(child1ptr->getValue(i)) == std::any_cast<T>(child1ptr->getValue(j)))
                    {
                        throw;
                    }
                    if (std::any_cast<T>(child2ptr->getValue(i)) == std::any_cast<T>(child2ptr->getValue(j)))
                    {
                        throw;
                    }
                }
            }
            std::vector<std::unique_ptr<Genome>> results;
            results.push_back(std::move(child1));
            results.push_back(std::move(child2));
            return std::move(results);
        }
    };
}
