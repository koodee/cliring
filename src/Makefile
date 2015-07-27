CC = clang
OBJ = keyring.o password.o main.o
OUT = cliring
LFLAGS = $(shell pkg-config --libs gnome-keyring-1)
CFLAGS = $(shell pkg-config --cflags gnome-keyring-1) -g

all: $(OBJ)
	$(CC) $^ -o $(OUT) $(LFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(OUT)
