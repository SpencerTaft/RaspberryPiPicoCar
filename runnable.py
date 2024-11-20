from micropython import const

class RuntimeExecutionStatus:
    SUCCESS = const(1)
    FAILURE = const(2)
    TIMEOUT = const(3)


#base class for all runtimes within the synchronous core
class Runnable:
    def __init__(self, defaultConfig, ID):
        self.config = defaultConfig
        self.ID = ID
    
    def runtime(self):
        raise NotImplementedError("Runtime Implementation Missing")
        return RuntimeExecutionStatus.FAILURE
    
    def getID(self):
        #this can return a string, or a tuple containing object type (overwrite by child class) and ID (eg. {light, frontLeftHeadlight})
            #ID should match an entry in the database
            #ID should be strings or tuples of strings, easy to support derived classes
        raise NotImplementedError("Runtime Implementation Missing")
    
    def setConfig(self, newConfig):
        raise NotImplementedError("Runtime Implementation Missing")