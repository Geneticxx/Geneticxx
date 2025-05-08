export module InitializeNoInit;

export import InitializationSchema;
import std;

namespace Geneticxx {
    export class InitializeNoInit : public InitializationSchema {
    public:
        // example class which does not modify the given population during initialization
        InitializeNoInit();

        ~InitializeNoInit() override;

        void initialize(std::vector<std::unique_ptr<Population> > *populations) override;
    };
}
