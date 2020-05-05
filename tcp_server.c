#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <fcntl.h> //open
#include <unistd.h> // close

int main()
{
	char server_message[256] = "You have reached the server!";
	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM, 0);

	//define server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002); // convert 9002 int to desired format
	server_address.sin_addr.s_addr = INADDR_ANY; // ip of own server. (0.0.0.0)

	// bind the socket to our specified IP and port
	bind(server_socket,(struct sockaddr *) &server_address, sizeof(server_address));
	
	listen(server_socket, 5); //number of clients from which it can listen

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// send the message
	send(client_socket, server_message, sizeof(server_message), 0);

	//and then close the socket
	close(server_socket);
	return 0;

}