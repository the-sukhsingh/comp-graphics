# Computer Graphics — GCC + `graphics.h` Setup

This guide explains how to set up **GCC/G++ with MSYS2 UCRT64** and the **WinBGIm `graphics.h` library** on Windows for Computer Graphics lab programs.

The setup allows programs such as:

```cpp
#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    char path[] = "";

    initgraph(&gd, &gm, path);

    putpixel(25, 25, RED);

    getch();
    closegraph();

    return 0;
}
```

to be compiled from VS Code/Antigravity.

---

## 1. Install MSYS2

Download and install MSYS2 from:

https://www.msys2.org/

The default installation directory is usually:

```text
C:\msys64
```

After installation, open:

**MSYS2 UCRT64**

> Important: Use the **UCRT64** terminal for the commands in this guide, not the plain MSYS terminal.

---

## 2. Update MSYS2

In the MSYS2 UCRT64 terminal, update the package database and system:

```bash
pacman -Syu
```

If MSYS2 asks you to close the terminal after updating, close it, reopen **MSYS2 UCRT64**, and run:

```bash
pacman -Syu
```

Repeat if required until there are no further updates.

---

## 3. Install GCC/G++

Install the UCRT64 GCC toolchain:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Verify the installation:

```bash
g++ --version
```

and:

```bash
gcc --version
```

Check the compiler architecture:

```bash
gcc -dumpmachine
```

For a 64-bit installation, you should see:

```text
x86_64-w64-mingw32
```

---

## 4. Add GCC to Windows PATH

The GCC executable is normally located at:

```text
C:\msys64\ucrt64\bin
```

Add this directory to your Windows **User PATH** or **System PATH**.

### Using Windows Environment Variables

1. Search Windows for **Environment Variables**.
2. Open **Edit the system environment variables**.
3. Click **Environment Variables**.
4. Under User variables or System variables, select `Path`.
5. Click **Edit**.
6. Click **New**.
7. Add:

```text
C:\msys64\ucrt64\bin
```

8. Click **OK** on all dialogs.
9. Completely close and reopen VS Code/Antigravity and PowerShell.

Verify from PowerShell:

```powershell
g++ --version
```

If `g++` is not recognized, check:

```powershell
$env:Path -split ';' | Select-String "msys64"
```

---

# 5. Install FreeGLUT (Optional)

FreeGLUT is useful for OpenGL-based programs, but it **does not provide the old BGI `graphics.h` API**.

Install it with:

```bash
pacman -S mingw-w64-ucrt-x86_64-freeglut
```

Do not expect this package alone to make:

```cpp
#include <graphics.h>
```

work.

---

# 6. Install WinBGIm / `graphics.h`

The old Turbo C++ `graphics.h` is not part of GCC.

For modern Windows development, use a **64-bit WinBGIm-compatible build**.

You need the matching files, typically:

```text
graphics.h
winbgim.h
libbgi.a
```

Make sure the BGI library is compatible with your **64-bit MinGW/UCRT64 compiler**.

A common source for a 64-bit WinBGIm build is:

https://github.com/ahmedshakill/WinBGIm-64

Do not mix unrelated versions of `graphics.h` and `libbgi.a`.

---

# 7. Install `graphics.h` Globally

If you want `graphics.h` available to all your MSYS2 UCRT64 C/C++ projects, copy:

```text
graphics.h
```

to:

```text
C:\msys64\ucrt64\include\
```

So the final location is:

```text
C:\msys64\ucrt64\include\graphics.h
```

If the package also provides `winbgim.h`, place it in the same directory:

```text
C:\msys64\ucrt64\include\winbgim.h
```

---

# 8. Install `libbgi.a` Globally

Copy:

```text
libbgi.a
```

to:

```text
C:\msys64\ucrt64\lib\
```

The final location should be:

```text
C:\msys64\ucrt64\lib\libbgi.a
```

Verify from MSYS2 UCRT64:

```bash
ls /ucrt64/include/graphics.h
```

and:

```bash
ls /ucrt64/lib/libbgi.a
```

Both files should be found.

---

# 9. Test `graphics.h`

Create a file named:

```text
test.CPP
```

Example:

```cpp
#include <graphics.h>

int main()
{
    int gd = DETECT, gm;

    char path[] = "";
    initgraph(&gd, &gm, path);

    setbkcolor(WHITE);
    cleardevice();

    putpixel(25, 25, RED);
    putpixel(30, 25, RED);
    putpixel(35, 25, RED);
    putpixel(40, 25, RED);

    getch();
    closegraph();

    return 0;
}
```

---

# 10. Compile from PowerShell

From your project directory:

```powershell
g++ -Wall -Wextra -g3 .\test.CPP `
    -lbgi `
    -lgdi32 `
    -lcomdlg32 `
    -luuid `
    -loleaut32 `
    -lole32 `
    -o .\output\test.exe
