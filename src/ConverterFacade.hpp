#include "configuration/Configuration.hpp"


class ConverterFacade {
public:
    ConverterFacade() = delete;

    static void convertBasingOnInputArguments(int argc, const char* argv[]);

    static void convertBasingOnConfiguration(const Configuration& configuration);
};
