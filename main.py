import runnable #local runnable.py
import light #local light.py
import scheduler #local scheduler.py
import httpRunnables #local httpRunnables.py
import time
import _thread

runtimeScheduler = scheduler.RuntimeScheduler()

runtimeScheduler.addRuntime(light.PWMLight({"ID": "Left Headlight", "status": "on", "pin": 28}))
runtimeScheduler.addRuntime(light.BinaryLight({"ID": "Right Headlight", "status": "off", "pin": 29}))


#runtimeScheduler.runtimeScan()
#Run the scan runtimes in the second core.  This is because the http server does not run well
#within the async environment since it encounters TinyUSB compatibility issues
_thread.start_new_thread(runtimeScheduler.runtimeScan, ())

#Run the http server on the primary core
server = httpRunnables.HTTPServer()
server.runtime()

print("Successful run")









