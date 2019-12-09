#ifndef HASHSETEXCEPTION_H
#define HASHSETEXCEPTION_H

// STL IO
#include <iostream>
#include <ostream>

// STL Containers
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <stack>
#include <string>
#include <tuple>

// STL utils, memory managment and exceptions
#include <memory>
#include <utility>
#include <exception>

class HashSetException {
public:
    HashSetException() = default;
    inline HashSetException(const std::string& msg)
        : _msg(msg) {}

    inline std::string what() const {
        return _msg;
    }

protected:
    std::string _msg;
};

template<class Key>
class HashSetKeyRepeatedError : public HashSetException {
public:
    inline HashSetKeyRepeatedError(const std::string msg, const Key& key)
        : HashSetException(msg), _key(key) {}

    inline Key get_repeated_key() const {
        return _key;
    }

private:
    Key _key;
};

class HashSetEmptyError : public HashSetException {
public:
    inline HashSetEmptyError(const std::string& msg)
        : HashSetException(msg) {}
};

class HashSetInvalidIterator : public HashSetException {
public:
    inline HashSetInvalidIterator(const std::string& msg)
        : HashSetException(msg) {}
};

#endif // HASHSETEXCEPTION_H
