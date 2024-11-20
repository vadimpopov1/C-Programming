# Название программы
TARGET = romb_program

# Компилятор
CC = gcc

# Исходные файлы
SRCS = main.c romb.c

# Объектные файлы (из исходных)
OBJS = $(SRCS:.c=.o)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Правило для создания объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для чистки
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

# Правило по умолчанию
all: $(TARGET)
