# Compiling instructions

Kitty is using the Slyvina framework and is not in need of 3rd party dependencies, only my own "dependencies" and only during compiling.

# Preparations

Regardless of your operating system these preparations are the same. For Windows I recommend you do this in PowerShell, and for Linux I guess sh or bash will do.

You need a dedicated directory for Slyvina. This file will assume this is the first Slyvina application you're gonna build. 
It goes of course without saying that git should be installed.
I'll call the Slyvina directory now /Slyvina, but I guess it's obvious you should substitute that with with your own directory.
Here goes.
~~~sh
mkdir /Slyvina
chdir /Slyvina
mkdir Tools
mkdir Apps # not really needed for Kitty, but if you're gonna build more, you may need it.
mkdir Libs
git clone Tricky1975/Kitty_CPP Tools/Kitty
git close Slyvina/Kitty Libs/Kitty
git clone Slyvina/Units Libs/Units
~~~

# Compiling in Windows
In /Slyvina/Tools/Kitty you will now find the Kitty.sln file. Run it in VisualStudio (don't try any other compiler in Windows. You'll be sorry). 
In it you'll find 3 projects. Kitty, Kitty_Lib and Kitty_DLL. Now if you are interested in creating your own tools with the Kitty library you may sort out Kitty_Lib and Kitty_DLL, but for now let's ignore that, just compile the Kitty project.
Make sure VS is configured to compile in 'Release' mode.

Once compiled there should be:
- Slyvina/Tools/Kitty/Exe.x64.Release\Kitty.exe
- Slyvina/Tools/Kitty/Exe.x64.Release\Kitty.pdb

The .pdb file is only a debugger file, not needed for actual action. The .exe file can run without it. Kitty should work now. Have fun.


# Compiling in Linux
I've just created a simple Python3 script for this, so you'll need Python3 to be installed along with GCC, as the script is set to use GCC for compiling.
~~~sh
chdir /Slyvina/Tools/Kitty
python3 Build_Linux.py
~~~
That should actually do the trick.
The file /Slyvina/Tools/Kitty/Linux/Exe/Kitty should be your executable file
The directory /Slyvina/Tools/Kitty/Linux/Objects contains all the object files created during compilation. You may wanna delete them if you really need the space.
