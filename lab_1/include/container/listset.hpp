#pragma once
 
#include <algorithm>

#include <list.hpp>
 
template <class T>
class ListSet{
public:
    typedef typename List<T>::iterator iterator;
    typedef typename List<T>::const_iterator const_iterator;
    
    ListSet();
    ListSet(const ListSet<T>&);
    ~ListSet();

    ListSet<T>& operator=(const ListSet<T>&);
    void insert(const T&);
    bool empty() const;
    void clear();


    iterator find(const T&);
    const_iterator find(const T&) const;

    size_t count(const T&) const;
    size_t size() const;
    
    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    List<T> list;
};


template <class T>
ListSet<T>::ListSet() : list() {};

template <class T>
ListSet<T>::ListSet(const ListSet<T>& other) : list() {
    for(auto it = other.begin(); it != other.end(); it++)
        list.push_back(*it);
}

template <class T>
ListSet<T>::~ListSet() {
    clear();
}

template <class T>
ListSet<T>& ListSet<T>::operator=(const ListSet<T>& other) {
    for(auto it = other.begin(); it != other.end(); it++)
        list.push_back(*it);

    return *this;
}


template <class T>
void ListSet<T>::insert(const T& value){
    if (list.empty()){
        list.push_back(value);
        return;
    }    
    if (find(value) == nullptr){
        for (auto it = list.begin(); it != list.end(); it++){
            if (*it > value){
                list.insert(it, value);
                return;
            }
        }
        list.push_back(value);
    }
    
}

template <class T>
bool ListSet<T>::empty() const {
    return list.empty();
}

template <class T>
void ListSet<T>::clear() {
    list.clear();
}

template <class T>
typename ListSet<T>::iterator ListSet<T>::find(const T& value){
    for (auto it = list.begin(); it != list.end(); it++){
        if (*it == value){
            return it;
        }
    }
    return nullptr;
}

template <class T>
typename ListSet<T>::const_iterator ListSet<T>::find(const T& value) const{
    for (auto it = list.cbegin(); it != list.cend(); it++){
        if (*it == value){
            return it;
        }
    }
    return nullptr;
}

template <class T>
size_t ListSet<T>::count(const T& value) const{
    size_t count = 0;
    for (auto it = list.cbegin(); it != list.cend(); it++){
        if (*it == value){
            count += 1;
        }
    }
    return count;
}

template <class T>
size_t ListSet<T>::size() const{
    return list.size();
}

template <class T>
typename ListSet<T>::iterator ListSet<T>::begin() {
    return list.begin();
}
 
template <class T>
typename ListSet<T>::iterator ListSet<T>::end() {
    return list.end();
}

template <class T>
typename ListSet<T>::const_iterator ListSet<T>::cbegin() const{
    return list.cbegin();
}
 
template <class T>
typename ListSet<T>::const_iterator ListSet<T>::cend() const{
    return list.cend();
}


