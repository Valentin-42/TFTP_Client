#include "gettftp.h"

int main(int argc, char* argv[]){
	/*TEST*/
	printf("Get\n");

	struct addrinfo hints;
	memset(&hints, 0,sizeof(hints));
	struct addrinfo *res;

	int err = getaddrinfo(argv[1], NULL, &hints, &res);
	if(err == -1){
		perror("Erreur getAddrInfo");
	}else{
		DISPLAY_IP(*res);
		int sock;
		if((sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP)) < 0){ //SOCK_DGRAM -> UDP // SOCK_STREAM -> TCP
			perror("Erreur creation socket");
		}else{
			printf("Socket créé : %d\n", sock);
			int err = connect(sock,res->ai_addr,res->ai_addrlen);//
			if(err == -1){
				perror("Erreur connection serveur");
			}else{
				printf("Connection établie\n");
				read_request(sock,argv[2]);
			}
		}
	}

	return 0;
}


void read_request(int fd, char* cmd){

	char* read_buf[BUF_SIZE];
	int* RRQ;
	int RRQ_size = strlen(cmd)+strlen("netascii")+4;
	RRQ = (int*) malloc(24);
	printf("Taille RRQ = %d\n", RRQ_size);
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1069);

	memset(&read_buf, 0,sizeof(read_buf));

	//Sendto

	*RRQ = (int) 0x0100;
	strncpy((char*)RRQ+2, cmd, strlen(cmd));

	strncpy((char*)RRQ+strlen(cmd)+3, "netascii", strlen("netascii"));

	*(RRQ+strlen(cmd)*sizeof(char)+4) = (int) 0x0;

	int err = sendto(fd,RRQ,RRQ_size,0,(struct sockaddr *) &server, sizeof(server));

	if(err == -1){
		perror("Erreur send");
	}else{
		printf("Write success\n");
		//Read socket
		socklen_t addrlen = sizeof(server);
		int err = recvfrom(fd, read_buf,sizeof(read_buf),0, (struct sockaddr *) &server, &addrlen);
		if(err == -1){
			perror("Error read request");
		}else{
			//buffer[128]=0;
			printf("Lecture réussi :) !");
			//write (1, buffer, 128);
			free(RRQ);
			}
		}
	}




void DISPLAY_IP(struct addrinfo res){
	char host[128];
	memset(&host, 0,sizeof(host));
	socklen_t hostlen=sizeof(host);

	int err = getnameinfo(res.ai_addr,res.ai_addrlen,host, hostlen, NULL,0, NI_NUMERICHOST | NI_NUMERICSERV);
	if(err == -1){
		printf("Erreur recuperation IP serveur");
	}else{
		printf("IP du serveur : %s\n",host);
	}

}
