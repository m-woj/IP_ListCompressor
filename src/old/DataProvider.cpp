#include "DataProvider.hpp"


std::vector<std::string_view> fetchRawRecords(const std::string& inputData, const std::string& delimiter);


DataProvider::DataProvider() : DataSource() {}


DataProvider::DataProvider(DataProviderConfig config) : DataSource(std::move(config.dataSourceConfig)) {}


std::vector<std::string_view> fetchRawRecords(const std::string& inputData, const std::string& delimiter) {
    size_t end = inputData.find(delimiter);
    size_t start = 0;

    std::vector<std::string_view> rawRecords;
    rawRecords.reserve(inputData.size() / 11); //Simple estimation

    auto emplace = [&](const auto& start, const auto& end){
        std::string_view record(inputData.data() + start, end - start);
        rawRecords.emplace_back(record);
    };

    while (end != std::string::npos) {
        emplace(start, end);
        start = end + delimiter.size();
        end = inputData.find(delimiter, start);
    }

    //To load last record if there was no delimiter in the end of file
    if (start < inputData.size()) {
        emplace(start, inputData.size());
    }

    rawRecords.shrink_to_fit();

    return rawRecords;
}


std::vector<std::string_view> DataProvider::getRawRecords(const std::string& content) const {
    return fetchRawRecords(content, config.recordsDelimiter);
}
