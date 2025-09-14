#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
// Nodo AVL
template <typename T>
class NodoAVL {
public:
    T clave;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(T c)
        : clave(c), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Árbol AVL
template <typename T>
class ArbolAVL {
private:
    NodoAVL<T>* raiz;

    int obtenerAltura(NodoAVL<T>* nodo) {
        return nodo == nullptr ? 0 : nodo->altura;
    }

    int obtenerBalance(NodoAVL<T>* nodo) {
        return nodo == nullptr ? 0 : obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
    }

    NodoAVL<T>* rotarDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izquierdo;
        NodoAVL<T>* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
        x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

        return x;
    }

    NodoAVL<T>* rotarIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->derecho;
        NodoAVL<T>* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
        y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

        return y;
    }

    NodoAVL<T>* insertar(NodoAVL<T>* nodo, T clave) {
        if (nodo == nullptr)
            return new NodoAVL<T>(clave);

        if (clave < nodo->clave)
            nodo->izquierdo = insertar(nodo->izquierdo, clave);
        else if (clave > nodo->clave)
            nodo->derecho = insertar(nodo->derecho, clave);
        else
            return nodo; // duplicados no se permiten

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && clave < nodo->izquierdo->clave)
            return rotarDerecha(nodo);

        if (balance < -1 && clave > nodo->derecho->clave)
            return rotarIzquierda(nodo);

        if (balance > 1 && clave > nodo->izquierdo->clave) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }

        if (balance < -1 && clave < nodo->derecho->clave) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    NodoAVL<T>* nodoMinimo(NodoAVL<T>* nodo) {
        NodoAVL<T>* actual = nodo;
        while (actual->izquierdo != nullptr)
            actual = actual->izquierdo;
        return actual;
    }

    NodoAVL<T>* eliminar(NodoAVL<T>* nodo, T clave) {
        if (nodo == nullptr)
            return nodo;

        if (clave < nodo->clave)
            nodo->izquierdo = eliminar(nodo->izquierdo, clave);
        else if (clave > nodo->clave)
            nodo->derecho = eliminar(nodo->derecho, clave);
        else {
            if (nodo->izquierdo == nullptr || nodo->derecho == nullptr) {
                NodoAVL<T>* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    *nodo = *temp;
                }
                delete temp;
            } else {
                NodoAVL<T>* temp = nodoMinimo(nodo->derecho);
                nodo->clave = temp->clave;
                nodo->derecho = eliminar(nodo->derecho, temp->clave);
            }
        }

        if (nodo == nullptr)
            return nodo;

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0)
            return rotarDerecha(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }

        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0)
            return rotarIzquierda(nodo);

        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    bool buscar(NodoAVL<T>* nodo, T clave) {
        if (nodo == nullptr) return false;
        if (clave == nodo->clave) return true;
        if (clave < nodo->clave) return buscar(nodo->izquierdo, clave);
        return buscar(nodo->derecho, clave);
    }

    void recorrerPreorden(NodoAVL<T>* nodo) {
        if (nodo != nullptr) {
            cout << nodo->clave << " ";
            recorrerPreorden(nodo->izquierdo);
            recorrerPreorden(nodo->derecho);
        }
    }

public:
    ArbolAVL() : raiz(nullptr) {}

    void insertar(T clave) { raiz = insertar(raiz, clave); }

    void eliminar(T clave) { raiz = eliminar(raiz, clave); }

    bool buscar(T clave) { return buscar(raiz, clave); }

    void imprimirPreorden() { recorrerPreorden(raiz); cout << endl; }
};

// Convierte un entero a string
string normalizarNumero(int n) {
    ostringstream ss;
    ss << setw(4) << setfill('0') << n;
    return ss.str();
}
int main() {
    ArbolAVL<string> arbol;

    arbol.insertar(normalizarNumero(1));
    arbol.insertar(normalizarNumero(2));
    arbol.insertar(normalizarNumero(3));
    arbol.insertar(normalizarNumero(4));
    arbol.insertar(normalizarNumero(200));
    arbol.insertar("z");
    arbol.insertar("Z");

    cout << "Recorrido preorden: ";
    arbol.imprimirPreorden();

    cout << (arbol.buscar("Z") ? "\nEncontrado Z" : "\nNo encontrado Z") << endl;
    cout << (arbol.buscar(normalizarNumero(200)) ? "Encontrado 200" : "No encontrado 200") << endl;

    arbol.eliminar("Z");
    cout << "Tras eliminar Z, preorden: ";
    arbol.imprimirPreorden();
}