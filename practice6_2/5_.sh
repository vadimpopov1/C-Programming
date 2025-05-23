gcc -dynamiclib -fPIC src/train_input_output.c src/train_search.c -Iinclude -o lib/libtrain.so
gcc src/main_dyn.c -Iinclude -ldl -o train_dynamic 
./train_dynamic