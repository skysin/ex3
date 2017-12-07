#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <vector>

#define MAX_THREAD_NUM 100
#define BACKLOG 20
#define BUFFER_SIZE 1024

using namespace std;

int thread_count = 0;
std::thread threads[MAX_THREAD_NUM];

struct User{
    string username;
    string password;
    vector<string> friends;
    User(string na, string pa){
        username = na;
        password = pa;
        friends.clear();
    }
};

vector<User> all;
vector<User> on;

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
            server_addr.sin_port = htons(12346);
            
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
                struct sockaddr_in client_addr;
                socklen_t length = sizeof(client_addr);
                int client_conn = accept(server_sock, (struct sockaddr*)&client_addr, &length);
                if(client_conn < 0){
                    cout << "connection error" << endl;
                }

                threads[thread_count ++] = std::thread(&Server::receive_data, this, client_conn);

            }
            close(server_sock);
        }

        void receive_data(int conn_socket){
            cout << conn_socket << " :receive data" << endl;
            char buffer[BUFFER_SIZE];
            int length = 0;
            
            while(true){
                memset(buffer, 0, BUFFER_SIZE);
                int receive_code = read(conn_socket, buffer, BUFFER_SIZE);
                if(receive_code == 0 || receive_code == -1){
                    cout << "receive error" << endl;
                }
                else{
                    cout << conn_socket << " " << buffer << endl;
                    const char delim[2] = " ";
                    char* ord = strtok(buffer, delim);
                    //cout << ord << endl;
                    //cout << buffer << endl;
                    if(strcmp(ord, "signup") == 0){
                        char* first = strtok(NULL, delim);
                        char* second = strtok(NULL, delim);
                        cout << first << "|" << second << endl;
                        if(signup(first, second)){
                            if(write(conn_socket, "succeed", strlen("succeed")) == -1){
                                cout << "write error" << endl;
                            }
                        }
                        else{
                            if(write(conn_socket, "fail", strlen("fail")) == -1){
                                cout << "write error" << endl;
                            }
                        }
                    }
                    if(strcmp(ord, "login") == 0){
                        char* first = strtok(NULL, delim);
                        char* second = strtok(NULL, delim);
                        cout << first << "|" << second << endl;
                        if(already_online(first, second)){
                            if(write(conn_socket, "alread_online", strlen("already_online")) == -1){
                                cout << "write error" << endl;
                            }
                        }
                        else{
                            if(non_count(first, second)){
                                if(write(conn_socket, "no_count", strlen("no_count")) == -1){
                                    cout << "write error" << endl;
                                }
                            }
                            else{
                                if(login(first, second)){
                                    if(write(conn_socket, "login_succeed", strlen("login_succeed")) == -1){
                                        cout << "write error" << endl;
                                    }
                                }
                                else{
                                    if(write(conn_socket, "login_fail", strlen("login_fail")) == -1){
                                        cout << "write error" << endl;
                                    }
                                }
                            }
                            
                        }
                    }
                }
            
                /*if(write(conn_socket, buffer, strlen(buffer)) == -1){
                    cout << "write error" << endl;
                }*/
            }
        }

        bool signup(char* na, char* pa){
            string un(na);
            string pw(pa);
            for (int i = 0; i < all.size(); i ++){
                if(all[i].username == na){
                    return false;
                }
            }
            User tmp(na, pa);
            all.push_back(tmp);
            return true;
        }

        bool already_online(char* na, char* pa){
            string un(na);
            string pw(pa);
            for (int i = 0; i < on.size(); i ++){
                if(on[i].username == na){
                    return true;
                }
            }
            return false;
        }

        bool non_count(char* na, char* pa){
            string un(na);
            string pw(pa);
            for (int i = 0; i < all.size(); i ++){
                if(all[i].username == na){
                    return false;
                }
            }
            return true;
        }

        bool login(char* na, char* pa){
            string un(na);
            string pw(pa);
            for (int i = 0; i < all.size(); i ++){
                if(all[i].username == na && all[i].password == pa){
                    on.push_back(all[i]);
                    return true;
                }
            }
            return false;
        }
};

int main(){
    Server server;
    return 0;
}
