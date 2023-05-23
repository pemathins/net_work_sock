#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main(){
	
	int server_sock,client_sock,addr_size;
	struct sockaddr_in server_addr, client_addr;
	int buffer[1024];

	server_sock = socket(AF_INET,SOCK_STREAM,0);
	if(server_sock<0) {printf("error");exit(1);}
	printf("server socket created\n");

	memset(&server_addr,'\0',sizeof (server_addr));

	server_addr.sin_family=AF_INET;
	server_addr.sin_port = 5555;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int n=bind(server_sock,(struct sockaddr*)&server_addr,sizeof (server_addr));

	if(n<0) {printf("error\n");exit(1);}
	printf("binded\n");

	listen(server_sock,5);
	printf("listening...\n");

	addr_size = sizeof(client_addr);

	client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);

	printf("Client connected\n");
	while(1){
		int no;
		memset(buffer,0,1024);
		recv(client_sock,&no,sizeof(no),0);
		recv(client_sock,&buffer,1024*sizeof(buffer[0]),0);
		for(int i=0;i<no;i++){
			for(int j=0;j<no;j++){
				if(buffer[i]<buffer[j]){
					int temp=buffer[i];
					buffer[i]=buffer[j];
					buffer[j]=temp;
				}
			}
		}
		send(client_sock,&buffer,1024*sizeof(buffer[0]),0);
	}
	close(client_sock);

	return;
}
