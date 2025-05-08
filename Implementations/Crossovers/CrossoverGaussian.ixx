export module CrossoverGaussian;

import CrossoverSchema;
import std;

namespace Geneticxx {
	export class CrossoverGaussian final : public CrossoverSchema {
	public:
		CrossoverGaussian();

		~CrossoverGaussian() override;

		std::vector<std::unique_ptr<Genome> > crossover(Genome *parent1, Genome *parent2) override;
	};
}
