#include <CLI/CLI.hpp>

#include <iostream>

#include "validators.hpp"
#include "transformers.hpp"
#include "ConfigurationProvider.hpp"


const static PrefixMaxLengthValidator prefixMaxLengthValidator;
const static SuffixMaxLengthValidator suffixMaxLengthValidator;
const static RecordsDelimiterMaxLengthValidator recordsDelimiterMaxLengthValidator;


void setOptions(CLI::App& app, Configuration& configuration);
void setDataProviderOptions(CLI::App& app, Configuration& configuration);
void setDataConverterOptions(CLI::App& app, Configuration& configuration);
void setPresenterOptions(CLI::App& app, Configuration& configuration);
void setOtherOptions(CLI::App& app, Configuration& configuration);


ConfigurationProvider ConfigurationProvider::createFromInputArguments(int argc, const char* argv[]) {
    return {argc, argv};
}


ConfigurationProvider::ConfigurationProvider(int argc, const char* argv[]) {
    CLI::App app {APP_DESCRIPTION};
    setOptions(app, configuration);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
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
    app.add_flag("-m,--multithreading", configuration.multithreadingRequired,
                   "Enable multithreading.");
    app.add_flag("-c,--compress", configuration.compressionRequired,
                   "Compress feeds.");
    app.add_flag("--decomposeRanges", configuration.rangesDecompositionRequired,
                   "Decompose ranges to hosts and subnets.");
    app.add_flag("--buildRanges", configuration.rangesBuildingRequired,
                   "Build ranges from hosts and subnets.");
    app.add_flag("--validationOnly", configuration.purificationOnlyRequired,
                   "Validate (delete invalid records) and merge only.");

    app.add_option("-d,--inputRecordsDelimiter", configuration.inputRecordsDelimiter,
                   "Set input records delimiter.")
            ->check(recordsDelimiterMaxLengthValidator)
            ->transform(rawSpecialCharactersToWorkingSpecialCharacters);
}


void setPresenterOptions(CLI::App& app, Configuration& configuration) {
    app.add_option("--hostsPrefix", configuration.hostsPrefix,
                   "Set host prefix added in an output.")
            ->check(prefixMaxLengthValidator)
            ->transform(rawSpecialCharactersToWorkingSpecialCharacters);
    app.add_option("--subnetsPrefix", configuration.subnetsPrefix,
                   "Set subnet prefix added in an output.")
            ->check(prefixMaxLengthValidator)
            ->transform(rawSpecialCharactersToWorkingSpecialCharacters);
    app.add_option("--rangesPrefix", configuration.rangesPrefix,
                   "Set range prefix added in an output.")
            ->check(prefixMaxLengthValidator)
            ->transform(rawSpecialCharactersToWorkingSpecialCharacters);

    app.add_option("--suffix", configuration.suffix,
                   "Set record suffix added in an output.")
            ->check(suffixMaxLengthValidator)
            ->transform(rawSpecialCharactersToWorkingSpecialCharacters);
}


void setOtherOptions(CLI::App& app, Configuration& configuration) {
    app.add_option("-o,--outputFilePath", configuration.inputDataFileURLs,
                   "Output file path.")
                    ->check(CLI::Validator(CLI::NonexistentPath));
}
