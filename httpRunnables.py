class HTTPConnector(runnable.Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("HTTP Connector Runtime")
        #todo check for new information from Async HTTP Server
        return runnable.RuntimeExecutionStatus.SUCCESS
    
class HTTPServer():
    def __init__(self):
        pass
    #async HTTP server that receives GET and POST requests from HTTP clients, and provides data or data requests to HTTP connector