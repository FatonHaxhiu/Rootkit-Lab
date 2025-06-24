# 🕵️‍♂️ Rootkit Tool

An **educational Linux userland rootkit** built using `LD_PRELOAD`, designed to simulate basic stealth techniques like hiding files and processes. This lab includes detection scripts and automated CI using GitHub Actions.

> ⚠️ For educational use only — do not run on systems you do not own or control.

---

## ✅ GitHub Actions Status

![Build](https://github.com/FatonHaxhiu/Rootkit-Lab/actions/workflows/ci.yml/badge.svg)
![C](https://img.shields.io/badge/C-ISO%209989%3A1990-blue)
![clang-tidy](https://img.shields.io/badge/clang--tidy-checked-green)
![cppcheck](https://img.shields.io/badge/cppcheck-passed-brightgreen)
![Docker](https://img.shields.io/badge/Docker-20.10-blue)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)


---

## 🛠️ Technologies Used

- **C** — for the LD_PRELOAD-based rootkit
- **Bash** — for the detection scripts
- **Makefile** — to build the shared object
- **GitHub Actions** — for CI (build + syntax check)
- **MIT License** — open source and permissive

---

## 🔐 Features

✅ **File hiding**  
Hides any file or directory whose name includes the keyword `rk_`.

✅ **Process hiding**  
Hides running processes whose command name starts with `rk_` by hooking `readdir()` on `/proc`.

✅ **LD_PRELOAD-based hooking**  
Intercepts libc functions at runtime to perform stealth operations without modifying the kernel.

✅ **Detection script**  
Includes a Bash script that detects use of `LD_PRELOAD` and scans `/proc` for hidden PIDs.

✅ **CI Integration**  
GitHub Actions automatically builds the rootkit and runs checks on every push.

---

## 🧪 How It Works

### Build the Rootkit

```bash
cd rootkit
make
