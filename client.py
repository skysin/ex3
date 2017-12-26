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
    '''s.send('123456')
    time.sleep(3)
    tp = s.recv(1024)
    print tp'''
    order = raw_input()
    s.send(order)
    if order == "exit_app":
        break
    else:
        #tp = s.recv(1024)
        #print tp
        if order.split(' ')[0] == "signup":
            tp = s.recv(1024)
            #print "sign up"
            #print tp
            #print len(tp)
            if tp == "succeed":
                print "sign up succeeded"
            elif tp == "fail":
                print "sign up failed. change username and have a try again"
        elif order.split(' ')[0] == "login":
            tp = s.recv(1024)
            #print tp
            #print len(tp)
            if tp == "already_online":
                print "you have been already online"
            elif tp == "non_count":
                print "wrong username"
            elif tp == "login_succeed":
                print "login succeed"
            elif tp == "login_fail":
                print "wrong password"
        elif order.split(' ')[0] == "logout":
            tp = s.recv(1024)
            #print tp
            #print len(tp)
            if tp == "logout_succeed":
                print "logout succeed"
            elif tp == "logout_fail":
                print "logout fail"
        elif order.split(' ')[0] == "search":
            tp = s.recv(1024)
            all_name = tp.split(' ')
            for i in all_name:
                if i is not None:
                    print "**  " + i
        elif order.split(' ')[0] == "add":
            tp = s.recv(1024)
            #print tp
            #print len(tp)
            if tp == "add_succeed":
                print "add succeed"
            elif tp == "add_fail":
                print "add fail"
        elif order.split(' ')[0] == "ls":
            tp = s.recv(1024)
            if tp == "None":
                print "**  No friends now."
            else:
                all_name = tp.split(' ')
                for i in all_name:
                    if i is not None:
                        print "**  " + i
        elif order.split(' ')[0] == "profile":
            tp = s.recv(1024)
            all = tp.split(' ')
            for i in range(len(all)):
                if i == 0:
                    print "--username: " + all[i]
                if i == 1:
                    print "--password: " + all[i]
                if i > 1:
                    print "----------: " + all[i]
        elif order.split(' ')[0] == "chat":
            print "**********************************"
            while True:
                tmp = raw_input()
                s.send(tmp)
                if tmp == "exit":
                    print "**********************************"
                    break
                od = tmp.split(' ')
                if od[0] == "sendmsg":
                    pass
                if od[0] == "sendfile":
                    print od[1]
                    time.sleep(5)
                    try:
                        with open(od[1], 'rb') as f:
                            while True:
                                data = f.read(1024)
                                if not data:
                                    break
                                else:
                                    s.send(data)
                                    #print data
                            time.sleep(5)
                            s.send("--EOF--")
                            print "sendfile end"
                    except Error as e:
                        print e
        elif order.split(' ')[0] == "recvmsg":
            tp = s.recv(1024)
            all = tp.split(' ')
            for i in range(len(all)):
                    if i > 0:
                        print "$$ " + all[i]
        elif order.split(' ')[0] == "recvfile":
            while True:
                tp = s.recv(1024)
                if tp == "**end**":
                    print "receiver end"
                elif len(tp) == 0:
                    pass
                elif len(tp) > 0:
                    with open("./receiver/" + tp, "wb") as f:
                        while True:
                            data = s.recv(1024)
                            if data == "--EOF--":
                                print "file write end"
                                break
                            else:
                                f.write(data)
                                #print data
        elif order.split(' ')[0] == "sync":
            print "sync succeed"
            

