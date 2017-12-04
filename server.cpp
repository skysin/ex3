#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

const int BACKLOG = 20;

class Server{
    private:
        int server_sock;
        struct sockaddr_in server_addr;

    public:    
        Server(){
            server_sock = socket(AF_INET, SOCK_STREAM, 0);
            if(server_sock < 0){
                cout << "socket created failed" << endl;
            }

            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            server_addr.sin_port = htons(12345);
            
            int res = 0;
            
            res = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
            if(res == -1){
                cout << "bind error" << endl;
            }

            res = listen(server_sock, BACKLOG);
            if(res == -1){
                cout << "listen error" << endl;
            }
        }
};

int main(){
    Server server;
    return 0;
}
