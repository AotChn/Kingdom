#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class ClientNetwork{
     sf::TcpSocket socket;
     sf::Packet last_packet;

     bool isConnected = false;
public:
     ClientNetwork();
     void Connect(sf::IpAddress, unsigned short);
     void ReceivePackets(sf::TcpSocket *);
     void SendPacket(sf::Packet &);
     void Run();
};
#endif