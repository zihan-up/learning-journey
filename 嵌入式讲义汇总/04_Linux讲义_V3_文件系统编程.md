# Linux讲义汇总（卷三 文件系统编程）

> 由 `Linux部分/卷三 文件系统编程/` 目录下 7 份 PDF 提取汇总生成。所有插图统一保存在 `Linux_assets/` 目录，请保持本文件与该文件夹的相对位置不变。

## 目录

- 01 HelloWorld
- 02 目录流
- 03 无缓冲文件流
- 04 文件映射
- 05 重定向
- 06 有名管道
- 07 IO多路复用

---

## 01 HelloWorld

### 1. 概述

到此为止，我们已经：

1. 学完了Linux基础，已经基本会使用常见的shell指令，对Vim编辑器的使用也已基本入门；
2. 紧接着我们也学习了GNU工具集，熟悉了编译工具链，学会了如何使用GDB来调试程序，了解了库文件，懂得了C程序的工程管理工具Makefile；
3. 现在我们将正式进入 Linux 系统编程的阶段，开始 Linux 环境下的 C 语言编程之旅。

就像我们第一次在图形界面上编写 “Hello World” C 程序一样，我也将本节命名为“HelloWorld”，象征着我们在 Linux 上进行 C 程序开发的新征程，新的开始。

在本节中，将要给大家讲解如何进行环境的配置，一些常见的代码规范，以及如何高效地利用工具在 Linux 环境下进行 C 程序的开发。

### 2. 创建公共头文件

在后续的课程中：

1. 我们会学习很多库函数，系统调用库函数，这样就需要包含很多不同的标准库头文件；
2. 其次，我们可能需要定义很多宏，类型，别名等，这些内容如果每次编码都重复进行定义，那就太折磨了。

于是我们自然而然就想到了一个解决思路：

**利用一个公共头文件，将以上内容装进这个公共头文件，于是每次写代码就只需要包含这个公共头文件就可以了。**

那么具体怎么做呢？

Linux系统存放系统头文件的目录是/usr/include ，我们可以使用sudo权限在该目录下新建一个头文件，比如叫：

my_header.h然后不要忘记给此文件的其它用户加上**写权限**，这样后续就不用sudo权限就可以直接进行修改了。后续我们就可以把所有的头文件包含，宏定义等内容放到这个公共头文件中了。

在一开始，我们建议这个头文件的内容如下：

```c
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#endif
```

最后一个问题：现在如何包含这个公共头文件呢？

很简单：

```c
#include <my_header.h>
```

思考一下：为什么可以用<> ，而不是"" 呢？

因为这个自定义头文件已经被我们放入系统头文件目录当中去了，所以可以使用<> 进行头文件包含了。

注：

**在系统库文件目录下新建头文件，不是一个标准推荐的做法，这里这么做是为了让大家在学习的过程中更方便，不用去管理琐碎的头文件以及一些常用代码片段。**

**等实际到了公司，还是要参考公司标准规范的做法，不要乱搞。**

### 3. 设置.c文件模板

如果安装了Vim-plus插件，那么它默认使用文件：

~/.vim/plugged/prepare-code/snippet/snippet.c 作为vim*.c 新建.c文件的模板。

于是我们就可以通过修改这个snippet.c 文件的内容，改变默认生成的.c文件的内容，这个操作就非常类似于我们在VS中配置代码模板的操作是一样的。

当下的话，我们建议大家先把模板配置成：

```c
#include <my_header.h>

/* Usage: */
int main(int argc, char *argv[]){
    printf("Hello world\n");
    return 0;
}
```

**注意，要将模板中的头文件包含设置为包含自定义的公共头文件。**

注意，如果你直接复制路径找不到这个目录，可以使用指令：

```c
find ~ -name snippet.c
```

在家目录下去寻找snippet.c 文件，然后修改模板文件，若还找不到可直接询问老师。

这个文件模板，你可以随着我们的课程进度的推进，自己自由的进行修改，不用拘泥于老师给定的模板。

### 4. Makefile

利用公共头文件，我们基本上不需要在当前目录下创建头文件了，在学习阶段时，我们完全可以用一个或几个.c文件完成所有任务。

所以我们可以创建一个Makefile如下：

```c
SRCS := $(wildcard *.c)
OUTS := $(patsubst %.c,%,$(SRCS))
CC := gcc
COM_OP := -Wall -g
.PHONY: clean rebuild all

all: $(OUTS)
% : %.c
    $(CC) $^ -o $@ $(COM_OP)

clean:
    $(RM) $(OUTS)

rebuild: clean all
```

这个Makefile会根据当前工作目录下的每一个.c 文件，都生成一个对应的可执行程序。

把它放在一个固定的目录下，每次创建新目录写代码需要Makefile构建工具时，就把它拷贝过去，非常好用！

比如：

我会在~/tools 目录下创建一个Makefile 文件，然后把上述代码拷贝过去。每次需要Makefile时，就使用以下指令复制到当前目录下：

```c
cp ~/tools/Makefile . #.代表当前目录
```

你也去试试吧，非常好用。

**当然，这个Makefile脚本会将当前目录下的每一个.c文件都生成对应的可执行程序，如果你需要多个.c文件生成一个可执行程序，该Makefile是实现不了的。**

### 5. 命令行参数

命令行参数的语法在C阶段时，我们就已经在《字符串》章节中学习过了，这里我们再复习一下。

所谓命令行参数，可以这样理解：

**当你在命令行中启动一个C程序时，你在指令输入窗口输入的文本（即命令行参数）就由操作系统接收。操作系统再将这些参数解析为一个字符串数组，并在启动程序时传递给这个C程序。**

所以命令行参数的传递过程，实际上是下面的流程：

1. 用户在命令行中启动C程序，传递给操作系统一个命令行参数字符串
2. 然后由操作系统解析这个字符串，解析成一个字符串数组
3. 最后操作系统启动C程序时，将字符串数组传递给这个C程序

标准C语言规定：

1. C程序可以不接收操作系统传递的命令行参数字符串数组，此时可以把mian函数声明为：

1int main(void);

2. C程序若希望接收命令行参数字符串数组，则需要把main函数声明为：

1int main(int argc,char *argv[]);

这里有几个问题：

1. 用户在命令行中启动程序，以什么格式给操作系统传递参数字符串呢？
2. 操作系统如何解析参数字符串，生成一个字符串数组呢？

**第一个问题的答案是：**

以Linux的命令行为例，假如要启动一个可执行程序main ，并希望额外传递两个参数test 和test2那你就可以这样启动这个C程序：./maintesttest2**第二个问题的答案是：**

操作系统接收到用户输入的命令行参数字符串后，会以空格为间隔，来分割每一个命令行参数，将用户输入的命令行字符串解析成一个字符串数组。

比如接收的命令行参数字符串是：./maintesttest2最终就会解析成字符数组：["./main", "test", "test2"]这个字符串数组就会被传递给main函数的形参argv字符串数组，当然操作系统还会传递该数组的长度，长度被main函数形参argc接收。

举例说明，对于下列代码：

```c
#include <stdio.h>

int main(int argc, char *argv[]){
    printf("argc = %d\n", argc);
    for(int i = 0; i < argc; i++){
       printf("第%d个命令行参数是:%s\n", (i + 1), argv[i]);
    }
    return 0;
}
```

在当前目录启动这个C程序，指令是：./main100200test ，那么程序的输出是：

argc = 4第1个命令行参数是:./main第2个命令行参数是:100第3个命令行参数是:200第4个命令行参数是:test**注意：命令行参数的第一个永远是可执行程序的路径名，从第二个参数开始才是可以自由给定的。**

### 6. HelloWorld

以上，万事俱备，我们就可以正式的开始编写我们的第一个Linux环境下的C程序了。

我们就以C阶段最后学习的文件流为载体，利用C语言的标准库函数，完成一个带有命令行参数的文件复制功能。

其函数声明如下：

```c
void copy_file(const char *src, const char *dest);
```

库函数是具有跨平台性的，所以这段代码的写法和以往没有什么区别，如下所示：

```c
#include <my_header.h> // 只需要包含公共头文件就可以了

// 将src文件复制到目标dest,若dest存在则直接覆盖
void copy_file(const char *src, const char *dest) {
    FILE *src_fp = fopen(src, "rb"); // b在Linux平台下加不加都无所谓
    if (src_fp == NULL) {
       // 将参数拼到当前errno的错误信息上
       perror("fopen src");
       exit(1);
    }

    FILE *dest_fp = fopen(dest, "wb");
    if (dest_fp == NULL) {
       perror("fopen dest");
       fclose(src_fp); // 关闭已打开的源文件
       exit(1);
    }

    // 用于临时存储数据的中转站
    char buf[1024] = { 0 };
    size_t count;

    // 从源文件读取数据并写入目标文件
    while ((count = fread(buf, 1, sizeof(buf), src_fp)) > 0) {
       fwrite(buf, 1, count, dest_fp);
    }

    // 关闭文件流
    fclose(src_fp);
    fclose(dest_fp);
}

int main(int argc, char *argv[]) {
    // ./00_copy_file src dest
    if (argc != 3) {
       fprintf(stderr, "args error!\n");
       exit(1);
    }
    copy_file(argv[1], argv[2]);
    return 0;
}
```

这段代码仍然可以做一些优化，比如：

1. 在带命令行参数的main函数中，判断参数个数是否正确是必须要做的
2. fopen 这类函数需要通过返回值来判定函数是否正确执行，需要对返回值做校验处理

我们可以把这部分代码提取出一段宏函数，然后加到公共头文件中，这样以后代码再有此类操作就可以很方便了。

于是我们的公共头文件变成了：

```c
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 检查命令行参数数量是否符合预期
#define ARGS_CHECK(argc, expected) \
    do { \
       if ((argc) != (expected)) { \
           fprintf(stderr, "args num error!\n"); \
           exit(1); \
       } \
    } while (0)

// 检查返回值是否是错误标记,若是则打印msg和错误信息
#define ERROR_CHECK(ret, error_flag, msg) \
    do { \
       if ((ret) == (error_flag)) { \
           perror(msg); \
           exit(1); \
       } \
    } while (0)

#endif
```

然后，我们就可以将这个C程序的实现改为：

```c
#include <my_header.h>

// 将src文件复制到目标dest,若dest存在则直接覆盖
void copy_file(const char *src, const char *dest) {
    // ./01_copy_file src dest
    FILE *src_fp = fopen(src, "rb");
    // 对返回值进行错误处理
    ERROR_CHECK(src_fp, NULL, "fopen src");

    FILE *dest_fp = fopen(dest, "wb");
    if (dest_fp == NULL) {
       perror("fopen dest");
       fclose(src_fp); // 关闭已打开的源文件
       exit(1);
    }

    // 用于临时存储数据的中转站
    char buf[1024] = { 0 };
    size_t count;

    // 从源文件读取数据并写入目标文件
    while ((count = fread(buf, 1, sizeof(buf), src_fp)) > 0) {
       fwrite(buf, 1, count, dest_fp);
    }

    // 关闭文件流
    fclose(src_fp);
    fclose(dest_fp);
}

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 3);
    copy_file(argv[1], argv[2]);
    return 0;
}
```

以上。

也就是说：在后续写代码过程中，如果有对命令行参数进行校验、对返回值进行校验的需求，就都可以直接复用这个宏。

最后思考一个问题：为什么宏定义中要使用一个do...while 结构呢？

### 7. 扩展：宏函数中do...while结构的作用

在 C 语言中，宏本质上是预处理阶段的文本替换，不是普通函数调用。

如果一个宏内部包含多条语句，或者宏内部本身带有if语句，那么直接展开后，可能会破坏外层代码的语法结构。

尤其是在if...else语句中使用时，容易出现“悬空 else”问题。

例如，假设我们定义了如下宏：

```c
#define ARGS_CHECK(argc, expected) \
    if ((argc) != (expected)) { \
       printf("args error!\n"); \
       return -1; \
    }
```

然后在代码中这样使用：

```c
if (1)
    ARGS_CHECK(argc, 3);
else
    printf("hello world!\n");
```

从表面上看，我们可能以为它等价于：

```c
if (1) {
    ARGS_CHECK(argc, 3);
}
else {
    printf("hello world!\n");
}
```

但实际上，宏会在预处理阶段被直接展开，展开后的代码大致如下：

```c
if (1)
    if ((argc) != (3)) {
       printf("args error!\n");
       return -1;
    };
else
    printf("hello world!\n");
```

可以看到，ARGS_CHECK(argc,3);后面的分号也被保留下来了。

这会导致else前面多出一个独立的空语句，从而破坏原本的if...else结构，最终可能导致编译失败，出现类似：

```c
else without a previous if
```

或者在某些宏写法中，else绑定到错误的if上，导致程序逻辑和预期不一致。

为了解决这个问题，通常会把多语句宏写成do{}while(0)的形式：

```c
#define ARGS_CHECK(argc, expected) \
    do { \
       if ((argc) != (expected)) { \
           printf("args error!\n"); \
           return -1; \
       } \
    } while (0)
```

此时同样这样使用：

```c
if (1)
    ARGS_CHECK(argc, 3);
else
    printf("hello world!\n");
```

宏展开后大致变成：

```c
if (1)
    do {
       if ((argc) != (3)) {
           printf("args error!\n");
           return -1;
       }
    } while (0);
else
    printf("hello world!\n");
```

此时do{}while(0);在语法上是一个完整的单条语句，所以它可以安全地放在if后面使用，不会破坏外层的if...else结构。

需要注意的是，while(0)并不是为了真正循环。

这个结构只会执行一次，执行完do代码块后，由于条件恒为0 ，循环立即结束。编译器通常也会把这类结构优化掉，所以一般不会带来额外运行开销。

当然，这种问题也可以通过规范代码风格来避免，比如始终给if...else加上大括号：

```c
if (1) {
    ARGS_CHECK(argc, 3);
}
else {
    printf("hello world!\n");
}
```

这样即使宏没有使用do{}while(0) ，也不容易破坏语法结构。

但是宏通常是给别人调用的，宏的定义者无法保证使用者一定会写大括号。

因此，在定义多语句宏时，使用do{}while(0)是一种更稳妥、更安全的写法。

总结来说：

```c
do {
    ...
} while (0)
```

在宏定义中的主要作用是：

1. 把多条语句包装成语法上的“一条语句”；
2. 避免在if...else等结构中使用宏时出现悬空else问题；
3. 提高宏的安全性和健壮性；
4. 让宏的使用方式更接近普通函数调用。

**因此，凡是宏内部包含多条语句，或者宏内部存在 if、return、变量定义等复杂逻辑时，通常都建议使用 do { } while (0) 结构进行包裹。**

---

## 02 目录流

### 1. 系统编程简介

我们仍然回到Linux课程的开端，在那里我们详细讲解了Linux系统的结构设计，如下图所示：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img001.png)

*图1-1Linux内核结构-图*

我们已经学习了利用shell命令来和内核进行交互，在C阶段我们也学习了大量的标准库函数，也可以实现与内核的交互。

那么从这节课开始，我们就学习一种直接与内核交互的方式——Linux系统调用。

稍微要注意的是：

1. 标准库函数遵循**C标准规范（ISO-C）**，任何使用标准C语言的平台都遵循这一规范，虽然不同编译器和平台的实现细节可能有所不同，但整体上是能够保证跨平台性的。
2. Linux的系统调用一般遵循POSIX规范，这意味着Linux系统调用最多在类Unix平台上实现跨平台性(实际上还是有些兼容性问题)。
3. 总之基本可以认为Linux系统调用就只能在Linux内核上使用。关于这个问题，我们下面还会进一步详细讲解。

#### 1.1 从文件系统编程开始

Linux系统编程主要可以分成三大部分：文件系统编程，进程和线程管理以及网络系统编程。

我们在学习的时候，学习的顺序也是这样的，那么为什么要这么学习呢？

1. 类Unix系统的设计哲学中，"一切皆文件" 是一个核心概念。
   - a. Linux系统下，把一切外部设备、进程线程资源以及网络通信等都视为文件，都可以使用类似文件操作的方式来进行访问和管理。
   - b. 先学习文件系统编程有利于后续的学习，可以作为后续系统编程学习的基础。
2. 文件系统编程直接操作各自文件，最简单且最直观。
3. 实用性强，文件系统编程的操作，如文件的创建、读写、权限修改等，是系统编程中最常见的操作。

总之，我们就从现在开始来学习Linux文件系统编程。

#### 1.2 如何学习呢？

很多人可能听到系统编程四个字，就下意识的觉得会很难，实际上这是一个错误的认知。

虽然学习系统的调用的过程，会有很多模型、概念需要理解记忆，但最核心，展现在代码上的还是——函数，C语言的系统调用函数。

Linux的系统调用虽然是在内核中实现的，但还是会通过C语言风格的函数，将接口暴露给用户空间的程序去使用。

所以在学习系统调用的过程中，我们会涉及大量的C语言系统调用函数，那么应该如何学习这么多的系统调用函数呢？

答：记住系统调用的函数名，大致记住功能，在忘记的时候查询man 手册寻找自己想要的答案。

系统调用的C语言函数，都放置在man手册的2号手册中，我们可以通过指令查询函数的使用方式，比如：

```c
man 2 chmod
```

如何通过man手册查看一个系统调用函数如何使用呢？遵循以下步骤：

第一步：学习系统调用函数以及标准库函数，总是需要先**记住函数的名字**，否则就无法打开man手册了第二步：使用指令打开man手册，在很多时候这需要你指定man手册的卷数。**系统调用函数在第2卷，库函数在第3卷。**

第三步：当你打开一个函数的man手册时，内容查看的顺序是：

1. 先看NAME，NAME块描述了函数的基本信息，描述了函数的基本作用。
2. 再看概述**(SYNOPSIS)**信息：
   - a. 先看头文件，要知道使用此函数要包含什么头文件
   - b. 接下来看函数的声明

怎么看函数的声明呢？

应该先看函数的名字，这是基本的然后看函数的返回值：

因为C语言缺乏错误的检查机制，所以函数执行出错都需要依赖返回值来确定，返回值是什么决定了函数应该如何进行错误处理，这是非常重要的。比如：

1. 返回值类型若是int或者ssize_t(跨平台的有符号整数) ，普遍来说如果此函数返回-1，就表示发生了错误。**（尤其返回值是ssize_t时）**
2. 返回值类型若是一个指针类型，普遍上如果此函数返回NULL，就表示发生了错误。

在一众返回值中，我们尤其要特别注意指针类型的返回值：

1. 返回值是指针类型，绝不可能返回此函数栈区的数据，因为这样的指针是一个悬空指针，不可能作为返回值。
2. **返回值是指针类型代表申请了栈区外的额外内存空间或者资源，这往往意味着需要手动管理/关闭这些额外的内存空间或资源(但也不是必然)。**

看完函数的返回值，可以紧跟着看函数的形参列表，在一众形参列表中我们也需要特别重视指针类型的形参，尤其关注它们有没有被const 修饰：

1. 被const 修饰的指针类型参数，意味着指针指向的内容，绝不会在函数体内部被修改。我们把这种指针类型参数称之为"传入参数"，单纯的传入，不会修改指向内容。
2. 没有被const 修饰的指针类型参数，一般就意味着函数要通过传入的指针修改指向的内容，并且往往会在修改内容后再将原指针作为返回值返回，这种指针类型参数称之为"传入传出参数"。**传入传出参数在传参时要特别小心空指针、野指针问题！！**

这里举一个例子：

```c
int chmod(const char *pathname, mode_t mode); // 传入参数pathname
char *getcwd(char *buf, size_t size); // 传入传出参数buf
```

比如我们这样调用getcwd函数：

```c
char *p;
getcwd(p, 128);
```

这样的调用显然会导致未定义行为：

1. p是一个野指针，指向随机内存位置。若这个随机位置是不可访问区域，将导致程序报错崩溃，这其实是一件好事。
2. 如果随机指向了一个可以访问修改的位置，发生了错误的数据修改，甚至程序还能短暂正常运行，那就太糟糕了。**(这在C语言中其实稀松平常，所以C语言很坑)**

C语言是一种非常不安全的语言，要想避免这种错误就需要程序自己的细心细致了，要确保指针指向的区域是已分配的。比如：

```c
char p[100]; // 栈上分配数组
char *p = malloc(100); // 堆上分配空间
```

总之，要想写好C语言代码，成为优秀的C语言开发，需要注意的事情非常多，要仔细一些。

### 2. 目录相关系统调用

在C语言阶段，我们已经学习过文件处理相关的库函数了，现在我们就把目录处理相关的操作补上。**注意：此小节我们将主要学习目录相关的系统调用，目录相关的库函数将在下一小节学习。**

###### 关于C语言的系统调用函数、标准库函数以及POSIX库函数的关系

操作系统内核为了实现对外开放系统功能，会主动对外暴露系统调用接口，这对于任何操作系统内核来说都是一样的。

而类Unix操作系统的设计与实现都深植根于 C 语言(C语言诞生的初衷就是为了写Unix系统)，**类 Unix 系统的系统调用都是以C语言风格暴露的，而且这些系统调用函数一般都遵循POSIX标准。**

实际上，C语言由于其接近硬件的特性和高效率，在操作系统开发中被广泛使用，包括Windows和MacOS在内的系统内核在对外暴露系统功能时都会选择C语言风格。

总之：

1. C语言的系统调用函数显然是不具有跨平台性，它植根于特定的系统内核，不同的系统内核会有不同的暴露方式
2. C语言的系统调用函数也不是C语言标准的一部分，不属于标准库函数。
3. 理论上来说，所有的类Unix系统都遵循POSIX标准，那么它们的系统调用函数应该是一致的。但实际上不同的类Unix系统内核，在系统调用上还是会有一些细微的差异。
4. **一般来说，我们基于Linux内核学习系统调用，就意味着开发出来的系统调用代码仅能运行于Linux平台上。**

但：

C语言的标准库函数显然不是这样的，标准库函数意味着遵循特定C语言规范(ISO-C)。由于标准库函数很多是对系统调用的封装，这使得标准库函数在不同平台上的实现方式是不同的，也就是实现的细节不同。

但从程序员的角度看，它们提供了一致的接口和行为。

所以：

1. 标准库函数具有较好跨平台性，基本保证在任何遵循标准C语言规范的平台上，它们的调用方式和行为是一致的。
2. 标准库函数可以在任何支持 C 标准的编译器和环境中使用，不受底层操作系统的限制。

**那么最后，什么是POSIX库函数呢？**

标准库函数指的是符合ISO-C官方C语言标准的库函数，这意味着它们在使用标准C语言的任意平台下使用起来都是一样的，具有最好的跨平台性。Windows、Linux、mac等平台下基本都是一样，使用起来没什么差异。

但POSIX库函数，指的是符合POSIX标准的C语言库函数。

POSIX标准一般所有的类Unix系统都遵守，所以你可以认为POSIX标准的库函数可以在类Unix系统平台中实现跨平台性。但非类Unix系统，比如Windows，那一般就不能直接移植代码了。

**但POSIX和ISO-C库函数仍然具有相同点：同为库函数，它们都不是系统调用，但都有可能利用系统调用来实现功能。**

