#pragma once 

#include <stdexcept>
#include <cstddef>

#include "exceptions.hpp"

template <class T>
class Node{
    public:
        Node(const T& value, Node<T>* next) :
                 value(value), next(next) {};
        
        T value;
        Node* next;
};

template <class T>
class ListIterator;

template <class T>
class List {

public:
    typedef ListIterator<T> iterator;
    typedef const ListIterator<T> const_iterator;
        
    List();
    List(const List<T>&);
    ~List();
 
    void push_back(const T&);
    void push_front(const T&);
    void insert(iterator, const T&);
 
    T pop_front();
    T pop_back();

    void clear();
    iterator erase(iterator);
 
    bool empty() const;
    
    size_t size() const;
 
    List<T>& operator=(const List<T>&);
 
    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

protected:
    Node<T>* head;
    size_t size_;
};


template <class T>
List<T>::List() : head(nullptr), size_(0) {};

template <class T>
List<T>::List(const List<T>& other) : head(nullptr), size_(other.size()){
    for(auto it = other.cbegin(); it != other.cend(); it++)
        push_back(*it);
}

template <class T>
List<T>::~List(){
    clear();
};

template <class T>
void List<T>::push_back(const T& value) {
    auto pnode = new Node<T>(value, nullptr);

    if (head == nullptr){
        head = pnode;
    }
    else{
        // Find last element in list
        auto current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = pnode;
    }

    size_ += 1;
}

template <class T>
void List<T>::push_front(const T& value){
    auto pnode = new Node<T>(value, head);
    head = pnode;
    size_ += 1;
}

template <class T>
void List<T>::insert(iterator it, const T& value){
    if (head == nullptr || it == nullptr){
        push_back(value);
        return;
    }
    auto current = head;
    while(!(current->value == *it))
        current = current->next;

    if (head->next == nullptr){
        auto temp = head;
        head = current;
        head->next = temp;
        return;
    }
    if (head == current){
        auto pnode = new Node<T>(value, head);
        head = pnode;
        return;
    }

    auto pnode = new Node<T>(value, current);
    auto current1 = head;
    while(!(current1->next->value == *it))
        current1 = current1->next;
    current1->next = pnode;
    
}


template <class T>
T List<T>::pop_back() {
    // Empty list
    if (head == nullptr){
        throw DeleteFromEmptyList<Node<T>*>(head);
    }
    else{
        // One element in list
        if (head->next == nullptr){
            return pop_front();
        }
        else{
            // Find penultimate element
            auto current = head;
            while(current->next->next != nullptr){
                current = current->next;
            }

            // pnode - last element
            auto pnode = current->next;
            T value = pnode->value;

            delete current->next;
            current->next = nullptr;
            
            size_ -= 1;
            return value;
        }
    }
}

template <class T>
T List<T>::pop_front() {
    if (head == nullptr){
        throw DeleteFromEmptyList<Node<T>*>(head);
    }
    else {
        T value = head->value;
        auto tmp = head->next;
        delete head;
        head = tmp;
        size_ -= 1;

        return value;
    }
}


template <class T>
bool List<T>::empty() const {
    return size_ == 0;
}

template <class T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator it){
    if (List<T>::empty()){
        throw DeleteFromEmptyList<Node<T>*>(head);
    }
    
    if (head->value == *it && size_ == 1){
        pop_front();
        return iterator();
    }
    if (head->value == *it && size_ > 1){
        auto temp = head;
        pop_front();
        head = temp->next;
        return iterator(head);
    }

    auto current = head;
    while(!(current->next->value == *it))
        current = current->next;
    
    current->next = current->next->next;
    return iterator(current->next);
}


template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    head = nullptr;
    size_ = other.size();
 
    for(auto it = other.begin(); it != other.end(); it++)
        push_back(*it);
 
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::begin() const {
    return iterator(head);
}

template <class T>
typename List<T>::iterator List<T>::end() const {
    return iterator();
}

template <class T>
typename List<T>::const_iterator List<T>::cbegin() const {
    return const_iterator(head);
}

template <class T>
typename List<T>::const_iterator List<T>::cend() const {
    return const_iterator();
}

template <class T>
size_t List<T>::size() const{
    return size_;
}

template <class T>
void List<T>::clear() {
    Node<T>* current = head;
    while( current != 0 ) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = 0;
}


 
template <class T>
class ListIterator {
private:
    friend class List<T>;

    Node<T>* pnode;

    void validateIterator() const;
    bool isValidIterator() const;

public:
    ListIterator(Node<T>*); 
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;
    
    ListIterator();
    ListIterator(const ListIterator<T>&);

 
    ListIterator& operator=(const ListIterator<T>&);
 
    bool operator==(const ListIterator<T>&) const;
    bool operator!=(const ListIterator<T>&) const;
 
    T& operator* ();
    T* operator-> ();
 
    ListIterator<T>& operator++();
    ListIterator<T> operator++(int);
 
};
 
template <class T>
ListIterator<T>::ListIterator(Node<T>* p) : pnode(p) {}
 
template <class T>
ListIterator<T>::ListIterator() : pnode(nullptr) {}
 
template <class T>
ListIterator<T>::ListIterator(const ListIterator<T>& other) : pnode(other.pnode) {}
 
template <class T>
ListIterator<T>& ListIterator<T>::operator=(const ListIterator<T>& other){
    pnode = other.pnode;
}
 
template <class T>
bool ListIterator<T>::operator==(const ListIterator<T>& other) const {
    return pnode == other.pnode;
}
 
template <class T>
bool ListIterator<T>::operator!= (const ListIterator<T>& other) const{
    return !(*this == other);
}
 
template <class T>
T& ListIterator<T>::operator*(){
    validateIterator();
    return pnode->value;
}
 
template <class T>
T* ListIterator<T>::operator->(){
    validateIterator();
    return &(pnode->value);
}
 
template <class T>
ListIterator<T>& ListIterator<T>::operator++(){
    validateIterator(); 
    pnode = pnode->next;
    return *this;
}
 
template <class T>
ListIterator<T> ListIterator<T>::operator++(int){
    validateIterator();
    ListIterator<T> tmp = *this;
    ++(*this);
    return tmp;
}
 
template <class T>
void ListIterator<T>::validateIterator() const {
    if(!isValidIterator())
        throw InvalidIterator<T>(this->pnode->value);
}
 
template <class T>
bool ListIterator<T>::isValidIterator() const {
    return pnode != nullptr;
}
