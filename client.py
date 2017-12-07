#coding: UTF-8

import socket
import time

#s = socket.socket()
host = socket.gethostname()
port = 12346
#s.bind((host, port))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 建立连接:
s.connect(('127.0.0.1', port))
while True:
    '''s.send('123456')
    time.sleep(3)
    tp = s.recv(1024)
    print tp'''
    order = raw_input()
    if order == "exit":
        break
    else:
        s.send(order)
        tp = s.recv(1024)
        #print tp
        if order.split(' ')[0] == "signup":
            #print "sign up"
            print tp
            print len(tp)
            if tp == "succeed":
                print "sign up succeeded"
            elif tp == "fail":
                print "sign up failed. change username and have a try again"
        elif order.split(' ')[0] == "login":
            print tp
            print len(tp)
            if tp == "already_online":
                print "you have been already online"
            elif tp == "non_count":
                print "wrong username"
            elif tp == "login_succeed":
                print "login succeed"
            elif tp == "login_fail":
                print "wrong password"

