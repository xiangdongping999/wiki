# C++ 多文件编程

C++ 的初学者通常将所有的代码编写在一个文件内。但随着学识的增长，我们总会接触到许多多文件的项目。那么，多文件能解决什么问题，又有什么好处？

## 多文件的好处

我们先不考虑 C++ 实现多文件的方法。我们只需考虑，如果把代码分区放在不同的文件中，是否会方便我们对于代码的查找、管理和协同工作？

此外，我们知道，C++ 是一门需要编译的语言。假如代码分别放在不同的区块中，是否可以实现在每次修改时，只更新改动了的部分？

带着这两个问题，我们便可以继续接下来的内容。

## C++ 编译链接简介

我们先从最熟悉的单文件的情况说起。下面是一个简单的 C++ 源文件，里面有一个 `foo` 函数和有一个 `main` 函数。根据经验我们知道，一个 C++ 程序需要有 `main` 函数才能运行。

```cpp
// demo.cpp

int foo(int, int);  // foo 函数的声明

int main() {
    int result = foo(3, 5);
    return 0;
}

int foo(int a, int b) {  // foo 函数的定义
    return 2 * a + b;
}
```

我们观察文件发现，`main` 函数调用了 `foo` 函数。这不是件理所当然的事。事实上，在 **编译** (compile) 过程中，当编译器遇到 `foo(3, 5)` 这样的表达式时，会去查看是否存在这样的函数可供使用，也就是查找在之前是否已经出现了函数的声明。

对于这里的 `foo(3, 5)` 语句来说，编译器就要去查找，是否有一个名为 `foo` 的函数声明，满足参数为两个 `int` 型整数的情况；如果没有，就要去查找之前的函数声明中，是否有参数列表中参数类型支持从 `int` 类型转换而得的 `foo` 函数。

幸运的是，在这条语句之前，我们有一个这样的函数声明，因此编译器能够通过编译；否则，就会报出 **未定义/未声明标识符** (undefined/undeclared identifier) 的错误。

但是，现在还不能生成最终的可执行程序，因为我们还不清楚 `foo` 函数的具体定义。编译器会将这个符号加入到 *未解决符号表* 中。

不过，在这个情况里，编译器接着往下走，就会发现 `foo` 函数的定义，并将其出现的位置记下来。

如此，编译器就从源代码文件生成了目标文件，之后，将进入**链接** (Linking) 阶段。在这个阶段中，编译器根据未解决符号表，去查找是否具有对应的符号，查找到之后，就将为未解决符号记下符号所在的位置。

在上面的例子中，`foo(3, 5)` 这个语句将会找到在 `main` 函数之后定义的 `foo` 函数，因此被解决。如果没有查找到，将会出现 **未解决的外部符号** (unresolved external symbol) 或者 **未定义引用** (undefined reference) 的错误。

> 事实上，我们也可以将函数和声明和函数定义写在一起，比如下面这样。
> 
> ```cpp
> // demo.cpp
> 
> int foo(int, int) { return 2 * a + b; }
> 
> int main() {
>     int result = foo(3, 5);
>     return 0;
> }
> ```

我们将每一个 C/C++ 源文件称作一个翻译单元 (translation unit)。那么在上述的例子中，我们的翻译单元会提供一个 `int foo(int, int)` 和一个 `int main()` 的符号，并且有一个 `int foo(int, int)` 的符号待解决。经过了链接过程，未解决符号得到了解决，于是就可以生成可执行程序了。

## 将文件拆开

假如 `foo` 函数是一个经常会被用到的函数。在单文件的情况时，我们每写一个新的程序，都需要将其复制到新的源代码文件中。但有了之前的基础，我们发现，可以将 `foo` 函数拿出来放进单独的文件中。

> 接下来的例子中涉及到通过命令行操作编译器。读者只需要明白操作的目的即可，实际使用中不必要手动输入这些命令。

下面的 `foo.cpp` 是一个包含 `foo` 函数的源代码文件。

```cpp
// foo.cpp

int foo(int a, int b) {
    return 2 * a + b;
}
```

我们让编译器编译 `foo.cpp` 生成目标文件 `foo.o`。

