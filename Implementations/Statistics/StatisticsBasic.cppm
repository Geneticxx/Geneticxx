module StatisticsBasic;

namespace Geneticxx
{
    StatisticsBasic::~StatisticsBasic()  {}

    StatisticsBasic::StatisticsBasic() : mutationCount{0}, crossoverCount{0},
        selectionCount{0}, replacementCount{0}, m_size{1}, m_realSize{1},
        m_meanFitness{0}, m_medianFitness{0}, m_varianceFitness {0} {}

    void StatisticsBasic::update(Population* population)
    {
        m_varianceFitness = 0;
        m_meanFitness = 0;
        m_medianFitness = 0;
        m_realSize = population->getSize() > m_size ? m_size : population->getSize();

         for (int i = 0; i < population->getSize(); i++)
         {
             m_Individuals.push_back(std::unique_ptr<Individual>(population->getIndividual(i)->clone()));
             m_meanFitness += m_Individuals[i]->getFitness();
         }
        m_meanFitness /= population->getSize();
        for (int i = 0; i < population->getSize(); i++)
        {
            m_varianceFitness += (m_Individuals[i]->getFitness() - m_meanFitness)*(m_Individuals[i]->getFitness() - m_meanFitness);
        }
        m_varianceFitness /= population->getSize();
        std::sort( m_Individuals.begin(),
                          //m_Individuals.begin() + m_realSize,
                           m_Individuals.end(),
                           [](const std::unique_ptr<Individual> &lhs, const std::unique_ptr<Individual> &rhs)
                           {
                              return lhs.get()->getFitness() > rhs.get()->getFitness(); //  (*lhs) > (*rhs) for the greatest n elements
                           });
        if (population->getSize() % 2 == 0)
        {
            m_medianFitness = (m_Individuals[population->getSize()/2]->getFitness() +
                m_Individuals[population->getSize()/2-1]->getFitness())/2;
        }
        else  m_medianFitness = m_Individuals[population->getSize()/2-1]->getFitness();
         m_Individuals.resize(m_realSize);
    }

    void StatisticsBasic::clear()
    {
        m_Individuals.clear();
    }

    StatisticsBasic* StatisticsBasic::createNew()
    {
        return new StatisticsBasic();
    }

    size_t StatisticsBasic::getSize()
    {
        return m_size;
    }

    void StatisticsBasic::setSize(size_t size)
    {
        m_size = size;
    }

    Individual* StatisticsBasic::getBestIndividual(int index)
    {
        if (index < m_realSize)
        {
            return m_Individuals[index].get()->clone();
        }
        throw std::runtime_error("m_Genomes' index out of range.");
    }

    double StatisticsBasic::getBestFitness(int index)
    {
        if (index < m_realSize)
        {
            return m_Individuals[index].get()->getFitness();
        }
        throw std::runtime_error("m_Genomes' index out of range.");
    }

    double StatisticsBasic::getMeanFitness(int index)
    {
        return m_meanFitness;
    }

    double StatisticsBasic::getMedianFitness(int index)
    {
        return m_medianFitness;
    }

    double StatisticsBasic::getVarianceFitness(int index)
    {
        return m_varianceFitness;
    }
}