#### 2.1 改变文件的权限

**注意，从这里开始每学习一个新的函数，你都需要将此函数的头文件包含(此前没有写过的)加到公共头文件中！**

在以往我们已经学过了shell指令当中，用于改变文件权限的一个shell指令：chmod在C语言代码也是一样的，也可以使用同名函数chmod来改变文件的权限。需要注意的是：在Linux环境下，chmod 既是一个系统调用的函数名，也是一个POSIX库函数名。

当我们在C语言代码中调用chmod 函数时，调用的是库函数chmod，当然此库函数的底层实现依赖于系统调用函数chmod。

所以chmod这个字符序列，在man手册的1、2、3号三个手册中都存在。

它的函数声明如下：

```c
#include <sys/stat.h> // 使用该函数需要包含的头文件
int chmod(const char *pathname, mode_t mode);
```

**形式参数：**

1. pathname ：文件或目录的路径字符串。
2. mode ：要设置的新权限，这里要使用权限数字表示法，即八进制数**（C语言中八进制整数需要以"0"开头）**。

**返回值：**

1. 成功时，chmod返回 0。
2. 失败时，返回 -1，并设置 errno 以指示错误原因。

一个使用示例：

```c
/* Useage: ./01_chmod pathname mode */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    mode_t mode;
    sscanf(argv[2], "%o", &mode ); // %o表示八进制无符号数

    int ret = chmod(argv[1], mode);
    ERROR_CHECK(ret, -1, "chmod");
    return 0;
}
```

**需要注意的是：设置权限时需要传参权限的"数字表示法"，而且设定的权限就是文件的最终权限，掩码只会影响新建文件，不会影响chmod函数。**

#### 2.2 扩展：如何查看类型别名的具体定义

在上面的chmod函数中，我们看到了一个类型别名：mode_t ，那么如何确定这个类型别名的具体类型呢？

有以下两种办法：

**查阅预处理后的.i文件：**

类型别名的具体定义肯定是包含在头文件里的，如果直接查看头文件中此别名的定义，可能会受到条件编译等预处理指令的干扰，所以最好的办法是查看预处理文件。

第一步可以随意创建一个.c源文件，只要确保包含目标类型别名的头文件即可，比如要查看类型别名mode_t ，就需要确保包含：

```c
#include <sys/stat.h>
```

然后直接利用指令：

```c
gcc -E main.c -o main.i
```

生成对应的预处理.i文件。

然后可以选择使用vim编辑器进入这个.i文件，然后使用vim编辑器查询即可，比如我们查到mode_t 类型别名的定义如下：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img002.png)

*图2.2-1查看类型别名的具体定义-图1*

或者也可以使用grep 指令搜索这个.i文件，指令如下：

```c
grep -nE "typedef.*mode_t" main.i
```

![](Linux_assets/卷三%20文件系统编程/02_目录流/img003.png)

*图2.2-2查看类型别名的具体定义-图2*

**于是我们就知道，在当前机器下，mode_t类型别名实际上就是无符号的int类型。**

**第二种方式，通过代码计算推导：**

对于类型别名而言，大多数情况下，别名的具体类型都是有符号整数或无符号整数，我们可以通过下列代码来确定它们的长度以及有无符号：

```c
int main(void){
    size_t size = sizeof(mode_t);
    printf("size of mode_t = %zu bytes\n", size); // %zu是专门提供给size_t类型进行格式化的转换说明

    if((mode_t)-1 > 0){
       // 无符号数的-1会溢出成为一个正数
       printf("mode_t是无符号的!\n");
    }else{
       // 有符号数的-1就是一个负数
       printf("mode_t是有符号的!\n");
    }
    return 0;
}
```

以上

#### 2.3 获取当前工作目录

getcwd 函数即"get current working directory"，它是一个**POSIX标准**的C语言库函数，用于获取当前工作目录的绝对路径名称。

这个库函数的作用，很类似于pwd这个shell指令。

其声明如下：

```c
#include <unistd.h> // 需要包含此头文件调用函数
char *getcwd(char *buf, size_t size);
```

**形式参数：**

1. buf: 指向存放当前工作目录字符串的字符数组
2. size: 这个数组的大小

返回值：

1. 成功时，getcwd返回一个指向buf的指针，buf中包含了当前工作目录的绝对路径。
2. 失败时，返回NULL ，并设置errno以指示错误的原因。**出错的原因普遍是buf数组过小，无法容纳整个工作目录绝对路径字符串。**

**一个演示示例如下：**

```c
/* Usage: ./02_getcwd */
int main(void){
    // 方式1：直接用栈数组作为getcwd返回值数组
    char path[1024] = {0};
    char *p = getcwd(path,sizeof(path));
    ERROR_CHECK(p,NULL,"getcwd");
    printf("cwd = %s\n", path);

    // 方式2：动态分配一个堆数组
    // char *path = (char *)malloc(1024);
    // char *p = getcwd(path,1024);
    // free(path);
}
```

注意：

1. getcwd**不负责管理传入函数的buf空间的生命周期，buf生命周期的管理是程序员的职责。**
2. 分配空间不要过于抠门，内存空间在当前的开发环境下一般不是稀缺资源。如果分配空间较少，那么会导致报错。

getcwd函数还有一种调用方式，如下：

```c
int main(void) {
    char* cwd = getcwd(NULL, 0);
    ERROR_CHECK(cwd, NULL, "getcwd");

    puts(cwd);
    // 由调用者负责释放申请的内存空间
    free(cwd);
    return 0;
}
```

注意：

1. 这种调用方式意味着，由getcwd函数来动态分配堆空间，存储当前工作目录字符串，然后返回。
2. 在这种情况下，getcwp仍然不负责管理它申请的空间，所以需要你自己手动free释放，否则会导致内存泄漏。

#### 2.4 改变当前工作目录

chdir 函数是一个**Linux系统调用函数**，它的作用是改变当前工作目录。"chdir" 代表"change directory"，即改变(当前工作)目录。

该函数的声明如下：

```c
#include <unistd.h>
int chdir(const char *path);
```

**形式参数：**

1. path : 是一个指向字符数组的指针，这个数组包含了新工作目录的路径。
2. 路径可以是绝对的（从根目录开始，例如 "/usr/local/bin"）或相对的（相对于当前工作目录，例如 "../docs"）。

**返回值：**

1. 成功时，chdir返回 0。
2. 失败时，返回 -1，并设置全局变量errno以指示错误的原因。比较常见的错误，比如目标目录不存在、权限问题、目标不是目录等。

**一个使用的示例如下：**

```c
/* Usage: ./03_chdir pathname */
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2); // 命令行参数必须2个，第二个是要切换的目标目录

    // 先获取当前工作目录，然后打印
    char buf[1024] = {0};
    char *ret = getcwd(buf, sizeof(buf));
    ERROR_CHECK(ret, NULL, "getcwd");
    printf("一开始的工作目录是: ");
    puts(buf);

    // 改变当前工作目录
    int ret2 = chdir(argv[1]);
    ERROR_CHECK(ret2, -1, "chdir");

    // 再次打印当前工作目录
    char *ret3 = getcwd(buf, sizeof(buf));
    ERROR_CHECK(ret3, NULL, "getcwd");
    printf("chdir后的工作目录是: ");
    puts(buf);

    return 0;
}
```

注意：

当前工作目录是进程的属性，也就是说每一个进程都有自己的当前工作目录。而且父进程创建子进程的时候，子进程会继承父进程的当前工作目录。

这里，我们有一个执行的进程是shell/bash 进程，它是一个父进程，执行可执行程序就会创建一个子进程，子进程在一开始继承父进程的当前工作目录。

然后在这个子进程中将工作目录修改了，并不会影响父进程的工作目录。这个过程有点类似于值传递，如下图所示：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img004.png)

*图2.4-1改变当前工作目录-图*

所以很明显，chdir 函数并不等同于cd 指令，cd这个shell指令可以修改shell/bash进程的当前工作目录。

那么cd指令是什么原理呢？

这是因为cd并不是一个独立于bash程序的外部可执行程序，它是bash这个程序的一部分，是bash/shell的内部指令。**这个cd指令的作用就是在进程内部，自己修改自己进程的当前工作目录。**

这也是whichcd 找不到可执行程序cd的原因，因为它不是一个独立的可执行程序，只是bash这个可执行程序的一部分。

这里涉及到了一些进程的知识，大家先了解一下，后续进程课程会详细了解。

#### 2.5 创建目录

mkdir （make directory）系统调用函数用于创建一个新目录。

**函数声明如下：**

```c
#include <sys/stat.h>
#include <sys/types.h>
int mkdir(const char *pathname, mode_t mode);
```

**形式参数：**

1. pathname : 要创建的目录的路径名。可以是绝对路径也可以是相对路径名。
2. mode : 设置新目录的权限。这是一个八进制数，类似于chmod的权限设置（例如，0775 ）。注意，最终的权限还会受到进程的 umask 设置的影响。

**返回值：**

1. 成功时，mkdir返回 0。
2. 失败时，返回 -1，并设置errno以指示错误的原因。常见错误比如目录已存在等。

**一个演示的代码如下：**

```c
/* Usage: ./04_mkdir pathname mode */
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3); // 需要三个命令行参数，允许传入一个三位八进制数表示权限
    mode_t mode;
    sscanf(argv[2], "%o", &mode); // 将第三个命令行参数字符串转换成八进制无符号整数
    int ret = mkdir(argv[1], mode);
    ERROR_CHECK(ret, -1, "mkdir");
    return 0;
}
```

注意：

新建一个目录设定权限为777 ，你可能会发现最终生成的目录权限为775

1. 这是因为文件掩码umask的影响
2. 文件掩码umask是一个三位的八进制数，**用于在创建新文件或者目录时移除一些权限**。
3. 比如umask若是0002 ，指定权限为777 ，最终结果就会是775 ，**看起来像**"新权限 - 掩码"会得到新权限
4. 可以通过shell指令umask 来查看当前掩码值，也可以用umaskn 来设定一个新的掩码值。
5. 掩码的存在是为了系统安全，避免新文件目录拥有过多的权限。
6. 较低的umask值会导致更开放的权限，而较高的umask值会导致更严格的权限。

当然原始权限和掩码之间，绝不是简单的减法关系。

更加详细的关于umask文件权限掩码的概念和计算，可以参考之前的文档：文件权限掩码

#### 2.6 删除目录

rmdir （remove directory）系统调用函数用于删除一个空目录，注意只能删除空目录。

**函数声明如下：**

```c
#include <unistd.h>
int rmdir(const char *pathname);
```

参数：pathname : 要删除的空目录的路径名。

**返回值：**

1. 成功时，rmdir返回 0。
2. 失败时，返回 -1，并设置errno以指示错误的原因。常见的错误原因有目录非空，不存在或无权限等。

**一个演示示例如下：**

```c
/* Usage: ./05_rmdir pathname */
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);

    int ret = rmdir(argv[1]); // 注意：rmdir 只能删除空目录
    ERROR_CHECK(ret, -1, "rmdir");
    return 0;
}
```

该函数比较简单，没有什么值得注意的。

### 3. 目录相关POSIX库函数/目录流

在上面我们已经学会了目录的初级操作：创建、删除等。那么这一小节，我们将使用目录流，来查看目录中的内容。

在具体讲解之前，我们还是要解释一下标题：

**我们这里使用的目录流是符合POSIX标准的C语言库函数，这意味着它不能直接用于Windows系统，只能类Unix系统平台上使用。**

首先，既然是目录流，那我们就需要回忆一下流的模型，类似水流或者流水线：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img005.png)

*图3-1流模型-图*

而且我们已经知道，目录中存储的是子目录或文件的目录项，它们近似以链表的形式链接。

那么一个目录流就可以用下图来理解：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img006.png)

*图3-2目录流-模型图*

目录流指针，完全可以和文件流指针做类似的理解，它一开始指向目录文件的第一个目录项，并且可以继续向后移动。

目录流和文件流的API对比如下，你可以发现它们非常的类型：

**目录流 VS 文件流**

| 文件流 | 目录流 |
|---|---|
| fopen | opendir |
| fclose | closedir |
| fread | readdir |
| fwrite | × |
| ftell | telldir |
| fseek | seekdir |
| rewind | rewinddir |

**但还是要再强调一下，Linux目录流是符合POSIX标准的API，一般仅兼容类Unix平台，在Windows平台下都是不可以直接使用的。**

**注意：目录流是没有写操作的，只能读。这是因为如果开放写权限非常容易破坏文件系统的目录结构，只提供读是为了保障文件系统的安全。**

#### 3.1 打开目录流

**opendir**函数，用于打开一个目录流以读取其中的目录项。

当你使用opendir打开一个目录时，系统会创建一个目录流，并返回一个指向该流的DIR 指针。

该目录流指针一开始指向目录项第一个，然后程序可以通过函数来移动这个目录项指针，从而实现对目录的遍历和管理。

从使用上来看，它的特点非常类似于文件流的fopen 函数以及FILE 指针，只不过文件流是"ISO-C"官方标准C语言的库函数，而我们今天讲的目录流是POSIX标准的库函数，不是官方C标准库函数。

该函数的声明如下：

```c
#include <dirent.h> // dirent是directory entry的简写，就是目录项的意思
#include <sys/types.h>
DIR *opendir(const char *name);
```

**形式参数：**name : 字符串，代表要打开的目录的路径。

**返回值：**

1. 成功时，返回指向DIR类型的指针，即目录流的指针
2. 失败时，返回NULL并设置errno以指示错误的原因。常见的失败原因，比如目录没有权限打开、目录不存在等。

#### 3.2 关闭目录流

既然可以打开目录流，那么就可以关闭目录流。这样做可以释放分配给目录流的资源，避免内存泄漏。

函数声明如下：

```c
#include <sys/types.h>
#include <dirent.h>
int closedir(DIR *dirp);
```

**形式参数：**dirp : 由opendir返回的目录流指针。

**返回值：**

1. 成功：返回0
2. 失败时，返回-1并设置errno以指示错误的原因。常见的错误原因就是乱传指针，传入的指针不是打开的目录流指针。

综合打开目录流和关闭目录流，我们可以写出一个目录流操作的标准格式写法：

```c
/* Usage: ./06_dirent pathname */
int main(int argc, char *argv[]){
    // 命令行参数校验
    ARGS_CHECK(argc,2);
    DIR *dirp = opendir(argv[1]);
    // 打开目录流的错误处理
    ERROR_CHECK(dirp,NULL,"opendir");
    // 读目录流的操作
    // 及时释放资源，关闭目录流
    closedir(dirp);
    return 0;
}
```

这一整套先打开，最后关闭，中间进行目录流操作的流程完全类似于我们之前学过的文件流，可以视为目录流操作的一套惯用法。

#### 3.3 读目录流

当你使用opendir打开一个目录流后，可以使用readdir依次读取目录中的每个条目，直到目录中没有更多条目为止。

其函数的声明如下：

```c
#include <dirent.h>
struct dirent *readdir(DIR *dirp);
```

**形式参数：**dirp : 由opendir返回的目录流指针。

**返回值：**

1. 返回值: 成功时，返回指向structdirent结构体对象的指针，这个结构体当中包含了目录下文件和子目录的信息（如文件名等）。
2. 当目录中没有更多条目时返回NULL 。
3. **当函数出错时该函数也会返回NULL。但只要传给函数的指针是一个打开的目录流指针，该函数一般不会出错，所以可以把返回NULL作为读完目录流的标记，而不需要做错误处理。**

聪明的同学，已经在思考一个问题了：

该函数返回一个指向结构体对象的指针，说明函数内部肯定分配了额外的内存空间，那么这片空间需不需要程序员来手动释放呢？

不需要，在man手册中，官方开发者明确提出了：返回值指针指向的结构体对象是静态分配的内存，这意味着这个结构体对象的存储方式是由系统管理的，而不需要由程序员手动管理。

man手册的原文如下：

On success, readdir() returns a pointer to a dirent struc‐ture. (This structure may be statically allocated; do not attempt to free(3) it.)**实际上只需要使用closedir函数关闭目录流，目录项相应的结构体对象就会被释放销毁，不需要再手动free这个结构体了。**

##### 3.3.1 dirent结构体

要想真正理解和掌握opendir函数，最需要理解的就是dirent结构体，这个结构体到底是什么呢？

首先 dirent 不是一个单词，它是词组 directory entry 的缩写，也就是目录项的意思。

所以 dirent 结构体，就是当前目录下的某个文件/子目录的目录项结构体，这个结构体中会存储当前目录下的某个文件/子目录的信息。

通过查询man 手册，我们知道**dirent结构体的定义如下：**

```c
// dirent是directory entry的简写，就是目录项的意思
struct dirent {
 // 此目录项的inode编号，目录项中会存储文件的inode编号。一般是一个64位无符号整数（64位平台）
 ino_t d_ino;
 // 到下一个目录项的偏移量。可以视为指向下一个目录项的指针(近似可以看成链表)，一般是一个64位有符号整数
 off_t d_off;
 // 此目录项的实际大小长度，以字节为单位(注意不是目录项所表示文件的大小，也不是目录项结构体的大小)
 unsigned short d_reclen;
 // 目录项所表示文件的类型，用不同的整数来表示不同的文件类型
 unsigned char d_type;
 // 目录项所表示文件的名字，该字段一般决定了目录项的实际大小。也就是说文件名越长，目录项就越大
 char d_name[256];
};
```

其中文件类型d_type 的可选值如下(使用宏常量定义的整数)：

DT_BLK // 块设备文件，对应整数值6

DT_CHR // 字符设备文件，对应整数值2

DT_DIR // 目录文件，对应整数值4

DT_FIFO // 有名管道文件，对应整数值1

DT_LNK // 符号链接文件，对应整数值10

DT_REG // 普通文件，对应整数值8

DT_SOCK // 套接字文件，对应整数值12

DT_UNKNOWN // 未知类型文件，对应整数值0所以我们这么理解readdir 函数：

```c
struct dirent *readdir(DIR *dirp);
```

readdir 函数需要传入一个目录流指针，用于从打开的目录流中读取下一个目录项，并返回一个存储该目录项数据的structdirent结构体指针。

这个结构体对象由readdir 函数在内部申请空间创建，也由目录流库自动管理生命周期，程序不需要考虑它的内存管理问题。

##### 3.3.2 扩展：如何查询结构体类型的具体定义

上述代码中出现了一个结构体类型，那么如何查询结构体类型的具体定义呢？

除了查阅man手册外，我们也可以直接自己搜索预处理后的.i文件，如下图所示：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img007.png)

*图3.3.2-1查询结构体类型的具体定义-图1*

当然你也可以通过grep指令来查询：

```c
grep -nEC10 "struct dirent" main.i
```

其中-C10 选项表示显示匹配行及其周围的10行。

包括这些类型的别名，也都可以用这种方式来查询：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img008.png)

*图3.3.2-2查询结构体类型的具体定义-图2*

大家可以自行找一个类型别名去练习一下即可。

##### 3.3.3 完全无关版ls指令

以上，我们就可以写出一个用于打印目录下所有文件的：inode编号、目录项大小、文件类型、文件名信息的类似ls 的工具（纯破产版，完全不一样好吧）。

参考代码如下：

```c
/* Usage: ./06_dirent pathname */
int main(int argc, char *argv[]){
 ARGS_CHECK(argc,2);
 DIR * dirp = opendir(argv[1]);
 // 打开目录流需要进行错误处理
 ERROR_CHECK(dirp,NULL,"opendir");
 struct dirent * pdirent;
 // 循环读目录项并打印目录信息，循环结束的条件是返回值为NULL
 while((pdirent = readdir(dirp)) != NULL){
     // printf的转换说明如果为了美观而换行，注意多行字符串的使用
     printf("inode num = %lu, reclen = %hu, type = %u, name =%s\n",
           pdirent->d_ino, // 64位平台这个inode编号一般是一个64位无符号整数
           pdirent->d_reclen, // 无符号短整型
           pdirent->d_type, // 无符号整型,也可以用%hhu
           pdirent->d_name); // 以字符串类型打印
 }
 // 及时释放资源，关闭目录流
 closedir(dirp);
 return 0;
}
```

**这段代码你应该非常熟悉，因为我们在使用文件流读文件内容时，也是一模一样的操作！实际上它们的原理也就是差不多的！**

#### 3.4 移动目录流指针的位置

**和文件流FILE指针视为指示文件当前读写位置的文件指针一样，目录流的DIR指针也用于指示当前读写目录项的位置。**

在上面的代码中，DIR指针遍历完了所有的目录项，也就是该指针指向了目录文件的末尾，那么有没有办法将这个指针再移动回去或者重置它么？

当然可以，和文件流类似，这里需要涉及三个函数：seekdir、telldir 、rewinddir下面我们先来看一下这三个函数的作用，再来具体讲解一下其中的细节问题。

##### 3.4.1 seekdir和telldir函数

seekdir函数用于设置目录流指针的当前位置，但和文件流的fseek 函数不同的是：

该函数没有参照点的概念，只能通过telldir函数提供的返回值来进行指针的移动。

即：必须先用telldir 函数记录指针的位置，然后才能够使用seekdir 返回记录的位置！

telldir 函数的声明如下：

```c
#include <dirent.h>
long telldir(DIR *dirp);
```

**形式参数：**dirp是由opendir返回的目录流指针。

**返回值：**

1. 返回值是目录流指针当前读取位置的标记，是一个长整型值。该返回值需要给seekdir 函数使用，一般不作其它用途。
2. 该函数如果出错，会返回-1。**但只要正确传递已打开的目录流指针，该函数一般不会出错，所以一般不做错误处理。**

seekdir 函数的声明如下：

```c
#include <dirent.h>
void seekdir(DIR *dirp, long loc);
```

**形式参数：**

1. dirp是由opendir返回的目录流指针。
2. loc是由telldir返回的位置标记。

**返回值：**

1. **该函数没有返回值，这说明函数的设计者认为该函数不需要错误处理。**
2. 该函数必须传入由telldir函数获取的位置
3. 在移动指针的过程中是纯粹的内存操作，也不涉及内存数据的读写操作，本身是非常安全的，不会出错，也确实不需要错误处理。

演示代码如下：

```c
/* Usage: ./06_dirent pathname */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    DIR * dirp = opendir(argv[1]);
    // 检查打开目录流是否成功
    ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent * pdirent;
    // 用于记录目录流指针的位置
    long loc;
    while((pdirent = readdir(dirp)) != NULL){
       printf("inode num = %lu, reclen = %hu, type = %u, name =%s\n\n",
              pdirent->d_ino, pdirent->d_reclen,
              pdirent->d_type,pdirent->d_name);
       if(strcmp("file1",pdirent->d_name) == 0){
           // 如果当前的目录项表示文件的名字是file1,那么记录文件指针的位置
           loc = telldir(dirp);
       }
    }
    printf("--------------------------\n"); // 一个代码分隔线

    seekdir(dirp,loc); // 目录流指针回到记录位置
    // 获取目录流指针指向的目录项结构体, 并打印信息
    pdirent = readdir(dirp);
    printf("inode num = %lu, reclen = %hu, type = %u, name =%s\n\n",
          pdirent->d_ino, pdirent->d_reclen,
          pdirent->d_type,pdirent->d_name);
    // 不要忘记关闭流
    closedir(dirp);
    return 0;
}
```

