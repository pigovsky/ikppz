server.exe: main.cpp sbl.o SocketImpl.o
	g++ -o server.exe main.cpp sbl.o SocketImpl.o
sbl.o: sbl.cpp
SocketImpl.o: SocketImpl.cpp

clean:
	rm server.exe sbl.o SocketImpl.o
