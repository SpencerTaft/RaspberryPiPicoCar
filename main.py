#import runnable #local runnable.py
import light #local light.py
import scheduler #local scheduler.py
import httpRunnables #local httpRunnables.py
import _thread

runtimeScheduler = scheduler.RuntimeScheduler()

lightDefaultConfig = {"ID": "headlights", "status": "off", "pin": 29}
runtimeScheduler.addRuntime(light.BinaryLight(lightDefaultConfig))

runtimeScheduler.addRuntime(httpRunnables.HTTPConnector({"ID": "connector"}))

#Run the scan runtimes in the second core.  This is because the http server encounters
#TinyUSB compatibility issues (micropython bug, which may be fixed in a future micropython release)
#_thread.start_new_thread(runtimeScheduler.runtime, ())
#runtimeScheduler.runtime()

#Run the http server on the primary core
server = httpRunnables.HTTPServer()

print("End of run")









