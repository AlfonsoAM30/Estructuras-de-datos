//
// Created by setea on 15/03/2024.
//

#ifndef TODOSLOSARBOLES_ARBOLESBINARIOS_H
#define TODOSLOSARBOLES_ARBOLESBINARIOS_H
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

template <typename T>
class LinkedBinaryTree{
public:
    template <typename S>
    class Node{
        friend class LinkedBinaryTree;
        S info;
        Node<S>* padre;
        std::shared_ptr<Node<S>> izq;
        std::shared_ptr<Node<S>> der;
    public:
        Node(S info, Node<S>* p = nullptr,
             std::shared_ptr<Node<S>> i = nullptr, std::shared_ptr<Node<S>> d = nullptr) :
                info(info), padre(p), izq(i), der(d) {}
    };

    LinkedBinaryTree(std::shared_ptr<Node<T>> node = nullptr) : raiz(node) {}

    bool isEmpty(){return raiz == nullptr;}
    bool isRaiz(Node<T>* node){return node == raiz.get();}
    bool isHoja(Node<T>* node){return (node->izq == nullptr) && (node->der == nullptr);}
    bool isInternal(Node<T>* node){return !isHoja(node);}

    Node<T>* getRaiz(){return raiz.get();}
    Node<T>* getHijoIzq(Node<T>* node){return node->izq.get();}
    Node<T>* getHijoDer(Node<T>* node){return node->der.get();}
    Node<T>* getPadre(Node<T>* node){return node->padre;}
    T getElemento(Node<T>* node){return node->info;}

    Node<T>* addRoot(T e) {
        raiz = std::make_shared<Node<T>>(e, nullptr);
        return raiz.get();
    }

    Node<T>* addHijoIzq(T e, Node<T>* node){
        if(node && node->izq == nullptr){
            auto nuevoNodo = std::make_shared<Node<T>>(e, node);
            node->izq = nuevoNodo;
            return nuevoNodo.get();
        }
        return nullptr;
    }

    Node<T>* addHijoDer(T e, Node<T>* node){
        if(node && node->der == nullptr){
            auto nuevoNode = std::make_shared<Node<T>>(e, node);
            node->der = nuevoNode;
            return nuevoNode.get();
        }
        return nullptr;
    }

    LinkedBinaryTree<T> cut(Node<T>* node){
        auto padre = getPadre(node);
        if (padre == nullptr){
            auto t = *this;
            raiz = nullptr;
            return t;
        } else {
            auto nodoDer = padre->der;
            auto nodoIzq = padre->izq;
            if (nodoDer.get() == node){
                LinkedBinaryTree<T> t{nodoDer};
                padre->der = nullptr;
                return t;
            } else if (nodoIzq.get() == node) {
                LinkedBinaryTree<T> t{nodoIzq};
                padre->izq = nullptr;
                return t;
            } else {
                return LinkedBinaryTree<T>(nullptr);
            }
        }
    }

    void preorden() const {
        preorden(raiz.get());
        std::cout << std::endl;
    }
    void inorden() const {
        inorden(raiz.get());
        std::cout << std::endl;
    }
    void postorden() const {
        postorden(raiz.get());
        std::cout << std::endl;
    }

private:
    std::shared_ptr<Node<T>> raiz = nullptr;

    void preorden(Node<T>* node) const {
        if (node == nullptr) return;
        std::cout << node->info << " ";
        preorden(node->izq.get());
        preorden(node->der.get());
    }

    void inorden(Node<T>* node) const {
        if (node == nullptr) return;
        inorden(node->izq.get());
        std::cout << node->info << " ";
        inorden(node->der.get());
    }

    void postorden(Node<T>* node) const {
        if (node == nullptr) return;
        postorden(node->izq.get());
        postorden(node->der.get());
        std::cout << node->info << " ";
    }

};

/*
template <typename T>
class ArrayBinaryTree {
public:
    ArrayBinaryTree() = default;

    // Agregar un elemento al árbol en una posición específica determinada por el índice del padre
    void add(const T& element, size_t parentIndex, bool isLeftChild) {
        size_t index = isLeftChild ? 2 * parentIndex + 1 : 2 * parentIndex + 2;
        if (index >= tree.size()) {
            tree.resize(index + 1, T()); // Redimensiona el vector y llena los nuevos espacios con elementos por defecto
        }
        tree[index] = element;
    }

    // Agregar raíz (solo si el árbol está vacío)
    void addRoot(const T& element) {
        if (tree.empty()) {
            tree.push_back(element);
        }
    }

    // Recorrido Preorden
    void preorden(size_t index = 0) const {
        if (index >= tree.size() || tree[index] == T()) return; // T() representa un valor por defecto/nulo
        std::cout << tree[index] << " ";
        preorden(2 * index + 1); // Hijo izquierdo
        preorden(2 * index + 2); // Hijo derecho
    }

    // Recorrido Inorden
    void inorden(size_t index = 0) const {
        if (index >= tree.size() || tree[index] == T()) return;
        inorden(2 * index + 1); // Hijo izquierdo
        std::cout << tree[index] << " ";
        inorden(2 * index + 2); // Hijo derecho
    }

    // Recorrido Postorden
    void postorden(size_t index = 0) const {
        if (index >= tree.size() || tree[index] == T()) return;
        postorden(2 * index + 1); // Hijo izquierdo
        postorden(2 * index + 2); // Hijo derecho
        std::cout << tree[index] << " ";
    }

    // Método para verificar si el árbol está vacío
    bool isEmpty() const {
        return tree.empty();
    }

private:
    std::vector<T> tree; // Vector que almacena los elementos del árbol
};
*/

#endif //TODOSLOSARBOLES_ARBOLESBINARIOS_H
