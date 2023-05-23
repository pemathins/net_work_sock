#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main(){
	
	int server_sock;
	struct sockaddr_in server_addr;
	int buffer[1024];

	server_sock=socket(AF_INET,SOCK_STREAM,0);
	if(server_sock<0) {printf("error");exit(1);}
	printf("socket created\n");
	
	memset(&server_addr,'\0',sizeof(server_addr));

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=5555;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	printf("Connected to server\n");

	while(1){
		int n;
		scanf("%d",&n);
		memset(buffer,0,1024);
		for(int i=0;i<n;i++) scanf("%d",&buffer[i]);
		send(server_sock,&n,sizeof(n),0);
		send(server_sock,&buffer,1024*sizeof(buffer[0]),0);
		memset(buffer,0,1024);
		recv(server_sock,&buffer,1024*sizeof(buffer[0]),0);
		for(int i=0;i<n;i++) printf("%d ",buffer[i]);
		printf("\n");
	}
	close(server_sock);
	return;
}
