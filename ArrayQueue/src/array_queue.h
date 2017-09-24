#ifndef STRUCTURES_ARRAY_QUEUE_H
/* Copyright [2017] <Acauã Pitta> */
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! Pilha em Array Implementação 17.2
class ArrayQueue {
 public:
    //! construtor sem parâmetros
    ArrayQueue() {
        size_ = -1;
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
    }

    //! construtor com parâmetros
    explicit ArrayQueue(std::size_t max) {
        max_size_ = max;
        size_ = -1;
        contents = new T[max_size_];
    }

    //! Destrutor
    ~ArrayQueue() {
        delete[] contents;
    }

    //! Enfileira
    void enqueue(const T& data) {
        if (full()) {
            throw std::out_of_range("Fila Cheia");
        }	 	  	 	   	      	    	    	    	   	      	 	
        size_++;
        contents[size_] = data;
    }

    //! Desenfileira
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        }
        size_--;
        T dadoVolta = contents[0];
        for (int i = 0; i < size(); i++) {
            contents[i] = contents[i+1];
        }
        return dadoVolta;
    }

    //! Ultimo Dado da FIla
    T& back() {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        }
        return contents[size_];
    }

    //! Limpa fila
    void clear() {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        }
        size_ = -1;
    }

    //! Tamanho da Fila
    std::size_t size() {
        return size_+1;
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! Tamanho Máximo da Fila
    std::size_t max_size() {
        return max_size_;
    }

    //! Vazia
    bool empty() {
        return size() == 0;
    }

    //! Cheia
    bool full() {
        return size() == max_size_;
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  //! namespace structures

#endif
	 	  	 	   	      	    	    	    	   	      	 	
