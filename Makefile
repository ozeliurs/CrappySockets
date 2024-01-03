all: libclient.so libserver.so

libclient.so:
	gcc -shared -o libclient.so -fPIC client.c

libserver.so:
	gcc -shared -o libserver.so -fPIC server.c

clean:
	rm libserver.so libclient.so