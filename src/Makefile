TARGET     = truthtable
CC         = gcc
SANITIZERS = -fsanitize=address $(if $(findstring clang,$(CC)),-fsanitize=undefined)
OPT        =
CFLAGS     = -g -std=c99 -Wall -Wvla -Werror  -lmath $(SANITIZERS) $(OPT)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(TARGET) *.o *.a *.dylib *.dSYM
