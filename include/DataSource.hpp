#ifndef CIDRBUILDER_DATASOURCE_HPP
#define CIDRBUILDER_DATASOURCE_HPP


#include <string>
#include <sstream>
#include <vector>

#include "DataSourceConfig.hpp"


class DataSource {
protected:
    DataSourceConfig config{};

public:
    DataSource() = default;

    explicit DataSource(DataSourceConfig newConfig);

    void set(DataSourceConfig newConfig);

    std::string getRawContent();
};

#endif //CIDRBUILDER_DATASOURCE_HPP
