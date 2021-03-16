CC = afl/afl-gcc
FUZZER = afl/afl-fuzz

TARGET = vulnerable

TESTCASES = in/testcases
FINDINGS = out/findings

$(TARGET):
	$(CC) -o $(TARGET) $(TARGET).c

test:
	make $(TARGET)
	$(FUZZER) -i $(TESTCASES) -o $(FINDINGS) ./$(TARGET)