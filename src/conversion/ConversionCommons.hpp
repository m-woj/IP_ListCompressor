#pragma once

#include <vector>
#include <memory>

#include "../common/ip_entity/Host.hpp"
#include "../common/ip_entity/Range.hpp"
#include "../common/ip_entity/Subnet.hpp"

#include "../common/logging/Logger.hpp"


template<class SizeT>
struct ConversionCommons {
    std::shared_ptr<Logger> logger = std::make_unique<Logger>();

    std::vector<Host<SizeT>> hosts {};
    std::vector<Range<SizeT>> ranges {};
    std::vector<Subnet<SizeT>> subnets {};
};