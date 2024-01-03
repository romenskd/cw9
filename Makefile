CC = gcc 
SRC_DIR = src
BIN_DIR = bin

my_program: $(BIN_DIR)/main.o $(BIN_DIR)/mat_io.o $(BIN_DIR)/gauss.o $(BIN_DIR)/backsubst.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/mat_io.h $(SRC_DIR)/gauss.h $(SRC_DIR)/backsubst.h
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/mat_io.o: $(SRC_DIR)/mat_io.c $(SRC_DIR)/mat_io.h
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/gauss.o: $(SRC_DIR)/gauss.c $(SRC_DIR)/gauss.h
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/backsubst.o: $(SRC_DIR)/backsubst.c $(SRC_DIR)/backsubst.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f my_program $(BIN_DIR)/*.o
