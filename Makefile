#comandos recorrentemente executados
EXEC = ./bin/main
CC = gcc
INCLUDE = -I./include

#e importante declarar essas variaveis com os nomes das pastas para que se mudarmos o nome seja mais facil muda-las no arquivo
SRC = ./src
OBJ = ./obj
APP = ./app

#condicional com os comandos respectivos do sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC := $(EXEC).exe
	OBJCLEAN = .\obj\
	BINCLEAN = .\bin\*.exe
else
	EXEC = ./bin/main
    RM = rm -f
	OBJCLEAN = ./obj/
	BINCLEAN = ./bin/*
endif

#target de compilacao (comando pra compilar no windows -> mingw32-make || comando pra compilar no linux -> make)
all:
#faco a compilacao dos arquivos do src (.c) e transformo-os em objetos
	$(CC) -c $(SRC)/TADDrone.c $(INCLUDE) -o $(OBJ)/TADDrone.o
	$(CC) -c $(SRC)/TADGalpao.c $(INCLUDE) -o $(OBJ)/TADGalpao.o
	$(CC) -c $(SRC)/TADListaDePacotes.c $(INCLUDE) -o $(OBJ)/TADListaDePacotes.o
	$(CC) -c $(SRC)/TADPacote.c $(INCLUDE) -o $(OBJ)/TADPacote.o
#faco a compilacao do main tranformando-o em um executavel
	$(CC) $(APP)/main.c $(OBJ)/*.o $(INCLUDE) -o $(EXEC)

#target de execucao (comando pra compilar no windows -> mingw32-make run || comando pra compilar no linux -> make run)
run:
	$(EXEC)

#target que limpeza (comando pra compilar no windows -> mingw32-make clean || comando pra compilar no linux -> make clean)
clean:
	$(RM) $(OBJCLEAN)* $(BINCLEAN)
