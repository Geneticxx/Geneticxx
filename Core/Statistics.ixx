export module Statistics;

export import Population;

import std.compat;

namespace Geneticxx
{
	export class Statistics{
	public:
		virtual ~Statistics() = default;

		// Updates statistics based on the given Population
		virtual void update(Population *population) = 0;

		// Resets the statistics to their initial state
		virtual void clear() = 0;

		// Creates and returns a new instance of the Statistics object
		virtual Statistics *createNew() = 0;

		virtual size_t getSize() = 0;
		virtual void setSize(size_t) = 0;
		virtual Individual* getBestIndividual(int index) = 0;
		virtual double getBestFitness(int index) = 0;
		virtual double getMeanFitness(int index) = 0;
		virtual double getMedianFitness(int index) = 0;
		virtual double getVarianceFitness(int index) = 0;

	};
}
