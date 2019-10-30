#ifndef List_HPP
#define List_HPP
 
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstddef>

#include <list.hpp>
 
template <class T>
class ListSet: protected List<T>{
public:
 
    typedef typename List<T>::iterator iterator;
 
    ListSet();
    ListSet(const ListSet<T>&);
    ~ListSet();
 
    ListSet<T>& operator=(const ListSet<T>&);
    void insert(const T&);
    bool empty() const;
    bool contains(const T&);
 
    iterator begin();
    iterator end();
};
 
template <class T>
ListSet<T>::ListSet() : List<T>() {}
 
template <class T>
ListSet<T>::ListSet(const ListSet<T>& other) : List<T>() {
    for(node<T>* pnode = other.head; pnode != NULL; pnode = pnode->next)
        insert(pnode->value);
}
 
template <class T>
ListSet<T>::~ListSet() {
    while(List<T>::head != NULL){
        node<T>* pnode = List<T>::head;
        List<T>::head = List<T>::head->next;
        delete pnode;
    }
}
 
template <class T>
ListSet<T>& ListSet<T>::operator=(const ListSet<T>& other) {
    List<T>::head = NULL;
        
    for(node<T>* pnode = other.head; pnode != NULL; pnode = pnode->next)
        push_back(pnode->value);
 
    return *this;
}
 
template <class T>
bool ListSet<T>::contains(const T& value){

    node<T>* pnode = List<T>::head;
    if (pnode == NULL){
        return false;
    }

    while(pnode){
        if (pnode->value == value){
            return true;
        }
        pnode = pnode->next;
    }

    return false;
}

template <class T>
void ListSet<T>::insert(const T& value){
    node<T>* pnode = List<T>::head;
 
    if (!contains(value)){
        for(auto it = begin(); it != end(); it++){
            if (value <= *(it+1) && value >= *it)
                
        }

        std::cout << "Try insert\n";
        ListSet<T>::push_back(value);
    }
}


 
template <class T>
bool ListSet<T>::empty() const {
    return List<T>::empty();
}
 
template <class T>
typename ListSet<T>::iterator ListSet<T>::begin() {
    return List<T>::begin();
}
 
template <class T>
typename ListSet<T>::iterator ListSet<T>::end() {
    return List<T>::end();
}

#endif