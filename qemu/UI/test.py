#!/usr/bin/python
import socket
if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)        
    s.bind(("localhost", 4243))        
    s.listen(1)
