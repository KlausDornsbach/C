//! Copyright [2019] <Klaus de Freitas Dornsbach>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! fila linkada
class LinkedQueue {
 public:
    LinkedQueue() {}
    ~LinkedQueue() {
        clear();
    }
    //! limpar
    void clear() {
        Node *actual, *previous;
        actual = head;
        while (actual != nullptr) {
            previous = actual;
            actual = actual->next();
            delete previous;
        }
        size_ = 0u;
        head = nullptr;
        tail = nullptr;
    }
    //!  enfilerar
    void enqueue(const T& data) {
        Node *novo_node = new Node(data);  // ! crio novo elemento
        if (empty()) {                     // ! se lista vazia
            head = novo_node;              // ! seto o head pro novo elemento
            tail = novo_node;
        } else {                           // ! se nao
            tail->next(novo_node);  // ! seto o ponteiro do penultimo pro novo
        }                           // ! ultimo
        tail = novo_node;  // ! seto o elemento de tail pro novo
        ++size_;           // ! aumento tamanho da lista
    }
    //! desenfilerar
    T dequeue() {
        //  ! condição pra haver retirada de elemento da fila: exitir nodo
        if (empty()) {
            throw std::out_of_range("nao ha elementos na fila");
        } else {
            T retorno;              // ! pra armazenar o dado do elemento retira
            Node *node_sai = head;  // ! ponteiro pro primeiro elemento da fila
            head = head->next();    // ! seto o head pro segundo elemento
            if (size_ == 1) {
                tail = nullptr;
            }
            retorno = node_sai->data();  // ! coloco o dado
            delete node_sai;        // ! deleto o nodo
            size_--;                // ! diminuo o tamanho da fila
            return retorno;  // ! retorno nodo que saiu
        }
    }
    //! primeiro dado
    T& front() const {
        if (empty()) {
            throw std::out_of_range("sem elementos na lista");
        }
        return head->data();
    }
    //! último dado
    T& back() const {
        if (empty()) {
            throw std::out_of_range("sem elementos na lista");
        }
        return tail->data();
    }
    //! fila vazia
    bool empty() const {
        return size_ == 0;
    }
    //! tamanho
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures
#endif
