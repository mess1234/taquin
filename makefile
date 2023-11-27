CC		:= gcc
CFLAGS	:= -ansi -pedantic -Wall -Wpadded
LDFLAGS	:= -lMLV
OBJ		:= obj/main.o obj/action.o obj/io.o obj/game_data.o obj/coord.o
EXEC	:= bin/taquin.out

######

.PHONY: all
all:
	mkdir -p bin/ obj/
	make $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# C modules

obj/main.o: src/main.c inc/action.h inc/io.h inc/game_data.h inc/coord.h
obj/action.o: src/action.c inc/action.h inc/coord.h inc/game_data.h inc/io.h
obj/coord.o: src/coord.c inc/coord.h
obj/game_data.o: src/game_data.c inc/game_data.h inc/coord.h
obj/io.o: src/io.c inc/io.h inc/coord.h inc/game_data.h

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

######

.PHONY: clean
clean:
	rm -rf bin/ obj/