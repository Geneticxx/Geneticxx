module GeneticAlgorithmSimple;

namespace Geneticxx {
    GeneticAlgorithmSimple::GeneticAlgorithmSimple(
        std::vector<std::unique_ptr<Population> > *populations,
        Evaluation *evaluation,
        ReplacementSchema *replacement,
        CrossoverSchema *crossover,
        MutationSchema *mutation,
        ScalingSchema *scaling,
        SelectionSchema *selection,
        InitializationSchema *initialization,
        StoppingCriterionSchema *stoppingCriterion,
        Dispatcher *dispatcher,
        RandomRealFromRange *genReal
    ) {
        m_populations = std::move(*populations);
        m_evaluation.push_back(std::unique_ptr<Evaluation>(evaluation));
        m_replacementSchema = std::unique_ptr<ReplacementSchema>(replacement);
        m_stoppingCriterionSchema = std::unique_ptr<StoppingCriterionSchema>(stoppingCriterion);
        m_selectionSchema = std::unique_ptr<SelectionSchema>(selection);
        m_initializationSchema = std::unique_ptr<InitializationSchema>(initialization);
        m_crossoverSchema = std::unique_ptr<CrossoverSchema>(crossover);
        m_mutationSchema = std::unique_ptr<MutationSchema>(mutation);
        m_scalingSchema = std::unique_ptr<ScalingSchema>(scaling);
        m_dispatcher = dispatcher;
        m_randomNumbersGeneratorReal = genReal;
    }

    GeneticAlgorithmSimple::~GeneticAlgorithmSimple() {
        //if (m_history != nullptr) {delete m_history;} the algorithm doesn't manage its history
        if (m_dispatcher != nullptr) { delete m_dispatcher; }
    }



    void GeneticAlgorithmSimple::step() {
        notify(genStart, &m_populations);

        for (auto &pop: m_populations) {
            auto newPopulation = pop.get()->createNew();
            newPopulation->resize(pop->getSize());
            size_t siz = 0;
            while (siz < pop->getSize()) {
                auto childrenGenomes = m_crossoverSchema->crossover(
                    m_selectionSchema->select(pop.get(), 1)[0]->getGenome(),
                    m_selectionSchema->select(pop.get(), 1)[0]->getGenome()
                    );

                // if generated number is lower than the set mutation rate then perform a mutation and update the phenome
                for (auto &child: childrenGenomes) {
                    tryToMutate(child.get());
                    auto temp = pop->getIndividual(0)->clone();
                    temp->setGenome(child.release()); // TODO set genome should take unique ptr
                    temp->updatePhenome();
                    newPopulation->setIndividual(siz, temp); // TODO do iterators get invalidated? this might break for longer vectors
                    ++siz; //TODO make function pushbackIndividual rather than this method?
                }
            }

            m_dispatcher->dispatch(newPopulation.get(), &m_evaluation); //TODO don't get(), or do, dispatch should use the whole vector?
            m_scalingSchema->scale(newPopulation.get()); //TODO don't get(), or do


            //
            //notify(evalDone, newPopulation);

            m_replacementSchema->replace(pop.get(), newPopulation.get()); //TODO don't get()

            notify(genDone, &m_populations);
        }
    }

    void GeneticAlgorithmSimple::step(int steps) {
        for (int i = 0; i < steps; i++) {
            step();
        }
    }

    void GeneticAlgorithmSimple::evolve() {
        bool stop = false;
            while (!stop) {
                step();
                for (auto &pop: m_populations)
                {
                    stop = stop || m_stoppingCriterionSchema->check(pop.get());
                }
            }

    }

    void GeneticAlgorithmSimple::initialize() {
        m_initializationSchema->initialize(&m_populations); //initialize
        for (auto &pop: m_populations) {
            m_dispatcher->dispatch(pop.get(), &m_evaluation);
            m_scalingSchema->scale(pop.get()); //scale the evaluation results
        }
    }

    void GeneticAlgorithmSimple::addPopulation(Population *population) {
        m_populations.push_back(std::unique_ptr<Population>(population));
    }

    void GeneticAlgorithmSimple::addEvaluation(Evaluation *evaluation) {
        m_evaluation.push_back(std::unique_ptr<Evaluation>(evaluation));
    }

    void GeneticAlgorithmSimple::setReplacementSchema(ReplacementSchema *replacementSchema) {
        m_replacementSchema = std::unique_ptr<ReplacementSchema>(replacementSchema);
    }

    void GeneticAlgorithmSimple::setStoppingCriterionSchema(StoppingCriterionSchema *stoppingCriterionSchema) {
        m_stoppingCriterionSchema = std::unique_ptr<StoppingCriterionSchema>(stoppingCriterionSchema);
    }

    void GeneticAlgorithmSimple::setSelectionSchema(SelectionSchema *selectionSchema) {
        m_selectionSchema = std::unique_ptr<SelectionSchema>(selectionSchema);
    }

    void GeneticAlgorithmSimple::setInitializationSchema(InitializationSchema *initializationSchema) {
        m_initializationSchema = std::unique_ptr<InitializationSchema>(initializationSchema);
    }

    void GeneticAlgorithmSimple::setCrossoverSchema(CrossoverSchema *crossoverSchema) {
        m_crossoverSchema = std::unique_ptr<CrossoverSchema>(crossoverSchema);
    }

    void GeneticAlgorithmSimple::setMutationSchema(MutationSchema *mutationSchema) {
        m_mutationSchema = std::unique_ptr<MutationSchema>(mutationSchema);
    }

    void GeneticAlgorithmSimple::setScalingSchema(ScalingSchema *scalingSchema) {
        m_scalingSchema = std::unique_ptr<ScalingSchema>(scalingSchema);
    }

    void GeneticAlgorithmSimple::setDispatcher(Dispatcher *dispatcher) {
        m_dispatcher = dispatcher;
    }

    void GeneticAlgorithmSimple::setRandomNumbersGenerator(RandomRealFromRange *genReal) {
        m_randomNumbersGeneratorReal = genReal;
    }

    void GeneticAlgorithmSimple::tryToMutate(Genome *object) {
        if (m_randomNumbersGeneratorReal->generate(0, 1) < m_mutationChance) {
            m_mutationSchema->mutate(object);
        }
    }
}
