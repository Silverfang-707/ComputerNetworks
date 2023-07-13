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

  // Send the source and destination nodes
  char *source = "A";
  char *destination = "B";
  char data[100];
  snprintf(data, sizeof(data), "{\"source\": \"%s\", \"destination\": \"%s\"}", source, destination);
  int send_status = send(sockfd, data, strlen(data), 0);
  if (send_status < 0) {
    perror("Error sending data");
    exit(1);
  }

  // Receive the shortest path
  char shortest_path[1024];
  int recv_status = recv(sockfd, shortest_path, sizeof(shortest_path), 0);
  if (recv_status < 0) {
    perror("Error receiving data");
    exit(1);
  }

  // Print the shortest path
  printf("Shortest path: %s\n", shortest_path);

  // Close the socket
  close(sockfd);

  return 0;
}
