#include <sstream>

#include <gtest/gtest.h>

#include "../ConverterBuilder.hpp"


TEST(Converter, purificationTest) {
    auto converter = ConverterBuilder()
            .setPurificationOnlyRequirement(true)
            .setInputRecordsDelimiter(',')
            .getConverter<uint32_t>();
    std::stringstream inputStream = std::stringstream() << "0.0.0.1,0.0.0.2,0.0.0.1";
    converter.addDataFromStream(inputStream);
    converter.convert();

    ASSERT_EQ(converter.getConvertedHosts().size(), 2);
}
