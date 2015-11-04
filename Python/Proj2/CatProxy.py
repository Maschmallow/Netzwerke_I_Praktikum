import sys
import socket
BUFSIZE = 4096
# create a TCP socket(SOCK_STREAM)
def OpenSocket():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as err:
        print('Fehler beim erstellen eines Sockets')
        print('Reason: %s' %str(err))
        sys.exit()
    print('Socket erstellt')
    return s

def modifyHeader(header):
    modifiedHeader = ""
    for line in header:
        if line.startswith('GET'):
            wordsInLine = line.split(" ")
            modifiedHeader += "GET / " + wordsInLine[2] + "\r\n"
            modifiedHeader += "Host:" + wordsInLine[1][1:] + "\r\n"
        elif line.startswith('Host:'):
            continue #ignore on purpose, set in GET case
        else:
            modifiedHeader += line + "\r\n"
    return modifiedHeader

def SendRequestAndGetResponse(host, modifiedHeader):
    client_socket = OpenSocket()
    ADDR = (host,80)
    client_socket.connect(ADDR)
    client_socket.send(modifiedHeader.encode('utf-8'))
    data = client_socket.recv(BUFSIZE)
    HTMLResponse = data.decode("utf-8")
    HTMLResponseLines = HTMLResponse.splitlines()
    return HTMLResponseLines

def Main():
    HOST = 'localhost'
    LISTENING_PORT = 8082

    if len(sys.argv) == 2:
        target_host = sys.argv[1]
    else:
        target_host = "mmix.cs.hm.edu"

    mySocket = OpenSocket()

    ADDR = (HOST, LISTENING_PORT)
    mySocket.bind(ADDR)
    mySocket.listen(5)  # allow 5 unaccepted connection before refusing
                        # any further connections
    while True:
        print('Server wartet auf Verbindungen...')
        client_sock, addr = mySocket.accept()
        print('Client verbunden: ', addr)
        client_sock.setblocking(0)
        while True:
            try:
                data = client_sock.recv(BUFSIZE)
            except socket.error as e:
                err = e.args[0]
                if err == socket.errno.EAGAIN or err == socket.errno.EWOULDBLOCK:
                    print("Keine Daten vorhanden")
                    break
            HTTPRequest = data.decode("utf-8")
            HTTPRequestLines = HTTPRequest.splitlines()
            print('Empfangen vom Client: %s' %(HTTPRequest))
            modifiedRequest = modifyHeader(HTTPRequestLines)

        client_sock.close()

        print('Sende veraenderten Http-Reply zum Client')
        HTMLResponseLines = SendRequestAndGetResponse(target_host, modifiedRequest)
        mySocket.send(HTMLResponseLines.encode('utf-8'))
        mySocket.close()
Main()