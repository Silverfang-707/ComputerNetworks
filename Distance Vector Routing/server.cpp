#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct routing_table_entry {
  char *destination;
  int cost;
  char *next_hop;
};

int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Error creating socket");
    exit(1);
  }

  // Bind the socket to a port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  int bind_status = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0) {
    perror("Error binding socket");
    exit(1);
  }

  // Listen for connections
  listen(sockfd, 5);

  // Accept a connection
  int client_fd = accept(sockfd, NULL, NULL);
  if (client_fd < 0) {
    perror("Error accepting connection");
    exit(1);
  }

  // Receive the routing table updates
  char data[1024];
  int recv_status = recv(client_fd, data, sizeof(data), 0);
  if (recv_status < 0) {
    perror("Error receiving data");
    exit(1);
  }

  // Update the routing table
  char *token = strtok(data, " ");
  while (token != NULL) {
    char *destination = token;
    token = strtok(NULL, " ");
    int cost = atoi(token);
    token = strtok(NULL, " ");
    char *next_hop = token;

    // Update the routing table entry
    int index = 0;
    while (routing_table[index].destination != NULL) {
      index++;
    }
    routing_table[index].destination = destination;
    routing_table[index].cost = cost;
    routing_table[index].next_hop = next_hop;

    token = strtok(NULL, " ");
  }

  // Print the routing table
  for (int i = 0; i < 10; i++) {
    if (routing_table[i].destination != NULL) {
      printf("Destination: %s, Cost: %d, Next hop: %s\n", routing_table[i].destination, routing_table[i].cost, routing_table[i].next_hop);
    }
  }

  // Close the socket
  close(client_fd);
  close(sockfd);

  return 0;
}
