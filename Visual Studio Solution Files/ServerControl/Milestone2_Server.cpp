#include <iostream>
#include "../MySocket.h"

int main()
{
	std::cout << "=== Server ===" << std::endl << std::endl;

	MilestoneTwo::MySocket TCPServerSocket(SocketType::SERVER, "127.0.0.1", 5000, ConnectionType::TCP, 100);

	char buff[100];

	int RxSize = TCPServerSocket.GetData(buff);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	std::string TCPPkt = "I love BTN415 too - Sent by TCP Server";

	TCPServerSocket.SendData(TCPPkt.c_str(), strlen(TCPPkt.c_str())+1);

	TCPServerSocket.DisconnectTCP();

	memset(buff, 0, sizeof(buff));
	RxSize = 0;

	MilestoneTwo::MySocket UDPServerSocket(SocketType::SERVER, "127.0.0.1", 9001, ConnectionType::UDP, 100);

	std::string UDPPkt = "I love BTN415 too - Sent by UDP Server";

	RxSize = UDPServerSocket.GetData(buff);

	UDPServerSocket.SendData(UDPPkt.c_str(), strlen(UDPPkt.c_str()) + 1);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	std::cin.get();

	return 1;
}
