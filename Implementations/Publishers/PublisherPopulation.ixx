export module PublisherPopulation;

export import Publisher;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class PublisherPopulation
     * @brief A class that notifies observers about the algorithm's progress or events.
     *
     * This class is responsible for managing a list of observers (subscribers) and notifying them about different
     * stages in the population evolution process, such as the start and end of a generation or the completion of evaluations.
     * The class implements the `Publisher` interface.
     */
    export class PublisherPopulation : public AlgorithmPublisher {
    private:
        /**
         * @brief A list of observer pointers.
         *
         * This list stores pointers to the `AlgorithmObserver` objects that are subscribed to the population's updates.
         * These observers are notified whenever certain events, such as the start or completion of a generation, occur.
         */
        std::list<AlgorithmObserver*> m_list_observer;

    public:
        /**
         * @brief Destructor.
         *
         * Cleans up the `PublisherPopulation` object. This destructor is virtual to ensure proper cleanup of derived classes.
         */
        virtual ~PublisherPopulation() {
        };

        /**
         * @brief Attach an observer to the publisher.
         *
         * This method allows an observer to subscribe to updates from the population. The observer will be notified about
         * specific events related to the population.
         *
         * @param observer A pointer to the `IAlgorithmObserver` object that should be added to the list of observers.
         */
        void attach(AlgorithmObserver* observer) override;

        /**
         * @brief Detach an observer from the publisher.
         *
         * This method allows an observer to unsubscribe from updates. The observer will no longer be notified about
         * events related to the population.
         *
         * @param observer A pointer to the `IAlgorithmObserver` object that should be removed from the list of observers.
         */
        void detach(AlgorithmObserver* observer) override;

        /**
         * @brief Notify all subscribed observers about an event.
         *
         * This method iterates over all subscribed observers and notifies them about the occurrence of an event, such as
         * the start of a generation or the completion of an evaluation. Different actions can be triggered depending on the
         * value of the parameter `i`.
         *
         * @param i An integer value representing the type of event:
         *          - 0: Generation start
         *          - 1: Generation done
         *          - 2: Evaluation done
         * @param population A pointer to a vector of unique pointers to `Population` objects, used as data passed to observers.
         * @return An integer status code, usually `0` indicating successful notification.
         */
        int notify(int i, std::vector<std::unique_ptr<Population>> *population) override;
    };
}
