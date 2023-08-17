#include <sstream>
#include <vector>

#include "../../../common/ip_entity/ip_entity.hpp"
#include "../../../common/logging//Logger.hpp"

#include "../DataFetcher.hpp"


int main() {
    std::vector<Host<uint32_t>> hosts = std::vector<Host<uint32_t>>();
    std::vector<Subnet<uint32_t>> subnets = std::vector<Subnet<uint32_t>>();
    std::vector<Range<uint32_t>> ranges = std::vector<Range<uint32_t>>();

    auto logger = Logger();
    auto dfConfig = DataFetcherConfig<uint32_t>{
            hosts, ranges, subnets, ',', logger};
    auto df = DataFetcher<uint32_t>::createFromDataFetcherConfig(dfConfig);
    auto input = std::stringstream() << "test";
    df.fetch(input);
}
