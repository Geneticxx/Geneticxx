module PublisherPopulation;

namespace Geneticxx
{
    void PublisherPopulation::attach(AlgorithmObserver *observer) {
        m_list_observer.push_back(observer);
    }

    void PublisherPopulation::detach(AlgorithmObserver *observer) {
        m_list_observer.remove(observer);
    }

    int PublisherPopulation::notify(int i, std::vector<std::unique_ptr<Population>> *population)
    {
        std::list<AlgorithmObserver *>::iterator iterator = m_list_observer.begin();
        while (iterator != m_list_observer.end()) {
            switch (i) {
            case 0: (*iterator)->generationStart(population);
                break;
            case 1: (*iterator)->generationDone(population);
                break;
            case 2: (*iterator)->evaluationDone(population);
                break;
            default: break;
            }

            ++iterator;
        }
        return 0;

    }

}
