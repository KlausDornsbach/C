// Copyright [2019] <Klaus de Freitas Dornsbach>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;  // seto tamanho pro default
    contents = new T[max_size_];  // crio array
    begin_ = 0;  // começo no 0
    end_ = -1;  // fim no -1
    size_ = 0;  // tamanho da fila = 0
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;  // tamanho passado como parametro no construtor
    contents = new T[max_size_];  // tamanho passado na alocaçao de memoria
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;  // deleta estrutura de dados
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {  // checa se fila comporta mais elementos
        throw std::out_of_range("fila cheia");  // joga exceção caso esteja chei
                                                                            // a
    } else {
        end_ = (end_  + 1) % max_size_;  // caso contrario fim da fila aumenta
        contents[end_] = data;  // em 1 e cria um array circular usando modulo
        size_++;  // adiciona elemento no array e aumenta tamanho
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
     if (empty()) {
        throw std::out_of_range("fila vazia");  // checa se há elementos pra ret
    } else {  // irar da fila
        T temp = contents[begin_];  // armazena elemento que vai ser retirado
        begin_ = (begin_ + 1) % max_size_;  // começo da fila aumenta 1
        size_--;  // tamanho decresce
        return temp;  // retorna elemento
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
     if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[end_];  // retorna elemento do fim da fila
    }
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    while (size_ > 0) {  // enquanto tamanho é maior que 0
        dequeue();  // retira elemento da fila
    }
}

template<class T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;  // retorna tamanho da fila
}

template<class T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;  // retorna quantos elementos fila comporta
}

template<class T>
bool structures::ArrayQueue<T>::empty() {
    if (size_ == 0) {  // retorna se fila está vazia
        return true;
    }
    return false;
}

template<class T>
bool structures::ArrayQueue<T>::full() {
    if (size_ == max_size_) {  // retorna se fila está cheia
        return true;
    }
    return false;
}
