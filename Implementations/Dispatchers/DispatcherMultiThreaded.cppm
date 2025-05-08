module DispatcherMultiThreaded;

namespace Geneticxx {
    DispatcherMultiThreaded::DispatcherMultiThreaded() {
    }

    DispatcherMultiThreaded::~DispatcherMultiThreaded() {
    }

    void DispatcherMultiThreaded::dispatch(Population* population, std::vector<std::unique_ptr<Evaluation>>* evaluation) {
        int i = 0;
        for (; i+3 < population->getSize(); i+=4) {
            auto individual1 = population->getIndividual(i);
            auto individual2 = population->getIndividual(i+1);
            auto individual3 = population->getIndividual(i+2);
            auto individual4 = population->getIndividual(i+3);
            std::thread t1(&DispatcherMultiThreaded::dispatched, individual1, evaluation);
            std::thread t2(&DispatcherMultiThreaded::dispatched, individual2, evaluation);
            std::thread t3(&DispatcherMultiThreaded::dispatched, individual3, evaluation);
            std::thread t4(&DispatcherMultiThreaded::dispatched, individual4, evaluation);
            t1.join();
            t2.join();
            t3.join();
            t4.join();
        }
        for (; i < population->getSize(); i++) {
            std::thread t1(dispatched, population->getIndividual(i), evaluation);
        }
    }

    void DispatcherMultiThreaded::dispatched(Individual* individual,
        std::vector<std::unique_ptr<Evaluation>>* evaluation)
    {
        std::vector<double> temp;
        for (int j = 0; j < evaluation->size(); j++) {
            temp.append_range(evaluation->at(j)->evaluate(individual->getPhenome()));
        }
        individual->setObjectiveScore(&temp);
    }
}
