//! Copyright [2017] <Acauã Pitta>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! Classe Linked List
class LinkedList {
 public:
    //! construtor padrão
    LinkedList() {
        head = NULL;
        size_ = 0;
    }

    //! destrutor
    ~LinkedList() {
        clear();
    }

    //! limpar lista
    void clear() {
        Node *atual, *anterior;
        atual = head;
        while (!empty()) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            size_--;
        }
        head = NULL;
    }

    //! inserir no fim
    void push_back(const T& data) {	 	  	 	   	      	    	    	    	   	      	 	
        insert(data, size_);  //! size == fim+1
    }

    //! Inserir no início
    void push_front(const T& data) {
        Node* novo = new Node(data, head);
        if (novo == NULL) {
            throw std::out_of_range("Sem Memória!");
        }
        head = novo;
        size_++;
    }

    //! inserir na posição
    void insert(const T& data, std::size_t index) {
        if (index > size_ || index < 0) {
            throw std::out_of_range("Fora dos Limites Insert");
        }
        if (index == 0) {
            push_front(data);
        } else {
            Node* novo = new Node(data, NULL);
            if (novo == NULL) {
                throw std::out_of_range("Sem Memória Insert!");
            }
            Node* ant = head;
            int i = 1;
            while (i < index) {
                ant = ant->next();
                i++;
            }
            novo->next(ant->next());
            ant->next(novo);
            size_++;
        }
    }	 	  	 	   	      	    	    	    	   	      	 	

     //! inserir em ordem
    void insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* aux = head;
            int i = 0;
            while (i < size_ && aux->data() < data) {
                aux = aux->next();
                i++;
            }
            insert(data, i);
        }
    }

    //! acessar um elemento na posição index
    T& at(std::size_t index) {
        if (empty()) {
           throw std::out_of_range("Lista Vazia At()");
        }
        if (index < 0 || index > size_) {
            throw std::out_of_range("Índice Inválido At()");
        } else {
            Node* aux = head;
            int i = 0;
            while (i < index) {
                aux = aux->next();
                i++;
            }
            return aux->data();
        }
    }

    //! retirar da posição
    T pop(std::size_t index) {	 	  	 	   	      	    	    	    	   	      	 	
        if (empty()) {
           throw std::out_of_range("Lista Vazia Pop()");
        }
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Índice Inválido PopAt()");
        }
        if (index == 0) {
            T dadoVoltaInicio = head->data();
            head = head->next();
            size_--;
            return dadoVoltaInicio;
        }
        T dadoVolta;
        Node* aux = head;
        Node* deletar;
        int i = 0;
        while (i < index-1) {
            aux = aux->next();
            i++;
        }
        deletar = aux->next();
        dadoVolta = deletar->data();
        aux->next(deletar->next());
        size_--;
        delete deletar;
        return dadoVolta;
    }

    //! retirar do fim
    T pop_back() {
        if (empty()) {
          throw std::out_of_range("Lista Vazia Pop_back()");
        }
        T dadoVolta;
        Node* aux = head;
        int i = 0;
        while (i < size_ -1) {	 	  	 	   	      	    	    	    	   	      	 	
        //! vai ate o -1 antes do elemento (9 < 9) false
        //! sem o -1 ele caminha até o ultimo+1 (9<10) true
        //! seg fault
            aux = aux->next();
            i++;
        }
        dadoVolta = aux->data();
        delete aux;
        size_--;
        return dadoVolta;
    }

    //! retirar do início
    T pop_front() {
        return pop(0);
        // Node* deletar;
        // T dadoVolta;
        // if (empty()) {
        //   throw std::out_of_range("Lista Vazia Pop_front");
        // } else {
        //     deletar = head;
        //     dadoVolta = head->data();
        //     head = head->next();
        //     delete deletar;
        //     size_--;
        // }
        // return dadoVolta;
    }

    //! remover específico
    void remove(const T& data) {
        pop(find(data));
    }

    //! Lista Vazia
    bool empty() const {	 	  	 	   	      	    	    	    	   	      	 	
        return size_ == 0;
    }

    //! Contém
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista Vazia Contains()");
        }
        Node* aux = head;
        int i = 0;
        while (i < size_) {
            if (aux->data() == data) {
                return true;
            } else {
                aux = aux->next();
                i++;
            }
        }
        return false;
    }

    //! Posição do dado
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista Vazia Find");
        }
        Node* aux = head;
        int i = 0;
        while (i < size_) {
            if (aux->data() == data) {
                return i;
            }
            aux = aux->next();
            i++;
        }
        return i;
    }	 	  	 	   	      	    	    	    	   	      	 	

    //! tamanho da lista
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

}  //! namespace structures

#endif
	 	  	 	   	      	    	    	    	   	      	 	
