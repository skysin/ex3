#coding: UTF-8

import socket
import time

#s = socket.socket()
host = socket.gethostname()
port = 12345
#s.bind((host, port))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 建立连接:
s.connect(('127.0.0.1', port))
while True:
    s.send('123456')
    time.sleep(3)
    tp = s.recv(1024)
    print tp

