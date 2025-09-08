#include <iostream>
#include <memory>
#include "ArbolesNario.h"
#include "ArbolesBinarios.h"
#include "ArbolesBinariosDeBusqueda.h"

int main() {
    auto raiz = std::make_shared<LinkedTree<int>::Node<int>>(1);
    LinkedTree<int> arbol(raiz);

    auto hijo1 = arbol.add(2, raiz.get());
    auto hijo2 = arbol.add(3, raiz.get());

    arbol.add(4, hijo1);
    arbol.add(5, hijo1);
    arbol.add(6, hijo2);
    arbol.add(7, hijo2);


    if (arbol.isEmpty()){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isRaiz(raiz.get())){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isHoja(hijo2)){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isInternal(hijo2)){std::cout << "si\n";} else {std::cout << "no\n";}

    auto raizDelArbol = arbol.getRaiz();
    auto padreDeNieto1 = arbol.getPadre(hijo1);
    if (raizDelArbol == padreDeNieto1){std::cout << "si\n";} else {std::cout << "no\n";}

    /*
    auto hijosDeRaiz = arbol.getHijos(raizDelArbol);
    std::cout << "Hijos de la raiz: ";
    for (auto hijo : hijosDeRaiz) {
        std::cout << hijo << " ";
    }
    std::cout << std::endl;
    */

    //auto arbolCortado2 = arbol.cutCHATGPT(hijo1);
    auto arbolCortado = arbol.cut2(hijo1);

    std::cout << "Recorrido Preorden: ";
    arbol.preorden();
    std::cout << std::endl;

    std::cout << "Recorrido Inorden (interpretado para estructura no binaria): ";
    arbol.inorden();
    std::cout << std::endl;

    std::cout << "Recorrido Postorden: ";
    arbol.postorden();
    std::cout << std::endl;

    arbol.attach(raiz.get(), arbolCortado);

    std::cout << "Recorrido Preorden: ";
    arbol.preorden();
    std::cout << std::endl;

    return 0;
}

int mainLCRS(){
    auto raiz = std::make_shared<LCRSTree<int>::Node<int>>(1);
    LCRSTree<int> arbol(raiz);

    // Agregar hijos al nodo raíz
    auto hijo1 = arbol.add(2, raiz.get());
    auto hijo2 = arbol.add(3, raiz.get());
    auto hijo3 = arbol.add(4, raiz.get());

    // Agregar hijos a uno de los nodos hijos de la raíz
    auto nieto1 = arbol.add(5, hijo1);
    auto nieto2 = arbol.add(6, hijo1);

    if (arbol.isEmpty()){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isRaiz(raiz.get())){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isHoja(hijo2)){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isInternal(hijo2)){std::cout << "si\n";} else {std::cout << "no\n";}

    auto raizDelArbol = arbol.getRaiz();
    auto padreDeNieto1 = arbol.getPadre(hijo1);
    if (raizDelArbol == padreDeNieto1){std::cout << "si\n";} else {std::cout << "no\n";}

    // Mostrar el árbol usando recorridos
    std::cout << "Recorrido Preorden del arbol original: ";
    arbol.preorden();

    std::cout << "\nRecorrido Postorden del arbol original: ";
    arbol.postorden();

    // Cortar un subárbol y mostrar el árbol resultante
    auto arbolCortado = arbol.cut(hijo1);
    std::cout << "\nRecorrido Preorden del arbol despues de cortar: ";
    arbol.preorden();

    std::cout << "\nRecorrido Preorden del subarbol cortado: ";
    arbolCortado.preorden();

    return 0;
}

int mainBinario() {
    // Crear el árbol binario vinculado
    LinkedBinaryTree<int> arbol;

    // Agregar la raíz y algunos nodos al árbol
    auto raiz = arbol.addRoot(1);
    auto hijoIzq = arbol.addHijoIzq(2, raiz);
    auto hijoDer = arbol.addHijoDer(3, raiz);

    // Agregar más nodos para hacer el árbol interesante
    arbol.addHijoIzq(4, hijoIzq);
    arbol.addHijoDer(5, hijoIzq);
    arbol.addHijoIzq(6, hijoDer);
    arbol.addHijoDer(7, hijoDer);

    if (arbol.isEmpty()){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isRaiz(raiz)){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isHoja(hijoIzq)){std::cout << "si\n";} else {std::cout << "no\n";}
    if (arbol.isInternal(hijoIzq)){std::cout << "si\n";} else {std::cout << "no\n";}

    auto raizDelArbol = arbol.getRaiz();
    auto padreDeNieto1 = arbol.getPadre(hijoIzq);
    if (raizDelArbol == padreDeNieto1){std::cout << "si\n";} else {std::cout << "no\n";}

    // Mostrar el árbol usando recorridos
    std::cout << "Recorrido Preorden del arbol: ";
    arbol.preorden();

    std::cout << "Recorrido Inorden del arbol: ";
    arbol.inorden();

    std::cout << "Recorrido Postorden del arbol: ";
    arbol.postorden();

    // Cortar un subárbol y mostrar los árboles resultantes
    std::cout << "\nCortando el arbol en el nodo con el valor 2...\n";
    auto arbolCortado = arbol.cut(hijoIzq);

    std::cout << "Recorrido Preorden del arbol original despues del corte: ";
    arbol.preorden();

    std::cout << "Recorrido Preorden del subarbol cortado: ";
    arbolCortado.preorden();

    return 0;
}

int mainABB() {
    ABB<int> arbol; // Crea un árbol para almacenar enteros

    // Inserta algunos valores
    arbol.insert(10);
    arbol.insert(5);
    arbol.insert(15);
    arbol.insert(3);
    arbol.insert(7);
    arbol.insert(12);
    arbol.insert(18);

    // Muestra el contenido del árbol en preorden, inorden y postorden
    std::cout << "Recorrido en preorden: ";
    arbol.preorden();

    std::cout << "Recorrido en inorden: ";
    arbol.inorden();

    std::cout << "Recorrido en postorden: ";
    arbol.postorden();

    return 0;
}

int mainAVL() {
    AVLTree<int> avlTree;

    // Insertar elementos en el árbol
    avlTree.insert(30);
    avlTree.insert(20);
    avlTree.insert(40);
    avlTree.insert(10);
    avlTree.insert(25);
    avlTree.insert(5);
    //avlTree.insert(27);

    // Mostrar el árbol usando recorridos
    std::cout << "Recorrido Preorden: ";
    avlTree.preorden();

    std::cout << "Recorrido Inorden: ";
    avlTree.inorden();

    std::cout << "Recorrido Postorden: ";
    avlTree.postorden();

    return 0;
}