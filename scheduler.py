import runnable #local runnable.py
import httpRunnables #local httpRunnables.py

class RuntimeScheduler():
    instance = None
    runnables = []

    #RuntimeScheduler is a singleton
    def __new__(cls, *args, **kwargs):
        if not cls.instance:
            cls.instance = super(RuntimeScheduler, cls).__new__(cls, *args, **kwargs)
        return cls.instance
    
    def addRuntime(self, runnable):
        self.runnables.append(runnable)
        
    def runtimeScan(self):
        receivedLightConfig = {}
        isNewLightConfig = False

        #runs a single scan of each runtime object added
        for runnableInstance in self.runnables:
            if runnableInstance.getID() == ("BinaryLight", "headlights"):
                if isNewLightConfig:
                    runnableInstance.setConfig(self, receivedLightConfig)
            else:
                print(runnableInstance.getID())

            if runnableInstance.getID() == ("HTTPConnector", "connector"):
                if httpRunnables.HTTPConnector.getIsNewConfigAvailable(runnableInstance):
                    receivedLightConfig = httpRunnables.HTTPConnector.getReceivedConfig(runnableInstance)
                    isNewLightConfig = True
            
            runStatus = runnableInstance.runtime()
            if (runStatus != runnable.RuntimeExecutionStatus.SUCCESS):
                break;
        print("runtime scan complete")
        
    def runtime(self):
        self.runtimeScan()
        while(True):
            self.runtimeScan()
            time.sleep(10)
            
