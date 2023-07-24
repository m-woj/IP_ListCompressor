#pragma once


#include "consts.hpp"
#include "RangeAbstract.hpp"


template<class SizeT>
class HostAbstract : public RangeAbstract<SizeT> {
    static char prefix[RECORD_DECORATOR_SIZE];

public:
    static void setPrefix(const char* newPrefix) {
        assert(std::strlen(newPrefix) < RECORD_DECORATOR_MAX_LENGTH);

        std::strcpy(prefix, newPrefix);
    }

protected:
    explicit HostAbstract(SizeT value) : RangeAbstract<SizeT>(value, value) {};
};


template<class SizeT>
char HostAbstract<SizeT>::prefix[RECORD_DECORATOR_SIZE] = DEFAULT_PREFIX;
