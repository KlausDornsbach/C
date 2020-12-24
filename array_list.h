//!  Copyright [2019] <Klaus de Freitas Dornsbach>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <stdexcept>  // C++ exceptions

#include <cstdint>


namespace structures {

template<typename T>
/**
 * constroi array list com tamanho maximo desejado
**/
class ArrayList {  // class array list
 public:
    ArrayList();
    /**
     * constroi array list com tamanho maximo desejado
    **/
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();
    /** limpa a lista **/
    void clear();
    /** coloca na ultima posicao **/
    void push_back(const T& data);
    /** coloca na primeira posicao **/
    void push_front(const T& data);
    /** insere dado na posicao **/
    void insert(const T& data, std::size_t index);
    /** insere dado na posicao logica **/
    void insert_sorted(const T& data);
    /** tira dado do indice desejado **/
    T pop(std::size_t index);
    /** retira dado do fim **/
    T pop_back();
    /** retira dado do inicio **/
    T pop_front();
    /** remove dado **/
    void remove(const T& data);
    /** booleano cheio **/
    bool full() const;
    /** booleano vazio **/
    bool empty() const;
    /** booleno arranjo contem o dado **/
    bool contains(const T& data) const;
    /** retorna indice do dado desejado **/
    std::size_t find(const T& data) const;
    /** retorna tamanho do arranjo **/
    std::size_t size() const;
    /** retorna tamanho alocado ao arranjo **/
    std::size_t max_size() const;
    /** retorna o conteudo de um indice **/
    T& at(std::size_t index);
    /** retorna o conteudo de um indice **/
    T& operator[](std::size_t index);
    /** retorna o conteude do espaço dese. **/
    const T& at(std::size_t index) const;
    /** retorna constante **/
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
};
    // cria metodo default utilizando o outro construtor com um parametro const
    // ante
    template<typename T>
    ArrayList<T>::ArrayList() {
        ArrayList(DEFAULT_MAX);
    }
    // construtor (especifica tamanho máximo da lista)
    template<typename T>
    ArrayList<T>::ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size_];
        size_ = 0;
    }
    // deleta lista
    template<typename T>
    ArrayList<T>::~ArrayList() {
        delete[] contents;
    }
    // limpa lista
    template<typename T>
    void ArrayList<T>::clear() {
        size_ = 0;
    }
    // coloca novo elemento no final da lista utilizando metodo insert
    // possivel erro: lista cheia
    template<typename T>
    void ArrayList<T>::push_back(const T& data) {
        insert(data, size());
    }
    // coloca novo elemento no inicio da lista utilizando metodo insert
    // possivel erro: lista cheia
    template<typename T>
    void ArrayList<T>::push_front(const T& data) {
        insert(data, 0);
    }
    // inserção em qualquer lugar da lista
    // problemas possiveis: lista cheia, indice fora do arranjo
    // metodo deve incrementar o size_
    template<typename T>
    void ArrayList<T>::insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("Lista cheia!");
        }
        if (index<0 || index > size_) {
            throw std::out_of_range("Indice fora do arranjo!");
        }
        for (int atual = size_; atual > index; atual--) {
            contents[atual] = contents[atual-1];
        }
        size_++;
        contents[index] = data;
    }
    template<typename T>
    void ArrayList<T>::insert_sorted(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista cheia!");
        }
        std::size_t index = 0;
        while (index < size_ && data > contents[index]) {
            index++;
        }
        insert(data, index);
}
    // retira qualquer elemento fornecendo seu indice
    // possiveis erros: lista vazia, indice fora do arranjo
    // deve armazenar dados do objeto antes de trocar os conteudos do endereço
    // gv(global variables): size_ decrementado
    template<typename T>
    T ArrayList<T>::pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Indice fora do arranjo!");
        }
        T temp = contents[index];
        for (int atual = index; atual < size_ - 1; atual++) {
            contents[atual] = contents[atual + 1];
        }
        size_--;
        return temp;
    }
    // retira elemento do final da fila
    template<typename T>
    T ArrayList<T>::pop_back() {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        T temp = size_ - 1;
        pop(size_-1);
        return temp;
    }
    // retira elemento da frente da fila (usa metodo pop())
    template<typename T>
    T ArrayList<T>::pop_front() {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        return pop(0);
    }
    // remove um elemento (se existir no arranjo) por busca
    template<typename T>
    void ArrayList<T>::remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        pop(contents[find(data)]);
    }
    // verifica se array list está cheia ou nao
    template<typename T>
    bool ArrayList<T>::full() const {
        if (size_ == max_size_) {
            return true;
        }
        return false;
    }
    // verifica se a fila está vazia ou nao
    template<typename T>
    bool ArrayList<T>::empty() const {
        if (size_ == 0) {
            return true;
        }
        return false;
    }
    // utiliza o metodo find() para assertar a existencia de um
    // elemento no array
    template<typename T>
    bool ArrayList<T>::contains(const T& data) const {
        if (find(data) < size_) {
            return true;
        }
        return false;
    }
    // acha um elemento no array
    template<typename T>
    std::size_t ArrayList<T>::find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        for (int i = 0; i < size_; i++) {
            if (contents[i] == data) {
                return i;
            }
        }
        return size_;
    }
    // retorna o tamanho do array
    template<typename T>
    std::size_t ArrayList<T>::size() const {
        return size_;
    }
    // retorna a quantidade maxima de elementos contidos no array
    template<typename T>
    std::size_t ArrayList<T>::max_size() const {
        return max_size_;
    }
    // retorna o elemento no indice passado no parametro
    template<typename T>
    T& ArrayList<T>::at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Indice fora do arranjo!");
        }
        return contents[index];
    }
    // metodo similar aos proximos
    template<typename T>
    T& ArrayList<T>::operator[](std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Indice fora do arranjo!");
        }
        return contents[index];
    }
    // retorna o conteudo do arranjo na posicao desejada
    template<typename T>
    const T& ArrayList<T>::at(std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Indice fora do arranjo!");
        }
        return contents[index];
    }
    // return o conteudo do arranjo na posicao desejada
    template<typename T>
    const T& ArrayList<T>::operator[](std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Indice fora do arranjo!");
        }
        return contents[index];
    }
}  // namespace structures
#endif
