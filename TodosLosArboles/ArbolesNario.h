//
// Created by setea on 15/03/2024.
//

#ifndef TODOSLOSARBOLES_ARBOLESNARIO_H
#define TODOSLOSARBOLES_ARBOLESNARIO_H
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <algorithm>

template <typename T>
class LinkedTree{
public:

    template <typename S>
    class Node{
        friend class LinkedTree;
        S info;
        Node<S>* padre;
        std::list<std::shared_ptr<Node<S>>> hijos;

    public:
        Node(S info = nullptr, Node<S>* p = nullptr, std::list<std::shared_ptr<Node<S>>> h = {}) :
        info(info), padre(p), hijos(h) {}
    };

    LinkedTree(std::shared_ptr<Node<T>> node = nullptr) : raiz(node) {};

    bool isEmpty(){return raiz == nullptr;}
    bool isRaiz(Node<T>* node){return node == raiz.get();}
    bool isHoja(Node<T>* node){return node->hijos.size() == 0;}
    bool isInternal(Node<T>* node){return !isHoja(node);}

   Node<T>* add(T e, Node<T>* padre = nullptr){
        if (padre == nullptr){
            raiz = std::make_shared<Node<T>>(e, nullptr);
            return raiz.get();
        } else {
            auto hijo = std::make_shared<Node<T>>(e, padre);
            padre->hijos.push_back(hijo);
            return hijo.get();
        }
    }

    Node<T>* getPadre(Node<T>* node){return node->padre;}
    Node<T>* getRaiz(){return raiz.get();}
    std::list<Node<T>*> getHijos(Node<T>* node){
        std::list<Node<T>*> hijosCrudos;
        for (const auto& hijo : node->hijos) {
            hijosCrudos.push_back(hijo.get());
        }
        return hijosCrudos;
    }

    LinkedTree<T> cut(Node<T>* node){
        auto padre = getPadre(node);
        if (padre == nullptr){
            auto t = *this;
            raiz = nullptr;
            return t;
        } else {
            auto hijos = padre->hijos;
            for (auto& item: hijos) {
                if(item.get() == node){
                    LinkedTree<T> t{item};
                    padre->hijos.remove(item);
                    return t;
                }
            }
        }
    }

    LinkedTree<T> cutCHATGPT(Node<T>* node) {
        if (!node) return LinkedTree<T>(nullptr); // Manejo de caso nulo

        auto padre = getPadre(node);
        if (!padre) {
            // Si el nodo es la raíz, copia el árbol actual y luego elimina la raíz
            LinkedTree<T> t = *this; // Hacer una copia del árbol actual
            raiz = nullptr; // Eliminar la raíz del árbol original
            return t;
        } else {
            // Buscar el hijo específico usando su puntero crudo para comparación
            auto it = std::find_if(padre->hijos.begin(), padre->hijos.end(),
                                   [node](const std::shared_ptr<Node<T>>& hijo) {
                                       return hijo.get() == node;
                                   });
            if (it != padre->hijos.end()) {
                // Si encontramos el hijo, podemos usar 'it' para manipular el std::shared_ptr directamente
                LinkedTree<T> nuevoArbol(*it); // Crear un nuevo árbol con el hijo encontrado como raíz
                padre->hijos.erase(it); // Eliminar el hijo de la lista de hijos del padre

                return nuevoArbol;
            }
        }
        // En caso de que no se encuentre el nodo, o si hay algún otro problema, devuelve un árbol vacío.
        return LinkedTree<T>(nullptr);
    }

    LinkedTree<T> cut2(Node<T>* node) {
        auto parent = getPadre(node);
        for (auto& item: parent->hijos) {
            if(item.get() == node) {
                item->padre = nullptr;
                LinkedTree t(item);
                parent->hijos.remove(item);
                return t;
            }
        }
    }

    void attach(Node<T>* node, LinkedTree<T> subt) {
        auto subroot = std::make_shared<Node<T>>(subt.getRaiz()->info, nullptr, subt.getRaiz()->hijos);
        subroot->padre = node;
        node->hijos.push_front(subroot);
    }

    void preorden() const {preorden(raiz);}
    void inorden() const {inorden(raiz);}
    void postorden() const {postorden(raiz);}

private:
    std::shared_ptr<Node<T>> raiz = nullptr;

    void preorden(std::shared_ptr<Node<T>> node) const {
        if (!node) return;
        std::cout << node->info << " "; // Visitar nodo
        for (auto& hijo : node->hijos) {
            preorden(hijo); // Visitar hijos
        }
    }

    void inorden(std::shared_ptr<Node<T>> node) const {
        if (!node) return;
        if (!node->hijos.empty()) {
            inorden(node->hijos.front()); // Solo visita el primer hijo para inorden
        }
        std::cout << node->info << " ";
        auto it = node->hijos.begin();
        if (it != node->hijos.end()) ++it; // Saltar el primer hijo
        for (; it != node->hijos.end(); ++it) {
            inorden(*it);
        }
    }

