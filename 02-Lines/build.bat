cls 
cl.exe /c /EHsc *.cpp
link.exe *.obj
renderer.exe
DEL *.obj
DEL *.exe
