#from micropython import const
import ujson

import runnable
import light

class Database(runnable.Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("DB Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
    
#not implemented for V1
class Motor(runnable.Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Motor Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
 
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

class RuntimeScheduler():
    def __init__(self):
        #todo convert to singleton
        self.runnables = []
    
    def addRuntime(self, runnable):
        #todo this should take a runtime type, and possibly return the index in the runtime list that this object is added as
        #possibly create a map for easy access to runtimes by key
        self.runnables.append(runnable)
        
    def runtimeScan(self):
        #runs a single scan of each runtime object added
        for runnableInstance in self.runnables:
            #todo time the run using async core, then timeout.  Long term goal
            runStatus = runnableInstance.runtime()
            if (runStatus != runnable.RuntimeExecutionStatus.SUCCESS):
                break; #temporary solution
            
        print("runtime scan complete")



runtimeScheduler = RuntimeScheduler()
#runtimeScheduler.addRuntime(Light())

pwmLightDefaultConfig = {"status": "on", "pin": 28}
runtimeScheduler.addRuntime(light.PWMLight("LeftHeadLight", pwmLightDefaultConfig))

binaryLightDefaultConfig = {"status": "off", "pin": 28}
runtimeScheduler.addRuntime(light.BinaryLight(), binaryLightDefaultConfig)

runtimeScheduler.runtimeScan()

print("Successful run")


#data = {"name": "Bob", "age": 30}
#json_string = ujson.dumps(data)









