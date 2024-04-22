copy /Y ..\x64\Debug\*.lib ..\CSTL\lib\*.lib
del ..\x64\Debug\*lib
del ..\x64\Debug\*.pdb
del ..\x64\Debug\*.exp
copy /Y ..\x64\Debug\*.dll ..\CSTL\DLL\*.dll
copy /Y *.h ..\CSTL\include\*.h
exit 0