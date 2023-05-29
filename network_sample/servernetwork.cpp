#include "servernetwork.h"

ServerNetwork::ServerNetwork(unsigned short port) : listen_port(port)
{
     logl("Chat Server Started");

     if (listener.listen(listen_port) != sf::Socket::Done)
     {
          logl("Could not listen");
     }
}

void ServerNetwork::ConnectClients(std::vector<sf::TcpSocket *> *client_array)
{
     while (true)
     {
          sf::TcpSocket *new_client = new sf::TcpSocket();
          if (listener.accept(*new_client) == sf::Socket::Done)
          {
               new_client->setBlocking(false);
               client_array->push_back(new_client);
               logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << client_array->size());
          }
          else
          {
               logl("Server listener error, restart the server");
               delete (new_client);
               break;
          }
     }
}

void ServerNetwork::DisconnectClient(sf::TcpSocket *socket_pointer, size_t position)
{
     logl("Client " << socket_pointer->getRemoteAddress() << ":" << socket_pointer->getRemotePort() << " disconnected, removing");
     socket_pointer->disconnect();
     delete (socket_pointer);
     client_array.erase(client_array.begin() + position);
}

void ServerNetwork::BroadcastPacket(sf::Packet &packet, sf::IpAddress exclude_address, unsigned short port)
{
     for (size_t iterator = 0; iterator < client_array.size(); iterator++)
     {
          sf::TcpSocket *client = client_array[iterator];
          if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port)
          {
               if (client->send(packet) != sf::Socket::Done)
               {
                    logl("Could not send packet on broadcast");
               }
          }
     }
}

void ServerNetwork::ReceivePacket(sf::TcpSocket *client, size_t iterator)
{
     sf::Packet packet;
     if (client->receive(packet) == sf::Socket::Disconnected)
     {
          DisconnectClient(client, iterator);
          return;
     }

     if (packet.getDataSize() > 0)
     {
          std::string received_message;
          packet >> received_message;
          packet.clear();

          packet << received_message << client->getRemoteAddress().toString() << client->getRemotePort();

          BroadcastPacket(packet, client->getRemoteAddress(), client->getRemotePort());
          logl(client->getRemoteAddress().toString() << ":" << client->getRemotePort() << " '" << received_message << "'");
     }
}

void ServerNetwork::ManagePackets()
{
     while (true)
     {
          for (size_t iterator = 0; iterator < client_array.size(); iterator++)
          {
               ReceivePacket(client_array[iterator], iterator);
          }

          std::this_thread::sleep_for((std::chrono::milliseconds)250);
     }
}

void ServerNetwork::Run()
{
     std::thread connetion_thread(&ServerNetwork::ConnectClients, this, &client_array);

     ManagePackets();
}


/*
     Sending game packets 

     The  next step in this is being able to time the packet data that is being set 
     in this way we would be able to ensure that all the data is sent in an efficent 
     manner. 

     To achieve this we can create a vector time to first time the packet out and then 
     when we recieve we can ping to server and to client and calculate the amount of time 
     it takes to be able to ping back and forth.

     I wonder if the necessary type of data we should send are char arrays or 
     can we send full files to replace other files such as binary files. Im thinking 
     that binary files transfer could potentially be too large and cause a lag in the 
     servers but also it would reduce disk reads and fully just transfer in one go.

*/

//TODO: Send binary file packets .