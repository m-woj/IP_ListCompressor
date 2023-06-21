#ifndef CIDRLINKER_RECORD_HPP
#define CIDRLINKER_RECORD_HPP


#include <string_view>
#include <optional>


class Record {
protected:
    std::optional<std::string_view> sourceStringForm{};

public:
    [[nodiscard]] virtual std::string toString() const = 0;

    bool hasValidSourceForm() {
        return sourceStringForm.has_value();
    }

    virtual ~Record() = default;
};

#endif //CIDRLINKER_RECORD_HPP
