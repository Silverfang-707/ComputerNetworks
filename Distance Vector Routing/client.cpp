#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Error creating socket");
    exit(1);
  }

  // Connect to the server
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = inet_addr("localhost");
  int connect_status = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0) {
    perror("Error connecting to server");
    exit(1);
  }

  // Send the routing table updates
  char data[1024];
  strcpy(data, "192.168.1.1 1 192.168.1.2");
  int send_status = send(sockfd, data, strlen(data), 0);
  if (send_status < 0) {
    perror("Error sending data");
    exit(1);
  }

  // Close the socket
  close(sockfd);

  return 0;
}
