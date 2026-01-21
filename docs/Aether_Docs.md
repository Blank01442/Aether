# 🌌 Aether: The Master Guide
**Version 1.0.0 (Universal Edition)**  
*Low-Level Power. High-Level Elegance.*

Welcome to Aether. You are holding a compiler that bridges the gap between the efficiency of x86-64 Assembly and the readability of modern logic. This guide will take you from a novice "player" to a master architect of the Aether ecosystem.

---

## ⚡ The Quick-Start Loop
Aether is built for a fast **Write -> Compile -> Run** cycle.

1. **Craft a file**: `hello.ae`
2. **Inject logic**: `say "System Online"`
3. **Execute**: `ae hello.ae -r`

---

## 💎 Core Syntax

### 1. The Assignment Engine
Aether uses a natural-language assignment style. No types are required; the compiler infers them instantly.
```aether
set count to 10              // Integer
set rate to 0.75             // Float
set status to "Operation Alpha" // String
set active to true           // Boolean
```

### 2. Control Logic
Aether provides robust flow control for complex logic.
```aether
// If / Else conditions
if score > 80 {
    say "Superior Performance"
} else {
    say "Optimization Required"
}

// Fixed-count loops
repeat 5 times {
    say "Running loop..."
}

// Ranges
for i from 1 to 10 {
    say i
}

// Dynamic conditions
while health > 0 {
    set health to health - 5
}
```

### 4. Tasks (Procedures)
Tasks allow you to wrap complex logic into reusable blocks. They are zero-overhead and highly performant.
```aether
task confirm_startup {
    say "Aether Engine: Operational."
    beep(880, 100) // Auditory feedback
}

call confirm_startup
```

---

## 🛠️ The Power Primitives (v1.0)
These are the "Heavy Hitters" of the Aether language—native commands that talk directly to Windows and the CPU.

| Command | Action | Example |
| :--- | :--- | :--- |
| `write` | Create/Overwrite a file | `write "Data" to "save.txt"` |
| `append` | Add data to end of file | `append "Log" to "save.txt"` |
| `beep` | Play a system frequency | `beep(440, 200)` |
| `execute` | Run machine commands | `execute("dir /w")` |
| `alert` | Pop up a system window | `alert("Done!")` |
| `exit` | Kill the current process | `exit` |

### 🖼️ Native Windows UI
Create system dialogues and query hardware info.
```aether
alert("Update Complete")
set w to screen_width()
set h to screen_height()
```

---

## 🧠 Neural & Math Primitives
Aether is built for math. High-speed tensors and specialized math functions are baked into the core.
- `array memory from 1000`: Allocates an array of 1000 high-speed 64-bit slots.
- `random(min, max)`: Fast, hardware-seeded random number generation.
- `sqrt(x)` & `exp(x)`: SSE2-optimized math functions.
- `time`: High-precision timer (ms since boot) for benchmarking AI performance.

---

## 🌍 The Universal Registry (Package Manager)
Aether features a global library ecosystem.

### Installing Libraries
Use the command line to fetch verified libraries from the Aether Registry:
```bash
ae install sound
ae install web_client
```

### Using Libraries
Import them at the top of your script to unlock new capabilities.
```aether
import "sound"
call play_success
```

### Private Registry Access
To access a private library registry, set your `AETHER_TOKEN`:
1. In Windows, run: `setx AETHER_TOKEN your_github_pat_here`
2. The compiler will now automatically authenticate all `ae install` requests.

---

## 🛠️ Included Standard Libraries
Aether v1.0 comes with a suite of professional-grade libraries:
1. `math_pro`: Advanced mathematical operations.
2. `neural_core`: AI weights and activation functions.
3. `win_ui`: Native Windows tools and alerts.
4. `app_core`: Process management and exit tasks.
5. `file_io`: Higher-level file management (logging, cleanup).
6. `web_client`: Network interactions (ping, public IP lookup).
7. `utility`: System cleanup, process listing, and directory tools.
8. `sound`: Pre-defined audio patterns (success, notification, sonar).

---

## ⚠️ Common Pitfalls & Pro-Tips
Even masters trip up. Here’s what to watch out for:

1.  **The 'to' Keyword**: Assignments use `to`, not `=`.
    -   ❌ `set x = 10`
    -   ✅ `set x to 10`
2.  **Task Braces**: Tasks **must** open with a `{` on the same line.
3.  **Strings**: Always use double-quotes `"`.
4.  **Permissions**: If `setup.exe` fails, ensure you are running in a terminal with **Administrator privileges** to allow the installer to provision the Toolchain and write to `C:\Aether`. Aether handles NASM and GCC setup automatically for you.

---

## 🏆 Becoming a Master
The best way to learn is to play. Check out `docs/Tutorial.ae` for a live-action demonstration of every single feature in the language.

---

## 🛡️ Smart Debugger
Aether features a "Human-First" debugger. Instead of cryptic assembly errors, it provides clear explanations and **Pro-Tips** on how to fix your code.

```text
ISSUE at Line 4, Col 2: The compiler expected a specific keyword here.
FOUND: "say"
PRO-TIP: Tasks need braces, like task my_task { ... }
```