按照上面代码的思路，我们记录了file1 目录项的位置，然后在下面回到这个位置，那么打印的结果是什么呢？

打印的结果却不是file1 ，而是. ，这是为什么呢？

这其实是由目录流指针DIR* 的行为引起的：

**readdir 函数在读取当前目录项并返回dirent结构体指针后，会自动移动到目录流中的下一个条目。**

**这意味着每次调用 readdir 后，目录流的内部指针都会向前移动到下一个条目。**

你可以参考下图来理解这个原理：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img009.png)

*图3.4.1-1readdir函数的行为-图*

所以，对于上图的目录项来说：

1. 如果希望记录. 这个目录项以待返回，需要在readdir函数的返回值为file1 时记录。
2. 如果希望记录file1 这个目录项以待返回，需要在readdir函数的返回值为.. 时记录。
3. 如果希望记录.. 这个目录项以待返回，需要在readdir函数的返回值为dir2 时记录。

也就是说，需要在readdir函数的返回值为上一个目录项时，记录下一个目录项的位置。

那我们就有一个问题了：

如果我希望记录第一个目录项dir2 的位置，咋办呢？

很简单，不用记录，因为有专门的函数来实现这个功能，也就是rewinddir ，倒带目录流，回到第一个目录项。

##### 3.4.2 倒带目录流

rewinddir函数重置目录流的位置到开始处，类似于文件流中的rewind函数。

其函数的声明如下：

```c
#include <dirent.h>
void rewinddir(DIR *dirp);
```

**形式参数：**dirp是由opendir返回的目录流指针。

**返回值：**没有返回值。**说明函数的设计者认为，该函数不会出错，也不需要进行错误的处理。**

使用rewinddir可以使得目录流回到初始位置，这样下一次调用readdir将返回目录中的第一个条目。

### 4. 实现无排序的ls -al指令

以上，我们就已经学完了目录流的内容，那么下面我们将做一个练习，自己来手动实现一个简化版本的ls-al 指令。

**简化，主要是简化了将目录项结果排序的过程，但-l选项所有的信息都要求大家打印出来。**

在上面我们已经实现了打印一个目录下，所有文件子目录的：inode编号、目录项大小、文件类型以及文件名。

这和ls-al 还有哪些差距呢？

差距太大了：

1. 文件类型应该用d 、b 、- 等形式来代表，而不是一个整数值。
2. 权限信息，完全没有
3. 硬链接数，完全没有
4. 拥有者名和拥有组名，完全没有
5. 文件大小，没有(目录项大小不是文件大小)
6. 最后修改时间，没有

看起来我们现在只有一个文件名，所以为了打印这些信息，我们还需要一个学习一个非常重要的函数**——stat系统调用函数**。

#### 4.1 stat系统调用函数

stat是一个系统调用函数，stat用于获取指定文件的相关详细信息，主要包括各种元数据信息。

它的函数声明如下：

```c
#include <sys/stat.h>
int stat(const char *path, struct stat *buf);
```

**形式参数：**

1. path ：这是一个指向字符数组的指针，代表要获取信息的文件的路径名。
2. buf ：这是一个指向structstat结构的指针，用于存储获取到的path文件的信息。

**返回值：**

1. **成功**：返回0 。
2. **失败**：返回-1 ，并且errno被设置以指示错误的原因。常见的出错原因有文件不存在、没有权限等。

关于这个函数的调用，我们需要注意以下几个细节问题。

##### 4.1.1 path参数的问题

该函数的调用，首先就有一个小细节需要注意：

利用dirent 结构体我们可以获取某个目录下所有文件的文件名，但这里的文件名就是stat 系统调用函数的第一个参数吗？

并不一定是：

1. 如果进程的当前工作目录就是dirent 结构体所表示的目录（就是opendir打开的目录），那么文件名就是路径名(相对路径).
2. 如果进程的当前工作目录不是dirent 结构体所表示的目录（不是opendir打开的目录），那么" dirent 结构体目录路径/文件名"才是路径名(绝对路径)。

此时基于dirent 结构体，来获取stat 函数形参的文件路径名就有了两种办法：

1. 在子l进程中使用chdir 函数切换进程的当前工作目录为dirent 结构体所表示的目录，此时文件名就是路径名。
2. 利用dirent 结构体中获取的文件名，结合dirent 结构体目录路径名，拼接得到一个绝对路径。

两种方式都可以，具体用哪个看自己的需求。

##### 4.1.2 buf参数的问题

函数的第二个形参是*buf 指针，需要传入一个指向stat结构体对象的指针。该形参没有被const修饰，传入stat函数后，显然函数内部会修改指向的内容，也就是在函数内部会修改stat结构体对象。

实际上这个函数的主要作用就是给stat结构体对象赋值，这非常类似scanf 函数，*buf 是一个非常典型的传入传出参数。

你可能非常好奇，stat 结构体到底是个什么东西呢？

确实，理解这个结构体，是理解stat系统调用函数最重要的部分。但不着急，我们先来思考一个问题：

这个传入函数的结构体对象，它的内存由谁进行管理呢？

**当然是由程序员自己管理了，推荐传入函数一个局部变量结构体指针，这样内存管理可以交给栈自动管理。**

##### 4.1.3 stat结构体(重点)

通过man2stat 查看stat函数的说明手册，我们可以找到stat结构体类型的定义，这里我们仅列出对我们实现ls-l 功能有用的字段：

```c
struct stat {
    mode_t st_mode; // 包含文件的类型以及权限信息
    nlink_t st_nlink; // 文件的硬链接数量
    uid_t st_uid; // 文件所有者的用户ID
    gid_t st_gid; // 文件所有者组的组ID
    off_t st_size; // 文件的实际大小, 以字节为单位

    struct timespec st_mtim; /* 包含文件最后修改时间的结构体对象 */
};
```

这些字段的类型都是使用别名来定义的，在64位Linux操作系统上，这些别名的类型一般是：

1. mode_t ：一个32位无符号整数，原始类型是usignedint 类型。
2. nlink_t ：一个64位无符号整数，原始类型是usignedlong 类型。
3. uid_t 和gid_t ：一个32位无符号整数，原始类型是usignedint 类型。
4. off_t ：一个64位有符号整数，原始类型是long 类型。

这些字段中，最后修改时间st_mtim 字段的类型稍微麻烦一些，是一个结构体timespec 类型，代码如下：

```c
struct timespec {
    __time_t tv_sec; // 时间戳，秒为单位。此类型别名一般就是long类型
    __syscall_slong_t tv_nsec; // 纳秒 - 存储时间戳当中不足秒的部分，用于精准表示时间。此类型别名一般就是long类型
};
```

综上所述，这里给出一个stat函数的简单调用：

```c
// 错误处理都省略了
DIR *dirp = opendir(argv[1]);
chdir(dir_name); // 切换当前进程的工作目录为dir_name目录
struct dirent* pdirent = readdir(dirp)); // 目录项结构体, dirp是打开的dir_name目录流指针
struct stat stat_buf; // 预先申请一个stat结构体对象
int ret = stat(pdirent->d_name, &stat_buf); // 获取文件的相关信息，相当于给stat_buf结构体对象初始化
```

可以把这段代码视为一个惯用方式。

**关于stat的成员"st_mtim"以及结构体"timespec"有一个细节需要注意：**

如果想要获取文件的最后修改时间戳的秒数，可以使用下面代码：

```c
stat_buf.st_mtim.tv_sec; // stat_buf是调用stat函数完成赋值的stat结构体对象
```

这样做是可以的，但是两个成员运算符"."的连用未免有些麻烦，于是在stat结构体的类型定义外，还有**一个宏定义**：

```c
#define st_mtime st_mtim.tv_sec
```

这就是man手册中显示的内容：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img010.png)

*图4.1.3-1stat结构体外的宏定义-图*

基于这个宏定义，下面两条代码就是完全等价的：

```c
stat_buf.st_mtim.tv_sec; // stat_buf是调用stat函数完成赋值的stat结构体对象
stat_buf.st_mtime; // 等价于上一条代码
```

注意：

1. 一个是**"st_mtim"**，这是一个结构体类型，它是stat结构体的成员。
2. 一个是宏定义**"st_time"**，它是一个"long int"类型的表示文件最后修改时间的时间戳秒数。

#### 4.2 实现青春版ls -al指令

以上内容学完后，我们就可以利用stat 函数实现一个青春版的ls -al指令。

参考代码如下所示：

```c
/* Usage: ./07_myls pathname */
int main(int argc, char *argv[]){
 ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir");

 // 切换工作目录为参数传入的目录
    int ret = chdir(argv[1]);
    ERROR_CHECK(ret, -1, "chdir");

 // dirent结构体指针，用于存放目录项信息
    struct dirent *pdirent;
    // 读取目录中的每个目录项
    while ((pdirent = readdir(dirp)) != NULL) {
       // 拼接文件路径，如果上面没有chdir切换目录，这里就需要做绝对路径的拼接操作
       // char path[1024] = {0};
       // sprintf(path, "%s%s%s", argv[1], "/", pdirent->d_name);
       // 或者也可以用strcpy以及strcat函数进行复制拼接获取最终目录
       // strcpy(path, argv[1]);
       // strcat(path, "/");
       // strcat(path, pdirent->d_name);

     // 获取文件相关的信息
       struct stat stat_buf;
       int ret = stat(pdirent->d_name, &stat_buf); // 由于切换了工作目录，所以文件名就是路径名。如果没有切换，那么这里需要传参path
       ERROR_CHECK(ret, -1, "stat");

     // 输出文件相关的信息
       printf("%o %lu %u %u %lu %lu %s\n",
              stat_buf.st_mode, // 以八进制无符号输出，可以看到权限的数字表示法
              stat_buf.st_nlink, // 无符号长整型输出
              stat_buf.st_uid, // 无符号int输出
              stat_buf.st_gid, // 无符号int输出
              stat_buf.st_size, // 无符号长整型输出
              statbuf.st_mtim.tv_sec, // 时间戳打印秒数，以无符号长整型打印。这里还可以写statbuf.st_mtime
              pdirent->d_name); // 字符串打印
    }
    // 关闭目录流
    closedir(dirp);
    return 0;
}
```

只需要注意stat 函数调用时需要传入的两个参数就可以了：

1. 第一个参数必须是文件的路径名，而文件名并不一定直接就是路径名。
2. 第二个参数必须是一个已申请内存的stat 结构体指针，整个stat函数相当于给stat 结构体对象初始化。

#### 4.3 处理文件类型和权限

首先，我们要把st_mode 成员的数字表示转换成"文件类型 + rwx权限"字符串，这要如何去实现呢？

首先，我们还是要理解st_mode 这个成员是如何存储文件类型和权限信息的。

上面已经讲过了，st_mode 在64位Ubuntu下一般是一个32位无符号整数，但实际上它也并不需要这么多位。它实际利用上的位只有：

1. **前4个(或前5个)二进制位，用于存储数据表示该文件的类型。**
2. **最后9个二进制位，用于存储数据表示该文件的权限。**

既然涉及到位，那我们应该立刻想要位运算，实际上要想通过st_mode 处理转换文件类型和权限，整个过程都需要依赖位运算。

文件类型转换的实现是比较简单的，因为man手册关于这个操作，给出了一个示例，如下：

```c
switch (sb.st_mode & S_IFMT) {
    case S_IFBLK: printf("block device\n"); break;
    case S_IFCHR: printf("character device\n"); break;
    case S_IFDIR: printf("directory\n"); break;
    case S_IFIFO: printf("FIFO/pipe\n"); break;
    case S_IFLNK: printf("symlink\n"); break;
    case S_IFREG: printf("regular file\n"); break;
    case S_IFSOCK: printf("socket\n"); break;
    default: printf("unknown?\n"); break;
}
```

其中：

1. sb.st_mode 就是结构体的st_mode成员
2. S_IFMT是一个位掩码，将st_mode 成员与S_IFMT进行位与操作，就能够得到代表文件类型的值。
3. 随后再用这个代表文件类型的值，进行switch选择判断，从而实现根据st_mode 来获取对应文件类型。

于是我们就完美的获取了文件类型。

那么接下来，如何转换权限数字，变为一个字符串呢？

st_mode 成员的低9位用于存储权限信息，我们只需要从低9位开始，向后一直判断到最低位，判断每一位数字是否是1，从而决定该位置的权限字符。

整个判断的过程，仍然要使用按位与& 运算符，举例：

1. st_mode & 100000000 (0400) ，若结果不为0说明拥有者有读权限，若为0表示拥有者没有读权限。
2. st_mode & 010000000 (0200) ，若结果不为0说明拥有者有写权限，若为0表示拥有者没有写权限。
3. st_mode & 001000000 (0100) ，若结果不为0说明拥有者有执行权限，若为0表示拥有者没有执行权限。
4. ...

于是我们可以写出这样的代码：

```c
void mode_to_string(mode_t mode, char str[10]) {
    // 所有者权限
    str[0] = (mode & 0400) ? 'r' : '-';
    str[1] = (mode & 0200) ? 'w' : '-';
    str[2] = (mode & 0100) ? 'x' : '-';

    // 组权限
    str[3] = (mode & 0040) ? 'r' : '-';
    str[4] = (mode & 0020) ? 'w' : '-';
    str[5] = (mode & 0010) ? 'x' : '-';

    // 其他用户权限
    str[6] = (mode & 0004) ? 'r' : '-';
    str[7] = (mode & 0002) ? 'w' : '-';
    str[8] = (mode & 0001) ? 'x' : '-';

    // 设置字符串结束符
    str[9] = '\0';
}
```

这样，我们就完成了文件类型和文件权限的处理。

#### 4.4 处理拥有者名和组名

现在我们已经有用户UID以及组ID了，可以直接通过以下两个**POSIX标准库函数**将uid和gid成员转换成对应字符串。

```c
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
struct passwd *getpwuid(uid_t uid);
struct group *getgrgid(gid_t gid);
```

其中passwd和group这两个结构体类型，如下所示：

```c
struct passwd {
    char *pw_name; // 用户名
    char *pw_passwd; // 密码（通常是加密后的密码，但在现代系统中通常是 'x'或'*'，真正的密码存储在安全文件中）
    uid_t pw_uid; // 用户ID
    gid_t pw_gid; // 组ID
    char *pw_gecos; // GECOS 字段，包含其他用户信息
    char *pw_dir; // 用户主目录
    char *pw_shell; // 用户登录 shell
};

struct group {
    char *gr_name; // 组名
    char *gr_passwd; // 组密码（在现代系统中通常是 'x' 或 '*'，真正的密码存储在安全文件中）
    gid_t gr_gid; // 组ID
    char **gr_mem; // 包含组成员用户名的字符串数组
};
```

这个转换的过程非常简单，不再赘述。

需要注意的是：

getpwuid() 和getgrgid() 函数都是**POSIX标准库函数**，不是标准库函数，更不是系统调用。

它们实际上是直接从系统的用户数据库（通常是/etc/passwd 文件）和组数据库（通常是/etc/group 文件）中获取用户和组的信息。

#### 4.5 处理最后修改时间戳

现在我们只剩下一件事情就可以完成简化版ls-al 的编写了——将时间戳修改为年月日的日期。

我们可以使用一个C语言标准库的库函数—— localtime这个函数的目的是将一个时间戳（time_t类型）转换为表示本地时间的struct tm结构体。时间戳是自 1970 年 1 月 1 日（UTC）以来的秒数。

该函数的声明如下：

```c
#include <time.h>
struct tm *localtime(const time_t *timer);
```

**形式参数：**

1. timer ：需要传入一个指向time_t类型变量的指针，也就是指向时间戳变量的指针。
2. 注意：结构体stat的成员st_mtim 是一个结构体类型，不能直接传参给localtime 函数。st_mtim.tv_sec 的类型则刚好匹配，可以传参。**（time_t一般就是long int）**
3. 当然，你还可以直接传参stat_buf.st_mtime ，其中st_mtime 是st_mtim.tv_sec 的宏定义，可以简化代码。

**返回值：**返回值是指向struct tm结构体的指针，该结构体包含了分解后的时间元素，例如年、月、日、小时、分钟、秒等。

这个struct tm结构体的定义如下：

```c
struct tm {
    int tm_sec; /* 秒 – 取值区间为[0,59] */
    int tm_min; /* 分 - 取值区间为[0,59] */
    int tm_hour; /* 时 - 取值区间为[0,23] */
    int tm_mday; /* 一个月中的日期 - 取值区间为[1,31] */
    int tm_mon; /* 月份（从一月开始，0代表一月）- 取值区间为[0,11] */
    int tm_year; /* 年份，其值从1900开始 */
    int tm_wday; /* 星期 – 取值区间为[0,6]，星期日为0 */
    int tm_yday; /* 从每年的1月1日开始的天数 – 取值区间为[0,365]，1月1日为0*/
    int tm_isdst; /* 夏令时标识符，夏令时时为正，不是夏令时时为0，不了解情况时为负*/
};
```

注意，这些数值的取值范围，不是正常的生活中的表示方式。比如月份不是[1, 12]，而是[0, 11]最后，你不需要手动释放localtime返回的struct tm结构体对象。localtime函数返回的是一个指向静态分配的结构体的指针。这片内存空间由C系统自动管理和重用，程序员无需进行管理。

获取这个结构体后，就可以对照ls-al 指令，选择出需要的数据项，然后拼接处理得到一个表示最后修改时间的字符串。

#### 4.6 最终实现

在最终实现时，我们要求大家多做一步处理：

1. 允许启动可执行程序时，只输入可执行程序名这个命令行参数，此时表示打印当前目录下的信息。实际上ls-al 也是这么设计的。
2. 允许输入第二个命令参数，表示要打印信息的目录，ls-al 也同样具有这个功能。

参考代码如下：

```c
// 设置文件类型和权限字符串
void set_type_mode(mode_t mode, char *tm_str){
    // 处理第一个字符，即文件类型
    switch (mode & S_IFMT) {
    case S_IFBLK: tm_str[0] = 'b'; break;
    case S_IFCHR: tm_str[0] = 'c'; break;
    case S_IFDIR: tm_str[0] = 'd'; break;
    case S_IFIFO: tm_str[0] = 'p'; break;
    case S_IFLNK: tm_str[0] = 'l'; break;
    case S_IFREG: tm_str[0] = '-'; break;
    case S_IFSOCK: tm_str[0] = 's'; break;
    default: tm_str[0] = '?'; break;
    }

    // 处理后续九个字符，即文件的权限信息
    // 设置拥有者的权限信息
    tm_str[1] = (mode & 0400) ? 'r' : '-';
    tm_str[2] = (mode & 0200) ? 'w' : '-';
    tm_str[3] = (mode & 0100) ? 'x' : '-';
    // 设置拥有者组的权限
    tm_str[4] = (mode & 0040) ? 'r' : '-';
    tm_str[5] = (mode & 0020) ? 'w' : '-';
    tm_str[6] = (mode & 0010) ? 'x' : '-';
    // 设置其他人的权限
    tm_str[7] = (mode & 0004) ? 'r' : '-';
    tm_str[8] = (mode & 0002) ? 'w' : '-';
    tm_str[9] = (mode & 0001) ? 'x' : '-';
    tm_str[10] = '\0'; // 确保字符串以 null 结尾
}

// 获取格式化的时间字符串
void set_time(time_t mtime, char *time_str){
    // 由于tm结构体中存储的是月份的整数值，我们需要的是月份字符串，所以用一个字符串数组来存储月份字符串
    const char month_arr[][10] = {
       "1月", "2月", "3月", "4月", "5月", "6月",
       "7月", "8月", "9月", "10月", "11月", "12月"
    }; // tm结构体当中的月份范围是[0, 11]，刚好可以适配这个数组

    // 调用localtime函数，获取tm结构体指针
    struct tm* st_tm = localtime(&mtime);
    // 构建时间字符串,格式为：月份 天数 时：分
    sprintf(time_str, "%s %2d %02d:%02d",
           month_arr[st_tm->tm_mon],
           st_tm->tm_mday,
           st_tm->tm_hour,
           st_tm->tm_min);
}

/* Usage: ./07_myls pathname 或 ./07_myls */
int main(int argc, char* argv[]) {
    char* dir_name; // 存储目录名的指针
    if(argc == 1) {
       dir_name = "."; // 如果命令行参数没有提供要打印的目录，就打印当前工作目录
    }
    else if (argc == 2){
       dir_name = argv[1]; // 否则使用提供的命令行参数作为待打印的目标
    }else {
       fprintf(stderr, "args num error!\n");
       exit(1);
    }

    DIR* dirp = opendir(dir_name); // 打开指定的目录
    ERROR_CHECK(dirp, NULL, "opendir");

    // 改变工作目录到指定目录
    int ret = chdir(dir_name);
    ERROR_CHECK(ret, -1, "chdir");

    struct dirent* pdirent;
    // 遍历目录项
    while ((pdirent = readdir(dirp)) != NULL) {
       struct stat stat_buf;
       // 获取目录项的详细信息
       int ret = stat(pdirent->d_name, &stat_buf);
       ERROR_CHECK(ret, -1, "stat");

       char mode_str[1024] = { 0 }; // 保存文件类型和权限信息
       set_type_mode(stat_buf.st_mode, mode_str); // 设置类型和权限

       char time_str[1024] = { 0 }; // 保存格式化后的时间信息
       /*
           localtime需要传入时间戳描述
           所以这里传参时可以写stat_buf.st_mtime（宏定义，更简写）
           也可以写stat_buf.st_mtim.tv_sec（宏定义的原版代码）
           但不能直接写stat_buf.st_mtim
           原因上面已经讲过了！
       */
       set_time(stat_buf.st_mtime, time_str); // 获取时间字符串

       printf("%s %2lu %s %s %6lu %s %s\n",
              mode_str, // 文件类型与权限
              stat_buf.st_nlink, // 硬链接数，不足2个字符的在前面补空格
              getpwuid(stat_buf.st_uid)->pw_name, // 拥有者名
              getgrgid(stat_buf.st_gid)->gr_name, // 拥有者组名
              stat_buf.st_size, // 文件大小,使用%4lu表示最少输出4个字符，若不足4个字符则在前面补空格
              time_str, // 最后修改时间字符串
              pdirent->d_name); // 文件名
    }

    // 关闭目录
    closedir(dirp);
    return 0;
}
```

实现这个代码最需要理解的地方就是——文件名和路径名的区别。具体的描述可以参考下图：

![](Linux_assets/卷三%20文件系统编程/02_目录流/img011.png)

*图4.6-1文件名和路径名-解释图*

以上。

#### 4.7 扩展：实现排序功能

shell指令ls-al 的显示效果，实际上还附带一个排序效果，若想要实现这个排序效果也并非难事，我们现在学习过的知识点就已经足够了——使用qsort 函数给dirent结构体数组排好序，然后再遍历打印详细信息即可。

**参考的实现代码如下（有部分细节问题，可以直接查看注释解决）：**

