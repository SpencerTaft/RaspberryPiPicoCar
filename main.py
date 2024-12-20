import light #local light.py
import scheduler #local scheduler.py
import httpRunnables #local httpRunnables.py
import _thread

runtimeScheduler = scheduler.RuntimeScheduler()

lightDefaultConfig = {"ID": "headlights", "status": "off", "pin": 29}
runtimeScheduler.addRuntime(light.BinaryLight(lightDefaultConfig))

runtimeScheduler.addRuntime(httpRunnables.HTTPConnector({"ID": "connector"}))

#Due to Micropython limitations on the Pico Pi W, multithreading does not work with the implemented HTTP server.
#Either the runtimeScheduler runs, or the server runs.  This project will be ported to C++, where multithreading
#will work as intended

#_thread.start_new_thread(runtimeScheduler.runtime, ())
server = httpRunnables.HTTPServer()

print("Program terminated")