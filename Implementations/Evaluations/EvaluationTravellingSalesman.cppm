module EvaluationTravellingSalesman;

namespace Geneticxx {
    EvaluationTravellingSalesman::EvaluationTravellingSalesman() : m_cols{2}, m_rows{8} {
        m_array = new double*[m_rows];
        for (int i = 0; i < m_rows; i++) {
            m_array[i] = new double[m_cols];
        }

        // Predefined set of city coordinates
        m_array[0][0] = 1;
        m_array[0][1] = 0;
        m_array[1][0] = 1;
        m_array[1][1] = -1;
        m_array[2][0] = -1;
        m_array[2][1] = -1;
        m_array[3][0] = 1;
        m_array[3][1] = 1;
        m_array[4][0] = 0;
        m_array[4][1] = 1;
        m_array[5][0] = -1;
        m_array[5][1] = 1;
        m_array[6][0] = -1;
        m_array[6][1] = 0;
        m_array[7][0] = -1;
        m_array[7][1] = -1;
    }

    EvaluationTravellingSalesman::EvaluationTravellingSalesman(int rows, double** array)
        : m_cols{2}, m_rows{rows}, m_array{array} {
    }

    EvaluationTravellingSalesman::~EvaluationTravellingSalesman() {
        for (int i = 0; i < m_rows; i++) {
            delete[] m_array[i];
        }
        delete[] m_array;
    }
    int EvaluationTravellingSalesman::getCols() const {
        return m_cols;
    }

    void EvaluationTravellingSalesman::setCols(int m_cols) {
        this->m_cols = m_cols;
    }

    int EvaluationTravellingSalesman::getRows() const {
        return m_rows;
    }

    void EvaluationTravellingSalesman::setRows(int m_rows) {
        this->m_rows = m_rows;
    }

    double * EvaluationTravellingSalesman::getCity(int index) {
        return m_array[index];
    }

    std::vector<double> EvaluationTravellingSalesman::evaluate(const Phenome* phenomeBase) {
        auto phenome = dynamic_cast<const Phenome1D*>(phenomeBase);
        double totalDistance = 0.0;
        int routeSize = phenome->getSize();

        if (routeSize != m_rows) {
            throw std::invalid_argument("Evaluation m_rows is not equal to the phenome size!");
        }

        // Compute total distance for the closed route
        for (int i = 0; i < routeSize; i++) {
            int currentCity = std::any_cast<int>(phenome->getValue(i));
            int nextCity = std::any_cast<int>(phenome->getValue((i + 1) % routeSize));
            // Wrap-around for the last city

            // Compute Euclidean distance between consecutive cities
            double dx = static_cast<double>(m_array[currentCity][0] - m_array[nextCity][0]);
            double dy = static_cast<double>(m_array[currentCity][1] - m_array[nextCity][1]);
            double distance = std::sqrt(dx * dx + dy * dy);
            totalDistance += distance;
        }
        //penalty for revisiting towns
        if (totalDistance == 0) totalDistance = 100;
        std::vector<int> repeats(routeSize, 0);
        double penalty = 1;
        for (int i = 0; i < routeSize; i++)
        {
            repeats[std::any_cast<int>(phenome->getValue(i))]++;
        }
        for (int i = 0; i < routeSize; i++)
        {
            if (repeats[i] > 1)
            {
                penalty *= std::pow(2, repeats[i]);
            }
        }
        totalDistance *= penalty;
        return std::vector<double>{totalDistance};
    }
}

