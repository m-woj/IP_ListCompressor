#pragma once


template<class SizeT>
class Host {
    SizeT value;

public:
    Host() = default;

    [[nodiscard]] static Host<SizeT> createFromInitialValue(SizeT initialValue) {
        return Host(initialValue);
    }

    [[nodiscard]] SizeT getValue() const {
        return value;
    }

    bool operator== (const Host<SizeT>& other) const {
        return this->getValue() == other.getValue();
    }

private:
    explicit Host(SizeT value): value(value) {};
};

