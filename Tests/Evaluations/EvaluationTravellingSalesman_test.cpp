// TODO: finish after decision about std::any case
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "../doctest.h"
// import EvaluationTravellingSalesman;
// import Phenome;
// import std;
//
// // Mock Phenome class
// class MockPhenome : public Geneticxx::Phenome {
// private:
//     std::vector<int> m_route;
//
// public:
//     MockPhenome(const std::vector<int>& route) : m_route(route) {}
//
//     int getSize() const override {
//         return m_route.size();
//     }
//
//     std::any getValue(int index) const override {
//         if (index >= 0 && index < m_route.size()) {
//             return m_route[index];
//         }
//         throw std::out_of_range("Index out of range");
//     }
//
//     void setRoute(const std::vector<int>& route) {
//         m_route = route;
//     }
// };
//
// using namespace Geneticxx;
//
// TEST_SUITE("EvaluationTravellingSalesman") {
//
//     TEST_CASE("Constructor: Default Initialization") {
//         // Arrange
//         EvaluationTravellingSalesman evaluator;
//
//         // Act
//         // Check the number of rows and coordinates of cities
//
//         // Assert
//         CHECK(evaluator.getRows() == 8);  // Assuming default 8 cities
//         CHECK(evaluator.getCols() == 2);  // Coordinates are 2D (x, y)
//     }
//
//     TEST_CASE("Constructor: Parameterized Initialization") {
//         // Arrange
//         double* customCities[3];
//         customCities[0] = new double[2]{0, 0};
//         customCities[1] = new double[2]{1, 1};
//         customCities[2] = new double[2]{2, 2};
//         EvaluationTravellingSalesman evaluator(3, customCities);
//
//         // Act
//         // Check custom cities initialization
//         auto city1 = evaluator.getCity(0);  // Check city 1 coordinates (0, 0)
//         auto city2 = evaluator.getCity(1);  // Check city 2 coordinates (1, 1)
//
//         // Assert
//         CHECK(city1[0] == 0);
//         CHECK(city1[1] == 0);
//         CHECK(city2[0] == 1);
//         CHECK(city2[1] == 1);
//     }
//
//     TEST_CASE("Destructor: Memory Deallocation") {
//         // Arrange
//         EvaluationTravellingSalesman* evaluator = new EvaluationTravellingSalesman();
//
//         // Act
//         // Destructor should be called at the end of the test case when evaluator goes out of scope
//         delete evaluator;  // Explicit call to delete for testing purposes
//
//         // Assert
//         // Check if memory is properly freed (implicitly by the absence of leaks).
//     }
//
//     TEST_CASE("Evaluate: Valid Route Calculation") {
//         // Arrange
//         EvaluationTravellingSalesman evaluator;
//         Phenome phenome(8);  // Assuming phenome has size 8
//         // Initialize phenome with a valid route, for example [0, 1, 2, 3, 4, 5, 6, 7]
//         phenome.setRoute({0, 1, 2, 3, 4, 5, 6, 7});
//
//         // Act
//         auto result = evaluator.evaluate(&phenome);
//
//         // Assert
//         CHECK(result.size() == 1);
//         CHECK(result[0] > 0);  // Total distance should be positive
//     }
//
//     TEST_CASE("Evaluate: Invalid Route Size") {
//         // Arrange
//         EvaluationTravellingSalesman evaluator;
//         Phenome phenome(5);  // Invalid route size (not matching the default 8 cities)
//         phenome.setRoute({0, 1, 2, 3, 4});
//
//         // Act and Assert
//         CHECK_THROWS_AS(evaluator.evaluate(&phenome), std::invalid_argument);
//     }
//
//     TEST_CASE("Evaluate: Minimal Route Size (2 cities)") {
//         // Arrange
//         EvaluationTravellingSalesman evaluator;
//         Phenome phenome(2);
//         phenome.setRoute({0, 1});  // Route with just two cities
//
//         // Act
//         auto result = evaluator.evaluate(&phenome);
//
//         // Assert
//         CHECK(result.size() == 1);
//         CHECK(result[0] > 0);  // Distance between two cities should be positive
//     }
//
//     TEST_CASE("Evaluate: Route with Only One City") {
//         // Arrange
//         EvaluationTravellingSalesman evaluator;
//         Phenome phenome(1);
//         phenome.setRoute({0});  // Route with only one city (shouldn't form a valid TSP route)
//
//         // Act and Assert
//         CHECK_THROWS_AS(evaluator.evaluate(&phenome), std::invalid_argument);
//     }
// }