```console
$ c++ foo.cpp -c -o foo.o
```

不出意外的话，当前目录下会多出一个名为 `foo.o` 的目标文件。目标文件的内容一般不易为人类所阅读，我们只需要知道，这个目标文件提供了 `int foo(int, int)` 这样一个符号。

接着，我们的 `main.cpp` 将会写作下面的样子。

```cpp
// main.cpp

int foo(int, int);  // 只需要 foo 函数的声明

int main() {
    int result = foo(3, 5);
    return 0;
}
```

同样，我们将 `main.cpp` 编译为目标文件。这个目标文件提供了 `int main()` 这样一个符号，但有一个 `int foo(int, int)` 的符号待解决。

之后，我们将两个目标文件链接起来，期望生成最后的可执行程序 `main`。很顺利，没有出现未解决符号，可执行文件生成成功。

```console
$ c++ main.o foo.o -o main
```

## 预处理指令

在编译之前，编译器会先对代码文件进行预处理。有很多预处理指令，比如 `define`、`include`。这些命令通常以 `#` 开始。

一般来说，`define` 命令可以用来将代码中的宏名替换为对应的内容。除此之外，`define` 也可以和 `ifndef`、`ifndef` 命令配合起来实现“条件编译”。

比如，下面的代码中，因为 `define` 过名为 `FLAG` 的宏 (macro)，因此，`ifdef` 命令条件为真，`#ifdef FLAG` 和 `#endif` 之间的代码将会出现在预处理过的代码中；反之，如果没有定义过 `FLAG`，则其中的代码将不会出现在预处理的结果中。

```cpp
#define FLAG

int foo(int, int);

int main() {
#ifdef FLAG
    foo(3, 4);
#endif
    return 0;
}
```

`ifndef` 的作用和 `ifdef` 相反，即，如果没有定义过相应的宏名，才会满足条件。下面的代码中，`#ifndef FLAG` 和 `#endif` 之间的代码不会出现在预处理的结果中。

```cpp
#define FLAG

int foo(int, int);

int main() {
#ifndef FLAG
    foo(3, 4);
#endif
    return 0;
}
```

而`include` 命令即为将相应的文件内容复制到当前文件里。没错，就是按照原样复制进来。

## 头文件

在上一节的例子中，我们在 `main.cpp` 中手动写入了 `int foo(int, int);` 的声明。但当声明较多时，手动编写或复制仍是比较麻烦的。因此，我们一般要为自己的 `foo.cpp` 编写相应的头文件 (headers) `foo.h`。这样，我们只需在 `main.cpp` 中 `include` 头文件 `foo.h` 即可。

现在，目录下有这样三个文件：

- [foo.h][foo-h]
- [foo.cpp][foo-cpp]
- [main.cpp][main-cpp]

```cpp
// foo.h

{{#include assets/1/foo.h}}
```

注意，[foo.h][foo-h] 中使用 `ifndef` 等命令实现了该文件在每个翻译单元中仅会被包含一次。这叫做头文件保护 (header guards)。如果用户在一个源文件中不小心引用了两次头文件，或是包含的若干个头文件中都包含了某个头文件，那么将会出现同一个头文件在一个源文件中被引用多次的情况，即造成了重复声明。

此外，头文件中一般不能包含函数定义。试想，如果包含了函数定义的头文件被多个源代码文件包含，则这些源代码文件编译生成的目标文件中都会出现相同的符号。这会导致链接过程中链接器无法决定该使用哪一个符号。同理，也不应该使用 `include` 将函数定义的代码直接包含进源代码文件。

不过，实际使用中也会出现需要将一些常用的函数放在头文件中的情况，亦即我们在会在很多源文件中用到这一函数。我们希望这些相同的函数在链接时不会相互冲突，因此，我们需要使用 `inline` 关键字修饰它。

另一种情况是，我们希望一个函数仅在当前翻译单元可用，而在不同的翻译单元中可能同名但定义不同的函数。这时我们应用 `static` 关键字修饰它们。

```cpp
// foo.cpp

{{#include assets/1/foo.cpp}}
```

