export module ReplacementBest;

import ReplacementSchema;

namespace Geneticxx
{
    export class ReplacementBest final : public ReplacementSchema {
    public:
        ReplacementBest();
        ~ReplacementBest() override;

        Population* replace(Population* originalPopulation, Population* replacingPopulation) override;
    };
}
