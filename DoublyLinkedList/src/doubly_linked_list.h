//! Copyright [2017] <Acauã Pitta>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! Lista Duplamente Encadeada
class DoublyLinkedList {
 public:
    //! Construtor Padrão
    DoublyLinkedList() {
        head = NULL;
        size_ = 0;
    }

    //! Destrutor
    ~DoublyLinkedList() {
        clear();
    }

    //! Limpa Lista
    void clear() {
        Node* atual = head;
        Node* anterior;
        while (!empty()) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            size_--;
        }
        head = NULL;
    }

    //! insere no fim
    void push_back(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* novo = new Node(data, NULL);
            if (novo == NULL) {
                throw std::out_of_range("Sem Memória push_back()");
            }
            Node* ant = head;
            int i = 0;
            while (i < size_-1) {
            //! "<" size-1 para não dar seg fault (0-1-2-3)
            //! size_ == 4, mas ultimo indice == 3
                ant = ant->next();
                i++;
            }
            ant->next(novo);
            novo->prev(ant);
            size_++;
        }
    }

    //! insere no início
    void push_front(const T& data) {
        Node* novo;
        if (empty()) {
            novo = new Node(data, NULL);
            if (novo == NULL) {
                throw std::out_of_range("Sem Memória push_front()");
            }
            head = novo;
            size_++;
        } else {
            Node* novo = new Node(data, head);
            if (novo == NULL) {
                throw std::out_of_range("Sem Memória push_front()");
            }
            head->prev(novo);
            head = novo;
            size_++;
        }
    }

    //! insere na posição
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > size_) {
            throw std::out_of_range("Índice Fora Dos Limites insert()");
        } else if (index == 0 || empty()) {
            push_front(data);
        } else if (index == size_) {
            push_back(data);
        } else {
            Node* novo = new Node(data);
            Node *ant, *apos;
            int i = 0;
            if (novo == NULL) {
                throw std::out_of_range("Sem Memória insert()");
            }
            ant = head;
            while (i < index-1) {
                ant = ant->next();
                i++;
            }
            apos = ant->next();
            novo->prev(ant);
            novo->next(apos);
            ant->next(novo);
            apos->prev(novo);
            size_++;
        }
    }

    //! insere em ordem
    void insert_sorted(const T& data) {
        Node* aux = head;
        int i = 0;
        while (i < size_ && data > aux->data()) {
            aux = aux->next();
            i++;
        }
        insert(data, i);
    }

    //! retira da posição
    T pop(std::size_t index) {
        Node *deletar, *ant, *apos;
        T dadoVolta;
        int i;
        if (index < 0 || index > size_-1) {
            throw std::out_of_range("Fora dos Limites");
        }
        if (empty()) {
            throw std::out_of_range("Lista Vazia pop()");
        } else if (index == size_-1) {
            ant = head;
            i = 0;
            while (i < index) {
                ant = ant->next();
                i++;
            }
            deletar = ant;
            dadoVolta = deletar->data();
            delete deletar;
            size_--;
            return dadoVolta;
        } else if (index == 0) {
            deletar = head;
            dadoVolta = deletar->data();
            head = head->next();
            size_--;
            delete deletar;
            return dadoVolta;
        }
        ant = head->next();
        i = 1;
        while (i < index) {
            ant = ant->next();
            i++;
        }
        deletar = ant;
        dadoVolta = deletar->data();
        apos = deletar->next();
        ant = deletar->prev();
        apos->prev(ant);
        ant->next(apos);
        delete deletar;
        size_--;
        return dadoVolta;
    }

    //! retira do fim
    T pop_back() {
        return pop(size_-1);
        //! size-1 para não dar seg fault (0-1-2) -> size_ == 3, index == 2;
    }

    //! retira do início
    T pop_front() {
        return pop(0);
    }

    //! Retira Específico
    void remove(const T& data) {
        pop(find(data));
    }

    //! lista vazia
    bool empty() const {
        return size_ == 0;
    }

    //! Contém
    bool contains(const T& data) const {
        Node* aux = head;
        int i = 0;
        while (i < size_-1) {
            if (aux->data() == data) {
                return true;
            }
            aux = aux->next();
            i++;
        }
        return false;
    }

    //! acesso a um elemento (checando limites)
    T& at(std::size_t index) {
        if (index < 0 || index > size_) {
            throw std::out_of_range("Índice Fora Dos Limites at()");
        }
        Node* aux = head;
        int i = 0;
        while (i < index) {
            aux = aux->next();
            i++;
        }
        return aux->data();
    }

    //! getter constante a um elemento
    const T& at(std::size_t index) const {
        if (index < 0 || index > size_) {
            throw std::out_of_range("Índice Fora Dos Limites at()");
        }
        Node* aux = head;
        int i = 0;
        while (i < index) {
            aux = aux->next();
            i++;
        }
        return aux->data();
    }

    //! posição de um dado
    std::size_t find(const T& data) const {
        Node* aux = head;
        int i = 0;
        while (i < size_) {
            if (aux->data() == data) {
                return i;
            }
            //! Duvida aqui, se ele não acha no último
            //! daria seg fault
            aux = aux->next();
            i++;
        }
        return i;
    }

    //! tamanho
    std::size_t size() const {
        return size_;
        //! para chegar com next() ao final: size_-1
        //! para chegar com index ao final: size_
        //! ^ usar chegagem de limites com index: size_+1
    }

 protected:
    //! Classe Privada Elemento
    class Node {
     public:
        //! Construtor
        explicit Node(const T& data):
        data_{data}
        {}

        //! Construtor com Next
        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Construtor com next e previous
        Node(const T& data, Node* prev, Node* next):
        data_{data},
        prev_{prev},
        next_{next}
        {}

        //! Retornar dado
        T& data() {
            return data_;
        }

        //! Retornar dado const
        const T& data() const {
            return data_;
        }

        //! Getter Node Previous
        Node* prev() {
            return prev_;
        }

        //! Getter Node Previous Const
        const Node* prev() const {
            return prev_;
        }

        //! Setter Node Previous
        void prev(Node* node) {
            prev_ = node;
        }

        //! Getter Node Next
        Node* next() {
            return next_;
        }

        //! Getter Node Next Const
        const Node* next() const {
            return next_;
        }

        //! Setter Node Next
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    //! Node Cabeça
    Node* head{nullptr};
    //! Size declaração
    std::size_t size_{0u};
};

}  //! namespace structures

#endif