```c
#include <61header.h>

void set_type_mode(mode_t mode, char *tm_str);
void set_time(time_t mtime, char *time_str);
int compare(const void* a, const void* b);
void str_to_lower(char *str);

/* Usage: ./08_myls dirname */
int main(int argc, char *argv[]){
    char *path;
    if(argc == 1){
       path = ".";
    }else if(argc == 2){
       path = argv[1];
    }else{
       fprintf(stderr, "args nums error!\n");
       return 1;
    }

    // path是一个目录的路径名
    DIR* dirp = opendir(path);
    ERROR_CHECK(dirp, NULL, "opendir");

    // 切换工作目录为待打印的目录
    int ret = chdir(path);
    ERROR_CHECK(ret, -1, "chdir");

    // 遍历目录项构建dirent结构体数组，用于实现排序
    // 为了更好的排序性能，选择使用结构体指针数组，而不是结构体数组
    // 为了程序能够更加灵活使用，选择动态内存分配这个结构体指针数组
    // 先遍历一次计算目录项的个数
    int count = 0;
    struct dirent* dp;

    // 第一次遍历：计算目录项数量
    while ((dp = readdir(dirp)) != NULL) {
       count++;
    } // while循环结束时,dp是一个空指针,count就是目录项的个数

    // 动态申请结构体指针数组
    struct dirent** dir_arr = (structdirent**)malloc(sizeof(struct dirent*)* count);
    ERROR_CHECK(dir_arr, NULL, "malloc dlist");

    // 倒带目录流指针
    rewinddir(dirp);

    // 第二次遍历: 将目录项结构体对象指针存入数组中
    int idx = 0;
    while((dp = readdir(dirp)) != NULL){
       dir_arr[idx] = dp;
       idx++;
    } // while循环结束时，待打印目录下的所有文件的dirent结构体指针斗被存入了dir_arr数组

    // 按照名字的字典顺序，利用qsort函数排序dir_arr数组
    qsort(dir_arr, count, sizeof(struct dirent *), compare);

    // 到这里为止，看似目录流的操作就已经结束了，似乎可以直接关闭目录流了
    // closedir(dirp);

    // 最后一步：根据已排序的目录项指针数组，获取stat结构体，打印文件详细信息
    for(int i = 0; i < count; i++){
       struct stat sb;
       // 文件名不再从dirent结构体中获取，不要忘记修改
       int ret = stat(dir_arr[i]->d_name, &sb);
       ERROR_CHECK(ret, -1, "stat");

       // 1.处理stat的成员st_mode，将它转换成权限和类型字符串
       char tm_str[1024] = {0};
       set_type_mode(sb.st_mode, tm_str);

       // 2.获取用户名和组名
       char *username = getpwuid(sb.st_uid)->pw_name;
       char *gname = getgrgid(sb.st_gid)->gr_name;

       // 3.将时间戳转换为时间字符串
       char time_str[1024] = {0};
       set_time(sb.st_mtim.tv_sec, time_str);

       printf("%s %2lu %s %s %6lu %s %s\n",
              tm_str,
              sb.st_nlink,
              username,
              gname,
              sb.st_size,
              time_str,
              // 文件名不再从dirent结构体中获取，不要忘记修改
              dir_arr[i]->d_name);
    }

    // 不要忘记free动态申请的目录项结构体指针数组
    free(dir_arr);

    // readdir返回的目录流结构体内存是由目录流自身管理的，会随着关闭目录流而自动释放
    // 所以如果在上面关闭目录流，极有可能导致目录项结构体被释放，从而导致数据漏输出
    closedir(dirp);
    return 0;
}

void set_type_mode(mode_t mode, char *tm_str){
    // 处理第一个字符，即文件类型
    switch (mode & S_IFMT) {
       case S_IFBLK: tm_str[0] = 'b'; break;
       case S_IFCHR: tm_str[0] = 'c'; break;
       case S_IFDIR: tm_str[0] = 'd'; break;
       case S_IFIFO: tm_str[0] = 'p'; break;
       case S_IFLNK: tm_str[0] = 'l'; break;
       case S_IFREG: tm_str[0] = '-'; break;
       case S_IFSOCK: tm_str[0] = 's'; break;
       default: tm_str[0] = '?'; break;
    }

    // 处理后续九个字符，即文件的权限信息
    // 设置拥有者的权限信息
    tm_str[1] = (mode & 0400) ? 'r' : '-';
    tm_str[2] = (mode & 0200) ? 'w' : '-';
    tm_str[3] = (mode & 0100) ? 'x' : '-';
    // 设置拥有者组的权限
    tm_str[4] = (mode & 0040) ? 'r' : '-';
    tm_str[5] = (mode & 0020) ? 'w' : '-';
    tm_str[6] = (mode & 0010) ? 'x' : '-';
    // 设置其他人的权限
    tm_str[7] = (mode & 0004) ? 'r' : '-';
    tm_str[8] = (mode & 0002) ? 'w' : '-';
    tm_str[9] = (mode & 0001) ? 'x' : '-';
    tm_str[10] = '\0'; // 确保字符串以 null 结尾
}

void set_time(time_t mtime, char *time_str){
    // 由于tm结构体中存储的是月份的整数值，我们需要的是月份字符串，所以用一个字符串数组来存储月份字符串
    const char month_arr[][10] = {
       "1月", "2月", "3月", "4月", "5月", "6月",
       "7月", "8月", "9月", "10月", "11月", "12月"
    };
    // 调用localtime函数，获取tm结构体指针
    struct tm* st_tm = localtime(&mtime);
    // 构建时间字符串,格式为：月份 天数 时：分
    sprintf(time_str, "%s %2d %02d:%02d",
           month_arr[st_tm->tm_mon],
           st_tm->tm_mday,
           st_tm->tm_hour,
           st_tm->tm_min);
}

// 用文件名的字典顺序 排序目录项结构体指针数组
// 用文件名的字典顺序，排序目录项结构体指针数组
int compare(const void* a, const void* b){
    // 此时a和b都是指向目录项结构体指针的指针，所以它们是二级指针，需要强转再解引用
    struct dirent* dir_a = *(struct dirent**)a;
    struct dirent* dir_b = *(struct dirent**)b;
    // 将文件名都转换成小写字母然后再按字典顺序排序
    // 原始文件名不能被修改，所以创建临时数组来存储文件名的副本
    char file_name[256];
    char file_name2[256];

    strncpy(file_name, dir_a->d_name, sizeof(file_name) - 1);
    strncpy(file_name2, dir_b->d_name, sizeof(file_name2) - 1);

    // 确保字符串以空字符终止
    file_name[sizeof(file_name) - 1] = '\0';
    file_name2[sizeof(file_name2) - 1] = '\0';

    // 将副本转换为小写
    str_to_lower(file_name);
    str_to_lower(file_name2);

    // 返回副本文件名的字典顺序
    return strcmp(file_name, file_name2);
}

// 将传入的字符串字母都转换成小写字母
void str_to_lower(char *str) {
    while (*str) {
       *str = tolower(*str);
       str++;
    }
}
```

以上。

### 5. 实现青春版tree指令

写一个小程序，实现青春版 tree 命令。大体效果如下：

```c
.
└───dir
└───────dir1
└───────file1
└───────a
└───────dir2
└───main.c
└───Makefile
└───test.c
└───simple_tree.c
└───simple_tree

3 directories, 7 files
```

怎么实现呢？

我们可以把整个打印分为三个部分：

1. 打印根目录的名字
2. 带缩进格式的，递归打印根目录下每一个目录项的信息(文件名)
3. 最下面打印统计文件和文件数量的信息

提示：

1. └和─这两个符号可以直接从tree指令执行结果里抄过来。
2. 递归打印根目录的每一个目录项的信息，其实就是深度优先(DFS)遍历树形结构，可以采用递归的方式来实现。**（而且总是优先打印出父目录的名字，才深入打印目录里的内容，这是一个先序深度优先遍历策略）**

**拼接绝对路径的实现方式：**

```c
// 全局变量，用于统计总目录数和文件数
static int dirs = 0;
static int files = 0;

// 深度优先搜索打印目录树
// dirpath: 要递归遍历的根目录
// width: 打印宽度，用于控制缩进，增强视觉层次感
void DFS_print(char* dirpath, int width) {
    DIR* dirp = opendir(dirpath);
    ERROR_CHECK(dirp, NULL, "opendir"); // 检查目录是否成功打开

    struct dirent* pdirent;
    while ((pdirent = readdir(dirp)) != NULL) { // 循环读取目录项
       // 跳过 "." 和 ".." 这两个特殊目录
       if (strcmp(pdirent->d_name, ".") == 0 ||
           strcmp(pdirent->d_name, "..") == 0) {
           continue;
       }
       // 打印前缀和缩进，构建树形结构的视觉效果
       printf("└");
       for (int i = 1; i < width; ++i) {
           printf("─");
       }
       // 打印当前文件或目录的名称（先序遍历）
       printf("%s\n", pdirent->d_name);
       // 如果是目录，则递归调用自己，继续深入遍历
       if (pdirent->d_type == DT_DIR) { // DT_DIR 表示目录文件
           dirs++;
           char path[1024] = { 0 };
           sprintf(path, "%s%s%s", dirpath, "/", pdirent->d_name);//构建递归调用的目录路径名
           DFS_print(path, width + 4); // 递归调用，增加宽度以增加缩进
       }
       else {
           // 文件数++
           files++;
       }
    }
    // 完成目录遍历后关闭目录
    closedir(dirp);
}

/* Usage: ./08_mytree pathname */
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    // 打印根目录名称
    printf("%s\n", argv[1]);
    // 从根目录开始深度优先遍历打印目录树, 初始-打印4个
    DFS_print(argv[1], 4);
    printf("\n%d directories, %d files\n", dirs, files);
    return 0;
}
```

**你当然也可以选择使用chdir切换目录来实现这个功能，但是在递归的过程中频繁切换工作目录，是一件比较麻烦的事情，思考难度比较大，代码容易摸不到头脑，建议优先考虑使用上面的拼接绝对路径的方式。**

参考代码如下：

```c
static int dirs = 0;
static int files = 0;

void DFS_print(char* dirpath, int width) {
    DIR* dirp = opendir("."); // 直接打开当前目录
    ERROR_CHECK(dirp, NULL, "opendir"); // 检查目录是否成功打开

    struct dirent* pdirent;
    while ((pdirent = readdir(dirp)) != NULL) { // 循环读取目录项
       // 跳过 "." 和 ".." 这两个特殊目录
       if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name,"..")== 0){
           continue;
       }

       // 打印前缀和缩进，构建树形结构的视觉效果
       printf("└");
       for (int i = 1; i < width; ++i) {
           printf("─");
       }
       printf("%s\n", pdirent->d_name); // 打印当前文件或目录的名称

       // 如果是当前正在处理的文件是目录文件，那么就递归深入该目录遍历
       if (pdirent->d_type == DT_DIR) { // DT_DIR 表示目录文件
           dirs++;
           int ret = chdir(pdirent->d_name); // 改变工作目录到当前遍历的目录
           ERROR_CHECK(ret, -1, "chdir"); // 检查目录是否成功切换
           DFS_print(".", width + 4); // 工作目录切换成功后，就递归的对当前目录进行深入遍历
           ret = chdir(".."); // 当前目录已经遍历完了，那就返回上一级目录
           ERROR_CHECK(ret, -1, "chdir"); // 检查是否成功返回
       } else {
           files++;
       }
    }
    closedir(dirp); // 完成目录遍历后关闭目录
}

/* Usage: ./08_mytree pathname */
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    printf("%s\n", argv[1]); // 打印根目录名称
    int ret = chdir(argv[1]); // 改变到提供的根目录
    ERROR_CHECK(ret, -1, "chdir");
    DFS_print(".", 4); // 从根目录开始深度优先遍历打印目录树, 初始打印4个横杠
    printf("\n%d directories, %d files\n", dirs, files);
    return 0;
}
```

这两种实现都是可以的，从效果上来说，都是OK的。

---

## 03 无缓冲文件流

### 1. 有缓冲文件流

文件流早在C语言阶段我们就已经学习过了，学的是标准C语言的库函数，比如fopen、fread、fwrite等函数。

这种文件流，更准确的称呼，应该是——**带有用户态缓冲区的文件流**。(包括我们刚学的目录流，也属于这个范畴)所谓带有用户态缓冲区的文件流，指的是在读写文件的过程中，标准C语言库在用户内存空间中预留一段区域，用来作为文件读写的缓冲区，以减少IO次数，减少系统调用次数，提高整体IO操作的效率。

之前我们画过类似的图：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img001.png)

*图1-1用户态缓冲区文件流-图*

这个图是一个简化的版本，实际上任何与外部设备(比如硬盘)的交互，都不可能绕开操作系统内核，所以更准确的画法是这样的：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img002.png)

*图1-2用户态缓冲区文件流-图2*

以往我们学习的文件流，即操作**FILE *指针**的那一套方案，文件数据的流向是：

读：磁盘数据 --> 内核态缓冲区 --> 用户态缓冲区 --> 用户进程(一般用一个buff数组存放)写：用户进程(一般用一个buff数组存放) --> 用户态缓冲区 --> 内核态缓冲区 --> 磁盘数据也就是说，在这个过程中，"用户态缓冲区"起到了一个**"二道贩子"**的作用：

1. 读的过程中，用户态缓冲区会一次性从内核态缓冲区中**读"一大块"**文件数据。这个过程由于要和内核交互，于是就涉及到系统调用。
2. 写的过程中，用户进程先将数据写入用户态缓冲区中，用户态缓冲区会"积攒"这些数据，然后一次性写"一大块"文件数据给内核态缓冲区，进而写入磁盘文件。这个过程仍然要和内核交互，仍然涉及到系统调用。

系统调用是一种远比函数调用，数据在用户空间复制代价要昂贵的多的操作，因为此过程首先要将进程状态由用户态切换到内核态，然后执行相关操作，最后进程还要回归用户态。

总之，我们不难得出一个结论：

1. 用户态缓冲区的存在，能够有效的减少系统调用的次数，也就减少了实际磁盘IO的次数，提升了整体的IO效率
2. 如果没有这个用户态缓冲区的存在，直接让用户进程和内核缓冲区进行系统调用级别的交互，就很有可能导致系统调用次数的增多，进而导致IO次数增多，降低整体的性能。

这就是我们之前学过的文件流，所谓的——**带有用户态缓冲区的文件流**。

### 2. 无缓冲文件流(重点)

今天这个小节的标题就叫做"无缓冲文件流"，但如果描述的更精确一些，应该是——**无用户态缓冲区，用户进程直接和内核态缓冲区进行系统调用交互的文件流。**

根据我们初步的理解，无缓冲文件流的模型可以参考下图：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img003.png)

*图2-1无缓冲文件流-图1*

这个模型正确吗？

这个模型显然是错误的。

内核区域显然不是普通用户进程应该直接交互访问的区域。如果内核态缓冲区也是直接返还一个指针给用户进程直接交互，那就太危险了——这意味着用户进程可以直接修改内核区域的数据，这么设计的操作系统，就太不安全，太不稳定了。

那怎么办呢？

谨记一句名言：如果计算机领域出现了解决不了的问题，那就**加一层**。

内核态缓冲区不能直接给一个指针让用户进程交互，那就加一层，让用户进程去交互其它的结构。

于是这里我们就要讲解一个非常重要的概念——内核区域文件缓冲区的数据结构。如下图所示：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img004.png)

*图2-2无缓冲文件流-图2*

在内核区域当中，维护了一个名为**"文件对象"**的数据结构。文件对象中维护了此file文件内核态缓冲区的文件指针，用于管理/控制文件的内核态缓冲区。

显然这个文件对象的指针以及整个文件对象都不可以直接给到用户空间，也不能直接交互用户空间。

于是内核区域就维护了一个**文件描述符表（本质就是文件对象指针数组）**，该指针数组中存储文件对象的地址，指向这个文件对象。

这个指针数组是有下标的，下标从0，1，2，3...（非负数，最大1023）

这个指针数组的下标就被称之为**"文件描述符"**。

于是：

1. 当用户进程想要打开一个文件操作文件时，内核区域就会创建一个该文件**文件对象**
2. 然后内核会将指向此文件对象的索引指针元素的下标返还给用户进程，用户进程只能得到一个非负整数，这个整数叫做**"文件描述符"**
3. 紧接着用户进程就通过文件描述符整数，与内核空间的文件数据进行系统调用级别的交互。

在这个过程中，用户进程全程没有获得内核区域的任何地址，没有和内核数据进行任何的直接交互，这样就保证了内核空间的安全，从而保证了操作系统的安全性和稳定性。

OK，到此为此无缓冲文件流的模型大家就都搞清楚了，那么接下来我们就要开始正式的学习代码了。

**下面我们所讲解的所有函数，全部都属于Linux系统调用函数。**

### 3. 打开文件open

首先，我们学习第一个系统调用函数——open函数。

调用open函数的作用是打开一个已存在的文件或创建一个新文件，此时内核区域会创建一个文件对象，并且将此文件对象的文件描述符，返还给函数调用者，该文件描述符可用于后续的读写操作。

**此函数的声明如下：**

```c
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

**返回值：**

1. 成功时，open返回一个非负整数，即新打开或创建文件的文件描述符。
2. 失败时，返回-1并设置errno以指示错误类型。

对于此函数的调用，最重要的是要理解它的形式参数列表，下面我们仔细讲解一下。

#### 3.1 了解：open的实现方式

我们在使用open时，经常会看到两种写法：

```c
open("a.txt", O_RDONLY);
open("a.txt", O_CREAT | O_WRONLY, 0644);
```

看起来像，一个同名函数实现了两种不同的版本，很类似C++/Java等编程语言中的函数重载。

但实际上：

1. **open 在 C 语言中只有一个函数原型。**
2. open 的实现方式也和函数重载没有任何关系。

那么 open 函数大体上是如何实现的呢？

由于不是重点，这部分知识点，大家了解一下即可。

open系统调用函数，其原型声明大概如下：

```c
int open(const char *pathname, int flags, ...);
```

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img005.png)

*图3.1-1open函数原型-图*

图中展示了在源码中查阅函数、类型等信息的方式。

**如果你也想下载源码，可以参考下列方式：**

源码下载的shell指令：

wget https://ftp.gnu.org/gnu/libc/glibc-2.35.tar.xz然后再解压缩这个源码压缩包：

tar -xf glibc-2.35.tar.xz随后就可以看到一个文件夹：

glibc-2.35这就是Linux下C语言源码文件夹。

**注意最后的 ... 参数，它表示这是一个可变参函数。**

但它并不是像printf那样可以接收任意数量的参数。

它的设计规则非常明确：

1. 普通情况下：只传两个参数
2. 如果flags包含O_CREAT
3. 则必须额外传入一个参数mode_t mode

**也就是说：第三个参数是“条件存在”的。**

这个函数在内部大体上是这么处理的（简化伪代码）：

```c
int open(const char *path, int flags, ...){
    mode_t mode = 0;

    if (flags & O_CREAT){
       va_list ap;
       va_start(ap, flags);
       mode = va_arg(ap, mode_t);
       va_end(ap);
    }

    return syscall(SYS_openat, AT_FDCWD, path, flags, mode);
}
```

核心逻辑只有两步：

1. 判断是否需要 mode 参数
2. 再调用 open 更底层的函数（open并不是最底层的实现函数）

**和 C++ 函数重载的区别**很多同学会误以为：open 是“函数重载”，这是错误的。

所谓函数重载语法，指的是编译器根据参数数量和类型在**编译期**决定调用哪个函数。

而 open 的情况是：

1. 只有一个函数
2. 使用 C 语言的可变参数机制
3. 在**运行时**根据 flags 判断是否读取第三个参数

所以open函数的实现方式，看起来类似函数重载，实则完全不是。

**总结：**

1. open 只有一个函数原型
2. 可选第三个参数通过 C 语言的...可变参数实现。
3. open的实现不是函数重载

一句话总结：

**open 看起来像重载，其实只是 C 语言可变参数的技巧封装。**

实际上，我们普通程序员也可以利用可变参数机制，实现一个函数在形式上“看似”具有多个版本。

但它本质上仍然只有一个函数实现。不过在 C 语言中，这种写法并不常见。

如果你确有这种需求，到时候再学习吧。

#### 3.2 open的形参列表

首先第一个参数，没啥可说的，就是你要打开/新建的文件的路径名。下面重点介绍flags 参数和mode 参数。

第二个参数flags 非常重要，它指定了打开文件的方式。它是由一个或多个标志的组合，常见的文件打开的标志有：

| 标志 | 描述/含义 |
|---|---|
| O_RDONLY | 以只读的方式打开 |
| O_WRONLY | 以只写的方式打开 |
| O_RDWR | 以可读可写的方式打开 |
| O_CREAT | 如果文件不存在，则创建文件。如果不添加此标志，那么文件不存在时，将打开失败 |
| O_EXCL | 仅与O_CREAT连用，单独使用无意义。如果文件已存在，则open失败 |
| O_TRUNC | 如果文件已存在且成功以写入模式打开，则将其长度截断为 0，即删除文件内容。 |
| O_APPEND | 以追加模式打开文件，不能和O_RDONLY或者O_TRUNC连用。 |

那么这些所谓的标志，应该如何使用呢？

要真正搞懂怎么用，我们还需要理解flags是如何存储这些标志的，具体如下：

flags 一般是一个32位无符号整数，对于上述表格中的某一个标志而言，每一个标志都意味着这个flags 的位模式的某一位是1，其余位都是0。

比如O_CREAT 标志，该标志的就对应着32位的位模式的某一位是1，也就是说：

1. 只要32位的该位值是1，那么就表示如果文件不存在，则创建文件
2. 如果32位的该位置是0，那么就表示文件不存在将打开失败

但有三个标志是比较特殊的，它们**固定利用32位整数的低两位**：

1. **O_RDONLY**：read only，只读模式。在Linux系统中，只读模式一般就直接用整数0来表示它。
2. **O_WRONLY**：write only，只写模式。在Linux系统中，只写模式一般就直接用整数1来表示它。
3. **O_RDWR**：read write，读写模式。在Linux系统中，可读可写模式一般就直接用整数2来表示它。

这样设计使得**这三个标志是互斥的，在打开文件选择模式时，必须进行三选一！**

除了这三个标志三选一外，其余标志可以进行自由的拼接组合，如何组合呢？

由于其余标志都是某位为1表示打开标志，为0表示关闭标志，**且利用的是非低两位的更高未，也不会互斥**，所以只需要用**"按位或|"运算符**拼接这些标志就可以了。

比如：

1. O_WRONLY|O_CREAT|O_EXCL ：以只写模式打开文件，如果文件不存在就创建新文件，如果文件存在则报错。这个标志组合可以避免覆盖已有文件。
2. O_RDONLY|O_CREAT ：以只读模式打开文件，但如果文件不存在就创建一个新文件。

**但也不是这些标志在二进制位上不互斥，就能够随意组合了，因为有些标志在含义作用上是互斥的。所以要注意以下：**

1. O_RDONLY、O_WRONLY、O_RDWR是互斥的，只能三选一使用，而且必须三选一。
2. **O_EXCL**仅能和O_CREAT一起使用，单独使用或者和其余选项连用，都没有意义。
3. O_APPEND表示写入操作将始终从文件末尾开始，即使文件指针移动到文件的其他位置也不例外。注意它和**O_RDONLY**或者**O_TRUNC**连用是没有意义的

最后还有一个参数mode_t mode ：

1. 这个参数本身我们很熟悉了，一般情况下我们可以使用一个八进制整数用于指定文件的权限。
2. 这个参数只在使用了O_CREAT标志时才需要带上，因为这意味着文件不存在时会创建新文件，创建新文件则需要指定新文件的权限！
3. 一旦选择使用了O_CREAT标志，就必须加上该参数，open函数要变为三参的，否则新建文件的权限将是未知的。但没有O_CREAT标志，不要加上此参数！！
4. 思考如果是"O_CREAT | O_EXCL"标志组合时还需要这个参数吗？答：当然需要！

###### 补充：fopen和open的关系

实际上，fopen这个C语言的标准库函数，它的各个打开模式就是基于open系统调用函数的，各个标志去实现的。

你可以自己使用man3fopen 指令去查看，如下图所示：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img006.png)

*图3.2-1fopen的打开模式-图*

显然fopen的底层系统调用，在Linux平台下就是open 函数。

#### 3.3 close函数

既然有open函数，那就有close函数，但系统调用的close函数和传统库函数文件流、目录流当中的close有非常大的区别。

**close函数表示关闭文件描述符，而不是立刻释放文件对象的资源。**关于这里的细节，我们先按住不讲，待到后面的小节中补充。

这个函数的声明如下：

```c
#include <unistd.h>
int close(int fd);
```

形参列表：fd : 要关闭的文件描述符返回值：

1. **成功**：返回 0。
2. **失败**：返回 -1，并且errno被设置为非0值，并指示错误的原因，该函数一般不需要进行错误处理。

#### 3.4 简单的演示demo

以下有几个演示demo：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 以读写模式打开文件，若文件不存在，没有权限等会打开失败
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd); // 打印文件描述符

    close(fd);
    return 0;
}
```

