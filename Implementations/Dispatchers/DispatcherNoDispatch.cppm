module DispatcherNoDispatch;

namespace Geneticxx {
    DispatcherNoDispatch::DispatcherNoDispatch() {
    }

    DispatcherNoDispatch::~DispatcherNoDispatch() {
    }

    void DispatcherNoDispatch::dispatch(Population* population, std::vector<std::unique_ptr<Evaluation>>* evaluation) {
        for (int i = 0; i < population->getSize(); i++) {
            std::vector<double> temp;
            for (int j = 0; j < evaluation->size(); j++) {
                temp.append_range(evaluation->at(j)->evaluate(population->getIndividual(i)->getPhenome()));
            }
            population->getIndividual(i)->setObjectiveScore(&temp);
        }
    }
}
