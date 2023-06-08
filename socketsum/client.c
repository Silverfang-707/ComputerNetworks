#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    // Connect the socket to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    int numbers[2];
    
    // Prompt the user for two numbers
    printf("Enter the first number: ");
    scanf("%d", &numbers[0]);
    
    printf("Enter the second number: ");
    scanf("%d", &numbers[1]);
    
    // Send the numbers to the server
    send(sock, numbers, sizeof(numbers), 0);
    
    int sum;
    
    // Receive the sum from the server
    if (recv(sock, &sum, sizeof(sum), 0) < 0) {
        printf("\nrecv failed\n");
        return -1;
    }
    
    printf("Sum received from the server: %d\n", sum);
    
    return 0;
}
