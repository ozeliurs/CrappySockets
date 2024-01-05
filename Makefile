libs: libclient.so libserver.so

libclient.so:
	gcc -fPIC -shared -o libclient.so -fPIC client.c

libserver.so:
	gcc -fPIC -shared -o libserver.so -fPIC server.c

main_client: libs
	gcc -o main_client main_client.c -L. -lclient

main_server: libs
	gcc -o main_server main_server.c -L. -lserver

main: main_client main_server

test: main
	./main_client & ./main_server

clean:
	rm -f libserver.so libclient.so main_client main_server