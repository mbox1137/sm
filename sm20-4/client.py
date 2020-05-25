#!/usr/bin/python3
import sys, os, time, builtins, shutil
import subprocess as sbp
import socket

def print(*args, **kwargs):
    builtins.print("main:", *args, **kwargs)

def main():
# create an INET, STREAMing socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# now connect to the web server on port 80 - the normal http port
    s.connect(("www.python.org", 80))

if __name__ == '__main__':
    main()
