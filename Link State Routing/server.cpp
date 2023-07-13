#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct link_state_entry {
  char *node;
  int cost;
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

  // Receive the source and destination nodes
  char data[1024];
  int recv_status = recv(client_fd, data, sizeof(data), 0);
  if (recv_status < 0) {
    perror("Error receiving data");
    exit(1);
  }

  // Split the data into the source and destination nodes
  char *token = strtok(data, " ");
  char *source = token;
  token = strtok(NULL, " ");
  char *destination = token;

  // Find the shortest path between the source and destination nodes
  struct link_state_entry links[] = {
    { "A", 1 },
    { "B", 2 },
    { "C", 3 },
    { "D", 4 },
  };

  int shortest_path_cost = INT_MAX;
  char *shortest_path_node = NULL;
  for (int i = 0; i < sizeof(links) / sizeof(links[0]); i++) {
    int path_cost = links[i].cost + links[i + 1].cost;
    if (path_cost < shortest_path_cost) {
      shortest_path_cost = path_cost;
      shortest_path_node = links[i].node;
    }
  }

  // Send the shortest path to the client
  char response[1024];
  snprintf(response, sizeof(response), "Shortest path: %s %s %d\n", source, shortest_path_node, shortest_path_cost);
  send(client_fd, response, strlen(response), 0);

  // Close the socket
  close(client_fd);
  close(sockfd);

  return 0;
}
