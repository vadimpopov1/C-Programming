#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> 

typedef void (*train_func)(const char*);

int main() {
    void* lib_handle;
    char* error;
    
    lib_handle = dlopen("./lib/libtrain.so", RTLD_LAZY); // Флажок который указывает на разреншение/запрет неопределенных символов в виде кода в исполняемой библиотеке
    if (!lib_handle) { // загрузка зависимостей по требованию
        fprintf(stderr, "Error loading libs: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    train_func search_records = (train_func)dlsym(lib_handle, "search_records");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error loading func: %s\n", error);
        dlclose(lib_handle);
        return EXIT_FAILURE;
    }

    train_func add_records = (train_func)dlsym(lib_handle, "add_records");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error loading func: %s\n", error);
        dlclose(lib_handle);
        return EXIT_FAILURE;
    }

    int n;
    printf("Enter counf of routes: ");
    scanf("%d", &n);
    getchar();

    add_records("Train.dat");
    search_records("Train.dat");

    dlclose(lib_handle);
    return EXIT_SUCCESS;
}

// void* dlopen(const char* filename, int flag);  filename: Путь к динамической библиотеке, которую нужно открыть. Это может быть абсолютный или относительный путь. flag: Опции для управления поведением загрузки. Например, RTLD_LAZY (загружать символы по мере необходимости) или RTLD_NOW (загружать все символы сразу).
// void* dlsym(void* handle, const char* symbol); handle: Дескриптор библиотеки, полученный от dlopen. symbol: Имя символа, адрес которого нужно получить.
// int dlclose(void* handle); handle Дескриптор библиотеки, который нужно закрыть.