**建议日常使用就以"读写模式"打开文件，这个用起来比较方便。**

第二个demo：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 以只读模式打开文件，若文件不存在会创建一个新文件
    int fd = open(argv[1],O_RDONLY | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd); // 打印文件描述符

    close(fd);
    return 0;
}
```

若文件不存在，这里会创建一个权限为0664 的新文件，这里同样是因为掩码的影响导致的。

第三个demo：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 以读写模式打开文件，文件不存在就创建一个新文件，若文件存在则清空此文件内容
    // 类似fopen的w+模式打开文件
    int fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd); // 打印文件描述符

    close(fd);
    return 0;
}
```

大家课下可以自由的练习这些标志的组合，以实现不同的功能，但要注意一些选项不能连用互斥的特点。

### 4. read函数

搞清楚无缓冲文件流的模型后，那么读写这个流就非常简单了：

1. 读，使用read函数，它表示用户进程从内核区域中直接将数据读取出来，数据从内核区域流向用户空间。
2. 写，使用write函数，它表示用户进程直接将内存数据写入到内核区域中，数据从用户进程流向内核区域。

注意：这个读写的过程仍然是一个流模型，我们只需要搞清楚数据流向以及通过函数调用来实现功能就可以了。至于其它问题：

1. 数据究竟如何流动？
2. 数据如何在外部设备和内核区域间交互？什么时机下进行？
3. ...

诸如此类问题，我们只需要知道它们全程都由硬件和操作系统共同来完成就可以，具体的细节我们就不要去纠结了。

**read函数的声明如下：**

```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```

**形式参数：**

1. fd : 文件描述符，它标识了一个已打开的文件流。
2. buf : 用户进程用于接收从内核缓冲区读取到的数据的一块内存区域，可以是数组，也可以是别的。
3. count : 指定最多读取的字节数。

**返回值：**

1. 成功时，read返回实际读取的字节数。可能等于count的值，也可能在最后一次读文件内容时，返回一个小于count的值。
2. 如果到达文件末尾（EOF），则返回 0。
3. 出错时，read返回 -1，并设置全局变量errno来指示错误类型。

接下来看几个使用的demo：

```c
// 读文本文件
int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);
    // 以读写的形式打开文件
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    // read函数读数据的单位是字节
    // 所以为了方便计算读取字节的数量，常用char数组作为数组buf中转站
    // 为了避免随机值导致输出结果中产生莫名其妙的字符出现，所以将buf数组元素初始化默认零值
    char buf[1024] = { 0 };
    ssize_t sret = read(fd, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    // 打印读到的实际字节数以及读到的字符信息
    printf("sret = %ld, buf = %s\n", sret, buf);

    close(fd);
    return 0;
}
```

下面我们将buf数组改小一点，然后多读几次：

```c
int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    char buf[6] = { 0 };
    ssize_t sret = read(fd, buf, sizeof(buf) - 1);
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);

    // 将buf数组内存区域清零
    memset(buf, 0, sizeof(buf));
    sret = read(fd, buf, sizeof(buf) - 1);
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);

    // 将buf数组内存区域清零
    memset(buf, 0, sizeof(buf));
    sret = read(fd, buf, sizeof(buf) - 1);
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);

    close(fd);
    return 0;
}
```

**上述代码中使用了一个memset函数，它是一个C 语言标准库函数。用于将一段内存中的所有字节都设置为特定的值，它经常被用于初始化数组或者清零内存区域。**

**此函数的声明如下：**

```c
#include <string.h>
void *memset(void *s, int c, size_t n);
```

**其中的三个参数的含义是：**

1. s ：指向要设定特定值的内存块的指针。此参数是一个传入传出参数，传入后同时还会作为返回值。
2. c ：是一个int类型的值，但memset实际上将该值转换为unsignedchar类型，然后用这个字节值来填充指定的内存块。
3. n ：指定要设定特定值的字节数，即要把内存块s 的多少个字节的内存空间设置为值c 。

**返回值：**

memset函数返回指向填充的内存块的指针，即参数s的值。

利用一个缓冲区数组读写文件的过程中，为了避免存在脏数据，可以选择使"memset"函数来清零缓冲区数据，但具体需不需要这么做要看实际应用场景。

#### 4.1 非阻塞read: 读硬盘文件

紧接着上面的一个代码实现，我们很容易就发现上面的代码中存在一个问题：存在重复代码，于是可以用循环简化一下代码实现。

于是我们就可以写出以下简化代码：

```c
int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    char buf[6] = { 0 };
    ssize_t read_count;

    // 循环读取文件直到文件末尾或出错
    // sret为0时表示读到文件末尾，sret为-1时表示read出错，这两种情况都会结束循环
    while ((read_count = read(fd, buf, sizeof(buf) - 1)) > 0) {
       printf("read_count = %ld, buf = %s\n", read_count, buf);
       memset(buf, 0, sizeof(buf)); // 清空缓冲区以准备下一次读取
    }
    // 检查是否是因为读取出错而退出循环
    ERROR_CHECK(sret, -1, "read");

    // 关闭文件
    close(fd);
    return 0;
}
```

这样的代码，我们写起来非常轻松自然，那么考虑一下为什么可以这么写呢？

这是**因为read读磁盘文件的时候，是一个没有阻塞的读过程。**这个过程中，数据始终从内核区域流向用户区域：

1. 一开始磁盘文件的待读取数据还比较充足，read函数能够正常读到参数count个字节。
2. 最后一次read数据，读到文件末尾时，read函数已经无法读到参数count个字节了。
3. **read到达末尾后，继续read，read并不会阻塞，而是返回0。**
4. 如果read的过程中出错，read也不会阻塞，而是返回-1。

**所以依据依据read磁盘文件这样的特点，我们可以以**>0**作为一个循环的条件，轻松实现循环读完一整个文件中的数据。**

#### 4.2 阻塞read: 读设备文件

既然有非阻塞read，那么自然就有阻塞read，最常见的就是read设备文件。

在上面的内容中，我们发现：

在利用系统调用函数open打开一个磁盘文件时，系统默认分配的文件描述符是3，那么0、1、2去哪里了呢？

当然是被系统默认保留了，在类 Unix 系统中，当一个进程启动时，它会自动打开三个特殊的文件描述符，这三个文件描述符分别是：

1. 0 ：表标准输入（stdin），默认是键盘输入。
2. 1 ：代表标准输出（stdout），默认是输出到屏幕。
3. 2 ：代表标准错误（stderr），它用于输出错误消息和诊断信息，默认是输出到屏幕。

在/dev 目录下，这三个标准流被指向了对应的设备文件，如下图所示：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img007.png)

*图4.2-1标准流文件描述符-图*

计算机的外部设备也被视为了一种设备文件，这体现了Linux的设计哲学，万物皆是文件。

利用这0 这个保留的文件描述符，我们可以实现从键盘接收输入：

```c
int main(void){
    char buf[1024] = {0};
    // 用文件描述符0表示从标准输入中读
    ssize_t sret = read(0, buf, sizeof(buf));
    ERROR_CHECK(sret,-1,"read");
    printf("sret = %ld, buf = %s\n", sret, buf);
    return 0;
}
```

这一段代码你应该非常熟悉了，这充分体现了Linux设计的精妙之处，哪怕是对一个外部设备进行read操作，至少从代码形式上来说，和read真正的磁盘文件是一致的。

然而，读取磁盘文件和设备文件在行为上存在以下区别：

1. **非阻塞和阻塞read:**
   - a. 读磁盘文件数据时是非阻塞read，因为磁盘文件的数据是持久存储的，read操作可以连续进行，直到文件末尾。于是在read磁盘文件时，我们可以正常的使用while循环，因为循环会有明确的结束标志，不会导致死循环。
   - b. 但从设备文件（例如键盘或网络套接字）的read操作一般是阻塞的。如果没有数据可读了（如用户尚未完成输入、等待网络连接），read函数会阻塞进程执行，直到数据到达，此时read函数就变成了一个阻塞函数。在这种情况下，如果仍然使用循环进行read，就非常容易导致循环无法退出，成为一个阻塞的死循环。
2. **不确定性**:
   - a. 磁盘文件的数据访问是确定性的，以一致且可预测的方式进行，使得读取操作简单且可靠。
   - b. 对于设备文件，数据的到来与否很多时候取决于外部因素，如用户输入或网络数据传输，这增加了读取操作的不确定性和复杂性。

总之，要理解读写磁盘文件和外部设备文件的区别，这里就相当于给后续课程打一个基础吧。

### 5. write函数

read函数会比较麻烦复杂一些，但write函数的使用就非常简单了：我们仅关心数据从用户进程输出到内核区域，就够了。

**write函数的声明如下：**

```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```

**形式参数：**

1. fd : 文件描述符，它标识了一个open函数打开的文件流对象。
2. buf : 指向一个内存区域，该区域包含了要写入的数据。
3. count : 要写入文件的字节数。

**返回值：**

1. 在成功时，write返回实际写入的字节数，基本上它就等于count 。
2. 如果发生错误，write返回-1 ，并且通过errno提供错误信息。

一个演示的代码如下：

```c
int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);
    // 读写模式打开文件
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    // 将数据段中的字面值字符串写到文件中
    ssize_t sret = write(fd, "howareyou", 9);
    printf("sret = %ld\n", sret);
    close(fd);
    return 0;
}
```

这段代码非常简单的演示了write函数的作用。

**总结read/write函数：**

1. 它们读写操作的第一个参数都是文件描述符，通过文件描述符间接和内核空间进行数据交互。
2. 它们读写操作的第二个参数都是通用指针类型，但区别是：
   - a. read函数的第二个参数buf通用指针，没有用const修饰，这说明read函数要修改buf指针指向的数据区域。这符合read函数读操作的作用，它会把内核区域的数据读到用户进程的buf内存块中。
   - b. write函数的第二个参数buf通用指针，使用const进行修饰，这说明write函数不需要修改buf指针指向的数据区域。这也符合write函数写操作的作用，它会把当前用户进程中的buf内存块中的数据输出到内核区域中。
3. 它们读写操作的第三个参数都是count，都是一个整数值，表示读写操作的字节数量。但区别是：
   - a. read函数指定了最大读取的字节数量是count，并通过返回值返回实际读到的字节数量。而**这个返回值，完全可能小于count**。
   - b. write函数指定了这一次写操作需要输出的字节数量是count，并通过返回值返回实际输出写的字节数量。而这个返回值，**通常都是等于count的**。

### 6. 读写二进制文件和文本文件

文本文件：

1. 文本文件由一系列的字符组成，这些字符要遵循特定的编码集（如ASCII或UTF-8等）
2. 文本文件是人类肉眼可以看懂的文件

二进制文件：

1. 二进制文件包含了一系列的字节，这些字节可以代表任何类型的数据，不限于文本字符。
2. 二进制文件的内容不遵循任何字符编码集规则，可以包含任意的字节序列。因此，人类肉眼不能直接看懂。

除此之外，文本文件由于采用特殊的编码形式，所以：

1. 同等内存大小的数据承载能力往往不如二进制文件。比如我想存一个整数"32767"，如果以文本形式存储，那么需要5个字节。而如果使用二进制文件存储，仅需要2个字节即可。
2. 文本文件的数据往往不能直接用于计算，而需要转换。以文本形式存储整数"32767"参与运算，是它的编码值参与运算，需要转换成整型后才是整数本身参与运算。

所以文本文件的目的是方便人类阅读和编辑，二进制文件则可以节省空间，并且转换效率高。

在实际使用read和write函数读写文本文件时：

我们一般会选择直接使用一个char数组，作为读写的媒介，此时操作的就是文本数据。

而如果操作的数据存在非字符串类型，比如int、double、结构体等其他类型，就是操作二进制数据，此时我们要遵循的原则是：

**按什么类型写入，就按什么类型读出！**

以下举了一些例子来证明上述的结论：

代码1：写文本数据到文件中

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 以读写模式打开
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    // 写字符串数据
    char str[] = "123456";
    write(fd,str,strlen(str));
    close(fd);
    return 0;
}
```

这个程序会把"123456"这个数组以字符串的形式写入文件，此时文件中存放的是该字符串的编码存储。可以用xxd-p文件名这个指令展示此文件的十六进制编码，此时输出的结果是：

313233343536 (即存储123456的ASCII码值)并且该文件会占6个字节的内存空间。这种做法的好处是：直观，人肉眼可以直接读文件但缺点也很明显：文件体积会偏大以及无法直接当成int类型使用，需要先转换一下。一个读文本文件中的文本数据，然后转换类型的代码示例如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    char buf[1024] = {0};
    int count = read(fd, buf, sizeof(buf)-1); // 确保将buf数组读成一个字符串
    ERROR_CHECK(count, -1, "read");

    puts(buf);
    // string -> int
    int num;
    sscanf(buf, "%d", &num);
    printf("num = %d\n", num);

    close(fd);
    return 0;
}
```

下面我们再看用二进制的方式来尝试写同样的数据到文件中，也就是直接写一个int num=123456 到文件中，直接把二进制数据写到文件中，这个操作的参考代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    // 直接将int的二进制数据写入文件
    int i = 123456;
    int ret =write(fd, &i, sizeof(i));
    ERROR_CHECK(ret, -1, "write");
    close(fd);
    return 0;
}
```

输出的文件，若直接用cat 指令打印结果是：

@7gd显然人肉眼是看不懂的，但也有好处：文件体积会更小且读到内存中可以直接当成int使用，不需要转换。

当然你仍然可以用xxd-p文件名这个指令展示此文件的十六进制编码，此时输出的结果是：

40e20100思考一下为什么是这样的呢？（考虑小端存储法）

所以这种写数据的方式，就是直接将内存中的数据写到外存的文件里。

最后这种二进制数据若想从新读取，那就需要重新read，遵循：**按什么类型写入，就按什么类型读出！**

参考代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    int i;
    // 用int写，就用int读
    int ret = read(fd, &i, sizeof(i));
    ERROR_CHECK(ret, -1, "read");
    // 可以直接把数据读出来当成int使用，效率更高
    printf("num + 100 = %d\n", (i + 100));
    close(fd);
    return 0;
}
```

那么实际的场景中，有哪些场景需要用二进制文件，哪些场景需要用文本文件呢？

比如日志文件，需要直接进行阅读，那当然用文本文件。

如果是应用程序的配置信息文件，游戏的存档文件等这些不需要也不应该让用户直接读内容的文件，则可以考虑用二进制文件。

总之，工作中可以灵活使用。

### 7. 中场练习：实现无缓冲IO文件复制

首先我们还是思考一下利用read和write函数实现文件复制的模型。如下图所示：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img008.png)

*图7-1无缓冲文件复制的模型-图*

这里提到了一个**页缓存（Page Cache）**的概念，在程序打开某个文件时，页缓存是操作系统在虚拟内存的内核区域开辟的一片动态区域，用于缓存磁盘上的文件数据。

上文中提到的某个文件的内核态缓冲区就是页缓存的一部分。

**页缓存是内核区域和磁盘文件交互数据的中转站，它会在恰当的时机将磁盘文件数据读出，也会在恰当的时机将数据写回磁盘，具体细节由硬件和操作系统自动管理完成，程序员可以不考虑这些细节。**

在这个过程中，用户空间里使用一个buf数组来作为中转站，整体的实现还是比较简单。

#### 7.1 一次性复制小文件

如果文件比较小，比如小于1024个字节，那我们可以写一个程序来一次性把它全部复制到目标文件。

参考代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr, -1, "open read");
    // 打印src文件对象的描述符，一般是3
    printf("%d\n", fdr);
    int fdw = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fdw, -1, "open write");
    // 打印dest文件对象的描述符，一般是4
    printf("%d\n", fdw);

    // 使用char数组的原因是方便控制内存大小，因为char元素固定1个字节。
    // 注意不要以为这里是复制文本文件，任何文件的数据都是字节书库
    char buf[1024] = {0};
    // 假设文件小于1024字节，一次性读写完成
    ssize_t sret = read(fdr, buf, sizeof(buf));
    // 读多少字节写多少字节，不要写多了。这里最好就写sret个字节
    write(fdw, buf, sret);

    close(fdr);
    close(fdw);
    return 0;
}
```

这个实现还是非常简单的。

**尤其要注意，write的时候要使用read的返回值，真正读到了多少个字节，就write多少个字节，否则有可能会出现在文件末尾多写数据的问题。**

#### 7.2 循环复制大文件

如果一个文件比较大，一个非常自然的想法就是用循环的方式去完成复制。

```c
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr, -1, "open read");
    int fdw = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fdw, -1, "open write");

    char buf[BUFFER_SIZE] = {0}; // 使用char数组的原因是方便控制内存大小
    // while(1){
    // memset(buf,0,sizeof(buf));
    // ssize_t sret = read(fdr,buf,sizeof(buf));
    // if(sret == 0){
    // break;
    // }
    // write(fdw,buf,sret);
    // }
    // 上面代码可以写成下面的while循环
    ssize_t read_count;
    // 注意这里的括号，不要多，也不要少
    while ((read_count = read(fdr, buf, sizeof(buf))) > 0) {
       // 如果read成功，但是返回的sret小于等于0，那么就没有必要继续了
       write(fdw, buf, read_count);
    }
    close(fdr);
    close(fdw);
    return 0;
}
```

总的来说，这段代码和我们以往实现的文件流文件复制，从代码上来看没有什么本质上的区别，模式是差不多的。

#### 7.3 性能比较

文件复制的操作，我们早在文件系统编程的第一天就讲解过了，当时我们使用的是文件流——fopen、fread、fwrite。

那么我们不由得就想到一个问题：

无缓冲文件流和文件流在实现文件复制时，它们的性能孰优孰劣呢？

**实际上，在相当多的情况下，使用无缓冲文件流的效率还赶不上普通有用户缓冲区的文件流。**

当你选择使用无缓冲文件流时，文件复制的效率主要看buf数组的大小，如果该数组小或者很小，那么效率是非常差的：

```c
char buf[100] = {0}; // buf如果是100甚至更小时，文件复制的效率非常低
```

这是什么原因呢？

下面是使用fopen有缓冲文件流进行文件复制和无缓冲文件流open文件复制时的两个原理模型图：

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img009.png)

*图7.3-1有缓冲文件复制原理-图*

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img010.png)

*图7.3-2无缓冲文件复制的模型-图*

在使用无缓冲系统调用实现文件复制时，如果buf数组很小，那么用户空间的buf数组需要频繁和内核区域进行数据交互，而每一次交互都是巨大的性能损耗，因为这个过程是系统调用。

系统调用涉及到用户进程的状态切换："用户态" --> "内核态" --> "用户态"，这个过程涉及到保存用户态的上下文、加载内核态的上下文、执行内核代码，然后再切换回用户态，这个过程性能损耗极大。

尤其是"用户态 --> 内核态"的切换，在系统调用中，这个过程被称之为"陷入(trap)"，占据系统调用性能损耗的大部分。

**总之如果使用的buf数组比较小，就会导致系统调用次数增多，进而导致进程频繁切换用户态和内核态，应用整体的性能就会骤降。**

相比之下，使用带有用户空间缓冲的文件流，由于自带一个比较大的中间缓冲区，就算用户数组buf很小，但也不会显著增加系统调用的次数。

比如：

1. 当你向文件写数据时，实际上是先把数据从进程内存写到文件输出流缓冲区中
2. 而只有当缓冲区填满，或者用户主动刷新缓冲区时，缓冲区才和内核区域交互，进行系统调用
3. 这样的一番操作就减少了系统调用的次数。

**带缓冲区的文件流实际上是一种"防呆"机制，照顾那些编程经验不丰富、思考不深入的程序员，让这些程序员在多数场景下都能获得一个较好的性能。所以如果比平均性能的话，往往带缓冲区的文件流会更好一些。**

那么什么时候read/write 的效率会比fread/fwrite 更高呢？或者说哪些场景下用会

主要有以下场景：

1. **实时性要求高的场景：**read()和write()提供了更为直接的磁盘访问，能够让你更精确地控制数据的读写时机。在需要即时处理数据的实时系统中，使用带缓冲的读写显然是不合适的。
2. **系统编程：**Linux系统编程中有很多操作都只支持read、write，这些场景中我们必须用read和write。比如：读写某些设备文件，管道的进程间通信，网络通信等操作，很多时候只能使用无缓冲文件IO。

相对应的：

1. 一般的，普通的文件操作
2. 需要跨平台的文件操作
3. **处理文本文件的操作，可以使用fgets/fputs这样读写一整行的函数，符合人类习惯。**

这些场景下，还是fread/fwrite 会更好用一些。

**附，一个用于获取当前时间戳毫秒值的函数：**

```c
#include <time.h>
#include <unistd.h>

