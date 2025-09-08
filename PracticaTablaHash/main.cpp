#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <unordered_set>
#include <random>
#include <ctime>

struct Persona {
    std::string nombre;
    std::string apellidos;
    unsigned long long num_DNI;
    char letra_DNI;
    bool es_valida;

    Persona(std::string nombre, std::string apellidos, unsigned long long num_DNI, char letra_DNI, bool es_valida)
            : nombre(nombre), apellidos(apellidos), num_DNI(num_DNI), letra_DNI(letra_DNI), es_valida(es_valida) {}
};

bool operator==(const Persona& lhs, const Persona& rhs) {
    return lhs.nombre == rhs.nombre &&
           lhs.apellidos == rhs.apellidos &&
           lhs.num_DNI == rhs.num_DNI &&
           lhs.letra_DNI == rhs.letra_DNI;
}

template <typename T, int N=100>
int hash (const T& e){
    if (e.num_DNI){
        int num = e.num_DNI%N;
        return num;
    } else {
        return -1;
    }
}

template <typename T, int N=100>
class efficientStorage {
private:
    std::vector<std::shared_ptr<T>> almacen;
    int colisiones;
public:
    efficientStorage() : almacen(N, nullptr), colisiones(0) {}

    void insertar(const T& e){
        auto p = std::make_shared<T>(e);
        auto digit = hash(e);
        if (almacen[digit] != nullptr && almacen[digit]->es_valida){
            colisiones++;
        } else {
            almacen[digit] = p;
        }
    }

    void borrado(const T& e){
        auto digit = hash(e);
        if (almacen[digit] != nullptr && almacen[digit]->es_valida){
            almacen[digit]->es_valida = false;
        }
    }

    bool countains(const T& e){
        auto digit = hash(e);
        if (almacen[digit] != nullptr && almacen[digit]->es_valida){
            return true;
        } else {
            return false;
        }
    }

    int colissions(){
        return colisiones;
    }
};


template <typename T, int N=100>
class efficientStorageColissionsYes {
private:
    std::vector<std::list<std::shared_ptr<T>>> almacen;
public:
    efficientStorageColissionsYes() : almacen(N) {}

    void insertar(const T& e){
        auto p = std::make_shared<T>(e);
        auto digit = hash(e);
        almacen[digit].push_back(p);
    }

    void borrado(const T& e){
        auto digit = hash(e);
        for (auto it = almacen[digit].begin(); it != almacen[digit].end(); ++it) {
            if ((*it)->num_DNI == e.num_DNI && (*it)->letra_DNI == e.letra_DNI) {
                almacen[digit].erase(it);
                return;
            }
        }
    }

    bool countains(const T& e){
        auto digit = hash(e);
        for (const auto& it: almacen[digit]) {
            if (it->num_DNI == e.num_DNI && it->letra_DNI == e.letra_DNI) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    efficientStorageColissionsYes<Persona> lista;
    auto p = std::make_shared<Persona>("hola", "adios", 11111111, 'A', true);
    lista.insertar(*p);
    auto p2 = std::make_shared<Persona>("adios", "put", 11111111, 'B', true);
    lista.insertar(*p2);
    if (lista.countains(*p)){
        printf("SIUU\n");
    }
    //printf("%d\n", lista.colissions());
    lista.borrado(*p);
    if (!lista.countains(*p)){
        printf("p no esta en nuestro almacen");
    }
    return 0;
}
