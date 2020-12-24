//!  Copyright [2019] <Klaus de Freitas Dornsbach>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"  // Import LinkedList

namespace structures {

template<typename T>
//! lista linkada
class LinkedStack : private LinkedList<T> {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top();   // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);

        T& data();  // getter: info
        const T& data() const;  // getter-constante: info

        Node* next();  // getter: próximo
        const Node* next() const;  // getter-constante: próximo

        void next(Node* next);  // setter: próximo
     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

//! construtor padrao
template<typename T>
LinkedStack<T>::LinkedStack() : LinkedList<T>::LinkedList() {}

//! destrutor
template<typename T>
LinkedStack<T>::~LinkedStack() {
    LinkedList<T>::~LinkedList();
}

//! limpa a lista
template<typename T>
void LinkedStack<T>::clear() {
    LinkedList<T>::clear();
}

//! limpa a stack
template<typename T>
void LinkedStack<T>::push(const T& data) {
    LinkedList<T>::push_front(data);
}

//! retira e retorna o elemento do topo da lista
template<typename T>
T LinkedStack<T>::pop() {
    return LinkedList<T>::pop_front();
}

//! retorna o dado que está no topo da stack
template<typename T>
T &LinkedStack<T>::top() {
    return LinkedList<T>::at(0);
}

//! retorna se a lista está vazia ou nao
template<typename T>
bool LinkedStack<T>::empty() const {
    return LinkedList<T>::empty();
}

//! retorna o tamanho da lista
template<typename T>
std::size_t LinkedStack<T>::size() const {
    return LinkedList<T>::size();
}

}  // namespace structures

#endif
