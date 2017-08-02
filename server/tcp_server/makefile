PHONY:all
all:server2 client

server2:server2.c
	gcc -o $@ $^ -lpthread
client:client.c
	gcc -o $@ $^ 
.PHONY:clean
clean:
	rm -f server2 client


