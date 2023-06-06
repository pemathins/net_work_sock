#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ntohs(9145);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr("127.0.0.1")

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));

    struct sockaddr_in tempSendAddr;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    char buf[100];
    int len = sizeof(struct sockaddr);

    recvfrom(serverSocket, buf, 100, 0, (struct sockaddr *)&tempSendAddr, &len);
    
    printf("Recieved from Client : %s\n", buf);

    char rev[100];
    int j = 0;
    len = strlen(buf);
    for(int g = len - 1 ; g >= 0; g--) {
        rev[j++] =  buf[g];
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(9145);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(serverSocket, rev, sizeof(rev), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
}
