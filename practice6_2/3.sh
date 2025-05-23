gcc -c src/train_input_output.c -Iinclude -o train_input_output.o # Компиляций объектных файлов
gcc -c src/train_search.c -Iinclude -o train_search.o # Компиляций объектных файлов
ar rc lib/libtrain.a train_input_output.o train_search.o # Создание статической библиотеки 'libtrain.a' из объектных файлов
gcc src/main.c -Iinclude -Llib -ltrain -o train_program # Компиляция основного файла с указанием загаловков
./train_program

# -Iinclude указывает компилятору искать заголовочные файлы в каталоге include.
# ar тилита для создания, модификации и извлечения из архивов
# rc опции для создания (или замены) библиотеки и добавления в нее указанных файлов.
