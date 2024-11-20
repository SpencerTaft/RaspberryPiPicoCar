import runnable #local runnable.py

class RuntimeScheduler():
    def __init__(self):
        #todo convert to singleton
        self.runnables = []
    
    def addRuntime(self, runnable):
        #ossibly return the index in the runtime list that this object is added as
        #possibly create a map for easy access to runtimes by key(key = runnable ID)
        self.runnables.append(runnable)
        
    def runtimeScan(self):
        #runs a single scan of each runtime object added
        for runnableInstance in self.runnables:
            #todo time the run using async core, then timeout.  Long term goal
            runStatus = runnableInstance.runtime()
            if (runStatus != runnable.RuntimeExecutionStatus.SUCCESS):
                break; #temporary solution
            
        print("runtime scan complete")
