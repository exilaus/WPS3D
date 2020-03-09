import androidhelper
import sys
import urllib.request
import time
import os

nshot=350 #nuber of shots
step = str(int(10500\nshot)) #steps
droid = androidhelper.Android()
droid.makeToast("Welcome to WPS3D basic")
print("|=======================|")
print("|=======================|")
print("|Welcome to WPS3D Basic |")
print("|=======================|")
print("|=======================|")
while True: 
   resultados=droid.wifiGetConnectionInfo()
   res=resultados[1]
   droid.makeToast("you are connect on "+str(res['ssid'])+"\n please Connect to:\n SSID ttable PWD scanner12123 ")
   print ("you are connect on "+str(res['ssid']))
   print ("connect to ssid ttable pwd scanner12123")
   if ("table" in str(res['ssid'])): 
                        break
   else : 
    droid.makeToast("Waiting 10 second")
    print ("Waiting 10 second")
    print("|=======================|")
    time.sleep(10)
    
fixpath= '/sdcard/WPS3D/'
fixpath += time.strftime("%m%d%Y%H%M%S")+'/'
droid.makeToast(fixpath)
for i in range(nshot): 
    temp = str(i)
    path = fixpath+temp
    path += '.JPG'
    droid.cameraCapturePicture(path, True)
    conn = urllib.request.urlopen("http://192.168.4.1/move?"step)
    droid.makeToast(temp)
    print(temp)  
conn = urllib.request.urlopen("http://192.168.4.1/off")
droid.wifiDisconnect()
droid.makeToast("Project saved in "+ fixpath)
droid.makeToast("Scan complete")
print("Project saved in "+ fixpath)
print("|=======================|")
print("|     Scan complete     |")
print("|=======================|")