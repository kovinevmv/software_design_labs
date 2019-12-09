#ifndef HASH_H
#define HASH_H

#include "hashsetexception.h"

#include <list>

template<class Key>
class HashSetIterator;

template<
        class Key,
        class Hash = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
        >
class HashSet
{
public:
    using iterator = HashSetIterator<Key>;
    friend class HashSetIterator<Key>;

    inline HashSet()
        : _storage(_storage_size) {}

    ~HashSet() = default;

    inline void insert(const Key& value) {
        const auto hash = _hash_fun(value);
        const auto index = hash % _storage_size;

        if (_storage[index].empty()) {
            _storage[index].push_back(value);
            _num_buckets++;
            _num_elements++;
        } else {
            for (const auto& elem : _storage[index]) {
                if (_key_equal(elem, value)) {
                    throw HashSetKeyRepeatedError<Key>("key repeated", value);
                }
            }

            _storage[index].push_back(value);
            _num_elements++;
        }

        if (_num_elements / _num_buckets > _max_load_factor) {
            _storage_size *= _increase_storage_size_factor;
            _num_buckets = 0;
            std::vector<std::list<Key>> tmp_storage(_storage_size);

            for (const auto& bucket : _storage) {
                for (const auto& elem : bucket) {
                    const auto hash = _hash_fun(elem);
                    const auto index = hash % _storage_size;

                    if (tmp_storage[index].empty()) {
                        _num_buckets++;
                    }

                    _storage[index].push_back(elem);
                }
            }

            _storage = std::move(tmp_storage);
        }
    }

    inline iterator find(const Key& value) {
        if (empty()) {
            throw HashSetEmptyError("hash set is empty");
        }

        const auto hash = _hash_fun(value);
        const auto index = hash % _storage_size;

        auto& bucket = _storage[index];

        for (auto bucket_it = bucket.begin(); bucket_it != bucket.end(); bucket_it++) {
            if (_key_equal(*bucket_it, value)) {
                auto storage_it = _storage.begin();
                std::advance(storage_it, index);

                return iterator(storage_it, _storage.end(), bucket_it, bucket.end(), false);
            }
        }

        return iterator();
    }

    inline void remove(const Key& key) {
        if (empty()) {
            throw HashSetEmptyError("hash set is empty");
        }

        const auto hash = _hash_fun(key);
        const auto index = hash % _storage_size;

        auto& bucket = _storage[index];

        for (auto bucket_it = bucket.begin(); bucket_it != bucket.end(); bucket_it++) {
            if (_key_equal(*bucket_it, key)) {
                bucket.erase(bucket_it);
                _num_elements--;
                if (bucket.empty()) {
                    _num_buckets--;
                }
            }
        }
    }

    inline void clear() {
        _storage.clear();
        _num_buckets = _num_elements = 0;
        _storage_size = _default_storage_size;
        _storage.resize(_storage_size);
    }

    inline std::size_t size() const {
        return _num_elements;
    }

    inline bool empty() const {
        return _num_elements == 0;
    }

    inline iterator begin() {
        for (auto it = _storage.begin(); it != _storage.end(); it++) {
            if (!it->empty()) {
                auto& bucket = *it;

                return iterator(it, _storage.end(), bucket.begin(), bucket.end(), false);
            }
        }

        return iterator();
    }

    inline iterator end() {
        return iterator();
    }

private:
    using bucket_t = std::list<Key>;
    using storage_t = std::vector<bucket_t>;

    static inline std::size_t _max_load_factor = 5;
    static inline std::size_t _increase_storage_size_factor = 2;
    static inline std::size_t _default_storage_size = 100;

    std::size_t _storage_size = _default_storage_size;
    std::size_t _num_elements = 0;
    std::size_t _num_buckets = 0;
    std::vector<std::list<Key>> _storage;

    Hash _hash_fun;
    KeyEqual _key_equal;
};

template<class Key>
class HashSetIterator
{
public:
    friend class HashSet<Key>;

    inline HashSetIterator()
        : _empty(true) {}

    inline Key& operator*() {
        if (_empty) {
            throw HashSetInvalidIterator("invalid iterator");
        }

        return *_bucket_begin;
    }

    inline Key* operator->() {
        if (_empty) {
            throw HashSetInvalidIterator("invalid iterator");
        }

        return &(*_bucket_begin);
    }

    inline HashSetIterator operator++(int) {
        if (_bucket_begin != _bucket_end) {
            _bucket_begin++;
        }

        if (_bucket_begin == _bucket_end) {
            while (_storage_begin != _storage_end) {
                _storage_begin++;

                if (_storage_begin != _storage_end) {
                    auto& bucket = *_storage_begin;

                    if (!bucket.empty()) {
                        _bucket_begin = bucket.begin();
                        _bucket_end = bucket.end();

                        break;
                    }
                }
            }

            if (_bucket_begin == _bucket_end) {
                _empty = true;
            }
        }

        return *this;
    }

    template<class T>
    inline friend bool operator==(const HashSetIterator<T>& lhs, const HashSetIterator<T>& rhs);

    template<class T>
    inline friend bool operator!=(const HashSetIterator<T>& lhs, const HashSetIterator<T>& rhs);

private:

    using storage_iterator_t = typename HashSet<Key>::storage_t::iterator;
    using bucket_iterator_t = typename HashSet<Key>::bucket_t::iterator;

    inline HashSetIterator(storage_iterator_t storage_begin, storage_iterator_t storage_end,
                           bucket_iterator_t bucket_begin, bucket_iterator_t bucket_end,
                           bool empty)
        : _storage_begin(storage_begin), _storage_end(storage_end),
          _bucket_begin(bucket_begin), _bucket_end(bucket_end),
          _empty(empty) {}

    storage_iterator_t _storage_begin;
    storage_iterator_t _storage_end;

    bucket_iterator_t _bucket_begin;
    bucket_iterator_t _bucket_end;

    bool _empty;
};

template<class T>
inline bool operator==(const HashSetIterator<T>& lhs, const HashSetIterator<T>& rhs) {
    if (lhs._empty && rhs._empty) {
        return true;
    } else if (lhs._empty && !rhs._empty || !lhs._empty && rhs._empty) {
        return false;
    } else {
        return (lhs._bucket_begin  == rhs._bucket_begin  &&
                lhs._bucket_end    == rhs._bucket_end	 &&
                lhs._storage_begin == rhs._storage_begin &&
                lhs._storage_end   == rhs._storage_end
                );
    }
}

template<class T>
inline bool operator!=(const HashSetIterator<T>& lhs, const HashSetIterator<T>& rhs) {
    return !(lhs == rhs);
}

#endif // HASH_H
