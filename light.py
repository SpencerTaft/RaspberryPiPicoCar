import runnable

#base light class
class Light(runnable.Runnable):
    
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        raise NotImplementedError("Light Implementation Missing")

    def getID(self):
        raise NotImplementedError("Light Implementation Missing")

    def setConfig(self, newConfig):
        raise NotImplementedError("Light Implementation Missing")
    
    #todo add timer logic here to be shared by both PWMLight and BinaryLight
        #PWMLight implements a sawtooth wave using timer logic
        #BinaryLight implements a square wave using timer logic

class PWMLight(Light):
    def __init__(self, defaultConfig):
        self.config = defaultConfig #save config as an attribute for quick compares for new config without parsing JSON.  This may be removed in the future
        self.ID = defaultConfig['ID']
        self.status = defaultConfig['status'] #on/off, on means that the pin is on at maxLightPercent.  status must be on to enable flashing
        self.pin = defaultConfig['pin']
        self.maxLightPercent = defaultConfig['maxLightPercent'] #max brightness that light can reach
        self.flashingPeriod = defaultConfig['flashingPeriod'] #period in seconds.  A value of zero or a status of off disables flashing
    
    def runtime(self):
        print("PWM Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
    
    def getID(self):
        return ("PWMLight", ID)
    
    def setConfig(self, newConfig):
        if (self.config != newConfig):
            self.config = newConfig
            self.status = newConfig['status']
            self.pin = newConfig['pin']
            self.maxLightPercent = newConfig['maxLightPercent']
            self.flashingPeriod = newConfig['flashingPeriod']
            pass
    
class BinaryLight(Light):
    def __init__(self, defaultConfig):
        self.config = defaultConfig #save config as an attribute for quick compares for new config without parsing JSON.  This may be removed in the future
        self.ID = defaultConfig['ID']
        self.status = defaultConfig['status'] #on/off
        self.pin = defaultConfig['pin']
        self.flashingPeriod = defaultConfig['flashingPeriod'] #period in seconds.  A value of zero or a status of off disables flashing
    
    def runtime(self):
        print("Binary Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
    
    def getID(self):
        return ("BinaryLight", ID)
    
    def setConfig(self, newConfig):
        if (self.config != newConfig):
            self.config = newConfig
            self.status = newConfig['status'] #on/off
            self.pin = newConfig['pin'] #GPIO pin
            self.flashingPeriod = newConfig['flashingPeriod']
            pass