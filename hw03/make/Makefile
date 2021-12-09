# Files
EXEC 	:= tardis
SRC	:= $(wildcard *.c)
OBJ	:= $(patsubst %.c,%.o,$(SRC))
# Options
CC	:= gcc
CFLAGS	:= -O3
GSL_DIR := -I$(TACC_GSL_INC)
GSL_LIB := -L$(TACC_GSL_LIB)
LDLIBS  := -lgsl -lgslcblas
#Rules
$(EXEC): $(OBJ)
	$(CC) $(GSL_DIR) $(GSL_LIB) $(LDLIBS) -o $@ $^
%.o: %.c
	$(CC) $(GSL_DIR) $(GSL_LIB) $(LDLIBS) $(CFLAGS) -c $<
main.c mytools.c: mytools.h
#Useful phony targets
.PHONY: clean neat echo
clean:  neat
	$(RM) $(EXEC)
	$(RM) $(OBJ)
echo:
	@echo $(OBJ)
