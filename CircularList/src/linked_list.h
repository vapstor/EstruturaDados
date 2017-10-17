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
    virtual void clear() {
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
        insert(data, size());  //! size == fim+1
    }

    //! Inserir no início
    virtual void push_front(const T& data) {
    	Node* novo = new Node(data, head);
    	if (novo == NULL) {
    		throw std::out_of_range("Sem Memória!");
    	}
    	head = novo;
    	size_++;
    }

    //! inserir na posição
    virtual void insert(const T& data, std::size_t index) {
    	if (index >= size()+1 || index < 0) {
            throw std::out_of_range("Fora dos Limites Insert Linked");
        } if (index == 0) {
        	push_front(data);
        } else {
            Node* ant = head;
            int i = 1;
            while (i < index) {
                ant = ant->next();
                i++;
            }
            Node* novo = new Node(data, ant->next());
            if (novo == NULL) {
                throw std::out_of_range("Sem Memória Insert!");
            }
            ant->next(novo);
            size_++;
        }
    }

     //! inserir em ordem
    virtual void insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* aux = head;
            int i = 0;
            while (i < size() && aux->data() < data) {
                aux = aux->next();
                i++;
            }
            insert(data, i);
        }
    }

    //! acessar um elemento na posição index
    virtual T& at(std::size_t index) {
        if (empty()) {
           throw std::out_of_range("Lista Vazia At()");
        }
        if (index < 0 || index > size()-1) {
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
    virtual T pop(std::size_t index) {
        if (empty()) {
           throw std::out_of_range("Lista Vazia Pop()");
        }
        if (index < 0 || index >= size()) {
            throw std::out_of_range("Índice Inválido PopAt()");
        }
        if (index == 0) {
           return pop_front();
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
        return pop(size()-1);
    }

    //! retirar do início
    virtual T pop_front() {
    	if (empty()) {
    		throw std::out_of_range("Lista Vazia Pop()");
    	}
    	T dadoVoltaInicio = head->data();
    	head = head->next();
    	size_--;
    	return dadoVoltaInicio;
    }

    //! remover específico
    void remove(const T& data) {
        pop(find(data));
    }

    //! Lista Vazia
    bool empty() const {
        return size() == 0;
    }

    //! Contém
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista Vazia Contains()");
        }
        Node* aux = head;
        int i = 0;
        while (i < size()-1) {
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
    virtual std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista Vazia Find");
        }
        Node* aux = head;
        int i = 0;
        while (i < size()) {
            if (aux->data() == data) {
                return i;
            }
            aux = aux->next();
            i++;
        }
        return i;
    }

    //! tamanho da lista
    virtual std::size_t size() const {
        return size_;
    }

 protected:
    //! Elemento
    class Node {
     public:
        //! Construtor
        explicit Node(const T& data):
            data_{data}
        {}

        Node():
            data_{NULL},
            next_{NULL}
        {}

        //! Construtor com next
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        //! getter: dado
        T& data() {
            return data_;
        }

        //! getter const: dado
        const T& data() const {
            return data_;
        }

        //! getter: próximo
        Node* next() {
            return next_;
        }

        //! getter const: próximo
        const Node* next() const {
            return next_;
        }

        //! setter: próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    //! último nodo da lista
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    //! Node Head
    Node* head{nullptr};
    //! size
    std::size_t size_{0u};
};

}  //! namespace structures

#endif