long long current_time_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; //转换为毫秒
}
```

你可以将这个函数分别在文件复制的首尾两端调用，最后相减，从而大致得出文件复制所需要的时间(毫秒值)。

### 8. 截断和扩展文件

在Linux文件系统编程中，经常需要截断或者扩展某个文件。

ftruncate是一个文件相关的系统调用函数，用于改变已打开文件的长度，这个函数允许你增大或减小文件的大小：

1. **如果文件大小增加，新增的部分将会被填充为零字节。**

2. 如果文件大小减小，超出新长度部分的数据将会被丢弃，也就是会从文件的末尾开始进行截断。

#### 8.1 ftruncate系统调用函数

**ftruncate函数的声明如下：**

```c
#include <unistd.h>
int ftruncate(int fd, off_t length);
```

**形参列表：**

1. fd ：文件描述符，它是通过打开文件的系统调用返回的。
2. length ：是想要改变到的新的文件大小，单位是字节。

**返回值：**

1. 成功时，ftruncate返回 0。
2. 失败时，返回 -1 并设置错误码errno来指示错误的类型。

ftruncate函数常见的使用场景如下：

1. **减小文件大小**：
   - a. 如果你想要删除文件的一部分内容，可以通过ftruncate将文件截断到指定的长度，超出的部分将会被去除。
   - b. 截断部分的内容无法恢复!
2. **增大文件大小**：
   - a. 如果你需要预留文件空间或者为文件追加固定长度的空白部分，可以使用ftruncate增加文件的大小。
   - b. 新增的部分会用零字节填充。
   - c. **新增的零字节填充部分不占用额外的磁盘空间，除非真正写入数据！**

**一个参考代码举例：**

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    // 改变文件的大小
    int ret = ftruncate(fd,100);
    ERROR_CHECK(ret,-1,"ftruncate");
    close(fd);
    return 0;
}
```

注意事项：

1. **数据丢失风险**：截断文件时，超出length的数据不可恢复，需谨慎操作。
2. 虽然此函数需要传入文件描述符，但此函数不会改变文件的读写位置，毕竟它不涉及读写文件的操作。
3. open打开文件时，必须具有写权限，否则ftruncate会调用失败。

注意，一旦截断减小文件大小，丢掉的数据是不能恢复的。

#### 8.2 stat指令

stat 是一个shell指令，它用于显示文件的详细信息，比如文件类型、文件大小、权限、所有权、最后访问时间、最后修改时间等。

比较需要关注的数据项有：

1. **Size:**文件的实际大小，以字节为单位。
2. **Blocks:**文件所占用的512字节磁盘块的数量，这个数值的大小代表了文件实际占用磁盘空间的大小。

在stat指令当中，块作为单位存在时，默认指的是512个字节。通过stat指令，我们发现磁盘最少要分配8个块给一个文件，也就是说Linux系统下一个文件实际占用磁盘空间的大小是以4096为单位的（固态硬盘的最小块是4096字节）。

比如：

1. 一个文件即便本身只有100个字节，但磁盘还是会给它分配8个块，即占用磁盘空间4096个字节
2. 一个文件本身的大小是20000个字节，那么磁盘就会给它分配40个块，即占用磁盘空间20480个字节

总之一般而言，一个文件所占磁盘空间的大小要比文件的实际大小要大。

但是，当我们使用ftruncate函数给一个文件分配特别大的字节数时，会发现文件本身的大小竟然会大于分配的磁盘空间大小，相当于反过来了。

**这就意味着，文件已经占用了虚拟文件系统当中的空间，已经在虚拟文件系统中标记了这一整块区域，但是底层磁盘还没有为其分配真正的磁盘数据块，这种现象就是文件空洞。**

![](Linux_assets/卷三%20文件系统编程/03_无缓冲文件流/img011.png)

*图8.2-1文件空洞-图*

文件空洞的主要作用是用来快速的为文件占位，因为文件系统分配速度很快，而磁盘真正分配数据则很慢。

一个经典的场景就是下载，在下载任务开始前，可以通过ftruncate 函数预先为文件分配一个特定大小的空间。

这样做的好处是可以确保有足够的磁盘空间来存储即将下载的数据，避免在下载过程中因为磁盘空间不足而失败。

总之ftruncate函数，基于文件空洞的原理，实现了高效地预留文件空间，这在很多场景下都很有用。

---

## 04 文件映射

### 1. 概述

所谓**文件映射（Memory Mapped Files, mmap）**是一种**内存映射文件**的技术：允许将文件的数据内容在虚拟内存中进行映射，使得程序可以像访问普通虚拟内存一样来访问磁盘上文件的内容。

一旦文件被映射到虚拟内存中，应用程序就可以通过指针操作映射区域，此时就不再需要传统的read、write等API来操作文件了：

1. 对这段虚拟内存的读操作就是读文件内容
2. 对这段虚拟内存的写操作就是写文件的内容，会自动同步修改到文件中。
3. 同样，文件内容的更新也可以立即反映在虚拟内存映射中。

根据以上内容，我们大体上，可以认为文件映射是下面的模型：

![](Linux_assets/卷三%20文件系统编程/04_文件映射/img001.png)

*图1-1文件映射-图*

**当然这个图是比较粗糙的，非常不准确，但对于使用文件映射而言，是足够的。**

### 2. 文件映射

**下面来讲一下文件映射的具体实现，也就是讲一系列系统调用函数的使用。**

文件映射的实现，首先要依赖于mmap 系统调用函数。该函数会返回一个指向用户态空间映射文件内容的指针，利用该指针操作映射的内存区域，就可以实现操作文件内容。

#### 2.1 mmap函数

首先mmap函数是一个符合POSIX标准的Linux系统调用函数。

**该函数的声明如下：**

```c
#include <sys/mman.h>
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```

**参数列表解释如下：**

1. void*addr ：
   - a. 该参数表示告诉mmap 函数从用户内存空间的哪里开始映射文件。
   - b. 建议这个参数设为NULL ，表示由操作系统决定映射的起始地址。
2. size_tlength :
   - a. 指示想要映射的区域的大小，以字节为单位。
   - b. 该参数和offset 参数配合使用，用于控制将文件的哪一部分映射到内存区域中。
   - c. 其中offset 参数表示映射的起点，length 参数表示映射文件的实际大小。
3. off_toffset ：
   - a. 被映射文件，映射位置的偏移量，表示从文件的哪个位置开始映射。
   - b. 一般可以直接写0，表示从文件开头进行映射。
   - c. 在用户空间的映射区域，offset也代表映射区域的起始地址偏移值。
4. **结合上面两个参数，如果想要一次性映射整个文件，length可以直接写文件的大小，offset则是0。**
5. intprot : 映射的内存区域的访问权限标志。比较常用的是：
   - a. PROT_READ ：区域可被读取。
   - b. PROT_WRITE ：区域可被写入。
   - c. 类似open函数的读写模式，该参数写PROT_READ|PROT_WRITE 就表示映射区域可读可写。
6. intflags : 决定内存映射区域的回写特性。常用的标志有：
   - a. MAP_SHARED ：对映射区域的修改会反映到文件上，并且对所有映射该文件的其他进程可见。
   - b. MAP_PRIVATE ：建立一个写时复制的私有映射，对该区域的修改不会影响原文件，也不会影响到其他进程。
   - c. 建议目前这个阶段，该参数就写MAP_SHARED
7. intfd : 要映射到进程空间的文件的文件描述符，由open 函数获取。

**该函数的形式参数列表，乍一看很丰富，内容很多，但实际上在一般情况下，大多数参数都是固定的：**

1. void*addr ：NULL
2. size_tlength : 想要映射的文件内容的字节大小
3. off_toffset ：一般就从文件头开始映射，写0
4. intprot : 写PROT_READ|PROT_WRITE
5. intflags : 写MAP_SHARED
6. intfd : 要映射到进程空间的文件的文件描述符，由open 函数获取。

**返回值：**

1. 成功时，mmap返回用户空间文件映射内存区域的指针。
2. 失败时，返回MAP_FAILED （即(void*)-1 ，指向-1这个内存区域的指针，不是空指针），并设置errno以指示错误。

#### 2.2 munmap函数

首先munmap函数是一个符合POSIX标准的Linux系统调用函数。

既然mmap 会返回用户空间文件映射区域的指针，分配了内存空间，那么自然就需要在使用完毕后释放内存资源。

munmap 函数用于解除一个映射区域，释放内存资源。munmap是词组**"memory unmap map"**的缩写，表示解除内存映射区域。

当你通过mmap创建了一个文件或内存的映射之后，完成操作并不再需要使用这个映射时，应该使用munmap来释放这部分资源。

**此函数的声明如下：**

```c
#include <sys/mman.h>
int munmap(void *addr, size_t length);
```

**参数列表：**

1. void*addr ：映射区域的起始地址，即mmap函数的返回值。
2. size_tlength : 这是映射区域的长度，应与mmap 创建映射时使用的长度相同。

**返回值：**

1. 成功时，munmap 返回 0。
2. 失败时，返回 -1 并设置 errno 以指示错误原因。

#### 2.3 注意事项1：offset参数

内存映射通过mmap 函数将文件数据映射到进程的虚拟内存空间时，必须特别注意offset 参数的取值。

**简单来说，offset参数的取值必须是内存页大小（通常为4KB，即4096字节）的整数倍!!**

这是因为内存管理硬件（MMU）和操作系统内核管理虚拟内存和物理内存的最基本单元是页（一般是4KB），若offset这个映射起点没有对齐到页，将导致物理文件块中的数据和内存页的数据无法建立映射关系，从而导致映射失败！

比如按照下列方式调用mmap函数，将导致调用失败：

```c
void* p = mmap(NULL, 100, PROT_READ, MAP_SHARED, fd, 1000); // offset传参不能是1000!
```

这段代码执行一般会直接报错：

mmap : Invalid argument无效参数!

#### 2.4 注意事项2: 总线错误

**总线错误（Bus Error）**和**段错误（Segmentation Fault）**是Linux下系统编程当中，非常常见的两种报错。

段错误常见于非法的内存访问场景，比如解引用空指针、数组越界访问、解引用野指针/悬空指针、修改只读数据段等等。

**总线错误常见于CPU访问了非法的物理内存。**

在文件映射当中：

1. 如果某个文件是一个空文件，却要使用mmap映射非零个字节的内存空间时，就有可能产生总线错误。
2. 同样的，如果使用mmap要映射内存的字节数量大于文件实际大小时，对于超出文件实际大小的部分也有可能出现一个总线错误。

为了避免这种情况的发生，在必要的时候，在mmap 映射文件之前，可以先用ftruncate来调整文件的大小为希望映射区域的大小。

比如下列代码：

```c
// 从文件开头开始, 映射5个字节内容到内存当中
char *p = (char*)mmap(NULL, 5, PROT_WRITE,MAP_SHARED, fd, 0);
```

被文件映射的文件file，实际上是一个空文件，那么程序大概率就会产生一个总线错误。

#### 2.5 注意事项3：open的打开模式

调用mmap函数时，需要传入一个open 函数打开文件返回的文件描述符，open 函数需要传入一个flags 参数用于确定打开文件的读写模式。

而mmap函数也需要传入一个用于确定映射区域读写特性的prot 参数，同样都是代表读写模式的参数，它们之间有关联吗？

如果你仅仅想要创建一个只读的映射区域，从而实现读文件数据，那么你可以使用只读模式open文件，open函数的标志只需要加一个O_RDONLY 。

而如果你想要创建一个可写的映射区域，即希望能够修改文件数据，此时open函数可不可以用O_WRONLY 标志打开呢？

**当然是不行的。**

**mmap在创建映射区域时，总是需要将文件的初始内容加载到内存中，也就是说总需要能够读这个文件，若此时open的打开模式是只写，将会导致无法读文件，从而创建映射区域失败！**

所以：

1. 如果你想要创建一个只读的映射PROT_READ ，你可以以只读方式O_RDONLY open打开文件。
2. 如果你想创建一个可写的映射PROT_READ|PROT_WRITE ，你必须以读写方式O_RDWR open打开文件。

#### 2.6 简单的示例

这个简单的示例，只用来演示映射5个字节的文件内容到用户空间中，并演示了一下随机访问以及随机修改。

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 以读写模式打开文件
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    // 调整文件大小为5字节
    int ret = ftruncate(fd, 5);
    ERROR_CHECK(ret, -1, "ftruncate");

    // 将文件映射到内存中，映射大小为5字节，允许读写，共享映射
    char *p = (char *)mmap(NULL, 5, PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    // 随机访问文件内容
    for(int i = 0; i < 5; ++i){
       printf("%c", p[i]);
    }
    printf("\n");

    // 随机修改文件内容
    p[4] = 'O';

    printf("-----------------------------\n");
    // 再次随机访问文件内容
    for(int i = 0; i < 5; ++i){
       printf("%c", p[i]);
    }
    printf("\n");

    // 先开后关，后开先关
    // 先解除内存映射，再关闭文件描述符
    munmap(p, 5);
    close(fd);
    return 0;
}
```

文件映射会带来一个非常大的优势：

**由于你可以像操作内存一样操作文件内容，而内存是支持随机访问的，于是你也可以对文件的内容进行随机访问。**

**相比较而言read和write是顺序读写的，它们做不到随机访问。**

### 3. 文件映射的原理

我们先来对比一下read/write 读写文件，这两个系统调用函数会让数据在内核态的文件对象和用户态内存之间进行来回拷贝。

内核区域文件对象里的数据如何交互到磁盘呢？这个过程还需要借助内核区域的页缓存来实现。

**页缓存（Page Cache）**，也称为文件系统缓存，是操作系统用来缓存磁盘中文件内容的一部分内存。你可以认为文件对象和页缓存之间具有关联的关系，而页缓存会直接和硬盘数据交互。

一般来说，操作系统会选择一个合适策略并使用专门的硬件(比如DMA设备)来同步磁盘和页缓存当中的内容，这样 read/write 操作最终就会影响到磁盘。

而 mmap 的处理就更加简单粗暴，它直接把页缓存中的文件数据的一部分映射到用户态内存，这样用户在用户态当中的操作就直接对应页缓存的操作，从而更直接的操作文件数据。

![](Linux_assets/卷三%20文件系统编程/04_文件映射/img002.png)

*图3-1文件映射的原理-图*

从数据流向来分析这两种文件读写的过程：

1. read/write实现的文件操作：
   - a. **磁盘文件数据 --> 页缓存 --> 用户进程的buf数组。**
   - b. 这个过程包含一次磁盘IO操作，和一次将数据从用户态缓冲区复制拷贝到用户进程的buf数组中。
2. mmap实现的文件操作:
   - a. **磁盘文件数据 --> 页缓存。**
   - b. 通过系统调用实现将页缓存中的数据映射到用户空间的一段空间中，然后只需要读写用户映射内存区域就可以实现读写文件。
   - c. **整个过程只有一次磁盘IO操作，没有文件数据的拷贝复制操作！**

这样看上去的话， mmap 的效率总是会比 read/write 更加高，因为它**避免了一次数据在用户态和内核态之间的数据拷贝**。

但是考虑到 read/write 的特殊性质——它们总是顺序地而不是随机地访问磁盘文件的内容，所以操作系统以及硬件可以根据这个特点进行优化，比如文件内容的预读等等。

总之最终经过测试，我们的结论是：

1. **read/write 在顺序读写文件时的性能更好。**
2. **mmap 在随机访问文件的时候性能更好。**

当然，日常使用更多的还是read/write，因为顺序读写的场景会更多一些。

### 4. 将文件内容中的小写字母转换成大写保存

将文件内容中的小写字母转换成大写并保存，可以通过read/write或mmap方法实现。我们首先来看一下使用文件映射来实现。

#### 4.1 mmap实现

mmap实现，只需要打开文件并建立映射，然后使用循环遍历，并判断文件内容是否是小写字母，然后将小写字母转换成大写。

参考代码如下：

```c
int main(int argc, char *argv[]) {
    // ./to_upper filename
    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    // ftruncate调整文件大小
    int ret = ftruncate(fd, 12);
    ERROR_CHECK(ret, -1, "ftruncate");

    char *p = (char*)mmap(NULL, 12, PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    for (size_t i = 0; i < 12; ++i) {
       p[i] = toupper(p[i]);
    }
    munmap(p, 12);
    close(fd);
    return 0;
}
```

注意：toupper函数用于将小写字符转换成大写，使用它要包含头文件<ctype.h>可以看到这个代码是比较简洁的。

#### 4.2 read/write实现

read/write我们已经相对比较熟练了，整个过程我们的想法就是：

从头开始读文件，一边读到字符就将它转换成大写，然后直接写回去。

```c
int main(int argc, char *argv[]) {
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    // 直接读取字符二进制，方便进行检查和转换
    char ch;
    while(1){
       ssize_t sret = read(fd,&ch,1);
       if(sret == 0){
           break;
       }
       // 将字符转换成大写字母，然后直接写回文件
       ch = toupper(ch);
       write(fd, &ch,1);
    }
    return 0;
}
```

这里能够实现需求嘛？

显然是不可以的，为什么呢？

因为在read/write的过程中，始终存在一个内核态缓冲区指针来指示文件读写的位置，每read一下文件指针就要后移1位**(移动读写元素大小个字节)**，每write一下指针同样后移1位。

如果原文件数据是：howareyou ，那么最终的结果是：

hHwWaAeEyYuU那怎么办呢？

要想真正实现需求，显然在read之后，就需要将文件指针向文件的开头移动1位。

于是我们就需要一个能够移动文件指针位置的函数，这个函数就是lseek 函数。

#### 4.3 lseek函数

**lseek函数**基本上和**fseek函数**是一致的，只不过lseek函数用来移动内核态缓冲区的文件指针。

其函数声明如下：

```c
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```

**形式参数：**

1. fd : 文件描述符，它是通过open 系统调用打开文件时返回的。
2. offset : 根据参数whence 的设置，这个值会指示文件内的新位置。
   - a. 如果是0表示不偏移
   - b. 如果是负数表示向文件开头偏移
   - c. 如果是正数表示向文件末尾偏移
3. whence : 文件指针偏移的基准点，它可以取以下几个值：
   - a. SEEK_SET ：offset是相对于文件开头的偏移值
   - b. SEEK_CUR ：offset是相对于文件指针当前位置的偏移值
   - c. SEEK_END ：offset是相对于文件末尾的偏移值

**返回值：**

1. **成功**：返回从文件开始到当前文件指针位置的字节数。利用这个特点，我们可以来获取文件的大小。
2. **失败**：返回-1，并设置errno 以指示错误类型。

基于这个函数，我们把上述代码改为：

```c
while(1){
    ssize_t sret = read(fd,&ch,1);
    if(sret == 0){
       break;
    }
    // 将字符转换成大写字母，先左移1位文件指针，再将字符写回文件
    ch = toupper(ch);
    lseek(fd,-1,SEEK_CUR);
    write(fd, &ch,1);
}
```

这样我们就可以正常的将一个文件的内容，从小写转换成大写了。

### 5. 利用mmap实现大文件的复制

基于以上文件映射的原理，我们知道mmap对比read/write性能主要的提升点在于：

mmap减少一次数据在内核区域和用户空间的拷贝。

那么换句话说：

如果内核区域频繁需要和用户空间进行数据交互拷贝，那么mmap肯能就会具有比read/write更好的性能了。

那么什么场景下，数据需要频繁大量的进行拷贝呢？

答：文件很大，尤其是特别大时。比如几十G，几百G，甚至上T的文件复制，这个过程如果使用read/write那么性能就会被大量的数据拷贝所拖累。

**所以在处理大型文件时，mmap非常具有优势！也就是说除了随机访问修改文件内容外，大型文件的处理，也是mmap一个非常重要的应用场景。**

当然，要想完成一个大文件的复制，就不能再像上面的做法那样，把整个文件全部映射到内存中了：

因为几十G上T的文件很正常，但内存可没有这么大。

**所以：我们需要将src文件分段映射到内存中，然后再将src分段映射的内存数据拷贝到dest文件的内存映射中。**

这个过程需要以下前置知识点：

1. 文件分段，分几段？所以首先要知道文件的大小
2. 将src映射内存中的数据拷贝到dest映射的内存中，这里需要知道一种内存数据复制的手段

下面来讲解一下这两个问题。

#### 5.1 获取文件大小

获取文件大小，你已经学过一种办法了：利用lseek 函数跳到文件末尾，返回值就是文件的字节大小。

除此之外，你还可以利用函数：

1. stat函数，获取stat结构体，该结构体中就存有文件的大小信息。但是要注意文件名和文件路径名的区别。
2. **fstat函数，此函数的声明如下：**

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int fstat(int fd, struct stat *buf);
```

该函数是stat函数的变种，直接利用文件描述符来获取对应stat结构体对象。

你可以利用man2fstat 来学习一下fstat函数，当然除了参数从文件路径名变为了文件描述符，它的用法完全类似stat函数。

#### 5.2 内存复制函数

如果你希望将一块内存的数据完全复制到另一块，那么memcpy就能够实现这个功能。

memcpy 是一个标准 C 语言库函数（ISO-C），它就是词组“memory copy”的缩写。**用于从源内存地址拷贝 n 个字节到目标内存地址，是进行内存操作十分常用的一个函数。**

**此函数的声明如下：**

```c
#include <string.h>
void *memcpy(void *dest, const void *src, size_t n);
```

**形参列表：**

1. dest ：内存复制的目的地内存块指针
2. src ：内存复制的数据源内存块指针
3. n ：复制的字节数量。

返回值：memcpy函数返回一个指向目标内存区域dest的指针。

#### 5.3 思路分析

利用mmap实现大文件复制的思路如下：

1. 分别open源文件和目标文件，并计算源文件大小
2. ftruncate 设置目标文件大小，避免文件大小不足，映射失败。也能够提前预留空间，避免因空间不足而复制失败。
3. 记录文件复制时dest目标文件的偏移量offset，也就是已复制字节的数量。利用该变量进行循环复制源文件到目标文件。

#### 5.4 代码实现

参考的代码实现如下：

```c
#define BLOCK_SIZE (1024 * 1024 * 8) // 定义每次复制的块大小为8MB

long long current_time_millis() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; //转换为毫秒
}

int main(int argc, char* argv[]) {
    long t1 = current_time_millis();

    ARGS_CHECK(argc, 3);

    // 打开源文件
    int src_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open src");

    // 获取源文件的大小
    off_t src_size = lseek(src_fd, 0, SEEK_END); // off_t是一个64位有符号整数
// lseek(src_fd, 0, SEEK_SET); // 重置文件指针到文件开始，思考这一句需要吗？
```

```c

    // fstat的方式获取文件大小
    //struct stat sb;
    //int ret = fstat(src_fd, &sb);
    //ERROR_CHECK(ret, -1, "fstat");
    //off_t src_size = sb.st_size;

    // 打开目标文件
    int dest_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);//目标文件以读写模式打开
    ERROR_CHECK(dest_fd, -1, "open dest");

    // 为了避免目标文件大小不足映射失败
    // 且大文件复制提前占位，也能防止中途因空间不足复制失败
    int ret = ftruncate(dest_fd, src_size);
    ERROR_CHECK(ret, -1, "ftruncate");

    off_t bytes_copied = 0; // 记录已复制的字节数
    while (bytes_copied < src_size) {
       // 确定本次复制的字节大小
       off_t current_block_size = (bytes_copied + BLOCK_SIZE >src_size)?
           // 如果已复制字节数加上一次复制的块大小超过了源文件大小，说明这是最后一次映射复制，此时只需要映射剩余文件内容就可以了
           (src_size - bytes_copied) :
       // 不是最后一次映射复制，那就继续映射一整个块的大小
       BLOCK_SIZE;

       // 映射源文件
       void* srcp =
           mmap(NULL, current_block_size, PROT_READ, MAP_SHARED,src_fd,bytes_copied);
       ERROR_CHECK(srcp, MAP_FAILED, "mmap src");

       // 映射目标文件
       void* destp =
           mmap(NULL, current_block_size, PROT_READ | PROT_WRITE,MAP_SHARED,dest_fd,bytes_copied);
       ERROR_CHECK(destp, MAP_FAILED, "mmap dest");

       // 执行内存复制
       memcpy(destp, srcp, current_block_size);

       // 解除映射
       munmap(srcp, current_block_size);
       munmap(destp, current_block_size);

       // 更新已复制的字节数
       bytes_copied += current_block_size;
    }
    // 清理资源
    close(src_fd);
    close(dest_fd);
    long t2 = current_time_millis();
    printf("time = %ld\n", (t2 - t1));
    return 0;
}
```

写完这段代码后，你可以和之前写过的"read/write文件复制"、文件流复制进行对比，比较它们在不同场景当中的性能差异。

---

## 05 重定向

### 1. 文件流和文件描述符的关系

fopen函数实际上在运行的过程中也获取了文件的文件描述符，这一点非常容易验证，我们只需要：

1. 用fopen 库函数打开一个文件
2. 然后用write 系统调用函数，使用文件描述符3写文件数据

代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    // 利用fopen打开一个文件
    FILE *fp = fopen(argv[1], "w+");
    ERROR_CHECK(fp, NULL, "fopen");

    // fileno函数用于获取文件流当中的文件描述符
    write(3, "hello", 5);
    ERROR_CHECK(ret, -1, "write");
    close(fp);
    return 0;
}
```

**这个写操作是可以成功的，hello这个字符串将被写入到文件里。**

这说明：

1. fopen的底层就是系统调用函数open，所以它也有文件描述符的概念。
2. 文件描述符的分配是从3开始的，012则被标准流保留了。

当然上述代码中直接使用魔法数，还是不太好，我们可以利用fileno 函数（ISO-C标准C语言库函数）来获取已打开文件流的文件描述符。

该函数的声明如下：

```c
#include <stdio.h> // fileno 函数的声明在这个头文件中
int fileno(FILE *stream);
```

**参数需要传入一个已打开的文件流，返回值则是该文件流的文件描述符。**

这样我们就可以把代码改成下面的样子：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    FILE *fp = fopen(argv[1], "w+");
    ERROR_CHECK(fp, NULL, "fopen");

    // fileno函数用于获取文件流当中的文件描述符
    write(fileno(fp), "hello", 5); // 用fileno函数来获取文件描述符，代替魔法数字
    ERROR_CHECK(ret, -1, "write");
    close(fp);
    return 0;
}
```

