@echo off
setlocal
echo Building Aether Compiler v2.7 "Ethereal Edition"...

:: Compile resource
windres src/resource.rc -o src/resource.obj

:: Compile core
gcc src/main.c src/lexer.c src/parser.c src/codegen.c src/resource.obj -o bin/ae.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ----------------------------------------------------
    echo Success! Aether v2.7 is ready.
    echo.
    echo The 'ae' command is located in:
    echo %cd%\bin
    echo ----------------------------------------------------
) else (
    echo Build failed. Check if GCC/Windres is installed.
)
endlocal