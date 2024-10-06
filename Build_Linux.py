#!/usr/bin/python3
from glob import glob
from os import system
from os import remove
import platform
import os

global incdir
incdir = ("../../Libs/Units/Headers","../../Libs/Kitty/Headers")
Units = ("SlyvAsk","SlyvDir","SlyvDirry","SlyvQCol","SlyvStream","SlyvString","SlyvTime","SlyvVolumes")

def gcc(name,dir):
    print("Building: ",name)
    print("Dir: ",dir)
    d=glob(dir+"/*.c")
    for fp in d:
        print("Compiling: ",fp)
        sfp=fp.split("/")
        o = sfp[len(sfp)-1]
        o = o[:-1]+"o"
        return_code = system("gcc -c -o Linux/Objects/%s \"%s\""%(o,fp))
        if return_code>0:
            print("Compilation failed! (%d)"%return_code)
            quit()
          
def delf(file):
        print("Deleting: ",file)
        remove(file)
        
        
def gpp(name,dir,full=True,dirislist=False):
    global incdir
    print("Building: ",name)
    if full: print("Include dirs:",incdir)
    if dirislist: 
        print("%d specific files requested"%len(dir))
        d=dir
    else:
        print("Dir: ",dir)
        d=glob(dir+"/*.cpp")
    for fp in d:
        print("Compiling: ",fp)
        sfp=fp.split("/")
        o = sfp[len(sfp)-1]
        o = o[:-3]+"o"
        cmd =  "g++ -Woverflow -c -o Linux/Objects/%s "%o
        if full:
            for id in incdir:
                cmd+="\"-I%s\" "%id
        cmd += " \"%s\""%fp
        # print cmd # debug (Python 2)
        return_code = system(cmd)
        if return_code>0:
            print("Compilation failed! (%d)"%return_code)
            quit()          

def glijst(dir,lst):
    ret = []
    for l in lst: ret.append("%s/%s.cpp"%(dir,l))
    return ret
    
def newdir(d):
    if not os.path.exists(d):
        print("Creating directory: ",d)
        os.makedirs(d)
          
print("Building Kitty for Linux")
print("OS: ",platform.system(),"; release: ",platform.release())
if platform.system()!="Linux":
    print("I'm sorry, but this script has been designed for Linux Only!")
    quit()
newdir("Linux")
newdir("Linux/Objects")
newdir("Linux/Exe")
gpp("Slyvina Units",glijst("../../Libs/Units/Source",Units),True,True)
gpp("Kitty Library","../../Libs/Source/Kitty")