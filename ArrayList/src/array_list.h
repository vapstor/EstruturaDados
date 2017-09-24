/* Copyright [2017] <Acauã Pitta> */
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include "./array_queue.h"
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! Lista em Array Implementação 17.2
class ArrayList : ArrayQueue<T> {
 public:
    //! construtor sem parâmetros
    ArrayList() {
        size_ = -1;
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
    }

    //! Construtor com parâmetros
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        size_ = -1;
        contents = new T[max_size_];
    }

    //! Destrutor
    ~ArrayList() {
        delete[] contents;
    }

    //! limpar
    void clear() {
        if (empty()) {
            throw std::out_of_range("Lista Vazia!");
        }	 	  	 	   	      	    	    	    	   	      	 	
        size_ = -1;
        // return ArrayQueue<T>::clear();
    }
    //! Insere no Fim
    void push_back(const T& data) {
        // ArrayQueue<T>::enqueue(data);
        if (full()) {
            throw std::out_of_range("Lista Cheia!");
        }
        size_++;
        contents[size_] = data;
    }
    //! Insere no Início
    void push_front(const T& data) {
        insert(data, 0);
        // if (full()) {
        //     throw std::out_of_range("Lista Cheia!");
        // }
        // size_++;
        // for (int i = size_; i > 0; i--) {
        //     contents[i] = contents[i-1];
        // }
        // contents[0] = data;
    }
    //! Insere no Índice
    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("Lista Cheia!");
        }
        if (index < 0 || index > size()) {
            throw std::out_of_range("Fora dos Limites");
        }
        size_++;
        int i;
        for (i = size_; i > index; i--) {
            contents[i] = contents[i-1];
        }	 	  	 	   	      	    	    	    	   	      	 	
        contents[i] = data;
    }

    //! Insere em Ordem
    void insert_sorted(const T& data) {
        int i;
        for (i = 0; i < size() && data > contents[i]; ) {
            i++;
        }
        insert(data, i);
    }

    //! Retira da Posição
    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Fora dos Limites");
        }
        T dadoVolta = contents[index];
        size_--;
        for (int i = index; i < size(); i++) {
            contents[i] = contents[i+1];
        }
        return dadoVolta;
    }
    //! Remove de Trás
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        }
        size_--;
        return contents[size_+1];
    }
    //! Remove da frente
    T pop_front() {	 	  	 	   	      	    	    	    	   	      	 	
        return pop(0);
    }

    //! Remover dado
    void remove(const T& data) {
        int i = 0;
        while (i < size() && contents[i] != data) {
            i++;
        }
        pop(i);
    }

    //! cheia
    bool full() {
        return size() == max_size_;
    }

    //! vazia
    bool empty() {
        return size() == 0;
        // return ArrayQueue<T>::empty();
    }

    //! Contém
    bool contains(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        }
        int i = 0;
        while (i < size()) {
            if (contents[i] == data) {
                return true;
            }
            i++;
        }
        return false;
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! Posição do Dado
    std::size_t find(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        }
        int i = 0;;
        while (i < size() && contents[i] != data) {
            i++;
        }
        return i;
    }

    //! Tamanho
    std::size_t size() {
        return size_+1;
        // return ArrayQueue<T>::size();
    }

    //! Tamanho Máximo
    std::size_t max_size() {
        return max_size_;
        // return ArrayQueue<T>::max_size();
    }

    //! Dado na Posição
    T& at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Fora dos Limites");
        }
        return contents[index];
    }

    //! dado Operator
    T& operator[](std::size_t index) {	 	  	 	   	      	    	    	    	   	      	 	
        return contents[index];
    }

    //! Posição do Índice CONST
    const T& at(std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Lista Vazia");
        }
        return contents[index];
    }

    //! Dado Operator CONST
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  //! namespace structures

#endif
	 	  	 	   	      	    	    	    	   	      	 	
