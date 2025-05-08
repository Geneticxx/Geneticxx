
module ReplacementFull;

namespace Geneticxx
{
  ReplacementFull::ReplacementFull() {
  }

  ReplacementFull::~ReplacementFull() {
  }

  Population* ReplacementFull::replace(Population* originalPopulation, Population* replacingPopulation) {
    if (originalPopulation->getSize() != replacingPopulation->getSize()) {
      originalPopulation->clear();
    }
    for (int i = 0; i < replacingPopulation->getSize(); i++) {
      originalPopulation->setIndividual(i, replacingPopulation->getIndividual(i)->clone());

    }
    originalPopulation->increaseIteration();
    return originalPopulation;
  }
}