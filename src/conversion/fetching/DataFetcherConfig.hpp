#pragma once

#include <vector>

#include "../../consts.hpp"

#include "../../common/ip_entity/Host.hpp"
#include "../../common/ip_entity/Range.hpp"
#include "../../common/ip_entity/Subnet.hpp"

#include "../../common/logging/Logger.hpp"


template<class SizeT>
struct DataFetcherConfig {
    std::vector<Host<SizeT>>& hosts;
    std::vector<Range<SizeT>>& ranges;
    std::vector<Subnet<SizeT>>& subnets;

    char recordsDelimiter {'\n'};

    Logger& logger;
};