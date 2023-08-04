#include <CLI/CLI.hpp>

#include <iostream>

#include "validators.hpp"
#include "ConfigurationProvider.hpp"


const static PrefixMaxLengthValidator prefixMaxLengthValidator;
const static SuffixMaxLengthValidator suffixMaxLengthValidator;
const static RecordsDelimiterMaxLengthValidator recordsDelimiterMaxLengthValidator;


void setOptions(CLI::App& app, Configuration& configuration);
void setDataProviderOptions(CLI::App& app, Configuration& configuration);
void setDataConverterOptions(CLI::App& app, Configuration& configuration);
void setPresenterOptions(CLI::App& app, Configuration& configuration);
void setOtherOptions(CLI::App& app, Configuration& configuration);


ConfigurationProvider ConfigurationProvider::createWithInputArguments(int argc, const char* argv[]) {
    return {argc, argv};
}


ConfigurationProvider::ConfigurationProvider(int argc, const char* argv[]) {
    CLI::App app {
            "This program is designed to conduct converting operations "
            "on lists of IP hosts, subnets and ranges. It gives the possibility to validate "
            "and compress such feeds into one."
    };

    setOptions(app, configuration);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        isValid = false;
        std::cerr << e.what();
    }
}

std::optional<std::reference_wrapper<const Configuration>> ConfigurationProvider::tryGetConfiguration() const {
    return isValid
        ? std::optional<std::reference_wrapper<const Configuration>>{configuration}
        : std::nullopt;
}


void setOptions(CLI::App& app, Configuration& configuration) {
    setDataProviderOptions(app, configuration);
    setDataConverterOptions(app, configuration);
    setPresenterOptions(app, configuration);
    setOtherOptions(app, configuration);
}


void setDataProviderOptions(CLI::App& app, Configuration& configuration) {
    app.add_option("-i,--inputDataFiles", configuration.inputDataFileURLs,
                   "A list of paths to files containing input data.");
}


void setDataConverterOptions(CLI::App& app, Configuration& configuration) {
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
                   "Set input records delimiter.")
                   ->check(recordsDelimiterMaxLengthValidator);
}


void setPresenterOptions(CLI::App& app, Configuration& configuration) {
    app.add_option("-hp,--hostsPrefix", configuration.hostsPrefix,
                   "Set host prefix added in an output.")
                   ->check(prefixMaxLengthValidator);
    app.add_option("-sp,--subnetsPrefix", configuration.subnetsPrefix,
                   "Set subnet prefix added in an output.")
                    ->check(prefixMaxLengthValidator);
    app.add_option("-rp,--rangesPrefix", configuration.rangesPrefix,
                   "Set range prefix added in an output.")
                    ->check(prefixMaxLengthValidator);

    app.add_option("-s,--suffix", configuration.suffix,
                   "Set record suffix added in an output.")
                    ->check(suffixMaxLengthValidator);
}


void setOtherOptions(CLI::App& app, Configuration& configuration) {
    app.add_option("-o,--outputFilePath", configuration.inputDataFileURLs,
                   "Output file path.")
            ->check(CLI::Validator(CLI::NonexistentPath));
}
