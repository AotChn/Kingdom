#include "clientnetwork.cpp"
#include "servernetwork.cpp"

using namespace std;

int client(){
    sf::IpAddress IP;
     ClientNetwork client_network;
     std::cout << "enter IP: ";
     std::cin >> IP;
     client_network.Connect(IP, 2525);
     client_network.Run();
     return 0;
}

int server(){
     ServerNetwork server_network(2525);
     server_network.Run();
     return 0;
}

int bears(){
 char ct = 's';
	cout << "s / c \n"; // s - server / c - client
	cin >> ct;

	if (ct == 's') {
		server();
	}
	else if (ct == 'c') {
		client();
	}   
}