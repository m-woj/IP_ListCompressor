#include <CLI/CLI.hpp>

#include "ConfigurationProvider.hpp"


void setOptions(CLI::App& app, Configuration& configuration);


ConfigurationProvider ConfigurationProvider::createWithInputArguments(int argc, const char* argv[]) {
    return {argc, argv};
}


ConfigurationProvider::ConfigurationProvider(int argc, const char* argv[]) {
    CLI::App app;

    setOptions(app, configuration);

//    CLI11_PARSE(app, argc, argv);
}


const Configuration &ConfigurationProvider::getConfiguration() const {
    return configuration;
}


void setOptions(CLI::App& app, Configuration& configuration) {
    //  Data Provider
    app.add_option("-i,--inputDataFiles", configuration.inputDataFileURLs,
                   "A list of URLs with input data.");

    //  Converter
    app.add_option("-m,--multithreading", configuration.multithreadingRequired,
                   "Set multithreading requirement.");
    app.add_option("-c,--compression", configuration.compressionRequired,
                   "Set compression requirement.");
    app.add_option("-rd,--rangesDecomposition", configuration.rangesDecompositionRequired,
                   "Set ranges decomposition requirement.");
    app.add_option("-rb,--rangesBuilding", configuration.rangesBuildingRequired,
                   "Set ranges building requirement.");
    app.add_option("-po,--purificationOnly", configuration.purificationOnlyRequired,
                   "Set purification only requirement.");
    app.add_option("-d,--inputRecordsDelimiter", configuration.inputRecordsDelimiter,
                   "Set input records delimiter.");

    //  Presenter
    app.add_option("-hp,--hostsPrefix", configuration.hostsPrefix,
                   "Set host prefix added in an output.");
    app.add_option("-sp,--subnetsPrefix", configuration.subnetsPrefix,
                   "Set subnet prefix added in an output.");
    app.add_option("-rp,--rangesPrefix", configuration.rangesPrefix,
                   "Set range prefix added in an output.");
    app.add_option("-s,--suffix", configuration.suffix,
                   "Set record suffix added in an output.");

    //Other
    app.add_option("-o,--outputFilePath", configuration.inputDataFileURLs,
                   "Output file path.");
}
