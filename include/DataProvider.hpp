#ifndef CIDRBUILDER_DATAPROVIDER_HPP
#define CIDRBUILDER_DATAPROVIDER_HPP

#include <string_view>
#include <vector>

#include "DataSource.hpp"
#include "DataProviderConfig.hpp"


class DataProvider: public DataSource {
    DataProviderConfig config{};

public:
    DataProvider();

    explicit DataProvider(DataProviderConfig config);

    [[nodiscard]] std::vector<std::string_view> getRawRecords(const std::string& content) const;
};


#endif //CIDRBUILDER_DATAPROVIDER_HPP
