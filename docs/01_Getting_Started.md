# 🏁 Getting Started with Aether
**Your first 5 minutes in the Ethereal Ecosystem.**

> **⚡ Zero-Config Notice**: Aether is a high-performance compiled language. To make setup effortless, the installer automatically provisions the necessary **AI Toolchain (NASM & GCC)**. No manual installation is required.

Follow these steps to go from nothing to a working Aether development environment.

---

## 1. Installation
1. Download `setup.exe` from the repository.
2. Run it as **Administrator**.
3. The installer will:
   - Create `C:\Aether`
   - Extract the `ae.exe` compiler.
   - Globally register the `ae` command.
   - Sync the standard libraries.

## 2. Verify Your Power
Open a **new** terminal (PowerShell or CMD) and type:
```bash
ae
```
If you see the Aether ASCII banner and version info, you are ready to code.

## 3. Your First Script
Create a file named `start.ae` and type:
```aether
import "sound"

task begin {
    say "Powering up Aether..."
    call play_success
    alert("System Online!")
}

call begin
```

## 4. Run It
Execute your script with the `-r` (run) flag:
```bash
ae start.ae -r
```
You should hear a melody, see a Windows alert, and see the terminal output.

## 5. Expanding the Engine
Want more features? Install a library from the Registry.
```bash
ae install web_client
```
Then use it in your code:
```aether
import "web_client"
call get_ip
```

---

**Next Steps:** Read `docs/Aether_Docs.md` for the full syntax guide.
