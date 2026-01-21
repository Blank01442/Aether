# 🌌 Aether Programming Language v1.0
**The Universal Neural Programming Language**

![Aether Logo](https://raw.githubusercontent.com/Blank01442/Aether/main/logo.png)

Aether is a high-performance, neural-first programming language. It compiles directly to **x86-64 NASM Assembly**, offering the readability of a high-level language with the raw power of bare metal.

---

## ⚡ Key Features
- **🧠 Neural First**: Native support for Tensors (Arrays) and AI math primitives (`sqrt`, `exp`, `random`).
- **🚀 Bare Metal**: No VM, no Garbage Collector. Compiles directly to optimized machine code.
- **🔊 Hardware Control**: Native `beep(freq, dur)` support for audio feedback.
- **📂 Native File IO**: High-speed `write` and `append` primitives.
- **🌍 Universal Registry**: Built-in package manager. Install any library globally with `ae install name`.
- **📂 Modular**: Recursive `import` system for multi-file projects.

---

## 💎 Quick Syntax Showcase

```aether
// Aether v1.0 File IO & Sound
import "sound"

task initialize {
    say "System booting..."
    call play_success
    write "Log Start" to "boot.log"
    execute("dir")
}

call initialize
```
            
---

## 🛠️ Installation & Usage

1. **Clone the repository**:
   ```bash
   git clone https://github.com/Blank01442/Aether.git
   cd Aether
   ```

2. **Build the ecosystem**:
   ```bash
   ./build_all.bat
   ```

3. **Install a library**:
   ```bash
   ae install sound
   ```

4. **Run a script**:
   ```bash
   ae tests/system_test.ae -r
   ```

---

## 📦 Package Manager & Private Registries
Aether supports private repositories. To use your own private registry:
1. Set the environment variable `AETHER_TOKEN` to your GitHub Personal Access Token (PAT).
2. Use `ae install <name>` as usual. The compiler will automatically use the token for authentication.

---

## 📜 Metadata
- **Version**: 1.0.0.0 (Universal Edition)
- **License**: MIT
- **Contact**: Aether Intelligence
