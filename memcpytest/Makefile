#
TARGET = memcpytest

#
CFLAGS = -O3 -Wall -std=c++17
LDFLAGS = -O3 -Wall -Wl,--no-as-needed -ldl -pthread 
CC = g++ 

build: $(TARGET)

$(TARGET): $(TARGET).o 
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~


