# AVL Tree en C++

## 📌 Descripción
Este proyecto implementa un **Árbol AVL** en C++, una estructura de datos balanceada que extiende el **árbol binario de búsqueda (BST)**.  
El árbol se mantiene balanceado después de cada inserción o eliminación mediante **rotaciones**, garantizando que las operaciones se realicen en tiempo `O(log n)`.

Además, el proyecto soporta la **regla personalizada de ordenación**:
**números < letras mayúsculas < letras minúsculas**

---

## ⚙️ Estructura del Código

### Clases principales:
- **`NodoAVL`**: representa un nodo del árbol (clave, punteros izquierdo y derecho, altura).
- **`ArbolAVL`**: contiene la raíz y las operaciones principales.

### Operaciones implementadas:
1. **Insertar (`insertar`)**
   - Inserta un nuevo elemento en el árbol.
   - Mantiene el balance usando rotaciones (LL, RR, LR, RL).

2. **Eliminar (`eliminar`)**
   - Elimina un nodo manteniendo la propiedad del AVL.
   - Caso con 0, 1 o 2 hijos.
   - Rebalancea el árbol después de la eliminación.

3. **Buscar (`buscar`)**
   - Verifica si un valor existe en el árbol.

4. **Recorrido Preorden (`imprimirPreorden`)**
   - Muestra los nodos en recorrido preorden.

---

## 🚀 Ejecución

### 1. Compilar el programa
```bash
g++ AVL-Tree.cpp -o avl
./avl
