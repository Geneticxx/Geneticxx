export module Observers;

import Population;
import std;
import std.compat;

namespace Geneticxx {
    export class AlgorithmObserver {
    public:
        virtual ~AlgorithmObserver() {
        };

        // called when the algorithm completes a generation
        virtual int generationDone(std::vector<std::unique_ptr<Population> > *population) = 0;

        virtual int generationStart(std::vector<std::unique_ptr<Population> > *population) = 0;

        virtual int evaluationDone(std::vector<std::unique_ptr<Population> > *population) = 0;
    };

    export class CrossoverObserver {
    public:
        virtual ~CrossoverObserver() {
        };

        // called when the algorithm completes a generation
        virtual int childrenDone(std::vector<std::unique_ptr<Genome>> *genomes) = 0;

    };

    export class MutationObserver {
    public:
        virtual ~MutationObserver() {
        };

        // called when the algorithm completes a generation
        virtual int mutationDone(Genome *genome) = 0; //TODO should it also inform about what exactly changed?

    };

    export class ReplacementObserver {
    public:
        virtual ~ReplacementObserver() {
        };

        // called when the algorithm completes a generation
        virtual int replacementDone(Population *population) = 0;
        //TODO should it pass information on original populations? removed individuals?
    };

    export class ScalingObserver {
    public:
        virtual ~ScalingObserver() {
        };

        // called when the algorithm completes a generation
        virtual int scalingDone(Population *population) = 0;

    };
}
