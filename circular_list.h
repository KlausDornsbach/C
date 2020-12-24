//! Copyright [2019] <Klaus de Freitas Dornsbach>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

//! ...
template<typename T>
class CircularList {
 public:
    //! ...
    CircularList();  // construtor padrão
    //! ...
    ~CircularList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

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

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

// ! metodo inicializaçao padrao, inicia pointer head em null
// ! e tamanho em 0
template<typename T>
CircularList<T>::CircularList() {}  // ! lista n inicia nada pois ja tem param
                                // ! inicializados na definicao
// ! metodo limpa lista
// ! dependencia: clear()
template<typename T>
CircularList<T>::~CircularList() {
    clear();
}

//! esvazia a lista
template<typename T>
void CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}


// ! coloca um node no fim da lista
template<typename T>
void CircularList<T>::push_back(const T &data) {
    insert(data, size_);
}

// ! coloca node na posicao head da fila
// ! algoritmo:
// !     checa se lista está cheia
// !     o proximo desse novo elemento passa a ser o primeiro da lista
// !     cabeça passa a apontar pro novo elemento
template<typename T>
void CircularList<T>::push_front(const T &data) {
    Node *node = new Node(data);
    node->next(head);
    head = node;
    size_++;
}
// ! insere um elemento no indice desejado
template<typename T>
void CircularList<T>::insert(const T &data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("indice fora da lista");
    } else {
        if (index == 0) {
            push_front(data);
        } else {
            Node *node = new Node(data);
            // push_front(data);
            Node *anterior = head;
            // Node *proximo = new Node();
            for (int i = 0; i < index - 1; i++) {
                anterior = anterior->next();
            }
            /*for(int i = 0; i < index; i++){
                proximo->next(head[i]);
            }*/
            node->next(anterior->next());   // ! node novo encaixa no proxim
            anterior->next(node);  // ! node anterior encaixa no novo
            size_++;
        }
    }
}
// ! insere um elemento de forma ordenada na lista
// ! mantendo a ordem de maior pra menor
template<typename T>
void CircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *atual = head;
    int posicao = 0;
    while (!(atual->data() >= data)) {
        atual = atual->next();
        posicao++;
        if (posicao >= size_) {
            return push_back(data);
        }
    }
    insert(data, posicao);
}

// ! retorna que elemento reside no indice dado
template<typename T>
T& CircularList<T>::at(std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("indice fora do alcance");
    }
    if (empty()) {
        throw std::out_of_range("pila vazia");
    }
    Node *target = head;
    if (index == 0) {
        return target->data();
    }
    for (int i = 0; i < index; i++) {
        target = target->next();
    }
    return target->data();
}

// ! retira e retorna um elemento da lista
template<typename T>
T CircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("lista vazia");
    if (index >= size_)
        throw std::out_of_range("indice fora da lista");

    if (index == 0)
        return pop_front();
    Node *antes_sai = head;
    for (int i = 0; i < index - 1; i++) {
        antes_sai = antes_sai->next();
    }
    Node *current = antes_sai->next();  // ! salvo o elemento antes de me livrar
    T dado = current->data();
    antes_sai->next(current->next());
    size_--;
    delete current;
    return dado;
}

//! retira o ultimo dado da lista
template<typename T>
T CircularList<T>::pop_back() {
    return pop(size_ - 1);
}
// ! retira um elemento da frente da lista
// ! algoritmo:
// !     testa existencia
// !     decrementa tamanho
// !     libera memoria
// !     devolve informacao
// ! usa pop
template<typename T>
T CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista não possui elementos!");
    }
    auto out = head;
    T data = out->data();
    head = out->next();
    size_--;
    delete out;
    return data;
}

//! remove o node com o dado especificado
template<typename T>
void CircularList<T>::remove(const T &data_) {
    pop(find(data_));
}

//! checa se está vazio
template<typename T>
bool CircularList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
bool CircularList<T>::contains(const T &data_) const {
    return find(data_) != size();
}

//! acha um dado na lista e retorna seu indice
template<typename T>
std::size_t CircularList<T>::find(const T& data) const {
    std::size_t temp;
    if (empty())
        throw std::out_of_range("lista vazia");
    Node *current = head;
    for (temp = 0; temp < size_; temp++) {
        if (current->data() == data) {
            break;
        }
        current = current->next();
    }
    return temp;
}

//! retorna o tamanho da lista
template<typename T>
std::size_t CircularList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
