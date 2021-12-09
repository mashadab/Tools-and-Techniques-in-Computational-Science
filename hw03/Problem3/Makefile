# Files
EXEC 	:= integrate
SRC	:= $(wildcard *.c)
OBJ	:= $(patsubst %.c,%.o,$(SRC))
# Options
CC	:= g++
#Rules
$(EXEC): $(OBJ)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) -c $<
main.c: func.h trapezoidal.h simpson.h
#Useful phony targets
.PHONY: clean neat echo
clean:  neat
	$(RM) $(EXEC)
	$(RM) $(OBJ)
echo:
	@echo $(OBJ)
