# 🚀 **2048**

The game 2048 developed in c

### 🚧 **PREREQUISITES** 

Before starting, you will need to have the following tools installed on your machine:
[Git](https://git-scm.com), [Docker](https://docs.docker.com/desktop/windows/install/). 
I recommend using the [VSCode](https://code.visualstudio.com/)

### 🎲 **HOW TO RUN**

* Clone the project

   *  HTTPS
  ```bash
  git clone https://github.com/geovannicorsino/2048.git
  ```
   * SSH
   ```bash
   git clone git@github.com:geovannicorsino/2048.git
   ```

<br/>

* Docker steps

   * Build
   ```bash
   docker build -t game2048:latest .
   ```

   * Run
   ```bash
   docker run --name game -v ${PWD}/:/app game2048
   ```
   
<br/>

* Run code

    * Create the compiled file
    ```bash
    gcc src/main.c -o main.o -lncurses -ltinfo
    ```

    * Run the compiled file
    ```bash
    ./main.o
    ```

<br/>

### 🛠️  **TECH STACK**

- [C](https://docs.microsoft.com/en-us/cpp/c-language/?view=msvc-170)
- [NCURSES](https://terminalroot.com.br/ncurses/)
