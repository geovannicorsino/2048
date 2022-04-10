# 🚀 **2048**

The game 2048 developed in c

### 🚧 **PREREQUISITES** 

 - Clone the project

  
  1. HTTPS
```bash
git clone https://github.com/geovannicorsino/2048.git
```

  2. SSH
```bash
git clone git@github.com:geovannicorsino/2048.git
```

- Access the project and build the container

```bash
docker build -t game2048:latest .
```

 - Start the container

```bash
docker run --name game -v ${PWD}/:/app game2048
```

### 🎲 **HOW TO RUN**

```bash
gcc src/main.c -o main.o -lncurses -ltinfo
```


```bash
./main.o
```

### 🛠️  **TECH STACK**

- [C](https://docs.microsoft.com/en-us/cpp/c-language/?view=msvc-170)
- [NCURSES](https://terminalroot.com.br/ncurses/)