#from micropython import const
import runnable
    
#base light class
class Light(runnable.Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS

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
        return runnable.RuntimeExecutionStatus.SUCCESS
    
class BinaryLight(Light):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Binary Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS


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
runtimeScheduler.addRuntime(Light())
runtimeScheduler.addRuntime(PWMLight())
runtimeScheduler.addRuntime(BinaryLight())

runtimeScheduler.runtimeScan()

print("Successful run")









