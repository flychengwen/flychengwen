#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 512

void udp_msg_sender(int fd, struct sockaddr* dst, int nr)
{
    socklen_t len;
    struct sockaddr_in src;
    char message[BUF_SIZE] = {"hello, welcome to China!\n"};
	int i = 0;
    while(i < nr)
    {
        len = sizeof(*dst);
		
		#if 0
        fputs("Input message:(输入Q退出):", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        sendto(fd, message, BUF_SIZE, 0, dst, len);
        memset(message, 0, BUF_SIZE);
        recvfrom(fd, message, BUF_SIZE, 0, (struct sockaddr*)&src, &len);
        printf("recv server message:%s\n",message);
		#else
		sendto(fd, message, 30, 0, dst, len);
		usleep(3);
		#endif

		++i;
    }
}

int main(int argc, char* argv[])
{
	unsigned int pkts = 0;
    int client_fd;
    struct sockaddr_in ser_addr;
	
    if(argc < 3)
    {
        printf("Usage: %s <IP> <port> {pkts|}\n", argv[0]);
        return -1;
    }

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
    ser_addr.sin_port = htons(atoi(argv[2]));

	if (argc >= 4)
		pkts = atoi(argv[3]);
	if (pkts < 1)
		pkts = 1;
    udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr, pkts);

    close(client_fd);

    return 0;
}
