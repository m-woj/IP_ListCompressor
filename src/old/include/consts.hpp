#ifndef CIDRBUILDER_CONSTS_HPP
#define CIDRBUILDER_CONSTS_HPP

#define ADDR_MIN_LENGTH 7
#define ADDR_MAX_LENGTH 15

#define SUBNET_MIN_LENGTH (ADDR_MIN_LENGTH + 2)
#define SUBNET_MAX_LENGTH (ADDR_MAX_LENGTH + 3)
#define SUBNET_SIGN '/'

#define RANGE_MIN_LENGTH (ADDR_MIN_LENGTH * 2 + 1)
#define RANGE_MAX_LENGTH (ADDR_MAX_LENGTH * 2 + 1)
#define RANGE_SIGN '-'

#define DEFAULT_DELIMITER "\n"
#define DEFAULT_SUFFIX "\n"

#endif //CIDRBUILDER_CONSTS_HPP