好到这里，你已经了解文件流和文件描述符的关系，实际上我们可以更进一步的去了解FILE 这个结构体。

你仍然可以通过查看预处理后生成的.i 文件的方式，来查看FILE 结构体的定义，使用vim编辑器打开预处理后得到的文件。

然后直接输入下列**Vim搜索指令**回车查找这个结构体：

```c
/struct.*FILE
```

该结构体的内容大体如下所示：

```c
struct _IO_FILE{
    int _flags;
    char *_IO_read_ptr; // 当前读取位置的指针
    char *_IO_read_end;
    char *_IO_read_base;
    char *_IO_write_base;
    char *_IO_write_ptr; // 当前写入位置的指针
    char *_IO_write_end;
    char *_IO_buf_base;
    char *_IO_buf_end;
    char *_IO_save_base;
    char *_IO_backup_base;
    char *_IO_save_end;
    struct _IO_marker *_markers;
    struct _IO_FILE *_chain;

    int _fileno; // 文件描述符
    int _flags2;
    __off_t _old_offset;
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t *_lock;
    __off64_t _offset;
    struct _IO_codecvt *_codecvt;
    struct _IO_wide_data *_wide_data;
    struct _IO_FILE *_freeres_list;
    void *_freeres_buf;
    size_t __pad5;
    int _mode;
    char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof(size_t)];
};
```

也就是说，这个FILE结构体当中直接保存了底层open打开的文件对象的文件描述符，除此之外该结构体还会保存一些缓冲区状态等信息，这个模型如下图所示：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img001.png)

*图1-1文件流中的文件描述符-图*

了解上述信息后，既然文件描述符直接就是FILE结构体的成员，那么我们就可以直接通过结构体指针操作来获取这个文件描述符成员，代码如下所示：

```c
write(fp->_fileno, "hello", 5);
```

当然你可以思考一个问题：

这样的操作合适吗？

虽然这种操作在技术上可行，但这种做法破坏了封装性直接访问到了内部实现细节，而且还缺乏跨平台性(不同平台成员的名字可能不同)总之这不是一个好的做法，更好的做法是通过fileno 函数来获取文件描述符。

### 2. 标准流和重定向

在每个进程启动伊始，都会自动打开三个文件流，就是标准输入流stdin、标准输出流stdout、标准错误输出流stderr。

我们已经知道文件流的底层是文件描述符，那么这些标准流也是一样的，它们的底层分别对应文件描述符：

1. **标准输入流stdin：宏STDIN_FILENO，对应整数值0**
2. **标准输出流stdout：宏STDOUT_FILENO，对应整数值1**
3. **标准错误流stderr：宏STDERR_FILENO，对应整数值2**

我们可以用下列代码来输出它们的文件描述符：

```c
int main(void){
    printf("stdin = %d\n", fileno(stdin));
    printf("stdout = %d\n", fileno(stdout));
    printf("stderr = %d\n", fileno(stderr));
    return 0;
}
```

我们已经知道文件流的底层结构体对象中会存储文件描述符，所以每次程序启动，这三个标准流的内存空间都固定存储这三个文件描述符。

如下图所示：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img002.png)

*图2-1标准流的文件对象-示意图*

这三个标准流由C标准库来管理维护，程序员只需要使用它们就可以，不需要考虑它们的内存管理问题。

#### 2.1 close和重定向的原理

由于用户空间的标准流结构体对象中固定存储了文件描述符，那么假如我们进行下面的操作：

1. 先使用printf 函数向终端输出一句话。**（重定向标准输出时，都建议先这么做一下）**
2. 然后close文件描述符1(stdout文件对象的描述符)
3. 最后重新open一个新的文件，再次调用printf函数打印一句话。

也就是说，代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 先向终端输出一句话
    printf("两情若是长久时!\n");
    close(STDOUT_FILENO); // 关闭文件描述符1
    // 以读写模式打开一个文件
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    // 再利用printf函数向标准输出中输出
    printf("fd = %d\n", fd);
    printf("又岂在朝朝暮暮!\n");
    return 0;
}
```

最终的输出效果是：

屏幕上输出：两情若是长久时!

输出到文件：又岂在朝朝暮暮!

为什么会这样呢？

首先，我们要理解一下close的原理：

close的作用是关闭了一个文件描述符，只有等到某个文件对象的全部文件描述符都被关闭了，才会考虑释放文件对象**（引用计数法）**。

**但标准流的文件对象，即便所有文件描述符都被关闭了，但一般操作系统也会继续保留它的文件对象（保留的目的当然是等待重新为标准流文件对象分配文件描述符）。**

然后，我们还要理解一下open的原理：

open的作用是打开一个文件，内核会创建文件对象，并分配一个当下**可用的最小文件描述符**，返还给用户进程。

基于这样的原理，我们可以用下图来描绘这个过程：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img003.png)

*图2.1-1重定向stdout-原理图*

我们之前在给大家讲shell指令中的重定向符号时，也是一直在强调：

**重定向不是断开/更改用户进程和标准流缓冲区的连接，而是断开/更改标准流缓冲区到外部设备(屏幕、磁盘等)的连接。**当然，在这里我们更进一步的理解了重定向。

思考：

既然能这样重定向标准输出，那么能不能重定向标准输入呢？

参考下面代码：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    close(STDIN_FILENO); // 关闭标准输入流的文件描述符
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    // 此时文件描述符0已经分配给了新打开的一个文件, 也就是说标准输入被重定向到从文件中读数据
    int a;
    scanf("%d",&a); // 把文件中的第一个数字读出来
    printf("a = %d\n", a);
    return 0;
}
```

原理和上面是一样的。但是我们要注意：**实际应用中几乎不会重定向标准输入，所以我们下面的讲解都会基于标准输出的重定向。**

#### 2.2 dup函数

假如我们想要实现重定向功能，比起直接关闭文件描述符然后再open文件，一个更好的办法是使用dup 函数，这里我们就介绍一下这个函数。

**首先dup这个函数名，缩写自单词"duplicate"，意为复制。**

dup是一个系统调用函数，它的作用就是复制文件描述符。当你使用dup 函数通过复制已存在的文件描述符，创建一个新的文件描述符时，这个新文件描述符和原始文件描述符就指向了同一个文件对象。

该函数的声明如下：

```c
#include <unistd.h>
int dup(int oldfd);
```

**形式参数：**oldfd ：要被复制的文件描述符。

**返回值：**

1. **成功**：返回新的文件描述符，新文件描述符是当下能够分配的文件描述符的最小值。**注意：新的文件描述符和被复制的文件描述符肯定不是同一个整数！但它们会指向同一个文件对象！**
2. **失败**：返回 -1，并且设置errno的值以表示错误原因。

这个过程如下图所示：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img004.png)

*图2.2-1dup函数原理-图*

下面我们先简单演示一下这个函数的调用，也就是复制文件描述符：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 被复制的文件描述符
    int old_fd = open(argv[1], O_RDWR);
    ERROR_CHECK(old_fd, -1, "open");
    printf("old_fd = %d\n", old_fd); // 3

    // 复制后得到的新文件描述符
    int new_fd = dup(oldfd);
    ERROR_CHECK(new_fd, -1, "dup");
    printf("new_fd = %d\n", new_fd); // 4

    // 最终会把helloworld写入同一文件
    write(old_fd,"Hello", 5);
    write(new_fd,"World", 5);

    // 关闭文件描述符
    close(new_fd);
    close(old_fd);
    return 0;
}
```

**首先我们需要注意：这里打印的两个新旧文件描述符，必然是不一样的。这就好比两个指针指向同一个对象，但这两个指针变量本身的地址肯定是不同的。**

其次dup复制文件描述符的过程，既然可以类比指针指向同一对象，那么使用任一文件描述符修改文件信息，这个修改对于所有文件描述符都是同步的。

**并且在这个过程中两个文件描述符，共享同一个文件对象的读写偏移量，也就是共享读写的位置。（因为它们本来就是同一个文件对象）**

于是最终文件的写入内容是：

HelloWorld最后思考一个问题：

close一个文件描述符，内核区域的文件对象会被释放资源吗？

当然不会，某个文件对象的所有文件描述符都被关闭后，才会释放此文件对象！

#### 2.3 利用dup函数重定向stdout

下面我们来使用dup函数来实现一些常见的，对stdout标准输出的重定向。

在这个过程中，大家不要过于注重代码，也不要尝试一上来就盯着代码来分析重定向的过程。而是**先搞定模型，然后根据模型写代码！**

下图就展示了一个，利用dup函数展示重定向stdout的过程：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img005.png)

*图2.3-1重定向stdout-图1*

这个过程用文字描述是：

1. 第一步是先open一个file文件，此时分配一个fd文件描述符（一般是3）
2. 接下来第二步，关闭文件描述符**——1（STDOUT_FILENO）**
3. 最后dup复制文件描述符fd（此时分配最小可用的文件描述符，先就是分配1，这样标准输出就被重定向到文件file中了）
4. 任何向stdout的输出操作都会最终输出到文件file中。

整个过程的实现参考代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    // 先使用printf函数向终端输出一句话
    printf("我们的爱错过就不再回来!\n");
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    close(STDOUT_FILENO);
    // 复制fp文件描述符,但此时给它分配的文件描述符是1，完成重定向操作
    int fd_cp = dup(fd);
    // 下面的输出都将输出到文件里
    printf("fd = %d\n", fd);
    printf("fd_cp = %d\n", fd_cp);
    printf("直到现在我还默默得等待!\n");

       fflush(stdout); // 在关闭文件描述符释放文件对象之前，刷新一下标准输出缓冲区，避免数据还留在缓冲区中导致数据丢失
    // 关闭文件描述符
    close(fd);
    close(fd_cp);
    return 0;
}
```

结合图来一起分析这个过程，还是不困难的。

注意：这里仍然建议先使用printf 函数向终端输出一句话。

#### 2.4 dup2函数

dup2函数和dup一样，都是用来复制文件描述符的系统调用函数。**dup2函数的唯一区别是可以自己指定复制后得到的文件描述符的数字。**

它的函数声明如下：

```c
#include <unistd.h>
int dup2(int oldfd, int newfd);
```

**形参列表：**

1. oldfd : 要被复制的文件描述符，需要是一个已经打开的正在使用的文件描述符。
2. newfd : 复制后的新文件描述符，此时需要考虑以下情况：
   - a. 如果newfd已经被程序使用，则dup2会首先关闭文件描述符newfd ，然

后再将oldfd的文件描述符复制到newfd 。最终的效果是：newfd 和oldfd 都指向原本oldfd 指向的文件对象。

   - b. 如果newfd还未被程序使用，那么正常将oldfd的文件描述符复制到

newfd 。最终的效果仍然是：newfd 和oldfd 都指向原本oldfd 指向的文件对象。

**返回值：**

1. **成功**：返回新的文件描述符（即newfd的值）。
2. **失败**：返回 -1，并且设置errno的值以表示错误原因。比较常见的错误就是：传入的oldfd是一个无效的文件描述符（即它不指向任何打开的文件），那么dup2将不会执行复制操作，并且会返回错误。在这种情况下，即使newfd是有效的，dup2也不会关闭它。

所以这个函数的行为就可以描述成：

dup2同样用于复制文件描述符，和dup 一样都可以使得两个文件描述符指向同一个文件对象。但它和dup函数的区别是：

1. dup2允许指定新文件描述符的具体数值，也就是多了一个参数newfd
2. **当newfd这个文件描述符存在时，dup2会先close这个文件描述符，然后再让newfd和oldfd两个文件描述符都指向oldfd的文件对象。**
3. 总之，在正常的情况下，dup2总能保证得到一个指向oldfd文件对象的文件描述符——newfd

#### 2.5 利用dup2函数重定向stdout

利用dup2函数重定向stdout非常简单，如果日常的需求就是简单的重定向stdout，那么推荐选择使用dup2 函数。

这个过程参考下图就可以了：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img006.png)

*图2.5-1重定向stdout-图2*

总共也就只需要两步就可以完成了：

1. 第一步，先open一个新文件file，分配一个fd文件描述符（此时一般就是3）
2. 直接调用dup2函数：dup(fd,STDOUT_FILENO)
   - a. 此时的操作是先关闭stdout的文件描述符——1
   - b. 再让文件描述符1指向fd文件描述符指向的文件，这样就完成了重定向到文件的操作。

参考代码实现如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    printf("表示从一楼到四楼的距离!\n"); // 先向终端输出一句话
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    // 关闭标准输出，再让文件描述符1指向fd文件对象，也就是重定向stdout到文件
    int fd_cp = dup2(fd, STDOUT_FILENO);
    // 下面的输出都将输出到文件里
    printf("fd = %d\n", fd);
    printf("fd_cp = %d\n", fd_cp);
    printf("原来只有三年!\n");

    fflush(stdout); // 在关闭文件描述符释放文件对象之前，刷新一下标准输出缓冲区，避免数据还留在缓冲区中导致数据丢失
    // 关闭文件描述符
    close(fd);
    close(fd_cp);
    return 0;
}
```

利用dup2函数相当于将关闭某个文件描述符，和复制文件描述符合并在一起了，代码会变得更简洁高效。

注意：这里仍然建议先使用printf 函数向终端输出一句话。

### 3. 结合dup和dup2实现"反复横跳"

如果我的需求是：

先在屏幕上展示一行，再在文件中输出一行，再在屏幕上展示一行，再在文件中输出一行....使得标准输出这样**反复横跳**应该如何实现呢？

这个需求实现起来，其实也并不困难，只需要结合dup和dup2一起就可以了。

模型图可以参考下图：

![](Linux_assets/卷三%20文件系统编程/05_重定向/img007.png)

*图3-1重定向stdout-图3*

整个过程是：

1. 第一步，先open一个新文件，分配一个fd文件描述符（一般就是3）
2. 第二步，由于要反复横跳，所以需要备份一下stdout文件对象。
   - a. 比如设置一个整数值intstdout_bak=7
   - b. 接下来可以使用dup2(STDOUT_FILENO,stdout_bak) ，通过这个函数调用完成对标准输入的备份。
3. 第三步，直接dup2重定向stdout到文件，代码是：dup2(fd,STDOUT_FILENO)
4. 第四步，将文件描述符1重新指向stdout文件对象，使得标准输出回归终端设备，代码是：dup2(stdout_bak,STDOUT_FILENO)
5. ....

整个过程的参考代码如下：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    printf("叹一句当时\n"); // 先向终端输出一句话
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    int stdout_bak = 7;
    dup2(STDOUT_FILENO, stdout_bak); // 备份stdout文件对象，现在文件描述符7指向它

    // 重定向标准输出到文件
    dup2(fd, STDOUT_FILENO);
    printf("只道是\n"); // 这一句话将输出到文件中

    // 将文件描述符1重新指向stdout文件对象
    dup2(stdout_bak,STDOUT_FILENO);
    printf("寻常!\n"); // 这一句话将输出到终端里
    // 可以继续进行重定向...回归...

    fflush(stdout); // 在关闭文件描述符释放文件对象之前，刷新一下标准输出缓冲区，避免数据还留在缓冲区中导致数据丢失
    // 关闭文件描述符
    close(fd);
    close(stdout_bak);
    return 0;
}
```

这个实现起来实际上也并不困难。

注意：这里仍然建议先使用printf 函数向终端输出一句话。

### 4. 扩展：重定向stdout过程中的缓冲区行为

在上述重定向stdout标准输出到文件的代码中，我们始终在重定向之前向终端输出了一句话，这是为什么呢？

为了解答这个疑惑，我们直接来看一段代码：

```c
int main(int argc, char *argv[]){
 ARGS_CHECK(argc, 2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open");

 //先备份标准输出的文件描述符
    int temp=dup(STDOUT_FILENO);
    //将标准输出重定向指向文件
    dup2(fd, STDOUT_FILENO);
    printf("How are you?\n");
    //将标准输出重新终端
    dup2(temp, STDOUT_FILENO);
    printf("I'm fine, and you?\n");
    //再将标准输出重定向到文件
    dup2(fd, STDOUT_FILENO);
    printf("Me too.\n");

 close(fd);
    return 0;
}
```

按照我们的理解，这段代码将使得标准输出在终端和文件之间"横跳"：

1. "how are u\n"将在文件中输出
2. "I'm fine, and you?\n"将在终端打印
3. "Me too.\n"又将在文件中输出

**但实际上，这三段文本都将输出到文件，这是为什么呢？**

这就涉及到操作系统、C 标准库对标准输出缓冲区模式的管理了，第一次使用 stdout 时的上下文（它指向的是终端还是文件）将决定 stdout 的缓冲区刷新机制，并且在整个进程生命周期，这个刷新机制将默认保持不变：

1. 如果第一次使用stdout时它指向一个终端（比如用printf），此时缓冲区就是行缓冲的。
2. 如果第一次使用时stdout被重定向到文件或其他非终端设备，缓冲区就变成了满缓冲区，这意味着缓冲区会积累输出直到满了或者手动刷新。

比如上面的代码：

虽然重定向都成功了，但由于stdout缓冲区的性质是满缓冲区，所以只能在最终进程结束时，刷新缓冲区，将所有内容全部输出到文件中。

