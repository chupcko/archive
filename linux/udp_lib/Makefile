UDPLIB  = udp_lib
SERVER  = server
CLIENT  = client

all: $(UDPLIB).lib $(SERVER) $(CLIENT)

$(UDPLIB).lib: $(UDPLIB).o
	$(AR) cr $(UDPLIB).lib $(UDPLIB).o

$(SERVER): $(SERVER).o $(UDPLIB).lib
	$(CC) -o $(SERVER) $(SERVER).o $(UDPLIB).lib

$(CLIENT): $(CLIENT).o $(UDPLIB).lib
	$(CC) -o $(CLIENT) $(CLIENT).o $(UDPLIB).lib

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CCFLAGS) $<

clean:
	rm -f *.o $(UDPLIB).lib $(SERVER) $(CLIENT)
