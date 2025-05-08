module IndividualSimple;

namespace Geneticxx {
    IndividualSimple::IndividualSimple()
        : m_Fitness(0.0), m_Genome(nullptr), m_Phenome(nullptr) {
    }

    IndividualSimple::IndividualSimple(Phenome* phenome, Genome* genome)
        : m_Fitness(0.0) {
        m_Genome = std::unique_ptr<Genome>(genome);
        m_Phenome = std::unique_ptr<Phenome>(phenome);
    }

    IndividualSimple::IndividualSimple(const IndividualSimple& individual) : m_Fitness{individual.m_Fitness},
                                                                             m_ObjectiveScore{
                                                                                 individual.m_ObjectiveScore
                                                                             } {
        if (individual.m_Genome) {
            m_Genome = std::unique_ptr<Genome>(individual.m_Genome->clone());
        }
        else {
            m_Genome = nullptr;
        }
        if (individual.m_Phenome) {
            m_Phenome = std::unique_ptr<Phenome>(individual.m_Phenome->clone());
        }
        else {
            m_Phenome = nullptr;
        }
    }

    IndividualSimple::IndividualSimple(IndividualSimple&& individual) : m_Fitness{individual.m_Fitness},
                                                                        m_ObjectiveScore{individual.m_ObjectiveScore},
                                                                        m_Genome{std::move(individual.m_Genome)},
                                                                        m_Phenome{std::move(individual.m_Phenome)} {
        individual.m_Fitness = 0.0;
        individual.m_ObjectiveScore = {0};
    }

    IndividualSimple& IndividualSimple::operator=(const IndividualSimple& individual) {
        if (this != &individual) {
            m_Fitness = individual.m_Fitness;
            m_ObjectiveScore = individual.m_ObjectiveScore;

            if (individual.m_Genome) {
                m_Genome = std::unique_ptr<Genome>(individual.m_Genome->clone());
            }
            else {
                m_Genome.reset();
            }
            if (individual.m_Phenome) {
                m_Phenome = std::unique_ptr<Phenome>(individual.m_Phenome->clone());
            }
            else {
                m_Phenome.reset();
            }
        }
        return *this;
    }

    IndividualSimple& IndividualSimple::operator=(IndividualSimple&& individual) {
        if (this != &individual) {
            m_Fitness = individual.m_Fitness;
            m_ObjectiveScore = individual.m_ObjectiveScore;
            m_Genome = std::move(individual.m_Genome);
            m_Phenome = std::move(individual.m_Phenome);
            individual.m_Fitness = 0.0;
            individual.m_ObjectiveScore = {0};
        }
        return *this;
    }

    IndividualSimple::~IndividualSimple() = default;

    Individual* IndividualSimple::createNew() const {
        return new IndividualSimple();
    }

    Individual* IndividualSimple::clone() const {
        auto cloned = new IndividualSimple();
        cloned->m_Fitness = this->m_Fitness;
        cloned->m_ObjectiveScore = this->m_ObjectiveScore;

        // Cloning genotype and phenome
        cloned->m_Genome = std::unique_ptr<Genome>(this->m_Genome->clone());
        cloned->m_Phenome = std::unique_ptr<Phenome>(this->m_Phenome->clone());

        return cloned;
    }

    double IndividualSimple::getFitness() const {
        return this->m_Fitness;
    }

    void IndividualSimple::setFitness(double fitness) {
        this->m_Fitness = fitness;
    }

    std::vector<double> IndividualSimple::getObjectiveScore() const {
        return this->m_ObjectiveScore;
    }

    void IndividualSimple::setObjectiveScore(std::vector<double> *objectiveScore) {
        if (objectiveScore == nullptr) {
            this->m_ObjectiveScore = std::vector<double>{0};
            return;
        }
        this->m_ObjectiveScore = *objectiveScore;
    }

    void IndividualSimple::updatePhenome() {
        if (m_Genome && m_Phenome) {
            m_Phenome->updatePhenome(m_Genome.get());
        }
    }

    // Const getter for Genome
    const Genome* IndividualSimple::getGenome() const {
        return this->m_Genome.get();
    }

    Genome* IndividualSimple::getGenome() {
        return this->m_Genome.get();
    }

    // Setter for Genome
    // void IndividualSimple::setGenome(Genome& genome) {
    //     m_Genome = std::unique_ptr<Genome> {&genome};
    // }

    void IndividualSimple::setGenome(Genome* genome) {
        // Przeniesienie własności do unique_ptr m_Genome
        m_Genome = std::unique_ptr<Genome>(genome);
    }

    // Getter for Phenome
    Phenome* IndividualSimple::getPhenome() const {
        return this->m_Phenome.get();
    }

    // Setter for Phenome
    // void IndividualSimple::setPhenome(Phenome& phenome) {
    //     m_Phenome = std::unique_ptr<Phenome> {&phenome};
    // }

    void IndividualSimple::setPhenome(Phenome* phenome) {
        m_Phenome = std::unique_ptr<Phenome>(phenome);
    }
}
