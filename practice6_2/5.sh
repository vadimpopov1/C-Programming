cd build # Создаем папку для мейка
rm -rf * # Удалим файлы которые находятся в папке build
read -p "Static Lib - 'ON' Dynamic Lib - 'OFF': " LIB_TYPE # Ввод с клавиатуры
if [[ "$LIB_TYPE" == "ON" ]]; then
    cmake -DUSE_STATIC_LIB=ON ..
elif [[ "$LIB_TYPE" == "OFF" ]]; then
    cmake -DUSE_STATIC_LIB=OFF ..
else
    echo "Incorrect."
    exit 1
fi
make
./practice6_2   