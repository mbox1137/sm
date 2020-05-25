#!/usr/bin/python3

#https://docs.python.org/3/howto/sockets.html

import sys, os, time, builtins, shutil
import subprocess as sbp
import socket

def print(*args, **kwargs):
    builtins.print("main:", *args, **kwargs)

def main():
    # create an INET, STREAMing socket
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind the socket to a public host, and a well-known port
    serversocket.bind((socket.gethostname(), 23456))
    # become a server socket
    serversocket.listen(5)
    while True:
        # accept connections from outside
        (clientsocket, address) = serversocket.accept()
        # now do something with the clientsocket
        # in this case, we'll pretend this is a threaded server
        ct = client_thread(clientsocket)
        ct.run()

if __name__ == '__main__':
    main()
