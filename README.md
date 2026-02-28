Here is a clean **student-focused README** suitable for GitHub.
Goal: easy download → build → run immediately.

You can paste this directly into `README.md`.

---

# Qt C++ Editor & Runner

A lightweight **C++ editor and runner built with Qt**, designed for students who want a simple way to write, compile, and run C++ programs without configuring complex IDE environments.

---

## Goal of the Project

Many beginners struggle with:

* installing full IDEs
* configuring compilers
* running programs that require `cin` input
* understanding terminal execution

This project provides a **minimal ready-to-use environment** where students can:

* write C++ code
* run programs instantly
* provide input easily
* focus on learning programming instead of setup

---

## Features

* Built with Qt (cross-platform GUI)
* Integrated C++ code editor
* One-click compilation using `g++`
* Program output window
* Dedicated input box for `cin`
* Terminal-like execution behavior
* Simple interface for beginners

---

## Intended Users

* Programming students
* C++ beginners
* University labs
* Teaching environments
* Anyone needing a lightweight C++ runner

---

## Requirements

You must have:

### 1. Qt

Install Qt Creator from:

[https://www.qt.io/download](https://www.qt.io/download)

---

### 2. C++ Compiler (g++)

#### Windows

Install **MinGW** (usually included with Qt).

Verify installation:

```bash
g++ --version
```

#### Linux

```bash
sudo apt install build-essential
```

#### macOS

```bash
xcode-select --install
```

---

## How to Build

Clone the repository:

```bash
git clone https://github.com/kevipegoraro/qt-cpp-editor-runner.git
```

Open the project in **Qt Creator**.

Then:

```
Build → Run
```

No additional configuration required if `g++` is available.

---

## How to Use

1. Launch the application
2. Write or modify C++ code in the editor
3. Click **Run**
4. Program output appears below
5. If the program requests input (`cin`):

   * type input in the input box
   * press **Enter**

Example supported:

```cpp
int x;
cin >> x;
cout << x;
```

---

## Educational Purpose

This tool intentionally avoids advanced IDE complexity.

It helps students understand:

* compilation
* execution flow
* standard input/output
* basic C++ program interaction

---

## Project Status

Active educational project.
Improvements and contributions are welcome.

---

## License

MIT License

---

If you want, next improvements typically added are:

* syntax highlighting
* file tabs
* compile error panel
* dark mode
* multi-file support

These are natural next milestones for this project.


---

git init
git add .
git commit -m "init"
git branch -M main
git remote add origin URL
git push -u origin main


------

git add .
git commit -m "support for cin"
git push



---