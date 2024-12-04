import runnable #local runnable.py
import light #local light.py
import scheduler #local scheduler.py
import httpRunnables #local httpRunnables.py
import _thread

runtimeScheduler = scheduler.RuntimeScheduler()

runtimeScheduler.addRuntime(light.PWMLight({"ID": "Left Headlight", "status": "on", "pin": 28, "maxLightPercent": 80, "flashingPeriod": 2}))
runtimeScheduler.addRuntime(light.BinaryLight({"ID": "Right Headlight", "status": "off", "pin": 29, "flashingPeriod": 3}))
runtimeScheduler.addRuntime(httpRunnables.HTTPConnector({"ID": "HTTP Connector"}))

#Run the scan runtimes in the second core.  This is because the http server encounters
#TinyUSB compatibility issues (micropython bug, which may be fixed in a future micropython release)
_thread.start_new_thread(runtimeScheduler.runtime, ())

#Run the http server on the primary core
server = httpRunnables.HTTPServer()
server.runtime()

print("End of run")









