#include <iostream>
#include "Socket.cpp"

using namespace std;

void run() {
	f();
	Socket& server = createSocket();
	server.listen("127.0.0.1", 8080);

	Socket& client = server.accept();

	client.write("fhjsdfkjhdfskjdfh");

	cerr << "I've received " << client.read() << endl;
	
	client.close();
}


