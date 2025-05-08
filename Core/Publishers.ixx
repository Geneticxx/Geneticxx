export module Publisher;

export import Population;
export import Observers;
import std;
import std.compat;

namespace Geneticxx {
    /**
 * @class AlgorithmPublisher
 * @brief Interface for publishing updates to observers during the execution of the genetic algorithm.
 *
 * The `Publisher` interface defines methods for attaching and detaching observers that receive
 * updates about the state of the genetic algorithm during its execution. It allows for notifying
 * observers about specific events or state changes, providing updates related to the population's
 * state at various points in the algorithm's execution.
 */
export class AlgorithmPublisher {
public:
    /**
     * @brief Destructor for the Publisher interface.
     *
     * Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~AlgorithmPublisher() {}

    /**
     * @brief Attach an observer to receive updates during the genetic algorithm execution.
     *
     * This method allows an observer to be added, so it can receive notifications about events
     * and state changes during the execution of the genetic algorithm.
     *
     * @param observer Pointer to the IAlgorithmObserver object that should be attached.
     */
    virtual void attach(AlgorithmObserver* observer) = 0;

    /**
     * @brief Detach an observer to no longer receive updates during the genetic algorithm execution.
     *
     * This method allows for detaching an observer, so it will no longer be notified of any events
     * or state changes during the algorithm's execution.
     *
     * @param observer Pointer to the IAlgorithmObserver object that should be detached.
     */
    virtual void detach(AlgorithmObserver *observer) = 0;

    /**
     * @brief Notify the algorithm about a specific event or state change.
     *
     * This method is used to send notifications during the execution of the genetic algorithm.
     * It provides information about the current state of the population and specific event details.
     *
     * @param i An integer representing a specific event or state change in the algorithm.
     * @param population Pointer to a vector of unique pointers to Population objects representing
     * the current population state.
     *
     * @return An integer indicating the result of the notification (e.g., success or failure).
     */
    virtual int notify(int i, std::vector<std::unique_ptr<Population>> *population) = 0;

};

    export class CrossoverPublisher {
    public:
        /**
         * @brief Destructor for the Publisher interface.
         *
         * Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~CrossoverPublisher() {}

        /**
         * @brief Attach an observer to receive updates during the genetic algorithm execution.
         *
         * This method allows an observer to be added, so it can receive notifications about events
         * and state changes during the execution of the genetic algorithm.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be attached.
         */
        virtual void attach(CrossoverObserver* observer) = 0;

        /**
         * @brief Detach an observer to no longer receive updates during the genetic algorithm execution.
         *
         * This method allows for detaching an observer, so it will no longer be notified of any events
         * or state changes during the algorithm's execution.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be detached.
         */
        virtual void detach(CrossoverObserver *observer) = 0;

        /**
         * @brief Notify the algorithm about a specific event or state change.
         *
         * This method is used to send notifications during the execution of the genetic algorithm.
         * It provides information about the current state of the population and specific event details.
         *
         * the current population state.
         *
         * @return An integer indicating the result of the notification (e.g., success or failure).
         */
        virtual int notify(std::vector<std::unique_ptr<Genome>> *genomes) = 0;

    };

    export class MutationPublisher {
    public:
        /**
         * @brief Destructor for the Publisher interface.
         *
         * Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~MutationPublisher() {}

        /**
         * @brief Attach an observer to receive updates during the genetic algorithm execution.
         *
         * This method allows an observer to be added, so it can receive notifications about events
         * and state changes during the execution of the genetic algorithm.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be attached.
         */
        virtual void attach(MutationObserver* observer) = 0;

        /**
         * @brief Detach an observer to no longer receive updates during the genetic algorithm execution.
         *
         * This method allows for detaching an observer, so it will no longer be notified of any events
         * or state changes during the algorithm's execution.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be detached.
         */
        virtual void detach(MutationObserver *observer) = 0;

        /**
         * @brief Notify the algorithm about a specific event or state change.
         *
         * This method is used to send notifications during the execution of the genetic algorithm.
         * It provides information about the current state of the population and specific event details.
         *
         * the current population state.
         *
         * @return An integer indicating the result of the notification (e.g., success or failure).
         */
        virtual int notify(Genome *genome) = 0;

    };

    export class ReplacementPublisher {
    public:
        /**
         * @brief Destructor for the Publisher interface.
         *
         * Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~ReplacementPublisher() {}

        /**
         * @brief Attach an observer to receive updates during the genetic algorithm execution.
         *
         * This method allows an observer to be added, so it can receive notifications about events
         * and state changes during the execution of the genetic algorithm.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be attached.
         */
        virtual void attach(ReplacementObserver* observer) = 0;

        /**
         * @brief Detach an observer to no longer receive updates during the genetic algorithm execution.
         *
         * This method allows for detaching an observer, so it will no longer be notified of any events
         * or state changes during the algorithm's execution.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be detached.
         */
        virtual void detach(ReplacementObserver *observer) = 0;

        /**
         * @brief Notify the algorithm about a specific event or state change.
         *
         * This method is used to send notifications during the execution of the genetic algorithm.
         * It provides information about the current state of the population and specific event details.
         *
         * the current population state.
         *
         * @return An integer indicating the result of the notification (e.g., success or failure).
         */
        virtual int notify(Population *population) = 0;

    };

    export class ScalingPublisher {
    public:
        /**
         * @brief Destructor for the Publisher interface.
         *
         * Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~ScalingPublisher() {}

        /**
         * @brief Attach an observer to receive updates during the genetic algorithm execution.
         *
         * This method allows an observer to be added, so it can receive notifications about events
         * and state changes during the execution of the genetic algorithm.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be attached.
         */
        virtual void attach(ScalingObserver* observer) = 0;

        /**
         * @brief Detach an observer to no longer receive updates during the genetic algorithm execution.
         *
         * This method allows for detaching an observer, so it will no longer be notified of any events
         * or state changes during the algorithm's execution.
         *
         * @param observer Pointer to the IAlgorithmObserver object that should be detached.
         */
        virtual void detach(ScalingObserver *observer) = 0;

        /**
         * @brief Notify the algorithm about a specific event or state change.
         *
         * This method is used to send notifications during the execution of the genetic algorithm.
         * It provides information about the current state of the population and specific event details.
         *
         * the current population state.
         *
         * @return An integer indicating the result of the notification (e.g., success or failure).
         */
        virtual int notify(Population *population) = 0;

    };

}
