#include <iostream>
#include <string>
#include <vector>
#include <list>

template <typename ValueType>
class MyClass {
public:
    ValueType operator[](int idx) const {
        return a[idx]; // creo una copia temporal
    }

    ValueType &operator[](int idx) {
        return a[idx]; // devuelvo la direccion y puedo modificarlo.
    }

private:
    std::vector<ValueType> a{100};
};

template <typename KeyType, typename valueType, int size = 100>
class HashMapES{
public:

    valueType operator[](KeyType k) const{
        auto idx = compress(std::hash<KeyType>(k));
        bool encontrado = false;
        auto it = a[idx].begin();
        while (!encontrado && (it != a[idx].end())){
            encontrado = (*it).first == k;
            if (!encontrado) ++it;
        }
        if (encontrado){
            return (*it).second;
        } else {
            return valueType();
        }
    }

    valueType& operator[](KeyType k){
        auto idx = compress(k);
        bool encontrado = false;
        auto it = a[idx].begin();
        while (!encontrado && (it != a[idx].end())){
            encontrado = (*it).first == k;
            if (!encontrado) ++it;
        }
        if (encontrado){
            return (*it).second;
        } else {
            a[idx].push_front(std::make_pair(k, valueType{}));
            return a[idx].front().second;
        }
    }

    bool contains(KeyType clave){
        auto idx = compress(clave);
        bool encontrado = false;
        auto it = a[idx].begin();
        while (!encontrado && (it != a[idx].end())){
            encontrado = (*it).first == clave;
            ++it;
        }
        return encontrado;
    }

private:
   std::vector<std::list<std::pair<KeyType, valueType>>> a{size};

    size_t compress(KeyType valor){
        return valor % size;
    }
};

template <typename KeyType, typename ValueType, int size>
class HashMapLP{
public:

    bool contains(KeyType k){
        int p = 0;
        auto idx = compress(hash(k, p));

    }
private:
    std::vector<std::tuple<KeyType, ValueType, bool>> a{size};

    size_t compress(KeyType valor){
        return valor % size;
    }

    int hash(KeyType k, int p=0){
        return std::hash<KeyType>(k) + p;
    }
};



class printer{
public:
    template <typename valueType>
    void print(MyClass<valueType>& c, int idx) const {
        std::cout << "C[" << idx << "] = " << c[idx] << "\n";
    }
};


int main() {

    MyClass<std::string> c;
    HashMapES<std::string, int> a;
    printer p;
    c[3] = "tres";
    c[42] = "cuarenta y dos";

    std::cout << "c[3] = " << c[3] << "\n";
    p.print(c,42);
    return 0;
}
