copy /Y ..\x64\Release\*.lib ..\CSTL\lib\*.lib
del ..\x64\Release\*lib
del ..\x64\Release\*.pdb
del ..\x64\Release\*.exp
copy /Y ..\x64\Release\*.dll ..\CSTL\DLL\*.dll
copy /Y *.h ..\CSTL\include\*.h
exit 0