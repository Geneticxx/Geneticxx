export module ReplacementElitist;

import ReplacementSchema;

namespace Geneticxx
{
	export class ReplacementElitist final : public ReplacementSchema {
	public:
		ReplacementElitist();
		~ReplacementElitist() override;

		Population* replace(Population* originalPopulation, Population* replacingPopulation) override;
	};
}
