#!/usr/bin/python

import sys
import socket

if len(sys.argv)!=4:
    print(f"{sys.argv[0]} 127.0.0.1 5001 0")
    sys.exit()

host_ip = sys.argv[1]
server_port = int(sys.argv[2])
print(f"{host_ip}:{server_port}")
tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
n=int(sys.argv[3])
bn=socket.htonl(n).to_bytes(4,'little')
try:
    tcp_client.connect((host_ip, server_port))
    tcp_client.sendall(bn)
finally:
    tcp_client.close()
print (bn)
