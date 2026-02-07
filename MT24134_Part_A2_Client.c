// Roll No: MT24134
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 5002
#define NUM_FIELDS 8

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <seconds> <field_size>\n", argv[0]);
        return 1;
    }

    int duration = atoi(argv[1]);
    size_t field_size = atol(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    char *buf = malloc(field_size);

    time_t start = time(NULL);
    while (time(NULL) - start < duration) {
        for (int i = 0; i < NUM_FIELDS; i++) {
            recv(sock, buf, field_size, 0);
        }
    }

    free(buf);
    close(sock);
    return 0;
}