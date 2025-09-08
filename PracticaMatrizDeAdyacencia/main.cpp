#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>

class Grafo {
private:
    int N; // Número de nodos
    std::vector<std::vector<int>> MatrizAdyacencia;
    std::unordered_map<std::string, int> NodoIndiceMap; // Mapa de nombres de nodos a índices

public:
    Grafo(int N) : N(N), MatrizAdyacencia(N, std::vector<int>(N, 0)) {}

    // Agrega un nodo al grafo
    void addNode(const std::string& nodeName) {
        if(NodoIndiceMap.size() >= N) {
            std::cout << "Error: se ha alcanzado el número máximo de nodos." << std::endl;
            return;
        }
        int index = NodoIndiceMap.size(); // Índice del nuevo nodo
        NodoIndiceMap[nodeName] = index;
    }

    // Añade una arista entre dos nodos con un peso específico
    void addAdyacency(const std::string& nodeA, const std::string& nodeB, int weight) {
        int indexA = NodoIndiceMap[nodeA];
        int indexB = NodoIndiceMap[nodeB];
        MatrizAdyacencia[indexA][indexB] = weight;
        MatrizAdyacencia[indexB][indexA] = weight;
    }

    // Verifica si dos nodos son adyacentes
    bool areAdyacent(const std::string& nodeA, const std::string& nodeB) {
        int indexA = NodoIndiceMap[nodeA];
        int indexB = NodoIndiceMap[nodeB];
        return MatrizAdyacencia[indexA][indexB] != 0;
    }

    // Devuelve una lista de nodos adyacentes a un nodo dado
    std::list<std::string> Adyacents(const std::string& nodeName) {
        int index = NodoIndiceMap[nodeName];
        std::list<std::string> adyacentNodes;
        for (int i = 0; i < N; ++i) {
            if (MatrizAdyacencia[index][i] != 0) {
                for (auto& pair : NodoIndiceMap) {
                    if (pair.second == i) {
                        adyacentNodes.push_back(pair.first);
                        break;
                    }
                }
            }
        }
        return adyacentNodes;
    }

    // Elimina la arista entre dos nodos
    void removeAdyacency(const std::string& nodeA, const std::string& nodeB) {
        int indexA = NodoIndiceMap[nodeA];
        int indexB = NodoIndiceMap[nodeB];
        MatrizAdyacencia[indexA][indexB] = 0;
        MatrizAdyacencia[indexB][indexA] = 0; // El grafo es no dirigido
    }
};

int main() {
    Grafo g(5);
    g.addNode("Madird");
    g.addNode("Sevilla");
    g.addNode("Barcelona");
    g.addNode("Valencia");
    g.addNode("Zaragoza");
    g.addAdyacency("Madrid", "Sevilla", 1);
    g.addAdyacency("Madrid", "Barcelona", 1);
    g.addAdyacency("Madrid", "Valencia", 1);
    g.addAdyacency("Madrid", "Zaragoza", 1);
    g.addAdyacency("Barcelona", "Sevilla", 1);
    g.addAdyacency("Valencia", "Zaragoza", 1);


    if (g.areAdyacent("Madrid", "Zaragoza")) {
        std::cout << "Madrid y Zaragoza son adyacentes." << std::endl;
    }

    auto adyacentesA = g.Adyacents("Madrid");
    std::cout << "Nodos adyacentes a Madrid: ";
    for (const auto& nodeName : adyacentesA) {
        std::cout << nodeName << " ";
    }
    std::cout << std::endl;

    return 0;
}

