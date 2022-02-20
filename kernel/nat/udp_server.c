#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void handle_udp_msg(int fd)
{
	unsigned int last_pkts = 0;
	unsigned int rx_pkts = 0;
	unsigned int rx_bytes = 0;
	
	char buf[BUF_SIZE];
	socklen_t len;
	int count,ret;
	struct sockaddr_in client_addr;
	struct timeval timeout;

	fd_set fds;
	while(1){
		FD_ZERO(&fds);
		FD_SET(fd, &fds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		memset(buf, 0, BUF_SIZE);
		len = sizeof(client_addr);
		//printf("select start...\n");

		ret = select(fd+1, &fds, NULL, NULL, &timeout);
		if (!ret){
			if (last_pkts != rx_pkts){
				printf("rx_pkts=%u rx_bytes=%u\n", rx_pkts, rx_bytes);
				last_pkts = rx_pkts;
			}

			continue;
		}else if (ret < 0){
			perror("select error\n");
			return;	
		}
			
		if (FD_ISSET(fd, &fds)){
			count = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &len);
			if (count < 0){
				printf("receive data failed!\n");
				return;
			}

			rx_bytes += count;
			++rx_pkts;
			//printf("recv client:%s\n", buf);
			//sendto(fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, len);
		}
	
	}
}

int main(int argc, char* argv[])
{
	int server_fd, ret;
	struct sockaddr_in ser_addr;

	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return -1;
	}

	server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(server_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));

	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ret < 0)
	{
		printf("socket bind fail!\n");
		return -1;
	}

	handle_udp_msg(server_fd);

    close(server_fd);
    return 0;
}
