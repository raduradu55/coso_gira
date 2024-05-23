

C_FILES = src/*.c
INCLUDES = -I src/include
LINKERS = -L src/lib -lSDL2main -lSDL2
FLAGS = -Wall

EXE_DIR = bin
EXE_NAME = coso_gira
STANDARD = c99

build:
	gcc -std=$(STANDARD) $(C_FILES) -o $(EXE_DIR)/$(EXE_NAME) $(LINKERS) $(FLAGS)

run:
	$(EXE_DIR)/$(EXE_NAME)

clean:
	del $(EXE_DIR)\*.exe