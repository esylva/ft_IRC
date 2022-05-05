/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:58:52 by esylva            #+#    #+#             */
/*   Updated: 2022/05/05 13:54:23 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

int socket(int domain, int type, int protocol); 


int main (int argc, char **argv) {

	// Create a socket
	int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket == -1) {
		std::cerr << "Can't create a socket!" << std::endl;
		return 1;
	}
	// Bind the socket to IP-port
	sockaddr_in	sAdiN;
	sAdiN.sin_family = AF_INET;
	sAdiN.sin_port = htons(6697);
	inet_pton(AF_INET, "0.0.0.0", &sAdiN.sin_addr);
	if (bind(listeningSocket, (sockaddr *) &sAdiN, sizeof(sAdiN)) == -1) {
		std::cerr << "Can't bind the socket to the port!" << std::endl;
		return 2;
	}

	// Mark the socket fot listening
	if (listen(listeningSocket, SOMAXCONN) == -1) {
		std::cerr << "Can't listen!" << std::endl;
		return 3;
	}

	
	// Accept a call
	sockaddr_in	client;
	socklen_t	clientLen = sizeof(client);
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];

	int clientSocet = accept(listeningSocket, (sockaddr *) &client, &clientLen);
	if (clientSocet == -1) {
		std::cerr << "Client connection problem!" << std::endl;
		return 4;
	}
	
	// Close the listening socket
	close(listeningSocket);
	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr *) &client, clientLen, 
								host, NI_MAXHOST, svc, NI_MAXSERV, 0);
	if (result)
		std::cout << host << " connected on " << svc << std::endl;
	else
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;

	// While receiving - display and resend messages
	char buf[4096];
	while (true) {
		// Clear buffer
		memset(buf, 0, 4096);
		// Wait for a message
		int byteRecv = recv(clientSocet, buf, 4096, 0);
		if (byteRecv == -1) {
			std::cerr << "The connection issue" << std::endl;
			break;
		}
		if (byteRecv == 0) {
			std::cout << "The client disconnected" << std::endl;
			break;
		}
		// Display message
		std::cout << std::string(buf, 0, byteRecv) << std::endl;
		// Resend message
		send(clientSocet, buf, byteRecv + 1, 0);
	}

	// Close the socket
	close(clientSocet);
	
	return 0;
}