尝试将代码改成下面的样子：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open");

    //先备份标准输出的文件描述符
    int temp=dup(STDOUT_FILENO);
    //将标准输出重定向为文件描述符对应的文件
    dup2(fd, STDOUT_FILENO);
    printf("How are you?\n");
    // 手动刷新缓冲区
    fflush(stdout);
    //将原来的标准输出文件描述符恢复给标准输出
    dup2(temp, STDOUT_FILENO);
    printf("I'm fine, and you?\n");
    // 手动刷新缓冲区
    fflush(stdout);

    //再将文件的文件描述符赋给标准输出
    dup2(fd, STDOUT_FILENO);
    printf("Me too.\n");
    // 手动刷新缓冲区
    fflush(stdout);

    close(fd);
    return 0;
}
```

即每一个printf输出后面都加上一个手动刷新缓冲区的fflush 操作，此时程序的行为将符合大家的预期：

1. "how are u\n"将在文件中输出
2. "I'm fine, and you?\n"将在终端打印
3. "Me too.\n"又将在文件中输出

再来看一段代码：

```c
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open");

    // 先printf输出一句话
    printf("start.\n");
    //先备份标准输出的文件描述符
    int temp=dup(STDOUT_FILENO);
    //将标准输出重定向指向文件
    dup2(fd, STDOUT_FILENO);
    printf("How are you?\n");
    //将标准输出重新终端
    dup2(temp, STDOUT_FILENO);
    printf("I'm fine, and you?\n");
    //再将标准输出重定向到文件
    dup2(fd, STDOUT_FILENO);
    printf("Me too.\n");

    close(fd);
    return 0;
}
```

这段代码和第一段代码，只有一个区别，在程序一开头就使用printf 输出一句话，于是**标准输出的缓冲区就是一个行缓冲区**。

此时程序的行为将符合大家的预期：

1. 终端显示：start、I'm fine, and you
2. 文件中：How are you、Me too

那么再改一下代码：

```c
int main(int argc, char *argv[]){
   ARGS_CHECK(argc, 2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open");

    // 先printf输出一句话
    printf("start.");
    //先备份标准输出的文件描述符
    int temp=dup(STDOUT_FILENO);
    //将标准输出重定向指向文件
    dup2(fd, STDOUT_FILENO);
    printf("How are you?");
    //将标准输出重新终端
    dup2(temp, STDOUT_FILENO);
    printf("I'm fine, and you?\n");
    //再将标准输出重定向到文件
    dup2(fd, STDOUT_FILENO);
    printf("Me too.\n");

    close(fd);
    return 0;
}
```

注意第一个换行符的位置：在printf("I'mfine,andyou?\n"); 这一行此时程序的输出结果是什么？

答：

1. 终端输出：前三句
2. 文件内容：最后一句

以上，你懂了吗？

---

## 06 有名管道

### 1. 管道概述

Linux中的**命名管道 (named pipe)**是一种特殊类型的文件，又称为**FIFO**。

它外的外在表现好像是一个磁盘文件，实际上本质只是一个数据流或缓冲区。

**管道允许一个进程的输出直接作为另一个进程的输入，在Linux系统中是一种重要的实现进程间通信（IPC）的机制。**

除了命名管道以外，还有一中用于进程间通信的匿名管道。(后面再讲)命名管道创建的管道文件不是普通的磁盘文件。

这个文件本身不存储数据（它不占用磁盘空间来存储长期数据），而是作为一个通信接口存在 (它是一个文件系统标识, 方便我们以**操作文件系统的方式**读写管道的缓冲区)。

命名管道, 从一端读取数据, 从另一端写入数据。使用命名管道, 必须读端写端同时打开, 无法单独去打开读端或者写端。

命名管道是一种半双工通信, 但是我们一般把它当作单工管道使用( 即: 一个进程只打开它的写端写数据, 另一个进程只打开它的读端读数据)。

当管道缓冲区无数据, 读管道的操作将被阻塞。

当管道缓冲区写满, 写管道将被阻塞。

在管道操作中, 如果写端关闭, 读端可以继续读取缓冲区的剩余数据, 如果缓冲区没有剩余数据, 读取操作(read)直接返回0。

在管道操作中, 如果读端关闭, 写端继续向管道中写数据的时候, 会导致写操作(write)触发SIGPIPE信号, 进而导致进程异常终止。

一般我们会使用两根管道构建两个进程间的全双工通信。

### 2. 创建管道文件

命名管道创建的管道文件不是普通的磁盘文件, 所以创建的方式也和普通文件创建方式不同。

1. 通过mkfifoname.pipe 创建管道文件
2. 不允许使用vim打开管道文件

![](Linux_assets/卷三%20文件系统编程/06_有名管道/img001.png)

*图2-1建立管道文件-演示图*

### 3. 使用管道

**直接使用一个管道：**

1. 假设先创建一个管道: mkfifo1.pipe
2. 通过echohello>1.pipe 向管道缓冲区写入数据, 我们会发现这个写入操作会直接写阻塞; 这是因为使用命名管道 , 是从一端读取数据, 从另一端写入数据, 必须读端写端同时打开, 无法单独去打开读端或者写端。
3. 当我们另开一个窗口(新的进程)使用cat1.pipe 读取管道数据, 相当于开启了管道的读端, 这可以使之前打开的写端正常写入, 从阻塞态变为非阻塞态写入; 等写端写入完成之后, 读端读出写入数据。

![](Linux_assets/卷三%20文件系统编程/06_有名管道/img002.png)

*图3-1使用管道-演示图*

**在代码中使用管道**示例代码：写端

```c
int main(int argc,char*argv[]){
    int pipe_fd = open("1.pipe", O_WRONLY);
    while(1){
       write(pipe_fd, "hello", 5);
       printf("write once \n");
       sleep(5);
    }
    return 0;
}
```

演示代码：读端

```c

int main(int argc,char*argv[]){
    int pipe_fd = open("1.pipe", O_RDONLY);
    while(1){
       char buf[60] = {0};
       read(pipe_fd, buf, sizeof(buf));
       printf("read : %s\n", buf);
    }
    return 0;
}
```

以上。

### 4. 通信的方式

在通信系统中，根据数据传输的方向和方式，通信可以被分为单工、双工和半双工三种模式

| 通信方式 | 描述 |
|---|---|
| 单工通信 | 永远只能由一方向另一方发送数据 |
| 半双工通信 | 双方都可以收发数据，但是在同一时刻只能一端发另一端收 |
| 全双工通信 | 两端可以同时收发数据 |

演示代码: 命名管道是半双工通信

```c
int main(int argc,char*argv[]){
    int pipe_fd = open("1.pipe", O_RDWR);
    while(1){
       write(pipe_fd, "hello", 5);
       printf("write \n");
       sleep(5);
       char buf[10] = {0};
       read(pipe_fd, buf, sizeof(buf));
       printf("read:%s \n", buf);
    }
    return 0;
}
```

以上。

### 5. 管道写阻塞

假设我们通过pipe实现一个通信, 写端一直在写, 读端不读, 会发生什么?

演示代码:写端

```c
int main(int argc,char*argv[]){
    int fd_write = open("1.pipe", O_WRONLY);

    char buf[4096] = {0};
    int times = 0;
    while(1){
       write(fd_write, buf, sizeof(buf));
       printf("write times: %d \n", ++times);
    }

    close(fd_write);
    return 0;
}
```

演示代码:读端

```c

int main(int argc,char*argv[]){
    int fd_read = open("1.pipe", O_RDONLY);

    sleep(10);
    char buf[4096] = {0};
    while(1){
       read(fd_read, buf, sizeof(buf));
       printf("read \n");
       sleep(2);
    }

    close(fd_read);
    return 0;
}
```

假设我们通过pipe实现一个通信, 写端一直在写, 读端不读, 会发生什么? 会发生写阻塞;

因为管道的大小是有限制的。

管道的真实可用缓冲区的大小取决于单个**单个管道缓冲区大小**和**管道缓冲区的数目**共同决定。而且在不同的操作系统设置是不一样的。

```c
ps:闲聊 (下面讨论按标准情况, 忽略非标准情况)
// 假设以我们上课使用系统为例:
// 我们通过查看ulimit -a 中的pipe size为 8*512=4096字节
// 我们也可以从操作系统的源码中查看, 管道缓冲区个数为16
// 假设我们创建一个1.pipe的管道, 我们在不读的情况下可以连续写入16个4096, 即可把管道写满,再试图写就会写阻塞;写满之后,假设又读出4096字节,我们可以再接着写4096个字节
// 假设我们创建一个1.pipe的管道, 我们在不读的情况下, open其两次, 得到同一个管道的两个管道文件描述符,按照每次4096字节写入管道;你会发现两个文件加起来最终还是16次写入
// 假设我们创建一个1.pipe和2.pipe的管道, 我们在不读的情况下, 分别open这两个管道,得到两个管道文件的文件描述符,按照每次4096字节写入管道;你会发现两个文件每个管道都是16次写入

// PIPE_BUF: 小于PIPE_BUF的写入应该是原子操作(不可被中断) (man 7 pipe)。
/usr/src/linux-source-4.15.0/linux-source-4.15.0/include/linux/pipe_fs_i.h
/usr/src/linux-source-4.15.0/linux-source-4.15.0/include/uapi/linux/limits.h
```

总结: Applications should not rely on a particular capacity: an application should be designed so that a reading process consumes data as soon as it is available, so that a writing process does not remain blocked.(应用程序不应依赖于特定的容量：应用程序的设计应确保读取过程在数据可用时立即消耗数据，这样写入过程就不会被阻止)

![](Linux_assets/卷三%20文件系统编程/06_有名管道/img003.png)

*图5-1image-20250220212232450*

以上。

### 6. 管道构建双工通信

**实现一份代码, 让两个程序基于基于pipe管道的双工通信。**工作流程图如下:

![](Linux_assets/卷三%20文件系统编程/06_有名管道/img004.png)

**创建两个pipe文件:**

```c
mkfifo 1.pipe
mkfifo 2.pipe
```

![](Linux_assets/卷三%20文件系统编程/06_有名管道/img005.png)

*图6-2image-20250220212312069*

EgCode: User_A

```c
int main(int argc,char*argv[]){
int fd_write = open("1.pipe", O_WRONLY);
int fd_read = open("2.pipe", O_RDONLY);

while(1){
   // 读取标准输入: 通过1.pipe发送给User_B
   char buf[60];
   bzero(buf, sizeof(buf));
   int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
   if(read_stdin == 0){
      // 用户按下ctrl+d;终止标准输入
      break;
   }
   write(fd_write, buf, sizeof(buf));

   bzero(buf, sizeof(buf));
   // 读取2.pipe: 打印到标准输出
   int read_num = read(fd_read, buf, sizeof(buf));
   if(read_num == 0){
      printf("对方断开链接 \n");
      break;
   }
   printf("UserB: %s ", buf);
}

close(fd_write);
close(fd_read);
return 0;
}
```

EgCode: User_B

```c

int main(int argc,char*argv[]){
int fd_read = open("1.pipe", O_RDONLY);
int fd_write = open("2.pipe", O_WRONLY);

while(1){
   char buf[60];
   bzero(buf, sizeof(buf));
   // 读取1.pipe: 打印到标准输出
   int read_num = read(fd_read, buf, sizeof(buf));
   if(read_num == 0){
      printf("对方断开链接 \n");
      break;
   }
   printf("UserA: %s ", buf);

   bzero(buf, sizeof(buf));
   // 读取标准输入: 通过2.pipe发送给User_A
   int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
   if(read_stdin == 0){
      // 用户按下ctrl+d; 输入文件终止符; 终止标准输入; read返回0
      break;
   }
   write(fd_write, buf, sizeof(buf));

}

close(fd_write);
close(fd_read);
return 0;
}
```

在上面的代码过程中, 我们需要注意一些问题:

1. 1.pipe和2.pipe在A和B中的打开顺序, 有可能导致产生竞争条件导致死锁。
2. 上面的对答流程属于一问一答式的模式, 需要由A发起聊天。连续发送多条数据对面无法立即显示。

上面流程明显不符合实际生活对话流程, 该怎么改进这个过程?

---

## 07 IO多路复用

### 1. IO多路复用概述

上面一问一答式的对话流程, 是因为在上面代码执行中, 它是一个串行执行的逻辑, 如果模拟现实情况, 我们更希望要做的是怎么把这个串行逻辑改为并行逻辑。这里我们就可以用到IO多路复用技术。

![](Linux_assets/卷三%20文件系统编程/07_IO多路复用/img001.png)

*图1-1image-20250220212537482*

**IO多路复用**操作系统允许单个进程或线程同时**监视**多个文件描述符的一种技术。

当其中的一个或多个文件状态变为非阻塞状态（**例如: 文件由阻塞态, 变得可读、可写或有异常待处理**）时，该进程或线程会收到一个对应通知。

而我们的逻辑中收到这个通知, 就可以根据对应变得可读的文件描述符处理是读取标准输入, 还是接收对端数据, 还是都处理。

这样, 就允许程序同时处理多个文件就绪, 或者称为**谁就绪就处理谁**，而不是只能按照固定处理顺序处理每一个任务，从而提高效率。

**select**是实现IO多路复用的一种方式。**(其他的还有poll, epoll)**

### 2. Select

**select的最基本的原理, 就是把要监视的文件描述符, 构建一个文件描述符监听集合。**

**这个集合交给select, select促使操作系统内核, 通过轮询的方式监听这个文件描述符集合。**

**直到监听集合中, 至少有一个文件按照条件就绪(条件:预设的监听是读就绪OR写就绪...), 这一次的select监听宣告结束, 并携带就绪的文件描述符集合返回, 继续执行用户书写的代码逻辑。**

#### 2.1 Select函数

select是一个在Unix系统中就已经出现了的, 传统的IO多路复用接口。(man select)

```c
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
// synchronous I/O multiplexing
// 同步 I/O 多路复用
int select(
    int nfds, // 被监听文件描述符集合最大的文件描述符+1 (最大的文件描述符+1)
    fd_set *readfds, // 要监听的: 读操作文件描述符集合
    fd_set *writefds, // 要监听的: 写操作文件描述符集合
    fd_set *exceptfds, // 要监听的: 异常操作文件描述符集合
    struct timeval *timeout // 监听时候的阻塞时间:NULL代表一直等待直到指定就绪,0代表不等待检查文件描述符立即返回
);
// 返回值: 正数表示就绪的文件描述符数量; 0表示监听超时; -1表示是失败
// 构建监听文件描述符:
void FD_ZERO(fd_set *set); // 初始化文件描述符集合
void FD_SET(int fd, fd_set *set); // 向文件描述符集合添加要监听的文件描述符
void FD_CLR(int fd, fd_set *set); // 从文件描述符集合移除一个文件描述符,不再监听移除项
int FD_ISSET(int fd, fd_set *set); // 判断某个文件描述符, 是否在文件描述符集合中
```

调用select之后, select会**阻塞进程**, 去监听设置的文件描述符状态; 直到监听到至少一个文件描述符就绪, select**解除阻塞状**态, 并携带就绪的文件描述符返回。

监听集合和监听完毕之后携带的就绪集合, 是同一个fd_set存储。(传入传出参数, 非const指针) (意味着在循环中, 每次都要重置监听集合set)

#### 2.2 代码示例

EgCode:

```c
int main(int argc,char*argv[]){
    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    char buf[60];
    // 监听集合
    fd_set set;

    while(1){
       // 初始化集合
       FD_ZERO(&set);
       // 添加要监听的文件描述符
       FD_SET(STDIN_FILENO, &set);
       FD_SET(fd_read, &set);

       // 调用select: 监听就绪
       int res_select = select(10, &set, NULL,NULL, NULL);

       if(FD_ISSET(fd_read, &set)){
           bzero(buf, sizeof(buf));
           int read_num = read(fd_read, buf, sizeof(buf));
           if(read_num == 0){
               printf("对方断开链接 \n");
               break;
           }
           printf("UserA: %s", buf);
       }
       if(FD_ISSET(STDIN_FILENO, &set)){
           bzero(buf, sizeof(buf));
           int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
           if(read_stdin == 0){
               // 用户按下ctrl+d; 输入文件终止符; 终止标准输入; read返回0
               break;
           }
           write(fd_write, buf, sizeof(buf));
       }
    }

    close(fd_write);
    close(fd_read);
    return 0;
}
```

UserA 和UserB代码除了打开pipe的顺序, 和确定pipe的读端写端以外, 其余的通信逻辑是相同的。

#### 2.3 超时设置

我们可以在select函数中设置指定的时间, 来限制select的阻塞时间。

```c
int select(
    int nfds, // 被监听文件描述符集合最大的文件描述符+1 (最大的文件描述符+1)
    fd_set *readfds, // 要监听的: 读操作文件描述符集合
    fd_set *writefds, // 要监听的: 写操作文件描述符集合
    fd_set *exceptfds, // 要监听的: 异常操作文件描述符集合
    struct timeval *timeout // 监听时候的阻塞时间:NULL代表一直等待直到指定就绪,0代表不等待检查文件描述符立即返回
);
// 返回值: 正数表示就绪的文件描述符数量; 0表示监听超时; -1表示是失败
// (man select )
struct timeval {
    long tv_sec; // seconds: 秒
    long tv_usec; // microseconds: 微秒 (1秒 = 1000 000微秒)
};
```

如果设置了阻塞时间, 可以通过select的返回值确定到底之超时返回,还是就绪返回。

timeout会随着select的阻塞时间而递减。如果因为就绪事件导致select返回, timeout留下的是剩余时间。

```c
int main(int argc,char*argv[]){
    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    char buf[60];
    // 监听集合
    fd_set set;

    while(1){
       // 初始化集合
       FD_ZERO(&set);
       // 添加要监听的文件描述符
       FD_SET(STDIN_FILENO, &set);
       FD_SET(fd_read, &set);

       struct timeval time_val;
       time_val.tv_sec = 10;
       time_val.tv_usec = 0;

       // 调用select: 监听就绪
       int res_select = select(10, &set, NULL,NULL, &time_val);

       // 打印剩余时间
       printf("tv_sec: %ld \n", time_val.tv_sec);

       if(FD_ISSET(fd_read, &set)){
           bzero(buf, sizeof(buf));
           int read_num = read(fd_read, buf, sizeof(buf));
           if(read_num == 0){
               printf("对方断开链接 \n");
               break;
           }
           printf("UserA: %s", buf);
       }
       if(FD_ISSET(STDIN_FILENO, &set)){
           bzero(buf, sizeof(buf));
           int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
           if(read_stdin == 0){
               // 用户按下ctrl+d; 输入文件终止符; 终止标准输入; read返回0
               break;
           }
           write(fd_write, buf, sizeof(buf));
       }
    }
    close(fd_write);
    close(fd_read);
    return 0;
}
```

#### 2.4 练习

**设计一份代码:当UserA用户10秒未发生信息, UserB关闭连接。**

```c
int main(int argc,char*argv[]){
    int fd_read = open("1.pipe", O_RDONLY);
    int fd_write = open("2.pipe", O_WRONLY);
    char buf[60];

    fd_set set;

    struct timeval time_val;
    time_val.tv_sec = 10;
    time_val.tv_usec = 0;
    while(1){
       FD_ZERO(&set);
       FD_SET(STDIN_FILENO, &set);
       FD_SET(fd_read, &set);

       int res_select = select(10, &set, NULL, NULL, &time_val);

       if(FD_ISSET(fd_read, &set)){
           bzero(buf, sizeof(buf));
           int read_num = read(fd_read, buf, sizeof(buf));
           if(read_num == 0){
               printf("对方断开链接 \n");
               break;
           }
           printf("UserA: %s", buf);

           time_val.tv_sec = 10;
           time_val.tv_usec = 0;
       }else{
           if(time_val.tv_sec <= 0){
               printf("对方十秒未说话 \n");
               break;
           }
       }
       if(FD_ISSET(STDIN_FILENO, &set)){
           bzero(buf, sizeof(buf));
           int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
           if(read_stdin == 0){
               // 用户按下ctrl+d; 输入文件终止符; 终止标准输入; read返回0
               break;
           }
           write(fd_write, buf, sizeof(buf));
       }
    }
    close(fd_write);
    close(fd_read);
    return 0;
}
```

思考: 如果在多人聊天的情况下, 上述实现有什么缺陷?

改进: 假设使用time_t计时可以实现吗? 有什么问题?

```c
int main(int argc,char*argv[]){
    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    char buf[60];

    fd_set set;

    // 记录a发过来信息的时间
    time_t tag_a_msg = time(NULL);
    // 记录当前时间
    time_t tag_cur = time(NULL);

    while(1){
       FD_ZERO(&set);
       FD_SET(STDIN_FILENO, &set);
       FD_SET(fd_read, &set);

       // 每1秒就绪一次
       struct timeval time_val;
       time_val.tv_sec = 1;
       time_val.tv_usec = 0;
       int res_select = select(10, &set, NULL,NULL, &time_val);
       // 更新当前时间
       tag_cur = time(NULL);

       if(FD_ISSET(fd_read, &set)){
           bzero(buf, sizeof(buf));
           int read_num = read(fd_read, buf, sizeof(buf));
           if(read_num == 0){
               printf("对方断开链接 \n");
               break;
           }
           printf("UserA: %s", buf);
           // 更新a的发送信息时间
           tag_a_msg = time(NULL);
       }
       if(FD_ISSET(STDIN_FILENO, &set)){
           bzero(buf, sizeof(buf));
           int read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
           if(read_stdin == 0){
               // 用户按下ctrl+d; 输入文件终止符; 终止标准输入; read返回0
               break;
           }
           write(fd_write, buf, sizeof(buf));
       }
       // 比较信息时间和当前时间
       if(tag_cur - tag_a_msg >= 10){
           printf("10秒未发信息 \n");
           break;
       }
    }
    close(fd_write);
    close(fd_read);
    return 0;
}
```

以上。

### 3. 了解：写就绪

基于上面的写满情况, 利用select监听其写就绪功能。

EgCode: 读端

```c
int main(int argc,char*argv[]){
   int fd_read = open("1.pipe", O_RDONLY);

   char buf[1024];
   fd_set set;

   while(1){
       FD_ZERO(&set);
       FD_SET(fd_read, &set);
       select(10, &set, NULL, NULL, NULL);

       read(fd_read, buf, sizeof(buf));
       printf("read \n");
       sleep(2);
    }

   return 0;
}
```

EgCode: 写端

```c

int main(int argc,char*argv[]){
   int fd_write = open("1.pipe", O_WRONLY);

   char buf[4096] = {0};
   int times = 0;
   fd_set set;

   while(1){
       FD_ZERO(&set);
       FD_SET(fd_write, &set);
       select(10, NULL, &set, NULL, NULL);
       printf("select : %d \n", ++times);
       write(fd_write, buf, sizeof(buf));
    }

   return 0;
}
```

### 4. 补充：重要细节

**select底层顺序**

1. 创建监听集合fd_set, 并初始化
2. 把要监听的文件描述符加到fd_set集合中
3. 调用select开始监听
4. select函数, 把处于用户态的监听集合拷贝到内核态空间
5. 内核进程根据拷贝到内核态的监听集合, **轮询**访问文件描述符对象, 监听状态变化 (轮询范围,根据select的最大文件描述符参数)
6. 在一次轮询过程中, 发现有文件状态就绪, 把就绪状态文件描述符放回拷贝到内核态的监听集合中, 并触发select结束阻塞
7. 把内核态的存储就绪的文件描述符集合, 拷贝回用户态
8. select结束

**select的缺陷**select监听的最大文件描述符为1024 (靠**位图**实现)

```c
// ps: 了解
// 虽然我们通过ulimit -a看到的open files 大小因为是1024, 意味着操作系统的一个进程可以打开的文件对象也是1024,看上去和select监听最大范围相匹配,但是进程可以打开的文件对象是可以修改的,而select监听的最大文件描述符为1024是没办法修改的(要想修改只能重新编译操作系统了)

// 我们可以找到fd_set类型, 进而确定它的监听的最大文件描述符为1024
    gcc -E 文件.c -o 文件.i
    vim 文件.i
    // 查找: fd_set
 typedef struct{
     __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
 } fd_set;
```

1. 监听集合和就绪集合, 需要反复从内核态空间和用户态空间来回拷贝(再需要循环监听的时候: 还需要反复设置监听集合)
2. 监听和就绪不分离, 每次需要充值监听集合
3. 不适合海量监听, 少量就绪的情况 (需要遍历每个被监听的文件描述符, 确定是否就绪)

### 5. 练习

**练习**编写程序A和B。A负责将文件的名字、长度和内容通过管道发送B，B需要新建一个目录/文件，并将该文件存储起来。

**EgCode: A端**

```c
int main(int argc,char*argv[]){
    int pipe_fd = open("1.pipe", O_WRONLY);

    char* name = "test1.txt";
    int file_lenth = 10;
    char* str = "helloworld";

    int name_length = strlen(name);
    write(pipe_fd, &name_length, sizeof(int));
    write(pipe_fd, name, name_length);

    write(pipe_fd, &file_lenth, sizeof(int));

    int str_length = strlen(str);
    write(pipe_fd, &str_length, sizeof(int));
    write(pipe_fd, str, str_length);

    return 0;
}
```

**EgCode: B端**

```c
int main(int argc,char*argv[]){
    int pipe_fd = open("1.pipe", O_RDONLY);

    // 先读取文件名长度, 再根据文件名长度读取文件名
    int name_length = 0;
    read(pipe_fd, &name_length, sizeof(int));
    char file_name[60] = {0};
    read(pipe_fd, file_name, name_length);

    // 读取文件长度
    int file_length = 0;
    read(pipe_fd, &file_length, sizeof(int));

    // 先读取文件内容长度, 再根据内容长度读取要写入文件的内容
    int str_length = 0;
    read(pipe_fd, &str_length, sizeof(int));
    char str_buf[60] = {0};
    read(pipe_fd, str_buf, str_length);

    // 创建文件夹, 修改当前工作路径
    mkdir("files", 0777);
    chdir("files");
    // 根据文件名创建文件
    int new_fd = open(file_name, O_RDWR|O_CREAT, 0664);
    // 修改文件大小
    ftruncate(new_fd, file_length);
    // 向文件中写入内容
    write(new_fd, str_buf, str_length);

    return 0;
}
```

以上。
