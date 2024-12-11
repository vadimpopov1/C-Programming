# Собрать многофайловый проект
# Подсказка: Опция -I в gcc помогает решить проблему с поиском заголовочных файлов. (#include "" No such file or directory)
# Для использования make его необходимо установить: sudo apt install make

CC = gcc
CFLAGS = -Wall -Ibackground -Ipipes

SRC = app/main.c background/background.c pipes/read_pipe.c pipes/write_pipe.c
OBJ = $(SRC:.c=.o)

TARGET = task0

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)


# ./task0
# cd Downloads/tasks/task0