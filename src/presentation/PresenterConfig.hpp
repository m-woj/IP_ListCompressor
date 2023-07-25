#pragma once


struct PresenterConfig {
    char hostsPrefix[RECORD_DECORATOR_SIZE] = "";
    char subnetsPrefix[RECORD_DECORATOR_SIZE] = "";
    char rangesPrefix[RECORD_DECORATOR_SIZE] = "";
    char suffix[RECORD_DECORATOR_SIZE] = "";
};