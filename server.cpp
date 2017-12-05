#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <pthread.h>
#include <thread>

#define MAX_THREAD_NUM 100
#define BACKLOG 20
#define BUFFER_SIZE 1024

using namespace std;

int thread_count = 0;
//pthread_t threads[MAX_THREAD_NUM];
std::thread threads[MAX_THREAD_NUM];



class Server{
    private:
        int server_sock;
        struct sockaddr_in server_addr;

    public:
        void receive_data(/*void* conn*/int conn_socket){
            cout << conn_socket << " :receive data" << endl;
            //int conn_socket = *((int*)conn);
            char buffer[BUFFER_SIZE];
            int length = 0;
            
            while(true){
                int receive_code = read(conn_socket, buffer, BUFFER_SIZE);
                if(receive_code == 0 || receive_code == -1){
                    cout << "receive error" << endl;
                }
                else{
                    cout << conn_socket << " " << buffer << endl;
                }
            
                if(write(conn_socket, buffer, strlen(buffer)) == -1){
                    cout << "write error" << endl;
                }
            }
        }

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

            while(true){
                cout << 1 << endl;
                struct sockaddr_in client_addr;
                socklen_t length = sizeof(client_addr);
                int client_conn = accept(server_sock, (struct sockaddr*)&client_addr, &length);
                cout << 2 << endl;
                if(client_conn < 0){
                    cout << "connection error" << endl;
                }

                /*int pthread_err = pthread_create(threads + (thread_count ++), NULL, receive_data, &client_conn);
                if(pthread_err < 0){
                    cout << "thread create error" << endl;
                }*/
                threads[thread_count ++] = std::thread(&Server::receive_data, this, client_conn);

            }
            close(server_sock);
        }

        
};

int main(){
    Server server;
    return 0;
}
