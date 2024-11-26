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
        raise NotImplementedError("Runtime Implementation Missing")
    
    def setConfig(self, newConfig):
        raise NotImplementedError("Runtime Implementation Missing")