
CC=gcc

FLAGS+=-g -Wall  -liconv

DEBUG+=-D_TEST_URL

SRC+= *.c

TARGET=ben

$(TARGET):$(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)  $(DEBUG)


clean:
	rm -rf $(TARGET) *.o
