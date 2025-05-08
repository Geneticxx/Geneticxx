#include "../doctest.h"

// --- Include Module Headers ---
import PublisherPopulation;
import Observers;
import Population;
import std;

using namespace Geneticxx;

// --- Dummy Observer Implementation ---
namespace PublisherPopulationTest {
    class DummyObserver : public AlgorithmObserver {
    public:
        int generationStartCalls = 0;
        int generationDoneCalls = 0;
        int evaluationDoneCalls = 0;

        // Each method simply increments its corresponding counter.
        int generationStart(std::vector<std::unique_ptr<Population>> *population) override {
            ++generationStartCalls;
            return 0;
        }
        int generationDone(std::vector<std::unique_ptr<Population>> *population) override {
            ++generationDoneCalls;
            return 0;
        }
        int evaluationDone(std::vector<std::unique_ptr<Population>> *population) override {
            ++evaluationDoneCalls;
            return 0;
        }
    };


    // --- Dummy Population Implementation ---

    // A minimal dummy population for notification tests.
    class DummyPopulation : public Population {
    public:
        // We don't need to implement full functionality for notifications.
        [[nodiscard]] std::unique_ptr<Population> createNew() const override {
            return std::make_unique<DummyPopulation>();
        }
        [[nodiscard]] std::unique_ptr<Population> clone() const override {
            return std::make_unique<DummyPopulation>();
        }
        Individual* getIndividual(size_t /*i*/) override {
            return nullptr;
        }
        void setIndividual(size_t /*i*/, Individual* /*individual*/) override { }
        size_t getSize() const override {
            return 0;
        }
        size_t getIteration() const override {
            return 0;
        }
        void increaseIteration() override { }
        void resize(size_t /*size*/) override { }
        void clear() override { }
    };


    // --- Test Suite for PublisherPopulation ---

    /// TODO: add checking handling passed nullptr as an argument to notify method
    TEST_SUITE("PublisherPopulation") {

        TEST_CASE("attach and notify: Single observer receives generation start notifications") {
            // Arrange
            PublisherPopulation publisher;
            DummyObserver observer;
            publisher.attach(&observer);

            // Create a dummy population vector with one dummy population.
            std::vector<std::unique_ptr<Population>> populations;
            populations.push_back(std::make_unique<DummyPopulation>());

            // Act: Notify generation start (event code 0)
            int status = publisher.notify(0, &populations);

            // Assert
            CHECK(status == 0);
            CHECK(observer.generationStartCalls == 1);
            CHECK(observer.generationDoneCalls == 0);
            CHECK(observer.evaluationDoneCalls == 0);
        }

        TEST_CASE("attach and notify: Single observer receives generation done notifications") {
            // Arrange
            PublisherPopulation publisher;
            DummyObserver observer;
            publisher.attach(&observer);

            std::vector<std::unique_ptr<Population>> populations;
            populations.push_back(std::make_unique<DummyPopulation>());

            // Act: Notify generation done (event code 1)
            int status = publisher.notify(1, &populations);

            // Assert
            CHECK(status == 0);
            CHECK(observer.generationDoneCalls == 1);
            CHECK(observer.generationStartCalls == 0);
            CHECK(observer.evaluationDoneCalls == 0);
        }

        TEST_CASE("attach and notify: Single observer receives evaluation done notifications") {
            // Arrange
            PublisherPopulation publisher;
            DummyObserver observer;
            publisher.attach(&observer);

            std::vector<std::unique_ptr<Population>> populations;
            populations.push_back(std::make_unique<DummyPopulation>());

            // Act: Notify evaluation done (event code 2)
            int status = publisher.notify(2, &populations);

            // Assert
            CHECK(status == 0);
            CHECK(observer.evaluationDoneCalls == 1);
            CHECK(observer.generationStartCalls == 0);
            CHECK(observer.generationDoneCalls == 0);
        }

        TEST_CASE("attach and notify: Multiple observers are notified correctly") {
            // Arrange
            PublisherPopulation publisher;
            DummyObserver observer1, observer2;
            publisher.attach(&observer1);
            publisher.attach(&observer2);

            std::vector<std::unique_ptr<Population>> populations;
            populations.push_back(std::make_unique<DummyPopulation>());

            // Act: Notify generation done (event code 1)
            publisher.notify(1, &populations);

            // Assert: Both observers should have been notified.
            CHECK(observer1.generationDoneCalls == 1);
            CHECK(observer2.generationDoneCalls == 1);
        }

        TEST_CASE("detach: Detached observer does not receive notifications") {
            // Arrange
            PublisherPopulation publisher;
            DummyObserver observer1, observer2;
            publisher.attach(&observer1);
            publisher.attach(&observer2);

            std::vector<std::unique_ptr<Population>> populations;
            populations.push_back(std::make_unique<DummyPopulation>());

            // Act: Detach observer2 and notify generation start.
            publisher.detach(&observer2);
            publisher.notify(0, &populations);

            // Assert: Only observer1 should have received the notification.
            CHECK(observer1.generationStartCalls == 1);
            CHECK(observer2.generationStartCalls == 0);
        }

        TEST_CASE("notify: Invalid event code does not trigger any observer calls") {
            // Arrange
            PublisherPopulation publisher;
            DummyObserver observer;
            publisher.attach(&observer);

            std::vector<std::unique_ptr<Population>> populations;
            populations.push_back(std::make_unique<DummyPopulation>());

            // Act: Notify with an invalid event code (e.g., 99)
            int status = publisher.notify(99, &populations);

            // Assert: No observer methods should be called.
            CHECK(status == 0);
            CHECK(observer.generationStartCalls == 0);
            CHECK(observer.generationDoneCalls == 0);
            CHECK(observer.evaluationDoneCalls == 0);
        }
    }
}