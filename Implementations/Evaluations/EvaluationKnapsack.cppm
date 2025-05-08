module EvaluationKnapsack;


namespace Geneticxx {
    EvaluationKnapsack::EvaluationKnapsack(int target) : capacity(target) {
    }

    EvaluationKnapsack::~EvaluationKnapsack() {
    }

    std::vector<double> EvaluationKnapsack::evaluate(const Phenome* phenomeBase) {
        auto phenome = dynamic_cast<const Phenome1D*>(phenomeBase); //TODO check for bad casts
        int size = phenome->getSize();
        double result = 0;
        int weight = 0;

        // Compute the score by checking how many phenome values match the expected pattern.
        for (int i = 0; i < size; i++) {
            weight += weights[i] * std::any_cast<bool>(phenome->getValue(i)); //TODO check for bad casts
            result += values[i] * std::any_cast<bool>(phenome->getValue(i));
        }
        result = weight <= capacity ? result : 0;
        double bonus1 = weight > 0 ? result / weight : 0; //bonus rewarding low weight
        return std::vector<double>{result, bonus1};
    }
}