```

Or as a single line:

```powershell
g++ -Wall -Wextra -g3 .\test.CPP -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -o .\output\test.exe
```

Run the program:

```powershell
.\output\test.exe
```

---

# 11. Why the `-l` Options Are Required

Finding `graphics.h` and linking the BGI implementation are two different things.

The header:

```text
graphics.h
```

provides declarations for functions such as:

```cpp
initgraph()
putpixel()
setbkcolor()
cleardevice()
closegraph()
```

The actual implementations are provided by:

```text
libbgi.a
```

Therefore, compiling only:

```powershell
g++ test.CPP -o test.exe
```

can produce errors such as:

```text
undefined reference to `initgraph'
undefined reference to `putpixel'
undefined reference to `closegraph'
```

The `-lbgi` option tells G++ to link the BGI library.

The additional Windows libraries are required by the BGI implementation:

```text
-lbgi
-lgdi32
-lcomdlg32
-luuid
-loleaut32
-lole32
```

---

# 12. VS Code / Antigravity Configuration

To build your Computer Graphics programs using a keyboard shortcut, create:

```text
.vscode/tasks.json
```

Use:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "Build C++ Graphics",
            "command": "C:\\msys64\\ucrt64\\bin\\g++.exe",
            "args": [
                "-Wall",
                "-Wextra",
                "-g3",
                "${file}",
                "-lbgi",
                "-lgdi32",
                "-lcomdlg32",
                "-luuid",
                "-loleaut32",
                "-lole32",
                "-o",
                "${workspaceFolder}\\output\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

Now:

```text
Ctrl + Shift + B
```

will run:

```text
Build C++ Graphics
```

---

# 13. Configure IntelliSense

If VS Code shows:

```text
graphics.h: No such file or directory
```

even though the program compiles, configure IntelliSense separately.

Create:

```text
.vscode/c_cpp_properties.json
```

with:

```json
{
    "configurations": [
        {
            "name": "MSYS2 UCRT64",
            "compilerPath": "C:\\msys64\\ucrt64\\bin\\g++.exe",
            "includePath": [
                "${workspaceFolder}/**",
                "C:\\msys64\\ucrt64\\include"
            ],
            "defines": [],
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

Then reload VS Code/Antigravity.

---

# 14. Optional Keyboard Shortcut

To assign a dedicated key such as `F6`, open:

```text
Preferences: Open Keyboard Shortcuts (JSON)
```

and add:

```json
[
    {
        "key": "alt+d",
        "command": "workbench.action.tasks.runTask",
        "args": "Build C++ Graphics"
    }
]
```

Now pressing:

```text
Alt + D
```

runs the **Build C++ Graphics** task.

---

# 15. Recommended Project Structure

A Computer Graphics project can look like:

```text
comp-graphics/
│
├── .vscode/
│   ├── tasks.json
│   └── c_cpp_properties.json
│
├── output/
│   ├── test.exe
│   ├── P1_2.exe
│   └── ...
│
├── test.CPP
├── P1_2.CPP
├── P1_3.CPP
└── README.md
```

The BGI library itself stays globally installed:

```text
C:\msys64\ucrt64\
├── bin\
├── include\
│   ├── graphics.h
│   └── winbgim.h
└── lib\
    └── libbgi.a
```

---

# 16. Common Errors

### `gcc is not recognized`

GCC is not available in Windows PATH.

Add:

```text
C:\msys64\ucrt64\bin
```

to PATH and restart your terminal.

---

### `graphics.h: No such file or directory`

Check:

```text
C:\msys64\ucrt64\include\graphics.h
```

If it exists but VS Code still reports the error, configure `c_cpp_properties.json`.

---

### `undefined reference to initgraph`

You found `graphics.h`, but the BGI library isn't being linked.

Use:

```text
-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

---

### `cannot find -lbgi`

G++ cannot find:

```text
libbgi.a
```

Check:

```text
C:\msys64\ucrt64\lib\libbgi.a
```

---

### Warning about converting string constant to `char*`

Avoid:

```cpp
initgraph(&gd, &gm, "");
```

Use:

```cpp
char path[] = "";
initgraph(&gd, &gm, path);
```

This works around the old BGI API's `char*` parameter.

---

## Final Checklist

Before starting your Computer Graphics lab:

```text
[ ] MSYS2 installed
[ ] UCRT64 terminal used
[ ] GCC/G++ installed
[ ] C:\msys64\ucrt64\bin added to PATH
[ ] g++ --version works in PowerShell
[ ] graphics.h installed
[ ] libbgi.a installed
[ ] graphics.h is in C:\msys64\ucrt64\include
[ ] libbgi.a is in C:\msys64\ucrt64\lib
[ ] tasks.json contains BGI linker flags
[ ] c_cpp_properties.json configured
[ ] Ctrl+Shift+B/Alt+D builds the program
```

Once this setup is complete, new `graphics.h` lab programs can be compiled without manually configuring the library paths each time.
