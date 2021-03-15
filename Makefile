CC=gcc
CXX=g++
CFLAGS=-Wall -g -O0

TARGET = vulnerable

.PHONY: clean $(TARGET) test 

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean: 
	$(RM) $(TARGET)

test: # add your command