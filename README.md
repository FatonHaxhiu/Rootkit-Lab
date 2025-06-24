# 🕵️‍♂️ Rootkit Tool

An **educational Linux rootkit project** demonstrating basic userland rootkit techniques using `LD_PRELOAD` to hide files and processes. Includes detection scripts to help understand how rootkits operate and how to spot them.

---

## 🛠️ Technologies Used

- **C** — for the rootkit shared library (`LD_PRELOAD` hooking)
- **Bash** — for the detection scripts
- **GitHub Actions** — for continuous integration (building and testing)

---

## ✅ Continuous Integration Status

This project uses GitHub Actions to automatically build the rootkit and run syntax checks on the detection scripts. The latest workflow runs are **passing**.

![GitHub Workflow Status](https://github.com/FatonHaxhiu/Rootkit-Lab/actions/workflows/ci.yml/badge.svg)

---

## 📚 Project Overview

Rootkits are stealthy malware that hide their presence on a system. This project simulates a simple userland rootkit that intercepts system calls to hide files and processes containing a specific keyword (`rk_`). It also includes a detection script that checks for suspicious environment variables and process anomalies.

This is **for educational purposes only** and should only be run in controlled lab environments.

---

## ⚙️ Features

- **File hiding**: Overrides `readdir()` via `LD_PRELOAD` to hide files/directories with names containing `rk_`
- **Detection script**: Checks if `LD_PRELOAD` is set and detects discrepancies between `/proc` and `ps` to find hidden processes
- Modular and easy-to-understand C and Bash code for learning

---

## 🛠️ Installation & Usage

### Prerequisites

- Linux system (tested on Kali Linux)
- GCC compiler for building shared libraries

### Build the Rootkit

```bash
cd rootkit
make
