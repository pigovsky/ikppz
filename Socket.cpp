class Socket {
public:

	Socket() {}

	virtual void listen(const char* host, int port) {}

	virtual Socket& accept() {return *new Socket;}

	virtual void connect(const char* host, int port) {}

	virtual void write(const char* message) {}

	virtual const char* read() {return NULL;}

	virtual void close() {}
};


void f();
Socket& createSocket();
