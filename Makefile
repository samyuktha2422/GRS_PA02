# Roll No: MT24134
CC=gcc
CFLAGS=-O2 -pthread

all:
	$(CC) $(CFLAGS) MT24134_Part_A1_Server.c -o MT24134_Part_A1_Server
	$(CC) $(CFLAGS) MT24134_Part_A1_Client.c -o MT24134_Part_A1_Client
	$(CC) $(CFLAGS) MT24134_Part_A2_Server.c -o MT24134_Part_A2_Server
	$(CC) $(CFLAGS) MT24134_Part_A2_Client.c -o MT24134_Part_A2_Client
	$(CC) $(CFLAGS) MT24134_Part_A3_Server.c -o MT24134_Part_A3_Server
	$(CC) $(CFLAGS) MT24134_Part_A3_Client.c -o MT24134_Part_A3_Client

clean:
	rm -f MT24134_Part_A1_Server MT24134_Part_A1_Client \
	      MT24134_Part_A2_Server MT24134_Part_A2_Client \
	      MT24134_Part_A3_Server MT24134_Part_A3_Client