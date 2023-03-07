# Makefile for Task Wizard

TARGET = twiz

CC = cc
CFLAGS = -lncurses -lsqlite3
OBJS = twiz.o wizard.o windows.o tasks.o

# Executable

all : $(TARGET)

$(TARGET) : $(OBJS)
	@echo "\033[92mCreating executable: $(TARGET)\033[0m"
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

# Object

%.o : %.c
	@echo "\033[92mCreating Object file: $@\033[0m"
	$(CC) -c $<

# Clean Up

clean:
	@echo "\033[92mCleaning up\033[0m"
	rm -rf $(TARGET) *.o *~

# Dependencey

twiz.o		: twiz.c
window.o	: window.c
