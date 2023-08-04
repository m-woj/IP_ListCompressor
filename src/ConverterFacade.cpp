#include "ConverterFacade.hpp"


ConverterFacade ConverterFacade::createFromInputArguments(int argc, const char **argv) {
    return {argc, argv};
}


void ConverterFacade::convert() const {
    auto configuration = configurationProvider.tryGetConfiguration();
    if (!configuration) {
        return;
    }

}