    void postorden(std::shared_ptr<Node<T>> node) const {
        if (!node) return;
        for (auto& hijo : node->hijos) {
            postorden(hijo); // Visitar hijos
        }
        std::cout << node->info << " "; // Visitar nodo
    }
};

template <typename T>
class LCRSTree{
public:
    template<typename S>
    class Node{
        friend class LCRSTree;
        S info;
        Node<S>* padre;
        std::shared_ptr<Node<S>> HijoIzquierdo;
        std::shared_ptr<Node<S>> HermanoDerecho;

    public:
        Node(S info, Node<S>* p = nullptr,
             std::shared_ptr<Node> hi = nullptr, std::shared_ptr<Node> he = nullptr) :
             info(info), padre(p), HijoIzquierdo(hi), HermanoDerecho(he) {}
    };

    LCRSTree(std::shared_ptr<Node<T>> node) : raiz(node) {};

    bool isEmpty(){return raiz == nullptr;}
    bool isRaiz(Node<T>* node){return node == raiz.get();}
    bool isHoja(Node<T>* node){return node->HijoIzquierdo == nullptr;}
    bool isInternal(Node<T>* node){return !isHoja(node);}

    Node<T>* add(T e, Node<T>* padre = nullptr){
        if ((padre== nullptr) && (raiz != nullptr)){
            std::cout << "ERROR: el árbol ya tiene raiz";
            return nullptr;
        } else if (padre == nullptr){
            raiz = std::make_shared<Node<T>>(e);
            return raiz.get();
        } else {
            auto aux = std::make_shared<Node<T>>(e, padre);
            if (padre->HijoIzquierdo == nullptr){
                padre->HijoIzquierdo = aux;
            } else {
                aux->HermanoDerecho = padre->HijoIzquierdo;
                padre->HijoIzquierdo = aux;
            } // parent no child
            return aux.get();
        } // no root
    }

    Node<T>* getPadre(Node<T>* node){return node->padre;}
    Node<T>* getRaiz(){return raiz.get();}
    std::vector<Node<T>*> getHijos(Node<T>* node){
        std::vector<Node<T>*> hijos;
        auto hijo = node->HijoIzquierdo;
        while (hijo){
            hijos.push_back(hijo.get());
            hijo = hijo->HermanoDerecho;
        }
        return hijos;
    }

    LCRSTree<T> cut(Node<T>* node){
        if (!node) return *this;
        std::shared_ptr<Node<T>> n;
        auto padre = getPadre(node);
        if (padre == nullptr){
            auto t = *this;
            raiz = nullptr;
            return t;
        } else {
            if(padre->HijoIzquierdo.get() == node){
                n = padre->HijoIzquierdo;
                padre->HijoIzquierdo = node->HermanoDerecho;
            } else {
                auto hermano = padre->HijoIzquierdo;
                while(hermano.get() && hermano->HermanoDerecho.get() != node){
                    hermano = hermano->HermanoDerecho;
                }
                if(hermano){
                    n = hermano->HermanoDerecho;
                    hermano->HermanoDerecho = node->HermanoDerecho;
                }
            }
            LCRSTree<T> t(n);
            node->padre = nullptr;
            node->HermanoDerecho = nullptr;
            return t;
        }
    }

    void attach(Node<T>* node, LCRSTree<T> subt) {
        auto subroot = std::make_shared<Node<T>>(
                subt.getRaiz()->info,
                subt.getRaiz()->padre,
                subt.getRaiz()->HijoIzquierdo,
                subt.getRaiz()->HermanoDerecho);
        if (node->HijoIzquierdo == nullptr) {
            node->HijoIzquierdo = subroot;
        } else {
            auto aux = node->HijoIzquierdo;
            while (aux->HermanoDerecho != nullptr) {
                aux = aux->HermanoDerecho;
            }
            aux->HermanoDerecho = subroot;
        }
        subroot->padre = node;
    }

    void preorden() const { preorden(raiz); }
    void postorden() const { postorden(raiz); }

private:
    std::shared_ptr<Node<T>> raiz;

    void preorden(std::shared_ptr<Node<T>> node) const {
        if (!node) return;
        std::cout << node->info << " ";
        preorden(node->HijoIzquierdo);
        preorden(node->HermanoDerecho);
    }

    void postorden(std::shared_ptr<Node<T>> node) const {
        if (!node) return;
        postorden(node->HijoIzquierdo);
        std::cout << node->info << " ";
        postorden(node->HermanoDerecho);
    }
};

#endif //TODOSLOSARBOLES_ARBOLESNARIO_H
