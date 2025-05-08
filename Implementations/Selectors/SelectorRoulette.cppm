module SelectorRoulette;

namespace Geneticxx {
  SelectorRoulette::SelectorRoulette(RandomRealFromRange *genReal) : m_RandomNumbersGeneratorReal{genReal} {
    m_PartialSums_Size = 0;
  }

  SelectorRoulette::~SelectorRoulette() {
  }


  void SelectorRoulette::updatePartialSums(Population *population) {
    if (population->getSize() > 0) {
      if (m_PartialSums_Size < population->getSize()) {
        m_PartialSums.resize(population->getSize());
      }
      m_PartialSums_Size = population->getSize();
      m_PartialSums[0] = population->getIndividual(0)->getFitness();
      for (int i = 1; i < population->getSize(); ++i) {
        m_PartialSums[i] = m_PartialSums[i - 1] + population->getIndividual(i)->getFitness();
      }
    } else {
      m_PartialSums_Size = 0;
    }
  }

  std::vector<std::unique_ptr<Individual> > SelectorRoulette::select(Population *population, size_t size) {
    if (population->getSize() > 0) {
      updatePartialSums(population);
      std::vector<std::unique_ptr<Individual> > results;
      for (size_t j = 0; j < size; ++j) {
        double cutoff = m_RandomNumbersGeneratorReal->generate(0,  m_PartialSums[m_PartialSums_Size - 1]);
        int i;
        int lower = 0;
        int upper = m_PartialSums_Size - 1;
        // binary search
        while (upper >= lower) {
          i = lower + (upper - lower) / 2;
          if (m_PartialSums[i] > cutoff) {
            upper = i - 1;
          } else {
            lower = i + 1;
          }
        }
        if (lower >= m_PartialSums_Size) { lower = m_PartialSums_Size - 1; }
        results.push_back(std::unique_ptr<Individual>(population->getIndividual(lower)->clone()));
      }

      return std::move(results);
    }
    std::vector<std::unique_ptr<Individual> > results {};
    return results;
  }
}
