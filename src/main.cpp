#include "ConfigurationProvider.hpp"
#include "Compressor.hpp"
#include "DataProvider.hpp"
#include "OutputManager.hpp"


int main(int argc, const char* argv[]) {
    auto config = ConfigurationProvider(argc, argv);
    if (!config.isValid()) {
        config.printErrors();
        return 1;
    }

    if (config.isHelpCall()) {
        config.printHelpMessage();
        return 0;
    }

    auto dataProvider = DataProvider(config.getDataProviderConfig());
    auto content = dataProvider.getRawContent();
    auto rawRecords = dataProvider.getRawRecords(content);

    auto compressor = Compressor(rawRecords);

    auto om = OutputManager(config.getOutputManagerConfig());
    om.send(compressor.getSubnets());
    om.send(compressor.getHosts());

    compressor.printErrors(); //to std error

    return 0;
}
