import network
import socket
from time import sleep
import machine
import runnable #local runnable.py

class HTTPConnector(runnable.Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("HTTP Connector Runtime")
        #todo check for new information from Async HTTP Server
        return runnable.RuntimeExecutionStatus.SUCCESS
    
class HTTPServer():
    #This class runs on a separate CPU core, so it does not need to be a runnable
    ssid = '*****'
    password = '*****'
    
    def __init__(self):
        self.runtime();
        pass
    #async HTTP server that receives GET and POST requests from HTTP clients, and provides data or data requests to HTTP connector
    
    def connect(self):
        #Connect to WLAN
        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        wlan.connect(self.ssid, self.password)
        while wlan.isconnected() == False:
            print('Waiting for connection...')
            sleep(1)
        ip = wlan.ifconfig()[0] #this is the ip address of the raspberry pi pico
        print(f'Connected on {ip}')
        return ip
    
    def open_socket(self, ip):
        # Open a socket
        address = (ip, 80)
        connection = socket.socket()
        connection.bind(address)
        connection.listen(1)
        return connection
    
    def webpage(self):
    #Template HTML
        html = f"""
                <!DOCTYPE html>
                <html>
                <p>TEST STATEMENT 1</p>
                <p>TEST STATEMENT 2</p>
                </body>
                </html>
                """
        return str(html)

    def serve(self, connection):
        #Start a web server
        while True:
            client = connection.accept()[0]
            request = client.recv(1024)
            request = str(request)
            try:
                request = request.split()[1]
            except IndexError:
                pass
            if request == '/lighton?':
                pico_led.on()
                state = 'ON'
            elif request =='/lightoff?':
                pico_led.off()
                state = 'OFF'
            html = self.webpage()
            client.send(html)
            client.close()
    
    
    def runtime(self):
        try:
            ip = self.connect()
            connection = self.open_socket(ip)
            self.serve(connection)
        except KeyboardInterrupt:
            machine.reset()
    
server = HTTPServer()
    