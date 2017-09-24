/* Copyright [2017] <Acauã Pitta> */
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! Pilha em Array Implementação 17.2
class ArrayStack {
 public:
    //  Construtor Padrão
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        T contents = new T[max_size_];
        top = -1;
    }

    //!  Construtor com argumentos
    explicit ArrayStack(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }

    ~ArrayStack() {
        delete[] contents;
    }
    //! empilha
    void push(const T& data) {
        if (full()) {
            throw std::out_of_range("Pilha Cheia!");
        }
        top_++;
        contents[top_] = data;
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! desempilha
    T pop() {
        if (empty()) {
            throw std::out_of_range("Pilha Vazia!");
        }
        top_ = top_-1;
        return contents[top_+1];
    }

    //! Retornar elemento do topo
    T& top() {
        return contents[top_];
    }

     //! limpa
    void clear() {
        top_ = -1;
    }

     //! tamanho
    std::size_t size() {
        return top_+1;
    }

    //! max_size
    std::size_t max_size() {
        return max_size_;
    }

    //! vazia
    bool empty() {
        return size() == 0;
    }

    //! cheia
    bool full() {	 	  	 	   	      	    	    	    	   	      	 	
        return size() == max_size_;
    }

 private:
    T* contents;
    int top_;
    std::size_t max_size_;
    static const auto DEFAULT_SIZE = 10u;
};

}  //! namespace structures


#endif
