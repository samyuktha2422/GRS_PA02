// Roll No: MT24134
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/uio.h>

#define PORT 5003
#define NUM_FIELDS 8

typedef struct {
    char *fields[NUM_FIELDS];
} message_t;

typedef struct {
    int sock;
    size_t field_size;
} thread_arg_t;

void *handle_client(void *arg) {
    thread_arg_t *t = (thread_arg_t *)arg;

    message_t msg;
    struct iovec iov[NUM_FIELDS];

    for (int i = 0; i < NUM_FIELDS; i++) {
        msg.fields[i] = aligned_alloc(4096, t->field_size);
        memset(msg.fields[i], 'A' + i, t->field_size);
        iov[i].iov_base = msg.fields[i];
        iov[i].iov_len = t->field_size;
    }

    struct msghdr hdr = {0};
    hdr.msg_iov = iov;
    hdr.msg_iovlen = NUM_FIELDS;

    while (sendmsg(t->sock, &hdr, MSG_ZEROCOPY) > 0);

    for (int i = 0; i < NUM_FIELDS; i++)
        free(msg.fields[i]);
    close(t->sock);
    free(t);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <threads> <field_size>\n", argv[0]);
        return 1;
    }

    int threads = atoi(argv[1]);
    size_t field_size = atol(argv[2]);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, threads);

    while (1) {
        int client = accept(server_fd, NULL, NULL);
        pthread_t tid;
        thread_arg_t *t = malloc(sizeof(*t));
        t->sock = client;
        t->field_size = field_size;
        pthread_create(&tid, NULL, handle_client, t);
        pthread_detach(tid);
    }
}