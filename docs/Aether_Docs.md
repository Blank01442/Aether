# 🌌 Aether Language: The Universal Documentation
**Version 1.0.0 (Universal Edition)**  
*The high-performance, neural-first logic engine.*

Aether is a Compiled, High-Level language that speaks directly to the metal. Designed for speed (x86-64 NASM) and simplicity (Human-Readable Syntax), it empowers developers to build everything from AI neural nets to system automation tools with zero overhead.

---

## 🚀 Quick Start
To get started, ensures you have the **Aether Ecosystem** installed via `setup.exe`.

1. **Create a file**: `main.ae`
2. **Write code**: `say "Hello Aether"`
3. **Compile & Run**: `ae main.ae -r`

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

### 3. Functional Units (Tasks)
Tasks are the building blocks of Aether applications. They are highly efficient and easy to call.
```aether
task finalize_boot {
    say "System initialized."
    beep(880, 100)
}

call finalize_boot
```

---

## 🔌 Native Primitives (New in v1.0)
Aether v1.0 "Universal Edition" introduces powerful native primitives for hardware and OS interaction.

### 📁 File I/O
Interact with the filesystem directly with extreme speed.
```aether
write "Data logged." to "app.log"
append " - [Timestamp Secured]" to "app.log"
```

### 🔊 Hardware & Audio
Generate pure square-wave audio for notifications or signals. Low-level accessibility with high-level syntax.
```aether
beep(440, 200) // frequency (Hz), duration (ms)
```

### 🛰️ System Execution
Run any shell command or native binary.
```aether
execute("dir /w")
execute("curl https://google.com")
```

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

## 🛡️ Smart Debugger
Aether features a "Human-First" debugger. Instead of cryptic assembly errors, it provides clear explanations and **Pro-Tips** on how to fix your code.

```text
ISSUE at Line 4, Col 2: The compiler expected a specific keyword here.
FOUND: "say"
PRO-TIP: Tasks need braces, like task my_task { ... }
```
