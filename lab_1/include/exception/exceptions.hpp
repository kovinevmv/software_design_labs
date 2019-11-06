# pragma once

#include <ostream>


class Exception {
public:
    friend std::ostream &operator<<(std::ostream &, const Exception &);
    virtual ~Exception() = default;

protected:
    virtual std::ostream& info(std::ostream &o) const = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Exception &ex) {
    return ex.info(os);
}

class DeleteFromEmptyList: public Exception {
public:
    explicit DeleteFromEmptyList(){};
protected:
    std::ostream& info(std::ostream &o) const override {
        return o << "Delete from elemet from empty list";
    }
};


template <typename T>
class InvalidIterator: public Exception {
public:
    InvalidIterator(T iterator) : iterator(iterator) {}

protected:
    std::ostream& info(std::ostream &o) const override {
        return o << "InvalidIterator: iterator on " << iterator << " is null";
    }

private:
    T iterator;
};