gcc -c src/train_input_output.c -Iinclude -o train_input_output.o # Компиляций объектных файлов
gcc -c src/train_search.c -Iinclude -o train_search.o # Компиляций объектных файлов
gcc -shared train_input_output.o train_search.o -o lib/libtrain.so # Создание динамической библиотеки
gcc src/main.c -Iinclude -Llib -ltrain -Wl,-rpath,lib -o train_program # Компиляция программы + библиотека
./train_program