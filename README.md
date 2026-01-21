# 🌌 Aether Programming Language v2.9
**The Universal Neural Programming Language**

![Aether Logo](https://raw.githubusercontent.com/AetherLang/Aether/main/logo.png)

Aether is a high-performance, neural-first programming language designed for humans and AI. It compiles directly to **x86-64 NASM Assembly**, offering the readability of a high-level language with the raw power of bare metal.

---

## ⚡ Key Features
- **🧠 Neural First**: Native support for Tensors (Arrays) and AI math primitives (`sqrt`, `exp`, `random`).
- **🚀 Bare Metal**: No VM, no Garbage Collector. Compiles directly to optimized machine code.
- **🛡️ Smart Debugger**: Human-friendly error messages that tell you exactly what’s wrong and how to fix it.
- **🌍 Universal Registry**: Built-in package manager. Install any library globally with `ae install name`.
- **📂 Modular**: Recursive `import` system for multi-file projects and custom libraries.

---

## 💎 Quick Syntax Showcase

```aether
// Aether v2.9 Logic
import "neural_core"

task train_epoch {
    set learning_rate to 0.05
    array weights from 1000  // Allocates high-speed memory

    for i from 1 to 100 {
        set loss to random(0, 100)
        say "Epoch Loss: "
        say loss
    }
}

call train_epoch
```

---

## 🛠️ Installation & Usage

1. **Clone the repository**:
   ```bash
   git clone https://github.com/AetherLang/Aether.git
   cd Aether
   ```

2. **Build the compiler**:
   ```bash
   ./build_compiler.bat
   ```

3. **Run your first script**:
   ```bash
   ae tests/neural.ae -r
   ```

4. **Install a library**:
   ```bash
   ae install math_pro
   ```

---

## 📦 Package Manager
Aether includes a built-in package manager that fetches from the central registry:
- `ae install <name>`: Downloads a library to your local `lib/` directory.
- `import "<name>"`: Uses the library in your code.

---

## 📜 Metadata
- **Version**: 2.9.0.0 (Neural Edition)
- **License**: MIT
- **Contact**: Aether Intelligence
