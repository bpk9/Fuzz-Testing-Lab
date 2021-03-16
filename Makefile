CC = afl/afl-gcc
FUZZER = afl/afl-fuzz

TARGET = vulnerable

TESTCASES = in/testcases
FINDINGS = out/findings

$(TARGET):
	$(CC) -o $(TARGET) $(TARGET).c

test:
	make clean
	make $(TARGET)
	$(FUZZER) -i $(TESTCASES) -o $(FINDINGS) ./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf $(FINDINGS)/*
	rm -f $(FINDINGS)/.cur_input