#base class for all runtimes within the synchronous core
class RuntimeObject:
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        raise NotImplementedError("Runtime Implementation Missing")
    
#base light class
class Light(RuntimeObject):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Light Runtime")
        pass


class Database(RuntimeObject):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("DB Runtime")
        pass
    
class Motor(RuntimeObject):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("Motor Runtime")
        pass

#Synchronous 
class HTTPConnector(RuntimeObject):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("HTTP Runtime")
        pass

class RuntimeScheduler():
    def __init__(self):
        #todo convert to singleton
        self.runtimeObjects = []
    
    def addRuntime(self, runtimeObject):
        #todo this should take a runtime type, and possibly return the index in the runtime list that this object is added as
        #possibly create a map for easy access to runtimes by key
        self.runtimeObjects.append(runtimeObject)
        
    def runtimeScan(self):
        #runs a single scan of each runtime object added
        for runtimeObject in self.runtimeObjects:
            runtimeObject.runtime()
        print("runtime scan complete")



runtimeScheduler = RuntimeScheduler()
runtimeScheduler.addRuntime(Light())
runtimeScheduler.addRuntime(Light())

runtimeScheduler.runtimeScan()

print("Successful run")









