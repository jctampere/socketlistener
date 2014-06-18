
import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 3333
MESSAGE = 'hello'

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

while True:
    s.send(MESSAGE)

