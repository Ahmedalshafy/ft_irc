// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.cpp                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/08 11:55:22 by alsaeed           #+#    #+#             */
// /*   Updated: 2025/02/04 18:06:45 by aalshafy         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "Includes/Server.hpp"
// #include <iostream>

// int main( int ac, char* av[] ) {

// 	// Ensure correct number of arguments
// 	if ( ac != 3 ) {

// 		std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
// 		return -1;
// 	}

// 	// Convert port argument to integer and validate it
// 	int 		portNum = std::atoi( av[1] );
// 	std::string	port( av[1] ), password( av[2] );

// 	if ( portNum < 1024 || portNum > 65535 || port.empty() || port.length() > 5 
// 		|| port.find_first_not_of( "0123456789" ) != std::string::npos ){

// 		std::cerr << "Invalid port number" << std::endl;
// 		return -2;
// 	}

// 	// Validate password is not empty
// 	if ( password.empty() ) {

// 		std::cerr << "Server's password is not given" << std::endl;
// 		return -3;
// 	}
	
// 	Server *server = NULL;
// 		// Initialize and run the server
// 	try {

// 		server = Server::getInstance();
// 		server->setServerPassword( password );
// 		server->setServerPort( portNum );
// 		server->initServer();
// 		server->runServer();
// 	} catch ( const IrcException &e ) {

// 		std::cerr << "Server error: " << e.what() << std::endl;
// 		delete server;
// 		return -4;
// 	} catch (const std::exception& e) {
//         std::cerr << "Unexpected error: " << e.what() << std::endl;
// 		delete server;
//         return -5;
//     } catch (...) {
//         std::cerr << "Unknown error occurred." << std::endl;
// 		delete server;
//         return -6;
//     }

// 	delete server;

// 	return 0;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:26:54 by mahmoud           #+#    #+#             */
/*   Updated: 2024/10/21 15:35:07 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Includes/Server.hpp"

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>\n";
        return 1;
    }

    // Convert the port argument to an integer
    int port = std::atoi(argv[1]);
    // Validate the port number
    if (port <= 0 || port > 65535)
    {
        std::cerr << "Error: Invalid port number. Please provide a valid port (1-65535).\n";
        return 1;
    }

    // Get the server password from command-line arguments
    std::string serverPassword = argv[2];

    try
    {
        // Create an instance of the Server class
        Server server(port, serverPassword);
        // Start the server
        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
