#include <iostream>
#include <memory>

template <typename T>
class AVLTree{
public:

    template <typename S>
    class Node{
        friend class AVLTree;
        S info;
        Node<S>* p;
        std::shared_ptr<Node<S>> l;
        std::shared_ptr<Node<S>> r;
        int height;
    };

    bool isEmpty(){return root == nullptr;}

    Node<T>* getRoot(){return root.get();}
    Node<T>* getParent(Node<T>* node){return node->p;}
    Node<T>* getLeftChild(Node<T>* node){return node->l;}
    Node<T>* getRightChild(Node<T>* node){return node->r;}

    bool isRoot(Node<T>* node){return node == root.get();}
    bool isLeaf(Node<T>* node){return (node->l == nullptr) && (node->r == nullptr);}
    bool isInternal(Node<T>* node){return !isLeaf(node);}

    Node<T>* insert2(T e){
        auto elem = root.get();
        Node<T>* parent = nullptr;
        auto it = std::make_shared<Node<T>>();
        if (elem == nullptr){
            it->info = e;
            it->height = 1;
            root = it;
            return it.get();
        }
        while (elem != nullptr){
            parent = elem;
            if (elem->info <= e){
                elem = elem->r.get();
            } else {
                elem = elem->l.get();
            }
        }
        it->info = e;
        it->p = parent;
        updateHeight(it.get());
        if(parent->info <= e){
            parent->r = it;
            return it.get();
        } else {
            parent->l = it;
            return it.get();
        }
    }

    //---------------------------------PROFE---------------------------------

    Node<T>* insert(T e){
        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>();
        node->info = e;
        node->p = nullptr;
        node->l = nullptr;
        node->r = nullptr;
        node->height = 1;
        insert(node, root.get());
        rebalance(node);
    }

    Node<T>* insert(std::shared_ptr<Node<T>> node, Node<T>* parent){

        if(parent == nullptr){
            root = node;
        } else {
            if(node->info < parent->info){
                if(parent->l) {
                    insert(node, parent->l.get());
                } else {
                    parent->l = node;
                    node->p = parent;
                    updateHeight(node.get());
                }
            } else {
                if(parent->r) {
                    insert(node, parent->r.get());
                } else {
                    parent->r = node;
                    node->p = parent;
                    updateHeight(node.get());
                }
            }
        }
    }

    bool isBalanced(Node<T>* node){
        if (!node) return true;

        auto lh = (node->l) ? node->l->height : 0;
        auto rh = (node->r) ? node->r->height : 0;

        int b = rh - lh;
        return (b >= -1) && (b <= 1);
    }

    void rebalance(Node<T>* node,  Node<T>* a = nullptr, Node<T>* b = nullptr, Node<T>* c = nullptr){
        if(node){
            if(isBalanced(node)){
                c = b;
                b = a;
                a = node;
                rebalance(node->p, a , b, c);
            } else {
                c = b;
                b = a;
                a = node;
                Estructurar(a, b, c);
            }
        }
    }

    void Estructurar(Node<T>* a, Node<T>* b, Node<T>* c){
        auto l = a->p->l;
        auto r = a->p->r;

        bool leftcb = c == b->l;
        bool leftba = b == a->l;

        Node<T>* x = nullptr;
        Node<T>* y = nullptr;
        Node<T>* z = nullptr;

        std::shared_ptr<Node<T>> t1;
        std::shared_ptr<Node<T>> t2;
        std::shared_ptr<Node<T>> t3;
        std::shared_ptr<Node<T>> t4;

        if(leftcb && leftba){ // caso 1
            std::shared_ptr<Node<T>> sa = (a == l) ? l : r;
            auto sb = a->l;
            auto sc = b->l;

            x = c;
            y = b;
            z = a;

            t1 = x->l;
            t2 = x->r;
            t3 = y->r;
            t4 = z->r;

        } else if (!leftcb && leftba){ // caso 2
            std::shared_ptr<Node<T>> sa = (a == l) ? l : r;
            auto sb = a->l;
            auto sc = b->r;

            x = b;
            y = c;
            z = a;

            t1 = x->l;
            t2 = y->l;
            t3 = y->r;
            t4 = z->r;

        } else if (leftcb && !leftba){ // caso 3
            std::shared_ptr<Node<T>> sa = (a == l) ? l : r;
            auto sb = a->r;
            auto sc = b->l;

            x = a;
            y = c;
            z = b;

            t1 = x->l;
            t2 = y->l;
            t3 = y->r;
            t4 = z->r;

        } else { // caso 4
            std::shared_ptr<Node<T>> sa = (a == l) ? l : r;
            auto sb = a->r;
            auto sc = b->r;

            x = a;
            y = b;
            z = c;

            t1 = x->l;
            t2 = y->l;
            t3 = z->l;
            t4 = z->r;
        }

        if(a->p){
            a->p = y;
        } else {
            root = y;
        }

        y->l = x;
        y-r = z;
        x->l = t1;
        x->r = t2;
        z->l = t3;
        z->r = t4;

    }

    void updateHeight(Node<T>* node){
        auto parent = node->p;
        if(parent){
            parent->height = node->height + 1;
            updateHeight(parent);
        }
    }

    //---------------------------------PROFE---------------------------------

private:
    std::shared_ptr<Node<T>> root;
};

template <typename T>
class arbolRojoNego{
public:
    template <typename S>
    class Node{
        friend class arbolRojoNego;
        S info;
        Node<S>* padre;
        std::shared_ptr<Node<S>> Izq;
        std::shared_ptr<Node<S>> Der;
        bool esRojo;
    };

private:
    std::shared_ptr<Node<T>> raiz;
};



int main() {
    AVLTree<int> t;
    AVLTree<int> t2;

    t.insert2(42);
    t.insert2(52);
    t.insert2(3);
    t.insert2(9);
    t.insert2(24);


    return 0;
}
