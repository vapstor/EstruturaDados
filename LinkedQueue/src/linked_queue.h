//! Copyright [2017] <Acauã Pitta>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {


template<typename T>
//! Classe Fila Encadeada
class LinkedQueue {
 public:
    //! Construtor
    LinkedQueue() {
        head = NULL;
        tail = head;
        size_ = 0;
    }

    //! Destrutor
    ~LinkedQueue() {
        clear();
    }

    //! limpar
    void clear() {
        Node* atual = head;
        Node* anterior;
        while (!empty()) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            size_--;
        }
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! enfilerar
    void enqueue(const T& data) {
        Node* novo = new Node(data, NULL);
        if (novo == NULL) {
            throw std::out_of_range("Sem Memória!");
        }
        if (empty()) {
            head = novo;
            tail = head;
            size_++;
        } else {
            Node* aux = head;
            int i = 1;
            while (i < size_) {
            // while (aux != tail) {
                aux = aux->next();
                i++;
            }
            aux->next(novo);
            tail = novo;
            size_++;
        }
    }

    //! desenfilerar
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        }
        T dadoVolta = head->data();
        Node* deletar = head;
        head = head->next();
        delete deletar;
        size_--;
        return dadoVolta;
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! primeiro dado
    T& front() const {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        }
        return head->data();
    }

    //! último dado
    T& back() const {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
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
    //! Elemento
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

 private:
    //! nodo-cabeça
    Node* head{nullptr};

    //! nodo-fim
    Node* tail{nullptr};

    //! tamanho
    std::size_t size_{0u};
};

}  //! namespace structures

#endif
	 	  	 	   	      	    	    	    	   	      	 	
