#include "ConverterFacade.hpp"


ConverterFacade ConverterFacade::createWithInputArguments(int argc, const char **argv) {
    return {argc, argv};
}


void ConverterFacade::convert() const {

}
