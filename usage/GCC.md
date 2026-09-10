# GCC 常用命令速查

## 1. 基本编译

```bash
gcc <源文件> -o <输出文件>
g++ <源文件> -o <输出文件>
```

```bash
gcc main.c -o main
g++ main.cpp -o main
```

运行：

```bash
./main
```

Windows：

```cmd
main.exe
```

---

## 2. 多文件编译

直接编译：

```bash
g++ main.cpp foo.cpp bar.cpp -o main
```

分步编译：

```bash
g++ -c main.cpp -o main.o
g++ -c foo.cpp -o foo.o
g++ main.o foo.o -o main
```

---

## 3. 指定 C/C++ 标准

```bash
gcc <源文件> -std=c11
g++ <源文件> -std=c++17
```

常用：

```bash
-std=c11
-std=c17
-std=c++11
-std=c++14
-std=c++17
-std=c++20
-std=c++23
```

---

## 4. 警告

```bash
-Wall
-Wextra
-Wpedantic
-Werror
```

常用组合：

```bash
g++ main.cpp -Wall -Wextra -o main
```

严格一些：

```bash
g++ main.cpp -Wall -Wextra -Wpedantic -Werror -o main
```

---

## 5. 调试与优化

调试：

```bash
-g
```

不优化：

```bash
-O0
```

优化：

```bash
-O1
-O2
-O3
```

常用调试：

```bash
g++ main.cpp -g -O0 -o main
```

常用优化：

```bash
g++ main.cpp -O2 -o main
```

---

## 6. 头文件搜索路径

```bash
-I<目录>
```

例如：

```bash
g++ main.cpp -Iinclude -o main
```

多个目录：

```bash
g++ main.cpp -Iinclude -Isrc -o main
```

---

## 7. 库

指定库目录：

```bash
-L<目录>
```

链接库：

```bash
-l<库名>
```

例如：

```bash
g++ main.cpp -L./lib -lmylib -o main
```

对应：

```text
libmylib.a
libmylib.so
```

---

## 8. 宏定义

定义宏：

```bash
-D<宏名>
-D<宏名>=<值>
```

例如：

```bash
g++ main.cpp -DDEBUG
g++ main.cpp -DVERSION=2
```

取消宏：

```bash
-U<宏名>
```

---

## 9. 预处理 / 汇编 / 目标文件

只预处理：

```bash
gcc -E main.c -o main.i
```

生成汇编：

```bash
gcc -S main.c -o main.s
```

只编译，不链接：

```bash
gcc -c main.c -o main.o
```

完整编译：

```bash
gcc main.c -o main
```

对应：

```text
.c
 ↓ -E
.i
 ↓ -S
.s
 ↓
.o
 ↓ 链接
可执行文件
```

---

## 10. 常用选项组合

普通 C++：

```bash
g++ main.cpp -std=c++17 -o main
```

C++ + 警告：

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -o main
```

C++ + 调试：

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -g -o main
```

C++ + 优化：

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -O2 -o main
```

完整一点：

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -g -O0 -o main
```

---

## 11. GCC 信息查询

查看版本：

```bash
gcc --version
g++ --version
```

详细信息：

```bash
gcc -v
g++ -v
```

帮助：

```bash
gcc --help
g++ --help
```

---

## 12. 常用参数速查

| 参数         | 作用               |
|--------------|--------------------|
| `-o`         | 指定输出文件       |
| `-c`         | 编译成 `.o`，不链接 |
| `-E`         | 只预处理           |
| `-S`         | 生成汇编           |
| `-std=`      | 指定语言标准       |
| `-Wall`      | 常用警告           |
| `-Wextra`    | 更多警告           |
| `-Wpedantic` | 严格标准检查       |
| `-Werror`    | 警告视为错误       |
| `-g`         | 生成调试信息       |
| `-O0`        | 不优化             |
| `-O2`        | 常用优化           |
| `-O3`        | 更激进优化         |
| `-I`         | 添加头文件目录     |
| `-L`         | 添加库目录         |
| `-l`         | 链接库             |
| `-D`         | 定义宏             |
| `-U`         | 取消宏             |
| `-pthread`   | 启用线程支持       |
| `-v`         | 显示详细编译信息   |
| `--version`  | 查看版本           |
| `--help`     | 查看帮助           |