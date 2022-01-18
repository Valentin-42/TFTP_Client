#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_SIZE 128

int main(int, char* []);
void DISPLAY_IP(struct addrinfo);
void read_request(int, char*);
