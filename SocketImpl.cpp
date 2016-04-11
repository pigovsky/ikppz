#include <iostream>
#include "Socket.cpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class SocketImpl : public Socket {
private:
	// Створюємо екземпляр прослуховуючого сокета:
	typedef int SOCKET; // В Unix типу даних SOCKET немає
	SOCKET socket;
	
	struct sockaddr socketAddr;

	SocketImpl(SOCKET socket) : Socket() {
		this->socket = socket;
	}

public: 
	SocketImpl() : Socket() {
		socket = ::socket(AF_INET,SOCK_STREAM,0);
	}

	virtual void listen(const char* host, int port);

	virtual Socket& accept();

	virtual void connect(const char* host, int port);

	virtual void write(const char* message);

	virtual const char* read();

	virtual void close();
};

Socket& createSocket() {
	return *new SocketImpl;	
}

void f() {
	cerr << "F";
}

void SocketImpl::listen(const char* host, int port) {
	cerr << "I'm listening to port " << port
		<< " at host " << host << endl;

	struct sockaddr_in my_serv_addr;
	my_serv_addr.sin_family = AF_INET;
	my_serv_addr.sin_port = htons(port); // де 5000 - номер порта
	my_serv_addr.sin_addr.s_addr = inet_addr(host); // де 127.0.0.1 - ІР-адреса локального мережевого інтерфейсу даного комп'ютера (для з'єднання між сокетами на одному комп'ютері)

	// Присвоюємо прослуховуючому сокету ІР-адресу і порт:
	bind(socket,(const struct sockaddr *)&my_serv_addr,sizeof(my_serv_addr));

	// Розпочинаємо процес прослуховування, дозволяючи одночасне під'єднання не більше 5 клієнтських сокетів:
	::listen(socket,5);
}

Socket& SocketImpl::accept() {
	cerr << "accept" << endl;
	socklen_t sockStructSize = sizeof(struct sockaddr);
	SOCKET client = ::accept(socket, &socketAddr, &sockStructSize);
	return *new SocketImpl(client);
}

void SocketImpl::connect(const char* host, int port) {
	cerr << "I'm connecting to port " << port
		<< " at host " << host << endl;
}

void SocketImpl::write(const char* message) {
	cerr << "Send message " << message << endl;
}

const char* SocketImpl::read() {
	char *buf = new char[1024];
	buf[recv(socket, buf, sizeof(buf), 0)]=0;
	return buf;
}

void SocketImpl::close() {
	::close(socket);
}
