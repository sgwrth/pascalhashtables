C = fpc
FLAGS = -Sew -Miso
OUTPUT = HashTables
OUTPUT_DIR = ./bin/
SOURCE = $(OUTPUT).pas
SOURCE_DIR = ./src/

all: $(OUTPUT)

$(OUTPUT): $(SOURCE_DIR)$(SOURCE)
	$(C) $(FLAGS) $(SOURCE_DIR)$(SOURCE) -FE$(OUTPUT_DIR)

clean:
	rm ./bin/*
