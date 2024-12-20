import runnable

class Light(runnable.Runnable):
    
    def __init__(self):
        pass
    
    def runtime(self):
        raise NotImplementedError("Light Implementation Missing")

    def getID(self):
        raise NotImplementedError("Light Implementation Missing")

    def setConfig(self, newConfig):
        raise NotImplementedError("Light Implementation Missing")

class BinaryLight(Light):
    def __init__(self, defaultConfig):
        self.config = defaultConfig #save config as an attribute for quick compares for new config without parsing dictionary contents
        self.ID = defaultConfig['ID']
        self.status = defaultConfig['status'] #on/off
        self.pin = defaultConfig['pin']
    
    def runtime(self):
        print("Binary Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
    
    def getID(self):
        return ("BinaryLight", self.ID)
    
    def setConfig(self, newConfig):
        if (self.config != newConfig):
            self.config = newConfig
            self.status = newConfig['status'] #on/off
            self.pin = newConfig['pin'] #GPIO pin
            pass
