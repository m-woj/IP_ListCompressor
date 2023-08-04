#pragma once

#define APP_DESCRIPTION \
    "This program is designed to conduct converting operations " \
    "on lists of IP hosts, subnets and ranges. It gives the possibility to validate " \
    "and compress such feeds into one."

#define RANGE_DELIMITER_SIGN '-'
#define SUBNET_AND_MASK_DELIMITER '/'

#define DEFAULT_SUFFIX "\n"
#define DEFAULT_PREFIX ""

#define IPV4_MAX_LENGTH 15
#define IPV6_MAX_LENGTH 39

#define RECORD_DECORATOR_MAX_LENGTH 31
#define RECORDS_DELIMITER_MAX_LENGTH 31


#define IPV4_SIZE (IPV4_MAX_LENGTH + 1)
#define IPV6_SIZE (IPV6_MAX_LENGTH + 1)

#define IPV4_SUBNET_MAX_LENGTH (IPV4_MAX_LENGTH + 3)
#define IPV4_SUBNET_SIZE (IPV4_SUBNET_MAX_LENGTH + 1)

#define IPV4_RANGE_MAX_LENGTH (2 * IPV4_MAX_LENGTH + 1)
#define IPV4_RANGE_SIZE (IPV4_RANGE_MAX_LENGTH + 1)

#define IPV6_SUBNET_MAX_LENGTH (IPV6_MAX_LENGTH + 4)

#define IPV6_RANGE_MAX_LENGTH (2 * IPV6_MAX_LENGTH + 1)
#define IPV6_RANGE_SIZE (IPV6_RANGE_MAX_LENGTH + 1)

#define IP_TEXT_SIZE IPV6_RANGE_SIZE

#define RECORD_DECORATOR_SIZE (RECORD_DECORATOR_MAX_LENGTH + 1)
#define RECORDS_DELIMITER_SIZE (RECORDS_DELIMITER_MAX_LENGTH + 1)

#define IP_RANGE_SIZE (IP_RANGE_MAX_LENGTH + 1)
