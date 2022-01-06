#include "gettftp.h"

int main(int argc, char* argv[]){
	/*TEST*/
	printf("Get\n");

	struct addrinfo hints;
	memset(&hints, 0,sizeof(hints));
	struct addrinfo *res;

	int err = getaddrinfo(argv[1], NULL, &hints, &res);
	if(err == -1){
		printf("Erreur getAddrInfo");
	}else{
		DISPLAY_IP(*res);
		int sock;
		if((sock = socket(PF_INET, SOCK_STREAM,0)) < 0){
			printf("Erreur creation socket\n");
		}else{
			printf("Socket créé\n");
			int err = connect(sock,res->ai_addr,res->ai_addrlen);
			if(err == -1){
				perror("Erreur connection serveur");
			}else{
				printf("Connection établie\n");
			}
		}
	}

	return 0;
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