在 [foo.cpp][foo-cpp] 中，同样引用了相对应的头文件，这是由于，头文件中可能包含了一些结构或类型的声明，或者包含其他的一些头文件。这时候，需要引用该头文件，否则编译时将会出现未声明符号的问题。

```cpp
// main.cpp

{{#include assets/1/main.cpp}}
```

最后，[main.cpp][main-cpp] 中只需要调用 [foo.h][foo-h] 中提供的符号即可。

[foo-h]: ./assets/1/foo.h
[foo-cpp]: ./assets/1/foo.cpp
[main-cpp]: ./assets/1/main.cpp

在编译的时候，分别生成目标文件：

```console
$ c++ foo.cpp -c -o foo.o
$ c++ main.cpp -c -o main.o
```

再执行链接操作：

```console
$ c++ main.o foo.o -o main
```

参考资料：

- https://en.cppreference.com/w/c/language/storage_duration
- https://en.cppreference.com/w/cpp/language/storage_duration

## 头文件搜索路径

当使用双引号 `""` 包含头文件时，编译器首先查找当前工作目录或源代码目录，然后再在标准位置查找。而使用尖括号 `<>` 时，编译器将在系统的头文件目录中查找。

## 构建工具

上述生成可执行文件 `main` 的过程，就叫做**构建** (build)。在这个过程中，我们的 *目标* 是生成可执行程序 `main`，而这个目标需要 `main.cpp`、`foo.h` 以及 `foo.cpp` 三个文件；其中，`main.cpp` 和 `foo.cpp` 又依赖于 `foo.h` 文件。

更具体地来说，生成可执行程序 `main` *依赖* `main.o` 和 `foo.o` 两个目标文件，而这两个目标文件，又分别由对应的 `cpp` 文件生成。假如目标文件对应的 `cpp` 文件发生了更改（又或者其所包含的头文件发生了更改），都需要重新生成相应的目标文件，才能保证最终链接之后生成的可执行程序是最新的。

不同于曾经的单文件，现在我们要构建一个目标需要多个文件。有两个问题需要解决：

- 每次都需要输入多条命令才能完成编译、链接，而不是一条；
- 我们希望减少编译的次数，因此需要记录哪些文件发生了更改，只对有必要重新编译的文件编译。

如果项目更多、项目之间有依赖关系，则需要输入更多、更复杂的命令，也需要留意更多的文件。如果全由用户来做，很容易出现差错。

构建工具可以帮助我们自动化上述的流程。我们告诉构建工具生成目标需要哪些依赖，构建工具就可以在每次我们需要重新构建目标时，检测需要重新生成的文件，并完成构建流程。

一些 IDE 会有自己的构建工具，但通常把这个过程对用户隐去了。用户将源代码添加进一个“项目”中，IDE 便将其视作生成该项目的依赖。

## CMake

使用 CMake 这样一个构建管理工具，只需编写一个 `CMakeLists.txt` 文件，便可以生成用于不同构建工具的脚本。

## 具体演示

可以在 [gitlab.com/klixr/cpp-multi-file-demo](https://gitlab.com/klixr/cpp-multi-file-demo/) 查看一个具体的示例。

也可通过下边的链接访问上述示例的副本。

假设我们现在有这样一个 C++ 文件 [single_file_demo.cpp](assets/2/single_file_demo.cpp)，示例将其拆分成了多文件的形式。

`Date` 库：

[Date/Date.hpp](assets/2/Date/Date.hpp)

```cpp
{{#include assets/2/Date/Date.hpp}}
```

[Date/Date.cpp](assets/2/Date/Date.cpp)

```cpp
{{#include assets/2/Date/Date.cpp}}
```

[Date/CMakeLists.txt](assets/2/Date/CMakeLists.txt)

```cmake
{{#include assets/2/Date/CMakeLists.txt}}
```

使用 `Date` 库：

[demo.cpp](assets/2/demo.cpp)

```cpp
{{#include assets/2/demo.cpp}}
```

[CMakeLists.txt](assets/2/CMakeLists.txt)

```cmake
{{#include assets/2/CMakeLists.txt}}
```
