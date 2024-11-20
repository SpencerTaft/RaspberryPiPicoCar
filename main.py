import runnable #local runnable.py
import light #local light.py
import scheduler #local scheduler.py

runtimeScheduler = scheduler.RuntimeScheduler()

runtimeScheduler.addRuntime(light.PWMLight({"ID": "Left Headlight", "status": "on", "pin": 28}))
runtimeScheduler.addRuntime(light.BinaryLight({"ID": "Right Headlight", "status": "off", "pin": 29}))

runtimeScheduler.runtimeScan()

print("Successful run")









