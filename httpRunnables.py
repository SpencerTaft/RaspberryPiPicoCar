import network
import socket
import time
import machine
import runnable #local runnable.py

httpAccessSemaphore = 0

def isAcquireHTTPConfigLockSuccess():
    #shared function between runtime and HTTP server to grab a simulated mutex (aka semaphore with users == 1).  Returns true if successful
    global httpAccessSemaphore
    
    if (httpAccessSemaphore > 0):
        #httpAccessSemaphore is already occupied
        return False 
    else:
        #increment the semaphore, wait 1ms, and then check for race conditions
        httpAccessSemaphore += 1
        time.sleep(1) #small delay to ensure no race condition
        
        if (httpAccessSemaphore == 1):
            #lock success
            return True
        elif (httpAccessSemaphore == 2):
            #since the lock attempt, another process incremented the semaphore.  reduce lock by one
            httpAccessSemaphore -= 1 #reset this attempt
            return False
        elif (httpAccessSemaphore == 0):
            #since the lock attempt, another process released the semaphore.  Reset the semaphore
            httpAccessSemaphore = 1
            return True
        else:
            #semaphore has overrun range
            print("httpAccessSemaphore has overrun bounds")
            return False

def isReleaseHTTPConfigLockSuccess():
    #shared function between runtime and HTTP server to release a simulated mutex (aka semaphore with users == 1)
    global httpAccessSemaphore
    httpAccessSemaphore -= 1
    

class HTTPConfig():
    #Shared resource
    def __init__(self):
        self.isNewConfigAvailable = False
        self.config = {}
    
    def getIsNewConfigAvailable(self):
        return self.isNewConfigAvailable

    def getConfig(self):
        if self.isNewConfigAvailable:
            self.isNewConfigAvailable = False
        return self.config
    
    def setConfig(self, newConfig):
        self.isNewConfigAvailable = True
        self.config = newConfig
        
httpConfig = HTTPConfig() #shared instance between HTTPConnector and HTTPServer

class HTTPConnector(runnable.Runnable):
    def __init__(self, defaultConfig):
        self.config = defaultConfig
        self.ID = defaultConfig['ID']
        self.isNewConfigAvailable = False
        self.receivedConfig = {}
    
    def runtime(self):
        print("HTTP Connector Runtime")
        global httpConfig

        if isAcquireHTTPConfigLockSuccess():
            print("HTTPConnector acquired lock")
            if httpConfig.getIsNewConfigAvailable():
                self.receivedConfig = httpConfig.getConfig()
                self.isNewConfigAvailable = True
            isReleaseHTTPConfigLockSuccess()
        else:
            print("HTTPConnector could not acquire lock")
        
        return runnable.RuntimeExecutionStatus.SUCCESS
    
    def getID(self):
        return ("HTTPConnector", self.ID)
    
    def setConfig(self, newConfig):
        if self.config != newConfig:
            self.config = newConfig
        #no config fields currently

    def getIsNewConfigAvailable(self):
        return self.isNewConfigAvailable
    
    def getReceivedConfig(self):
        self.isNewConfigAvailable = False
        return self.receivedConfig

#async HTTP server that receives requests from HTTP clients, and provides config to HTTP connector
class HTTPServer():    
    def __init__(self):
        self.state = 'OFF'
        self.runtime();
    
    def connect(self):
        #Connect to WLAN
        fileContents = []
        with open('secret.txt','r') as file:
            for line in file:
                print(line, end='')
                fileContents.append(line.rstrip())
        ssid = fileContents[0]
        password = fileContents[1]
        
        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        wlan.connect(ssid, password)
        while wlan.isconnected() == False:
            print('Waiting for connection...')
            time.sleep(1)
        ip = wlan.ifconfig()[0] #this is the ip address of the raspberry pi pico w
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
                <form action="./lighton">
                <input type="submit" value="Light on" />
                </form>
                <form action="./lightoff">
                <input type="submit" value="Light off" />
                </form>
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
                if self.state == 'OFF':
                    self.state = 'ON'
                    self.updateConfig()
            elif request =='/lightoff?':
                if self.state == 'ON':
                    self.state = 'OFF'
                    self.updateConfig()
            html = self.webpage()
            client.send(html)
            client.close()
    
    def updateConfig(self):
        global httpConfig

        updatedConfigSuccess = False
        while (not updatedConfigSuccess):
            if not isAcquireHTTPConfigLockSuccess():
                newConfig = {}

                if self.state == 'ON':
                    print ("update config switching to ON state")
                    newConfig = {"ID": "headlights", "status": "on", "pin": 29}
                else:
                    print ("update config switching to ON state")
                    newConfig = {"ID": "headlights", "status": "off", "pin": 29}

                httpConfig.setConfig(newConfig)
                updatedConfigSuccess = True
            else:
                print("Failed to acquire lock after receiving new HTTP config")
                time.sleep(1)

    
    def runtime(self):
        try:
            ip = self.connect()
            connection = self.open_socket(ip)
            self.serve(connection)
        except KeyboardInterrupt:
            machine.reset()
    