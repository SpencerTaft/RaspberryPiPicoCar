import runnable #local runnable.py
import time

class RuntimeScheduler():
    instance = None
    runnables = []

    #RuntimeScheduler is a singleton
    def __new__(cls, *args, **kwargs):
        if not cls.instance:
            cls.instance = super(RuntimeScheduler, cls).__new__(cls, *args, **kwargs)
        return cls.instance
    
    def addRuntime(self, runnable):
        #possibly return the index in the runtime list that this object is added as
        #possibly create a map for easy access to runtimes by key(key = runnable ID)
        self.runnables.append(runnable)
        
    def runtimeScan(self):
        #runs a single scan of each runtime object added
        for runnableInstance in self.runnables:
            if runnableInstance.getID() == ("PWMLight", "Left Headlight"):
                print("hit the special condition!")
            else:
                print(runnableInstance.getID())       
            
            #todo time the run using async core, then timeout.  Long term goal
            runStatus = runnableInstance.runtime()
            if (runStatus != runnable.RuntimeExecutionStatus.SUCCESS):
                break; #temporary solution
        print("runtime scan complete")
        
    def runtime(self):
        while(True):
            self.runtimeScan()
            time.sleep(10)
            
