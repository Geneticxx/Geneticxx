module PopulationSimple;

namespace Geneticxx {
  PopulationSimple::PopulationSimple() : m_Iteration{0}, m_PopulationVector{} {
  }

  PopulationSimple::~PopulationSimple() {
  }

  PopulationSimple::PopulationSimple(const PopulationSimple &other) : m_Iteration(other.m_Iteration) {
    m_PopulationVector.resize(other.m_PopulationVector.size());
    for (size_t i = 0; i < other.m_PopulationVector.size(); i++) {
      if (other.m_PopulationVector[i]) {
        m_PopulationVector[i] = std::unique_ptr<Individual>(other.m_PopulationVector[i]->clone());
      } else {
        m_PopulationVector[i] = nullptr;
      }
    }
  }

  PopulationSimple::PopulationSimple(PopulationSimple &&other) : m_Iteration{other.m_Iteration}, m_PopulationVector{std::move(other.m_PopulationVector)} {
    other.m_Iteration = 0;
  }

  PopulationSimple &PopulationSimple::operator=(const PopulationSimple &other) {
    if (this != &other) {
      m_Iteration = other.m_Iteration;
      std::vector<std::unique_ptr<Individual> > newVector;
      newVector.resize(other.m_PopulationVector.size());
      for (size_t i = 0; i < other.m_PopulationVector.size(); i++) {
        if (other.m_PopulationVector[i]) {
          newVector[i] = std::unique_ptr<Individual>(other.m_PopulationVector[i]->clone());
        } else {
          newVector[i] = nullptr;
        }
      }
      m_PopulationVector = std::move(newVector);
    }
    return *this;
  }

  PopulationSimple &PopulationSimple::operator=(PopulationSimple &&other) {
    if (this != &other) {
      m_Iteration = other.m_Iteration;
      m_PopulationVector = std::move(other.m_PopulationVector);
      other.m_Iteration = 0;
    }
    return *this;
  }

  std::unique_ptr<Population> PopulationSimple::createNew() const {
    return std::make_unique<PopulationSimple>();
  }

  std::unique_ptr<Population> PopulationSimple::clone() const {
    auto newPopulation = new PopulationSimple();
    newPopulation->resize(this->getSize());
    for (int i = 0; i < this->m_PopulationVector.size(); i++) {
      newPopulation->m_PopulationVector[i] = std::unique_ptr<Individual>(this->m_PopulationVector[i]->clone());
    }
    return std::unique_ptr<Population>(newPopulation);
  }

  Individual *PopulationSimple::getIndividual(size_t i) {
    return this->m_PopulationVector[i].get();
  }

  void PopulationSimple::setIndividual(size_t i, Individual *individual) {
    this->m_PopulationVector[i] = std::unique_ptr<Individual>(individual);
  }

  /// TODO: simple addIndividual? (simple push_back)

  size_t PopulationSimple::getSize() const {
    return this->m_PopulationVector.size();
  }

  /*
    size_t PopulationSimple::getCapacity() const {
      return this->m_PopulationVector.capacity();
    }
  */
  size_t PopulationSimple::getIteration() const {
    return this->m_Iteration;
  }

  void PopulationSimple::increaseIteration() {
    this->m_Iteration++;
  }

  void PopulationSimple::resize(size_t size) {
    m_PopulationVector.resize(size);
  }

  void PopulationSimple::clear() {
    m_PopulationVector.clear();
  }
}
