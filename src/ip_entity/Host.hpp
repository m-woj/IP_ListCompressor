#pragma once


template<class SizeT>
class Host {
    SizeT value;

public:
    [[nodiscard]] static Host<SizeT> createFromInitialValue(SizeT initialValue) {
        return Host(initialValue);
    }

    [[nodiscard]] SizeT getValue() const {
        return value;
    }

private:
    explicit Host(SizeT value): value(value) {};
};
