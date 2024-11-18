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
    
    #todo could add timer logic here to be shared by both PWMLight and BinaryLight


    #Comments below are for brainstorming necessary methods:
    #lights can: turn on/off (state), dim (0-100%) using PWM, flashing (ramp up and down) using PWM
        #dim and on/off can be combined into a single functionality.  However, the microcontroller has only 8 PWM channels
    #needs an enum setting if it can support PWM or binary on off
        #eg. PWMLight, SimpleLight

class PWMLight(Light):
    def __init__(self, defaultConfig,ID):
        self.config = defaultConfig #save config as an attribute for quick compares for new config without parsing JSON
        self.ID = ID
        defaultConfigData = ujson.loads(defaultConfig)
        self.status = defaultConfigData['status'] #on/off
        self.pin = defaultConfigData['pin']
        #todo more fields for ramp, etc.
        pass #constructor
    
    def runtime(self):
        print("PWM Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
    
    def getID(self):
        #this can return a string, or a tuple containing object type (overwrite by child class) and ID (eg. {light, frontLeftHeadlight})
            #ID should match an entry in the database
            #ID should be strings or tuples of strings, easy to support derived classes
        return ("PWMLight", ID)
    
    def setConfig(self, newConfig):
        if (self.config != newConfig):
            newConfigData = ujson.loads(newConfig)
            status = newConfigData['status'] #on/off
            pin = newConfigData['pin'] #GPIO pin
            pass
    
class BinaryLight(Light):
    def __init__(self, defaultConfig,ID):
        self.config = defaultConfig #save config as an attribute for quick compares for new config without parsing JSON
        self.ID = ID
        defaultConfigData = ujson.loads(defaultConfig)
        self.status = defaultConfigData['status'] #on/off
        self.pin = defaultConfigData['pin']
        #todo more fields for blink, etc.
        pass #constructor
    
    def runtime(self):
        print("Binary Light Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS
    
    def getID(self):
        #this can return a string, or a tuple containing object type (overwrite by child class) and ID (eg. {light, frontLeftHeadlight})
            #ID should match an entry in the database
            #ID should be strings or tuples of strings, easy to support derived classes
        return ("BinaryLight", ID)
    
    def setConfig(self, newConfig):
        if (self.config != newConfig):
            newConfigData = ujson.loads(newConfig)
            status = newConfigData['status'] #on/off
            pin = newConfigData['pin'] #GPIO pin
            pass