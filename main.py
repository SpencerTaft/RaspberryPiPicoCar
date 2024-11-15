#todo split project into a file per class

#base class for all runtimes within the synchronous core
class Runnable:
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        raise NotImplementedError("Runtime Implementation Missing")
        #todo this should return the execution status(success, timeout, etc.) and executionTime
    
    #Commented methods below are for brainstorming necessary methods:
    #def returnID():
        #this can return a string, or a tuple containing object type (overwrite by child class) and ID (eg. {light, frontLeftHeadlight})
            #ID should match an entry in the database
        #ID should be strings or tuples of strings, easy to support derived classes
    
#base light class
class Light(Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Light Runtime")
        pass

    #Comments below are for brainstorming necessary methods:
    #methods in base class should be logic usable by all derived classes: cabin light
        #might not need derived classes, pending usage of light objects
    #lights can: turn on/off (state), dim (0-100%) using PWM, flashing (ramp up and down) using PWM
        #dim and on/off can be combined into a single functionality.  However, the microcontroller has only 8 PWM channels
    #needs an enum setting if it can support PWM or binary on off
        #eg. PWMLight, SimpleLight

class PWMLight(Light):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("PWM Light Runtime")
        pass
    
class BinaryLight(Light):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Binary Light Runtime")
        pass


class Database(Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("DB Runtime")
        pass
    
#not implemented for V1
class Motor(Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Motor Runtime")
        pass
 
class HTTPConnector(Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("HTTP Connector Runtime")
        #todo check for new information from Async HTTP Server
        pass
    
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
        for runnable in self.runnables:
            runnable.runtime()
        print("runtime scan complete")



runtimeScheduler = RuntimeScheduler()
runtimeScheduler.addRuntime(Light())
runtimeScheduler.addRuntime(PWMLight())
runtimeScheduler.addRuntime(BinaryLight())

runtimeScheduler.runtimeScan()

print("Successful run")









