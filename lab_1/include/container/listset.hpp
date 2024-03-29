#pragma once
 
#include <algorithm>

#include <list.hpp>
 
template <class T>
class ListSet : protected List<T> {
public:
    typedef typename List<T>::iterator iterator;
    typedef typename List<T>::const_iterator const_iterator;
    
    ListSet();
    ListSet(const ListSet<T>&);
    ~ListSet();

    ListSet<T>& operator=(ListSet<T>&);
    void insert(const T&);
    bool empty() const;

    iterator erase(iterator);
    void clear();

    iterator find(const T&);
    const_iterator find(const T&) const;

    ListSet<T>& operator+(const ListSet<T>& other);
    ListSet<T>& operator-(const ListSet<T>& other);

    ListSet<T> intersectionWith(const ListSet<T>& other);

    bool operator==(const ListSet<T>& other);
    bool operator!=(const ListSet<T>& other);

    size_t count(const T&) const;
    size_t size() const;
    
    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;
};


template <class T>
ListSet<T>::ListSet() : List<T>() {};

template <class T>
ListSet<T>::ListSet(const ListSet<T>& other) : List<T>() {
    for(auto it = other.begin(); it != other.end(); it++)
        List<T>::push_back(*it);
}

template <class T>
ListSet<T>::~ListSet() {
    clear();
}

template <class T>
ListSet<T>& ListSet<T>::operator=(ListSet<T>& other) {
    for(auto it = other.begin(); it != other.end(); it++)
        List<T>::push_back(*it);

    return *this;
}


template <class T>
void ListSet<T>::insert(const T& value){
    if (this->empty()){
        List<T>::push_back(value);
        return;
    }

    auto iteratorOnFoundElement = this->find(value);
    if (iteratorOnFoundElement == nullptr){
        for (auto it = begin(); it != end(); it++){
            if (*it > value){
                List<T>::insert(it, value);
                return;
            }
        }
        List<T>::push_back(value);
    }
}

template <class T>
typename ListSet<T>::iterator ListSet<T>::erase(ListSet<T>::iterator it){
    return List<T>::erase(it);
}

template <class T>
bool ListSet<T>::empty() const {
    return List<T>::empty();
}

template <class T>
void ListSet<T>::clear() {
    List<T>::clear();
}

template <class T>
typename ListSet<T>::iterator ListSet<T>::find(const T& value){
    for (auto it = begin(); it != end(); it++){
        if (*it == value){
            return it;
        }
    }
    return nullptr;
}

template <class T>
typename ListSet<T>::const_iterator ListSet<T>::find(const T& value) const{
    for (auto it = cbegin(); it != cend(); it++){
        if (*it == value){
            return it;
        }
    }
    return nullptr;
}

template <class T>
size_t ListSet<T>::count(const T& value) const{
    size_t count = 0;
    for (auto it = cbegin(); it != cend(); it++){
        if (*it == value){
            count += 1;
        }
    }
    return count;
}

template <class T>
size_t ListSet<T>::size() const{
    return List<T>::size();
}

template <class T>
typename ListSet<T>::iterator ListSet<T>::begin() const {
    return List<T>::begin();
}
 
template <class T>
typename ListSet<T>::iterator ListSet<T>::end() const {
    return List<T>::end();
}

template <class T>
typename ListSet<T>::const_iterator ListSet<T>::cbegin() const{
    return List<T>::cbegin();
}
 
template <class T>
typename ListSet<T>::const_iterator ListSet<T>::cend() const{
    return List<T>::cend();
}

template <class T>
ListSet<T>& ListSet<T>::operator+(const ListSet<T>& other){
    for (auto it = other.begin(); it != other.end(); it++){
        this->insert(*it);
    }
    return *this;
}

template <class T>
ListSet<T>& ListSet<T>::operator-(const ListSet<T>& other){
    for (auto it = other.begin(); it != other.end(); it++){
        auto iteratorOnFoundValue = this->find(*it);
        if (iteratorOnFoundValue != nullptr){
            this->erase(iteratorOnFoundValue);
        }
    }
    return *this;
}

template <typename T>
ListSet<T> ListSet<T>::intersectionWith(const ListSet<T>& other){
    return *this - (*this - other);
}

template <class T>
bool ListSet<T>::operator==(const ListSet<T>& other){
    if (this->size() != other.size()){
        return false;
    }

    // A=B <=> A ⊆ B, B ⊆ A <=> ∀k∈A k⊂B && ∀k∈B k⊂A 
    for (auto it = other.begin(); it != other.end(); it++){
        if(this->find(*it) == nullptr)
            return false;
    }
    for (auto it = this->begin(); it != this->end(); it++){
        if(other.find(*it) == nullptr)
            return false;
    }
    return true;
}

template <class T>
bool ListSet<T>::operator!=(const ListSet<T>& other){
    return !(*this == other);
}
