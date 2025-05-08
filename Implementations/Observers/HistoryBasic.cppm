module HistoryBasic;

namespace Geneticxx {
    HistoryBasic::HistoryBasic(Statistics *statistics) : m_CurrentStatisticsIndex{0}, m_BestFitness{0}, m_BestGeneration{0}, m_BestPopulationIndex{0} {
        m_statisticsTotal = std::unique_ptr<Statistics>(statistics);
        m_statistics.push_back(std::vector<std::unique_ptr<Statistics>>());
    }

    HistoryBasic::~HistoryBasic() {
    }

    void HistoryBasic::updateCurrentStatistics(Population *population, int index) {
        if (index < m_statistics[m_CurrentStatisticsIndex].size())
        {
            if (!m_statistics[m_CurrentStatisticsIndex][index])
            {
                m_statistics[m_CurrentStatisticsIndex][index] = std::unique_ptr<Statistics>(m_statisticsTotal->createNew());
            }
            m_statistics[m_CurrentStatisticsIndex][index]->update(population);
        }
        else
        {
            throw std::out_of_range ("tried to update statistics beyond set size in HistoryBasic::updateCurrentStatistics");;
        }
    }

    void HistoryBasic::pushStatistics() {
        for (int j = 0; j < m_statistics[m_CurrentStatisticsIndex].size(); ++j)
        {
            for (int i = 0; i < m_statistics[m_CurrentStatisticsIndex][j]->getSize(); i++) {
                if (m_BestFitness < m_statistics[m_CurrentStatisticsIndex][j]->getBestFitness(i)) {
                    m_BestFitness = m_statistics[m_CurrentStatisticsIndex][j]->getBestFitness(i);
                    m_BestGeneration = m_CurrentStatisticsIndex;
                    m_BestPopulationIndex = j;
                }
            }

        }
        m_statistics.push_back(std::vector<std::unique_ptr<Statistics>>());
        ++m_CurrentStatisticsIndex;
    }

    void HistoryBasic::clear()
    {
        m_statistics.clear();
        m_populations.clear();
        m_statistics.push_back(std::vector<std::unique_ptr<Statistics>>());
        m_CurrentStatisticsIndex = 0;
        m_BestFitness = 0;
        m_BestGeneration = 0;
        m_BestPopulationIndex = 0;
    }

    double HistoryBasic::getBestFitness(int index) const {
        return m_statistics[m_BestGeneration][m_BestPopulationIndex]->getBestFitness(index);
    }

    std::vector<double> HistoryBasic::getBestObjectiveScores(int index) const {
        return m_statistics[m_BestGeneration][m_BestPopulationIndex]->getBestIndividual(index)->getObjectiveScore();
    }

    int HistoryBasic::getBestGeneration() const {
        return m_BestGeneration;
    }

    int HistoryBasic::getBestPopulationIndex() const
    {
        return m_BestPopulationIndex;
    }

    const Individual *HistoryBasic::getBestIndividual(int generation, int populationIndex, int index) const {
        return m_statistics[generation][populationIndex]->getBestIndividual(index);
    }

    const Individual* HistoryBasic::getBestIndividual(int index) const
    {
        return getBestIndividual(m_BestGeneration, m_BestPopulationIndex, index);
    }

    std::vector<double> HistoryBasic::getObjectiveScore(int generation, int populationIndex, int index) const {
        return m_statistics[generation][populationIndex]->getBestIndividual(index)->getObjectiveScore();
    }

    double HistoryBasic::getFitness(int generation, int populationIndex, int index) const {
        return m_statistics[generation][populationIndex]->getBestFitness(index);
    }

    int HistoryBasic::evaluationDone(std::vector<std::unique_ptr<Population> > *population) {
        return 0;
    }

    int HistoryBasic::generationStart(std::vector<std::unique_ptr<Population> > *population) {
        return 0;
    }

    int HistoryBasic::generationDone(std::vector<std::unique_ptr<Population> > *population) {
        m_statistics[m_CurrentStatisticsIndex].resize(population->size());
        for (int i = 0; i < population->size(); ++i)
        {
            updateCurrentStatistics((*population)[i].get(), i);
        }
        pushStatistics();
        return 0;
    }
}
