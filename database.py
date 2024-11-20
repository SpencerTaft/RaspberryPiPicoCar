class Database(runnable.Runnable):
    def __init__(self):
        pass #constructor
    
    def runtime(self):
        print("DB Runtime")
        return runnable.RuntimeExecutionStatus.SUCCESS