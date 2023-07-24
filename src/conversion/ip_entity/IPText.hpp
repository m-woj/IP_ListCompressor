#pragma once


class IPText {
    virtual std::ostream& operator<<(std::ostream &out) = 0;

protected:
    virtual ~IPText() = default;
};
