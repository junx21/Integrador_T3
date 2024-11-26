# Link del Repositorio

https://github.com/junx21/Integrador_T3.git

# Trabajos Prácticos

## Descripción del Proyecto
Este proyecto se centra en la implementación de funciones para cargar scripts en Tiny-Lisp utilizando C++ en CLion. El objetivo es desarrollar funciones robustas para cargar y mostrar scripts desde archivos, manejando adecuadamente los errores potenciales.

## Contenido del Proyecto

### 1. Carga de Scripts en Tiny-Lisp
El módulo `Labmain.cpp` define la función `load_script()`, que se utiliza para cargar un script en la memoria y aplicarle la coloración sintáctica. Esta función se basa en la librería estándar de C.

#### Funciones a Implementar
- `void load_script(const char* filename, bool show_script = false);`
- `void load_script();`

**Objetivo**: Implementar estas funciones para abrir y leer archivos de texto. La primera función toma el nombre de un archivo como entrada del usuario, mientras que la segunda muestra el contenido del archivo. Ambos métodos deben cargar el script en la consola.

### 2. Asegurando la Robustez del Código
Asegúrate de que tu código pueda manejar diferentes tipos de errores de entrada, tales como:
- El usuario proporciona un nombre de archivo que no existe.
- El archivo proporcionado no se puede abrir.
- Se produce un error durante la lectura del archivo.

Se recomienda agregar comprobaciones de errores adicionales para manejar los fallos de manera más sofisticada.

## Rúbrica
### Carga de Scripts (50 puntos)
- Implementación correcta de `load_script(const char* filename, bool show_script = false)` que carga correctamente el archivo dado y muestra su contenido si `show_script` es verdadero. (25 puntos)
- Implementación correcta de `load_script()` que solicita al usuario un nombre de archivo, llama a la función `load_script(const char* filename, bool show_script = false)` y maneja cualquier error apropiadamente. (25 puntos)

### Manejo de Errores (50 puntos)
- Manejo de errores sólido para el caso donde el nombre del archivo proporcionado no existe. (15 puntos)
- Manejo de errores sólido para el caso donde el archivo proporcionado no se puede abrir. (15 puntos)
- Manejo de errores sólido para el caso donde se produce un error durante la lectura del archivo. (20 puntos)

## Notas
Este ejercicio no requiere el uso de funciones seguras específicas de Microsoft (las funciones con sufijo `_s`). En cambio, deberías usar las funciones estándar de C/C++ disponibles en todas las plataformas y compiladores, como `fopen`, `printf` y `scanf`.

## Propuesta de Solución
A continuación se muestra cómo se podría reescribir el código para CLion:

```cpp
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox {
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false) {
    string script;
    FILE* f = nullptr;
    try {
        f = fopen(filename, "rb");
        if (!f) {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0) {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script) {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    } catch (...) {
        cerr << "error durante la lectura del archivo" << endl;
        if(f) fclose(f);
    }
}

void load_script() {
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
```
# Conrección 

Voy a corregir el ejercicio Caso Integrador 3 de Luis Crespo Garcia 

# Mejoras Propuestas para el Código

## main.cpp

### 1. Implementar manejo de excepciones
```cpp
#include "cargararchivo.h"
#include <iostream>

int main() {
    try {
        load_script();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

cargaarchivo.cpp
1. Usar std::string para nombres de archivo
cpp
void load_script(const std::string& filename, bool show_script = false)

2. Implementar manejo de excepciones
cpp
if (!file) {
    throw std::runtime_error("No se pudo abrir el archivo '" + filename + "'.");
}

3. Utilizar std::string_view para eficiencia
cpp
#include <string_view>
void load_script(std::string_view filename, bool show_script = false)

4. Añadir validación de nombre de archivo
cpp
bool is_valid_filename(const std::string& filename) {
    return !filename.empty() && filename.find_first_of("/\\?%*:|\"<>") == std::string::npos;
}

5. Mejorar la función load_script() sin argumentos
cpp
void load_script() {
    std::string filename;
    do {
        std::cout << "Ingrese el nombre del archivo: ";
        std::getline(std::cin, filename);
    } while (!is_valid_filename(filename));

    load_script(filename, true);
}
