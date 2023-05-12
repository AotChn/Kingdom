#ifndef SOCKET_H
#define SOCKET_H

#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <optional>

const char data[100] = "hello john";

////////////////////////////////////////////////////////////
/// Launch a server, wait for a message, send an answer.
///
////////////////////////////////////////////////////////////
#include <iostream>

using namespace sf;

void runTcpServer(unsigned short port){}
void runTcpClient(unsigned short port){}
void runUdpServer(unsigned short port);
void runUdpClient(unsigned short port);


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int bear()
{
    char ans;
    std::cout<< "are you [c] or [s]";
    std::cin>>ans;
    if(ans == 's')
        runUdpServer(50022);
    else 
        runUdpClient(50021);


}

void runUdpServer(unsigned short port){
    sf::IpAddress a("192.168.139.107");
    sf::UdpSocket socket;
    if (socket.bind(port) != sf::Socket::Status::Done)
        return;
    char buffer[] = "whats up brian"; 

    if (socket.send(buffer, sizeof(buffer), a, port) != sf::Socket::Done){
        std::cout<< "ITS NOT BINDING FOR SOME REASON!!!!!";
    }
    std::cout << buffer << std::endl; // "Hi guys !"
    
}

void runUdpClient(unsigned short port){
    char buffer[128];
    std::size_t Received;
    sf::IpAddress a("192.168.139.107");
    sf::UdpSocket socket;
    unsigned short Port = 5000;
    if (socket.receive(buffer, sizeof(buffer), Received, a, Port) != sf::Socket::Done)
    {
        std::cout<< "NOT RECIEVED!!!!!" << std::endl;
    }
    

    // Show the address / port of the sender
    std::cout << a << ":" << Port << std::endl;

    // Show the message
    std::cout << buffer << std::endl; // "Hi guys !"
    
}





#endif