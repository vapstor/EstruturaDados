//! Copyright [2017] <Acauã Pitta>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include "./linked_list.h"

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {


template<typename T>
//! Class Pilha Encadeada
class LinkedStack : LinkedList<T>{
 public:
    LinkedStack() {
        // LinkedList<T>::LinkedList();
        top_ = NULL;
        size_ = 0;
    }

    ~LinkedStack() {
        clear();
    }

     //! limpa pilha
    void clear() {
        // LinkedList<T>::clear();
        Node* anterior;
        Node* atual = top_;
        while (!empty()) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            size_--;
        }	 	  	 	   	      	    	    	    	   	      	 	
        top_ = NULL;
    }

     //! empilha
    void push(const T& data) {
        // LinkedList<T>::push_front(data);
        Node* novo = new Node(data, top_);
        if (novo == NULL) {
            throw std::out_of_range("Sem Memória Push!");
        }
        top_ = novo;
        size_++;
    }

    //! desempilha
    T pop() {
        // return LinkedList<T>::pop(0);
        if (empty()) {
            throw std::out_of_range("Sem Memória Pop!");
        }
        Node* deletar;
        T dadoVolta = top_->data();
        deletar = top_;
        top_ = top_->next();
        size_--;
        delete deletar;
        return dadoVolta;
    }

    //! dado no topo
    T& top() const {
        if (empty()) {
            throw std::out_of_range("Pilha Vazia Top()");
        }
        return top_->data();
        // return LinkedList<T>::at(0);
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! pilha vazia
    bool empty() const {
        return size_ == 0;
        // return LinkedList<T>::empty();
    }

    //! tamanho da pilha
    std::size_t size() const {
        return size_;
        // return LinkedList<T>::size();
    }

 private:
    //! Classe Elemento
    class Node {
     public:
        //! Construtor
        explicit Node(const T& data):
            data_{data}
        {}
        //! Construtor com next
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        //! getter: info
        T& data() {
            return data_;
        }
        //! getter-constante: info
        const T& data() const {
            return data_;
        }

        //! getter: próximo
        Node* next() {	 	  	 	   	      	    	    	    	   	      	 	
            return next_;
        }

        //! getter-constante: próximo
        const Node* next() const {
            return next_;
        }

         //! setter: próximo
        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  //! namespace structures

#endif

	 	  	 	   	      	    	    	    	   	      	 	
