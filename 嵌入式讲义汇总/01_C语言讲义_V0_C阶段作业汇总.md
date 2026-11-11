# C语言讲义·V0：C阶段作业汇总

> 来源：[王道 C 语言在线讲义](http://8.136.0.191:8080/stm32/index.html?toc=0&ws=off&reset=true)

> 按网站原卷及章节顺序整理；保留正文、代码、表格、公式和图片，代码及原文表述不作改写。

## 本卷目录

1. [01 C语言基础阶段作业](#ch-01)
2. [02 数组阶段作业](#ch-02)
3. [03 函数阶段作业](#ch-03)
4. [04 指针和数组阶段作业](#ch-04)
5. [05 字符串阶段作业](#ch-05)
6. [06 结构体和枚举阶段作业](#ch-06)
7. [07 指针高级阶段作业](#ch-07)
8. [08 链表阶段作业](#ch-08)
9. [09 队列和栈阶段作业](#ch-09)
10. [10 哈希表和BST阶段作业](#ch-10)
11. [11 算法基础阶段作业](#ch-11)
12. [12 文件流阶段作业](#ch-12)

<a id="ch-01"></a>

## 01 C语言基础阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/01_C语言基础阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### printf和scanf基础练习题

> 题目：
>
> 1. 键盘输入一名学生的语文、数学和英语成绩（均为整数百分制）。计算其平均成绩，并保留两位小数打印显示。
> 2. 键盘输入一个位于(0, 1)范围内的浮点数，并将其转化为百分比形式，结果保留一位小数。例如：输入0.12转换为12.0%，而输入0.1234转换为12.3%。
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码：
> >
> > ```c
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     int chinese, math, english;
> >     float average;
> >
> >
> >     printf("请输入语文成绩：");
> >     scanf("%d", &chinese);
> >
> >
> >     printf("请输入数学成绩：");
> >     scanf("%d", &math);
> >
> >
> >     printf("请输入英语成绩：");
> >     scanf("%d", &english);
> >
> >
> >     average = (chinese + math + english) / 3.0; // 使用 3.0 以确保结果是浮点数
> >     printf("平均成绩为：%.2f\n", average);
> >
> >
> >     return 0;
> > }
> >
> >
> > // ------------------ 第二题 ------------------- //
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     float input, percentage;
> >
> >
> >     printf("请输入一个(0, 1)范围的浮点数：");
> >     scanf("%f", &input);
> >
> >
> >     if (input <= 0 || input >= 1) {
> >         printf("输入值超出范围!\n");
> >         return 1; // 返回一个错误代码
> >     }
> >
> >
> >     percentage = input * 100; // 转换为百分比
> >     printf("转化后的百分比为：%.1f%%\n", percentage);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### char类型处理函数练习

> 题目：
>
> **编写一个程序实现以下需求：**
>
> 1. **用户键盘录入一整行字符数据，包含数字和字母。**
> 2. **当用户按下回车键后结束数据录入。**
> 3. **请统计用户输入的一整行字符数据中，数字和字母分别有多少个。**
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码：
> >
> > ```c
> > int main(void) {
> >     // main函数里
> >     int ch;
> >     int letters = 0;    // 字母的数量
> >     int nums = 0;   // 数字的数量
> >
> >
> >     printf("请输入一行字符，包含数字和字母，按回车结束:\n");
> >
> >
> >     while ((ch = getchar()) != '\n') {
> >         if (isalpha(ch)) {  // 检查是否为字母
> >             letters++;
> >         }else if (isdigit(ch)) {  // 检查是否为数字
> >             nums++;
> >         }
> >     }
> >
> >
> >     printf("字母的数量: %d\n", letters);
> >     printf("数字的数量: %d\n", nums);
> > }
> > ```
>
> 以上。

#### 位运算符基础面试题

> **用位运算符实现以下算法：**
>
> 1. **定义一个函数，判断某个整数是否为奇数。**
> 2. **给定一个正整数，请定义一个函数判断它是否为2的幂(1, 2, 4, 8, 16, ....)。**
> 3. **给定一个不为0的整数，编写函数找出它值为1的最低有效位 (称之为Last Set Bit)。LSB是1表示此整数的最低位就是1,2则表示倒数第二位是第一个1,4表示倒数第三位是第一个1....**
>     一个示例如下：
>     > 输入：n = 24
>     >
>     > 输出：8
>     >
>     > 解释：24的二进制表示为 11000，值为 1 的最低有效位是倒数第四位，则输出 2^3，即输出的结果8。
> 4. **给定两个不同的整数 a 和 b，请交换它们两个的值。(不要定义函数来实现，直接在main函数里实现)**
> 5. **给定一个非空的整数数组nums，已知某个元素只出现了一次，其余元素均出现两次，那么请你找出这个只出现一次的元素。（不要定义函数来实现，直接在main函数里实现）**
>
> **位运算符本身就具有一定难度，需要对整数二进制位表示比较熟悉，如果有问题不妨直接参考下列代码。**
>
> > ###### 参考代码：
> >
> > **判断奇偶性：**
> >
> > ```c
> > // 定义一个函数，判断某个整数是否为奇数。true表示是奇数，否则是偶数
> > bool is_odd(int num) {
> >     return num % 2 != 0;    
> > }
> > // 用位运算符来判断奇偶性
> > // 奇数的位模式最低位必须是1
> > bool is_odd2(int num) {
> >     /*
> >         1.如果num是奇数，最低位是1，和1做按位与操作
> >             最后一位仍然是1，此时结果是非0的，于是结果就是1
> >             1在C语言是true
> >         2.如果num是偶数，最低为是0，和1做按位与操作
> >             最后一位是0，所有位都是0，于是结果就是0
> >             0在C语言中是false
> >         1111 1100 & 0000 0001 = 0000 0000
> >         0111 1101 & 0000 0001 = 0000 0001
> >     */
> >     return num & 1;
> > }
> > ```
> >
> > **判断2的正整数幂：**
> >
> > ```c
> > // 判断是否为2的正整数幂
> > bool is_power2(int num) {
> >     while (num > 1 && num % 2 == 0) {
> >         num /= 2;
> >     } //while结束时，num已经时小于等于1了 或者num已经不是偶数了
> >     return num == 1;
> > }
> > // 判断是否为2的正整数幂
> > bool is_power2(int num) {
> >     while (num > 1 && num % 2 == 0) {
> >         num /= 2;
> >     } //while结束时，num已经时小于等于1了 或者num已经不是偶数了
> >     return num == 1;
> > }
> >
> >
> > // 用位运算符来优化性能，确定num是不是2的正整数幂
> > bool is_power2_opt(int num) {
> >     return (num & (num - 1)) == 0;
> > }
> > ```
> >
> > **寻找lsb：**
> >
> > ```c
> > /*
> >     寻找LSB
> >     LSB是什么?(last set bit)
> >     值为1的最低有效位, 称之为Last Set Bit
> >     LSB的结果是1表示此整数的最低位就是1, 2则表示倒数第二位是第一个1, 4表示倒数第三位是第一个1....
> >     8的位模式: 1000
> >     那么LSB就是2^3=8,表示倒数第四位是第一个1
> > */
> > int find_lsb(int num) {
> >     int x = 1;
> >     while ((num & x) == 0) {
> >         // 说明num在x的lsb上不是1
> >         x <<= 1;
> >     }   // while循环结束时, num和x的相与结果不是0, 于是x就是num的lsb
> >     return x;
> > }
> >
> >
> > /*
> >     不用循环,直接求解LSB
> >     补码的性质,求一个相反数的补码
> >     x: 1000 1100
> >     -x: 0111 0100
> >     实际上就是找到x的LSB,然后LSB位不变, 从LSB的高一位开始,全部取反,就得到了相反数-x
> >     于是直接对 x 和 -x做&运算, 得到的结果就是LSB
> > */
> > int find_lsb_opt(int num) {
> >     return num & (-num);    //最好加(),虽然可以不加
> > }
> > ```
> >
> > **交换两个元素：**
> >
> > ```c
> > // 以下代码直接写在main函数里：
> > int a = 100, b = 200;
> >
> >
> > int tmp = a;
> > a = b;
> > b = tmp;    // 利用一个临时变量，完成两个元素的交换
> >
> >
> > // 以下代码直接写在main函数里：
> > int a = 100, b = 200;
> >
> >
> > a = a ^ b;
> > b = a ^ b;
> > a = a ^ b;  // 利用位运算符，完成两个元素的交换
> > ```
> >
> > **寻找数组中唯一元素：**
> >
> > ```c
> > // 以下代码直接写在main函数里：
> > int nums[] = { 1, 4, 2 ,1, 2 };
> > /*
> > * result就是最终找出的出现一次的元素
> > * 对于异或运算来说，0异或其它值都是其它值本身
> > * 所以result的初始值设置为0
> > */
> > int result = 0;
> >
> >
> > // 遍历将数组中的所有元素都使用^运算符链接起来
> > for (int i = 0; i < 5; i++){
> >     result ^= nums[i];
> > }
> >
> >
> > printf("数组中的唯一元素就是 %d.\n", result);
> > ```
>
> 以上。

#### switch语法基础练习

> 利用switch语句编写一个程序，先键盘录入一个成绩(int整数)，然后把用数字表示的成绩转化为字母表示的成绩等级。
>
> 评定规则是：
>
> 1. 90~100为A
> 2. 80~89为B
> 3. 70~79为C
> 4. 60~69为D
> 5. 0~59为F
> 6. 如果成绩高于100或者低于0，则显示出错消息。
>
> 提示：
>
> **switch只能对离散的值进行选择，而不能直接选择区间，所以要先想办法把区间变成离散数值。**
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码如下：
> >
> > ```c
> > int main(void) {
> >     int score;
> >     printf("请输入您的成绩: ");
> >     scanf("%d", &score);
> >
> >
> >     // 处理非法数据输入
> >     if (score > 100 || score < 0) {
> >         printf("Illegal score!\n");
> >         return;
> >     }
> >
> >
> >     // 对分数进行预处理，以适应 switch 语句
> >     int category = score / 10;
> >
> >
> >     switch (category) {
> >         case 10: // 100分
> >         case 9:  // 90-99分
> >             printf("Grade: A\n");
> >             break;
> >         case 8:  // 80-89分
> >             printf("Grade: B\n");
> >             break;
> >         case 7:  // 70-79分
> >             printf("Grade: C\n");
> >             break;
> >         case 6:  // 60-69分
> >             printf("Grade: D\n");
> >             break;
> >         case 5:  // 50-59分
> >         case 4:  // 40-49分
> >         case 3:  // 30-39分
> >         case 2:  // 20-29分
> >         case 1:  // 10-19分
> >         case 0:  // 0-9分
> >             printf("Grade: F\n");
> >             break;
> >             // 不需要default分支
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

#### 循环语法基础练习题

> 经典循环案例：请求出所有的水仙花数，并统计总共有几个。
>
> 1. 所谓的水仙花数是指一个三位数，其各位数字的立方和等于该数本身。
> 2. 举例：153就是一个水仙花数，153 = 1 \* 1 \* 1 + 5 \* 5 \* 5 + 3 \* 3 \* 3 = 1 + 125 + 27 = 153
>
> 提示：
>
> 你可以选择使用while循环，也可以选择使用for循环，但只需要给出一个解法就足够了。
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码如下：
> >
> > ```c
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     int count = 0; // 用于统计水仙花数的数量
> >
> >
> >     // 遍历所有的三位数
> >     for (int i = 100; i < 1000; i++) {
> >         int hundreds = i / 100;  // 百位
> >         int tens = (i / 10) % 10;  // 十位
> >         int ones = i % 10;  // 个位
> >
> >
> >         // 计算各位数字立方和
> >         int sumOfCubes = (hundreds * hundreds * hundreds) + (tens * tens * tens) + (ones * ones * ones);
> >
> >
> >         // 判断是否为水仙花数
> >         if (sumOfCubes == i) {
> >             printf("%d 是一个水仙花数.\n", i);
> >             count++;
> >         }
> >     }
> >
> >
> >     // 输出水仙花数的总数
> >     printf("水仙花数一共有 %d 个.\n", count);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### continue关键字语法练习

> 读以下代码：
>
> ```c
> int count = 0;
> int sum = 0;
> int i;
> while (count < 5) {
>     scanf("%d", &i);
>     if (i == 0) {
>         // 输入0就不必要累加了
>         continue;
>     }
>     sum += i;
>     count++;
> }
> printf("sum = %d\n", sum);
>
>
> // -----------------------------------  //
>
>
> int sum = 0;
> int i;
> for (int count = 0; count < 5; count++) { 
>     scanf("%d", &i);
>     if (i == 0) {
>         // 输入0就不必要累加了
>         continue;
>     }
>     sum += i;
> }
> printf("sum = %d\n", sum);
> ```
>
> 以上两段代码中都使用了continue关键字，一个使用while循环实现，一个使用for循环实现。
>
> 那么它们实现的功能有什么区别呢？为什么有这样的区别呢？
>
> > ###### 参考回答如下：
> >
> > 这两段代码的主要目的都是通过用户输入累加五个非零整数，并输出这些数的总和。然而，它们在处理输入为0的情况时的行为有显著差异，这是由它们的循环结构和条件处理决定的：
> >
> > 1. 第一段代码（使用 `while` 循环）
> >     1. 这段代码使用 `while` 循环，在变量 `count` 达到5之前持续循环，所以就一共循环五次，接受五次键盘输入。
> >     2. 如果用户输入的是 `0`，则通过 `continue` 语句跳过当前循环的剩余部分，不对 `sum` 进行累加，也**不增加** `count` 的值。这意味着这个循环会一直执行，直到用户输入了五个**非零**的整数为止。
> >     3. **总之，第一段代码总会累加五个非零整数的输入求和。**
> > 2. 第二段代码（使用 `for` 循环）
> >     1. 这段代码使用 `for` 循环，明确循环五次，每次循环 `count` 会自增。
> >     2. 如果输入的是 `0`，同样通过 `continue` 跳过当前循环的剩余部分，不累加 `sum`。但由于 `count` 是在 `for` 语句的控制下自动增加的，所以即便sum不累加但count还是会累加的。
> >     3. **总之，第二段代码只接受5次键盘录入，不管录入什么，非0还是0都可以，然后求和，在求和的过程中，如果输入的是0，不进行累加操作。**
> >
> > 这两段代码的核心差异在于：
> >
> > 1. **循环次数**：`while` 版本将确保至少有五个非零输入被累加；`for` 版本总共执行五次输入，不管输入值是什么。
> > 2. **结束条件**：`while` 循环是基于非零输入的数量，而 `for` 循环是严格的五次循环。

#### 简易交互式程序、跳转控制语法练习

> 现在我们就来开发一个简单的交互式程序：
>
> 程序将为用户提供选择菜单：
>
> 1. 清空账户余额
> 2. 往账户上存钱
> 3. 从账户上取钱
> 4. 显示当前余额
> 5. 退出程序。
>
> 选择项分别用整数 0、1、2、3 和 4 表示，账户余额可以用一个简单的局部变量表示，整体代码全部写在main函数里。交互程序大致界面如下：
>
> ![1.7题目功能示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_f6d2ab69-fd93-46a1-acdb-51eaee4c390b1704101959635.jpg)
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     int choice;     // 菜单选择指令
> >     float balance = 0.0;    // 账户余额
> >
> >
> >     do {
> >         // 显示菜单
> >         printf("\n======= 记账程序菜单 =======\n");
> >         printf("0. 清空账户余额\n");
> >         printf("1. 往账户上存钱\n");
> >         printf("2. 从账户上取钱\n");
> >         printf("3. 显示当前余额\n");
> >         printf("4. 退出程序\n");
> >
> >
> >         // 获取用户选择
> >         printf("请选择操作（0-4）： ");
> >         scanf("%d", &choice);
> >
> >
> >         // 根据用户选择执行相应的操作
> >         switch (choice) {
> >             case 0:
> >                 balance = 0.0;
> >                 printf("\n账户余额已清空。\n");
> >                 break;
> >             case 1: {       // 注意这里要加一个{}
> >                 float deposit;  // 存款金额
> >                 printf("\n请输入存款金额： ");
> >                 scanf("%f", &deposit);
> >                 balance += deposit;
> >                 printf("\n成功存款 %.2f 元。\n", deposit);
> >                 break;
> >             }
> >             case 2: {
> >                 float withdrawal;   // 取款金额
> >                 printf("\n请输入取款金额： ");
> >                 scanf("%f", &withdrawal);
> >                 if (withdrawal > balance) {
> >                     printf("\n余额不足，取款失败。\n");
> >                 }
> >                 else {
> >                     balance -= withdrawal;
> >                     printf("\n成功取款 %.2f 元。\n", withdrawal);
> >                 }
> >                 break;
> >             }
> >             case 3:
> >                 printf("\n当前余额为 %.2f 元。\n", balance);
> >                 break;
> >             case 4:
> >                 printf("\n感谢使用记账程序。再见！\n");
> >                 break;
> >             default:
> >                 printf("\n无效的选择，请重新输入。\n");
> >         }
> >
> >
> >     } while (choice != 4);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 化简分数练习题

> 写一个程序，实现分数相加。用户以分子/分母的形式输入分数，程序打印相加后的结果(化为最简分数)。如：
>
> ![1.8题目功能示意图1](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/002_a317b19e-4a83-4fb0-b4bf-240e6e44c1311714965303593.jpg)
>
> ![1.8题目功能示意图2](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/003_6d0c4788-6392-4da0-93a9-e9cc5a0ae7e01714965314404.jpg)
>
> **（注：可以利用欧几里得算法求最大公约数，进行分数简化）**
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> **欧几里得算法若不会写实现，不妨直接参考代码中的实现，算法问题不作为我们学习的重点！**
>
> > ###### 参考代码如下：
> >
> > ```c
> > // 利用欧几里得算法求a和b的最大公约数
> > int gcd(int a, int b) {
> >     // 首先确保a>=b
> >     if (a < b) {
> >         int tmp = a;
> >         a = b;
> >         b = tmp;
> >     }
> >     // 当b不为0时，计算a除以b的余数r，将b的值赋给a，r的值赋给b
> >     while (b != 0) {
> >         int r = a % b;
> >         a = b;
> >         b = r;
> >     }
> >
> >
> >     return a;
> > }
> >
> >
> > /*
> > * 递归求解欧几里得算法
> > * 递归的出口： b=0时，a的值就是最大公约数
> > * 递归体：只要b不是0，把b赋值成a，把a%b赋值给b，再次调用函数自身
> > */
> > int gcd_recursion(int a, int b) {
> >     // 递归的出口
> >     if (b == 0) {
> >         return a;
> >     }
> >     // 递归体
> >     return gcd_recursion(b, a % b);
> > }
> >
> >
> > int main(void) {
> >     int num1, denom1;   // 第一个分子分母
> >     int num2, denom2;   // 第二个分子分母
> >
> >
> >     printf("请输入第一个分数(分子/分母)： ");
> >     scanf("%d/%d", &num1, &denom1);
> >     printf("请输入第二个分数(分子/分母)： ");
> >     scanf("%d/%d", &num2, &denom2);
> >
> >
> >     int result_num = num1 * denom2 + num2 * denom1;
> >     int result_denom = denom1 * denom2;
> >
> >
> >     // 欧几里得算法求最大公约数
> >     int result_gcd = gcd(result_num, result_denom);
> >
> >
> >     // 下面进行结果分数的化简，特殊情况是最大公约数等于结果分母，此时分数可以化简成一个整数
> >     if (result_gcd == result_denom) {
> >         printf("两个分数的和是一个整数，即：%d\n", (result_num / result_denom));
> >     }else{
> >         // 结果是一个分数
> >         printf("两个分数的和是一个分数，即：%d/%d\n", (result_num / result_gcd), (result_denom / result_gcd));
> >     }
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 运算符优先级结合性练习题

> 根据运算符优先级和结合性的相关语法，阅读下面的表达式，为表达式手动添加小括号以显示运算的优先级，然后指出表达式中每一个操作数的值。
>
> 1. 假设（x = 0xFF33, MASK = 0xFF00），请计算表达式：`c = x & MASK == 0;`
> 2. 假设（x = 10, y = 2, z = 2），请计算表达式：`z = x++ + ++y * 2;`
> 3. 假设（x = 10, y = 4, z = 1），请计算表达式：`y >>= x & 0x2 && z;`
> 4. 假设（a = 100），请计算表达式：`b = c = d = a;`
>
> **注意：不要将表达式作为代码运行，请自行思考答案后再运行验证。**
>
> > ###### 参考的回答如下：
> >
> > **第一小题：**
> >
> > 表达式中一共有三个运算符：`=`、`&`以及`==`
> >
> > 首先，添加小括号以明确运算符优先级：
> >
> > 1. 根据 C 语言中的运算符优先级，按位与运算符 `&` 的优先级低于关系运算符 `==`，优先级最低的是赋值运算符 `=`。
> > 2. 因此，该表达式等价于：`c = (x & (MASK == 0));`
> >
> > 操作数的值：
> >
> > 1. `x = 0xFF33`
> > 2. `MASK = 0xFF00`
> >
> > 进行计算：
> >
> > 1. `MASK == 0`这个口算就可以算出来了，显然MASK不是0，所以结果就是false，即0
> > 2. `x & 0` 的结果也可以直接口算出来，仍然是0。
> >
> > 因此，`c` 的值为 `0`，而`x`和`MASK`的值是不变的。
> >
> > **第二小题：**
> >
> > 首先，添加小括号以明确运算符优先级：
> >
> > 1. 这里，`++` 作为前缀和后缀自增运算符时都是一元运算符，它们的优先级都高于作为二元运算符的加法和乘法。
> > 2. 乘法的优先级又高于加法
> > 3. 赋值运算符的优先级一般是最低的
> > 4. 因此，该表达式等价于：`z = ((x++) + ((++y) * 2));`
> >
> > 操作数的值：
> >
> > （x = 10, y = 2, z = 2）
> >
> > 计算表达式：
> >
> > 1. `(x++)`的主要作用是：返回自增前x的值，也就是在整个表达式中(x++)被计算的值是10
> > 2. `(++y)`的作用作用是：返回自增后y的值，也就是在整个表达式中(++y)被计算的值是3
> > 3. z = (10 + 3 \* 2) = 16
> >
> > 所以：
> >
> > 1. x最终的值是11
> > 2. y最终的值是3
> > 3. z最终的值是16
> >
> > **第三小题：**
> >
> > 首先，添加小括号以明确运算符优先级：
> >
> > 1. 位与操作 `&` 的优先级高于逻辑与 `&&`，逻辑与的优先级又高于赋值运算 `>>=`。
> > 2. 因此，表达式的结构应该理解为：`y >>= ((x & 0x2) && z);`
> >
> > 操作数的值：
> >
> > （x = 10, y = 4, z = 1）
> >
> > 计算表达式：
> >
> > 1. `x & 0x2` 的计算：`1010`（二进制的整数`10`）与 `0010`（二进制的整数`2`）进行与操作得 `0010`（二进制的 `2`），结果是 `2`。
> > 2. z = 1，2 && 1 两个非0值进行逻辑与运算，也就是两个true进行逻辑与运算，结果还是true，在C语言中true就是1。
> > 3. 最终`y >>= 1`，也就是将y按位右移1位然后赋值给y，右移1位相当于除以2，所以y的结果最终是2
> >
> > 所以：
> >
> > 1. x最终的值是10，不变
> > 2. y最终的值是2
> > 3. z最终的值是1，不变
> >
> > **第四小题：**
> >
> > 题目中运算符只有赋值运算符`=`，优先级一致就看结合性
> >
> > `=运算符`的结合性是右结合的，所以这个表达式添加小括号就是：
> >
> > `b = (c = (d = a));`
> >
> > 最终所有操作数的结果都和a保持一致：
> >
> > a = 100
> >
> > b = 100
> >
> > c = 100
> >
> > d = 100
>
> 以上。

#### 宏定义、零散语法相关

> **简答题：**
>
> (a) `double ans = 10.0 + 2.0 / 3.0 − 2.0 ∗ 2.0;`请在适当的位置插入()，使得 ans = 11.0.
>
> (b) `double ans = 18.0 / SQUARED(2 + 1);` 如果宏函数定义如下，请写出对应 ans 的值。
>
> ```c
> #define SQUARED(x) x*x
> #define SQUARED(x) (x*x)
> #define SQUARED(x) (x)*(x)
> #define SQUARED(x) ((x)*(x))
> ```
>
> (c) 请解释下面代码为什么错了，并改正它。
>
> ```c
> 1) #include <stdio.h>;
> 2) int function(void arg1){
>        return arg1-1;
>    }
> 3) #define MESSAGE = "Happy new year!"
> ```
>
> 这三道题目主要涉及一些基础的语法辨析，比较简单。参考的回答如下：
>
> > ###### 参考回答：
> >
> > **第一题参考：**
> >
> > ans = 10.0 + 2.0 / ((3.0 - 2.0) \* 2.0);
> >
> > **第二题参考：**
> >
> > #define SQUARED(x) x\*x
> >
> > ans = 18.0 / 2 + 1 \* 2 + 1 = 12.0
> >
> > #define SQUARED(x) (x\*x)
> >
> > ans = 18.0 / (2 + 1 \* 2 + 1) = 3.6
> >
> > #define SQUARED(x) (x)\*(x)
> >
> > ans = 18.0 / (2 + 1) \* (2 + 1) = 18.0
> >
> > #define SQUARED(x) ((x)\*(x))
> >
> > ans = 18.0 / ((2 + 1) \* (2 + 1)) = 2.0
> >
> > **第三题参考：**
> >
> > 1. **头文件包含不是语句,而是预处理指令,它没有";"分号**
> > 2. **形参列表"(void arg1)" void表示没有返回值时的返回值类型，它不能用在形参的类型声明上**
> > 3. **宏定义是不用加"="的，否则等号也会成为宏常量的一部分**

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：位运算符面试题

> 给定一个非空的整数数组nums，已知有两个元素只出现了一次，其余元素均出现两次。那么请你找出这两个只出现一次的元素。
>
> **（不要定义函数来实现，直接在main函数里实现）**
>
> > ###### 参考代码：
> >
> > ```c
> > int arr[] = { 1,2,100,1,2,3,4,3,5,4,5,11,12,12,11,100,10,10,99,77,77,88 };
> > int len = sizeof(arr) / sizeof(arr[0]);
> > int res = 0;
> > for (int i = 0; i < len; i++) {
> >     res ^= arr[i];
> > }
> > int lsb = res & (-res);
> > int a = 0, b = 0;
> > for (int i = 0; i < len; i++) {
> >     if (arr[i] & lsb) {
> >         // 和a一组,在LSB位上是1的元素
> >         a ^= arr[i];
> >     }
> >     else {
> >         // 和b一组,在LSB位上是0的元素
> >         b ^= arr[i];
> >     }
> > }
> > printf("数组中唯二唯一的元素是: %d, %d\n", a, b);
> > ```
>
> 以上。

#### 扩展：位运算符面试题2

> 1.编写一个函数，计算一个整数的二进制位模式中1的个数。
>
> 2.判断两个整数是否具有相反的符号。比如1和-2就具有相反的符号。
>
> 3.利用位运算符求一个整数的绝对值。
>
> > ###### 参考代码如下：
> >
> > ```c
> > /*
> >     编写一个函数，计算一个整数的二进制表示中1的个数。
> >     思路：
> >     循环计数
> >     每次循环都将该整数值为1的低位改为0
> >     当n变为0的时候，结束循环
> > */
> > int count_bits(int n) {
> >     int count = 0;
> >     while (n != 0) {
> >         // 对n进行与操作 n & (n - 1) 可以直接去除n的二进制表示中最低位的1
> >         // 这是因为n - 1会将n的最低位1变为0，并且将这一位之后的所有位变为1
> >         // 当与n进行与操作时，仅最低位的1会被清零，其余位不变
> >         n &= (n - 1);
> >         count++; // 每执行一次操作，就表示找到了一个1
> >     }
> >     return count;
> > }
> >
> >
> > /*
> > 判断两个整数是否具有相反的符号
> >     思路：
> >     如果x和y有相反的符号，说明它们的最高位是不相同的，最高位异或的结果是1
> > */
> > int have_opposite_sign(int x, int y) {
> >     // 所以如果x和y有相反的符号，那么它们异或的结果就是一个负数
> >     return ((x ^ y) < 0);
> > }
> >
> >
> > /*
> > 利用位运算符求绝对值
> > 思路：
> > 对于整数x
> > 非负数和负数求绝对值要分开，所以第一步要知道x的符号位
> > 如果x是一个非负数，符号位是0，绝对值是它本身
> > 如果x是一个负数，符号位是-1，绝对值是x的相反数，所以需要返回-x
> >
> >
> > 小细节：
> > 对于有符号整数而言，最小值的绝对值和最大值是对不上的
> > 比如int的最小值求绝对值就会溢出
> > 为了避免这种情况发生, 可以使用无符号数作为返回值
> > */
> > size_t absolute_value(int x) {
> >     // 获取符号位，通过将 x 右移 (sizeof(int) * 8 - 1) 位
> >     // sizeof(int) 获取 int 类型的字节数，乘以 8 转换为位数
> >     // 减 1 是因为要求的是最高位符号位
> >     int mask = x >> (sizeof(int) * 8 - 1);
> >
> >
> >
> >
> >     // 如果x为正数，mask为0，x ^ mask == x，x + mask == x；
> >     // 如果x为负数，x ^ mask实际上是对x按位取反
> >     // 此时再减去mask，也就是+1，将负数x按位取反再加1，也就得到了-x
> >     return (x ^ mask) - mask;
> > }
> >
> >
> > int main(void) {
> >     int test_values[] = { 2147483647, (-2147483647 - 1), 0, 1, -1 };
> >     for (int i = 0; i < 5; i++) {
> >         // 测试int最小值求绝对值会不会溢出
> >         printf("整数%d的绝对值是%zu\n", test_values[i], absolute_value(test_values[i]));
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

### 日历相关题目篇

> 所有和日历相关的题目都总结放在一起，放在下面。

#### 判断闰年

> **用C语言编写程序实现以下需求：**
>
> 编写一个函数，输入一个公元年份（如2004），判断该年是否为闰年，并返回判断结果。
>
> **平年闰年的规则如下**：
>
> 1. 如果年份不是4的倍数，则是平年。
> 2. 如果年份是4的倍数但不是100的倍数，则是闰年。
> 3. 如果年份是100的倍数但不是400的倍数，则是平年。
> 4. 如果年份是400的倍数，则是闰年。
>
> 要求使用bool类型作为函数的返回值。
>
> **注意：日历有一系列的题目，这道题编写的函数在下一道题目中可能会用到。**
>
> > ###### 参考代码：
> >
> > ```c
> > #include <stdbool.h>
> >
> >
> > // 判断年份是否为闰年
> > bool is_leap_year(int year) {
> >     // 如果年份能被400整除，则为闰年
> >     // 或者如果年份能被4整除但不能被100整除，也是闰年
> >     return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
> > }
> > ```
>
> 以上。

#### 计算下一天的日期

> **用C语言编写程序实现以下需求：**
>
> 紧接着上一问，编写一个函数，输入年、月、日，计算并输出下一天的日期。
>
> 比如：
>
> 传入函数的日期是2004年3月31日
>
> 那么函数体内部要直接打印下一天是：2004年4月1日
>
> 要求：
>
> 键盘录入年月日日期时，键盘录入的格式是：**"年/月/日"**
>
> **注意：日历有一系列的题目，这道题编写的函数在下一道题目中可能会用到。**
>
> **提示：**
>
> **求下一天的日期，无非就是传入日期的天数加1，但加1后天数有可能"溢出"，所以需要知道输入的月份有几天。**
>
> **天数+1如果溢出，天数就需要归1，然后让月份+1**
>
> **月份+1如果溢出，那就需要将年份+1**
>
> **当然年份不需要考虑溢出...**
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> >
> >
> > // 判断年份是否为闰年
> > bool is_leap_year(int year) {
> >     // 如果年份能被400整除，则为闰年
> >     // 或者如果年份能被4整除但不能被100整除，也是闰年
> >     return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
> > }
> >
> >
> > // 根据年份和月份，获取该月的天数
> > int get_days_in_month(int year, int month) {
> >     // 普通年份每月的天数, 下标为0的位置填充一个占位元素0以使得下标和月份对应
> >     int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
> >     // 二月份，如果是闰年，则天数为29天
> >     if (month == 2 && is_leap_year(year)) {
> >         return 29;
> >     }
> >     // 返回指定月份的天数
> >     return days_in_month[month];
> > }
> >
> >
> > // 打印给定日期的下一天
> > void print_next_day(int year, int month, int day) {
> >     // 获取当前月份的天数
> >     int days_in_month = get_days_in_month(year, month);
> >     // 日期加1
> >     day++;
> >     // 如果日期超出了当前月份的天数，则进入下一个月
> >     if (day > days_in_month) {
> >         day = 1; // 日期重置为1
> >         month++; // 月份加1
> >     }
> >     // 如果月份超出了12，则进入下一年
> >     if (month > 12) {
> >         month = 1; // 月份重置为1
> >         year++; // 年份加1
> >     }
> >
> >
> >     // 打印下一天的日期
> >     printf("您输入的日期的下一天是: %d年%d月%d日\n", year, month, day);
> > }
> >
> >
> > int main(void) {
> >     int year, month, day;
> >     printf("请输入一个日期 (YYYY/MM/DD): ");
> >     scanf("%d/%d/%d", &year, &month, &day);
> >     print_next_day(year, month, day);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 计算相隔天数

> **用C语言编写程序实现以下需求：**
>
> 编写一个函数，输入两个日期（年/月/日），计算这两个日期之间相隔的天数。
>
> 要求键盘录入的第一个日期，必须要早于第二个日期。
>
> 例如：
>
> 键盘录入2020/01/01和2020/01/02，打印它们相隔1天
>
> 键盘录入2020/01/01和2021/01/02，打印它们相隔367天
>
> **提示：**
>
> 这个问题求解的思路不唯一，你可以自己思考求解，我这里提供一种比较简单直观的思路。
>
> 直接计算两个日期相隔多少天，可能不太好计算。于是我们就找一个基准点。
>
> 比如设置基准点为："1/1/1"，即公元1年1月1日
>
> **然后求两个日期到基准点的总天数，再把得到的两个总天数相减，结果就是两个日期相隔的天数。**
>
> **于是这里就存在一个问题：如何求某个日期到"1/1/1"的总天数呢？**
>
> 计算三点即可：
>
> 1. **加上前面所有过去年份的天数**：对于已经过去的每一年，判断它是平年还是闰年（闰年366天，平年365天），并累加所有这些年份的天数。
> 2. **加上当前年份中之前月份的天数：**给定日期的前面所有月都是已经过去的，根据月份确定该月的天数（考虑闰年2月有29天），并累加起来。当然当前月份还没过完，不要累加进去。
> 3. **加上当前月份中已经过去的天数**：直接加上给定日期中的“日”部分。今天也算过去了，不需要减1
>
> 试一试求解该题吧。
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> >
> >
> > // 判断年份是否为闰年
> > bool is_leap_year(int year) {
> >     // 如果年份能被400整除，则为闰年
> >     // 或者如果年份能被4整除但不能被100整除，也是闰年
> >     return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
> > }
> >
> >
> > // 根据年份和月份，获取该月的天数
> > int get_days_in_month(int year, int month) {
> >     // 普通年份每月的天数, 下标为0的位置填充一个占位元素0以使得下标和月份对应
> >     int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
> >     // 二月份，如果是闰年，则天数为29天
> >     if (month == 2 && is_leap_year(year)) {
> >         return 29;
> >     }
> >     // 返回指定月份的天数
> >     return days_in_month[month];
> > }
> >
> >
> > // 计算给定日期从公元1年1月1日起的天数
> > int calculate_days_from_start(int year, int month, int day) {
> >     int total_days = 0;
> >     // 加上之前所有过去年份的天数
> >     for (int y = 1; y < year; y++) {
> >         total_days += is_leap_year(y) ? 366 : 365;
> >     }
> >     // 加上当前年份中之前月份的天数
> >     for (int m = 1; m < month; m++) {
> >         total_days += get_days_in_month(year, m);
> >     }
> >     // 加上当前月份中已经过去的天数
> >     total_days += day;
> >     return total_days;
> > }
> >
> >
> > // 计算两个日期之间的天数差
> > int calculate_date_diff(int year1, int month1, int day1, int year2, int month2, int day2) {
> >     int days1 = calculate_days_from_start(year1, month1, day1);
> >     int days2 = calculate_days_from_start(year2, month2, day2);
> >     return days2 - days1;
> > }
> >
> >
> > int main(void) {
> >     int year1, month1, day1;
> >     int year2, month2, day2;
> >     printf("请输入第一个日期 (YYYY/MM/DD): ");
> >     scanf("%d/%d/%d", &year1, &month1, &day1);
> >     printf("请输入第二个日期 (YYYY/MM/DD): ");
> >     scanf("%d/%d/%d", &year2, &month2, &day2);
> >
> >
> >     int difference = calculate_date_diff(year1, month1, day1, year2, month2, day2);
> >     printf("您输入的两个日期之间相隔: %d 天\n", difference);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 计算星期几

> **用C语言编写程序实现以下需求：**
>
> 已知1970年1月1日是星期四，编写一个函数，输入一个日期（年、月、日），计算该日期是星期几。
>
> 规定输入的日期，必须在1970年1月1日后。
>
> **注意：**
>
> **你已经可以求解出输入日期到1970年1月1日相隔多少天了，那么求解星期几还不是轻轻松松？**
>
> **提示：取余运算**
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> >
> >
> > // 判断年份是否为闰年
> > bool is_leap_year(int year) {
> >     // 如果年份能被400整除，则为闰年
> >     // 或者如果年份能被4整除但不能被100整除，也是闰年
> >     return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
> > }
> >
> >
> > // 根据年份和月份，获取该月的天数
> > int get_days_in_month(int year, int month) {
> >     // 普通年份每月的天数, 下标为0的位置填充一个占位元素0以使得下标和月份对应
> >     int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
> >     // 二月份，如果是闰年，则天数为29天
> >     if (month == 2 && is_leap_year(year)) {
> >         return 29;
> >     }
> >     // 返回指定月份的天数
> >     return days_in_month[month];
> > }
> >
> >
> > // 计算给定日期从公元1年1月1日起的天数
> > int calculate_days_from_start(int year, int month, int day) {
> >     int total_days = 0;
> >     // 加上之前所有过去年份的天数
> >     for (int y = 1; y < year; y++) {
> >         total_days += is_leap_year(y) ? 366 : 365;
> >     }
> >     // 加上当前年份中之前月份的天数
> >     for (int m = 1; m < month; m++) {
> >         total_days += get_days_in_month(year, m);
> >     }
> >     // 加上当前月份中已经过去的天数
> >     total_days += day;
> >     return total_days;
> > }
> >
> >
> > // 计算两个日期之间的天数差
> > int calculate_date_diff(int year1, int month1, int day1, int year2, int month2, int day2) {
> >     int days1 = calculate_days_from_start(year1, month1, day1);
> >     int days2 = calculate_days_from_start(year2, month2, day2);
> >     return days2 - days1;
> > }
> >
> >
> > // 计算输入的日期是星期几
> > int calculate_weekday(int year, int month, int day) {
> >     // 计算给定日期与1970年1月1日之间的天数差
> >     int days_diff = calculate_date_diff(1970, 1, 1, year, month, day);
> >     // 根据天数差计算星期几
> >     /*
> >     * 1970年1月1日是星期四，所以相隔天数直接取余7
> >     * 如果余数是0就是周四
> >     * 为了让余数为0的时候表示周天，余数为1表示周1，余数为2表示周2...
> >     * 需要在取余之前给天数加上4
> >     */
> >     return (4 + days_diff) % 7;
> > }
> >
> >
> > int main(void) {
> >     int year, month, day;
> >     printf("请输入一个日期 (YYYY/MM/DD): ");
> >     scanf("%d/%d/%d", &year, &month, &day);
> >     int weekday = calculate_weekday(year, month, day);
> >     if (weekday == 0){
> >         printf("您输入的日期是星期天!");
> >     }
> >     else{
> >         printf("您输入的日期是星期%d!", weekday);
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：打印年历

> **扩展题，不要求每一位同学做。大家可以酌情做。**
>
> 在前面所有日历题目的基础上，完成最后一个需求。
>
> 输入1970年之后任意一年的年份，输出该年的年历。打印的格式如下：
>
> ![年历-图1](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/004_c175941d10d84af28ef0f3d648f54ca.png)
>
> ![年历-图2](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/005_11acbab6830adff67ad04562642fed8.png)
>
> 注：
>
> **基于上面几个问题已经实现的函数，这题其实没有太大难度，难的在于怎么把格式调对齐，这需要一定的耐心罢了。**
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> >
> >
> >
> >
> > // 判断年份是否为闰年
> > bool is_leap_year(int year) {
> >     // 如果年份能被400整除，则为闰年
> >     // 或者如果年份能被4整除但不能被100整除，也是闰年
> >     return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
> > }
> >
> >
> > // 根据年份和月份，获取该月的天数
> > int get_days_in_month(int year, int month) {
> >     // 普通年份每月的天数, 下标为0的位置填充一个占位元素0以使得下标和月份对应
> >     int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
> >     // 二月份，如果是闰年，则天数为29天
> >     if (month == 2 && is_leap_year(year)) {
> >         return 29;
> >     }
> >     // 返回指定月份的天数
> >     return days_in_month[month];
> > }
> >
> >
> > // 计算给定日期从公元1年1月1日起的天数
> > int calculate_days_from_start(int year, int month, int day) {
> >     int total_days = 0;
> >     // 加上之前所有过去年份的天数
> >     for (int y = 1; y < year; y++) {
> >         total_days += is_leap_year(y) ? 366 : 365;
> >     }
> >     // 加上当前年份中之前月份的天数
> >     for (int m = 1; m < month; m++) {
> >         total_days += get_days_in_month(year, m);
> >     }
> >     // 加上当前月份中已经过去的天数
> >     total_days += day;
> >     return total_days;
> > }
> >
> >
> > // 计算两个日期之间的天数差
> > int calculate_date_diff(int year1, int month1, int day1, int year2, int month2, int day2) {
> >     int days1 = calculate_days_from_start(year1, month1, day1);
> >     int days2 = calculate_days_from_start(year2, month2, day2);
> >     return days2 - days1;
> > }
> >
> >
> > // 计算输入的日期是星期几
> > int calculate_weekday(int year, int month, int day) {
> >     // 计算给定日期与1970年1月1日之间的天数差
> >     int days_diff = calculate_date_diff(1970, 1, 1, year, month, day);
> >     // 根据天数差计算星期几
> >     /*
> >     * 1970年1月1日是星期四，所以相隔天数直接取余7
> >     * 如果余数是0就是周四
> >     * 为了让余数为0的时候表示周天，余数为1表示周1，余数为2表示周2...
> >     * 需要在取余之前给天数加上4
> >     */
> >     return (4 + days_diff) % 7;
> > }
> >
> >
> > void print_year_calendar(int year) {
> >
> >
> >     printf("\n|=====================The Calendar of Year %d====================|\n", year);
> >
> >
> >     // 存储月份字符串的常量字符串数组
> >     const char* months[] = {
> >         "", "January", "February", "March", "April", "May", "June",
> >         "July", "August", "September", "October", "November", "December"
> >     };
> >
> >
> >     for (int month = 1; month <= 12; month++) {
> >         printf("\n%s\n", months[month]);    // 打印月份标题
> >         printf("SUN MON TUE WED THU FRI SAT\n");    // 打印星期标题
> >
> >
> >         // 计算当年当月的第一天是周几
> >         int first_day_weekday = calculate_weekday(year, month, 1);  
> >
> >
> >         // 打印第一天前的空格
> >         for (int i = 0; i < first_day_weekday; i++) {
> >             printf("    ");
> >         }
> >         // 获取当月共有多少天
> >         int days = get_days_in_month(year, month);
> >
> >
> >         // 打印当月剩下的天数
> >         for (int day = 1; day <= days; day++) {
> >             printf("%3d ", day);
> >             if ((first_day_weekday + day) % 7 == 0 || day == days) {
> >                 printf("\n");
> >             }
> >         }
> >     }
> >
> >
> >     printf("\n|==================================================================|\n");
> > }
> >
> >
> > int main(void) {
> >     int year;
> >     printf("Enter year to print calendar: ");
> >     scanf("%d", &year);
> >     print_year_calendar(year);
> >     return 0;
> > }
> > ```
>
> 以上。

### 简易计算器问题

> 编写一个程序实现一个简单的计算器，能够处理加法、减法、乘法和除法。
>
> **输入**：用户输入两个数字**(可以带小数)**和一个操作符（+、-、\*、/）。
>
> **输出**：显示计算的表达式及结果。
>
> 注意以下几个要求：
>
> 1. 代码可以直接写在main函数里，不需要提取函数。
> 2. 输入的表达式应当符合格式要求，应当正常录入两个操作数和一个运算符，否则直接退出程序。
> 3. 在进行除法操作时，需要保证除数不为0，若除数为0，则直接退出程序。
>
> 运算结果截图如下：
>
> ![简易计算器问题-运行截图1](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/006_fb75ad35-bd33-4788-a8e0-46b612789f8b1721204807432.jpg)
>
> ![简易计算器问题-运行截图2](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/007_6c776721-fe89-4c72-97e8-2883ce133a411721281164062.jpg)
>
> 提示：考虑switch结构，选择不同的运算符。
>
> 参考代码如下：
>
> > ###### 参考代码
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     double num1, num2;
> >     char operator;
> >     double result;
> >
> >
> >     printf("请输入需要计算的表达式（例如：1 + 1）: ");
> >     int ret = scanf("%lf %c %lf", &num1, &operator, &num2);
> >     if (ret != 3) {
> >         printf("Error: 输入的表达式格式不合法！\n");
> >         return 1;   // 程序异常退出
> >     }
> >     switch (operator) {
> >         case '+':
> >             result = num1 + num2;
> >             break;
> >         case '-':
> >             result = num1 - num2;
> >             break;
> >         case '*':
> >             result = num1 * num2;
> >             break;
> >         case '/': {
> >             if (num2 != 0) {
> >                 result = num1 / num2;
> >             }
> >             else {
> >                 printf("Error: 除数为0!\n");
> >                 return 1;  // 程序异常退出
> >             }
> >             break;
> >         }
> >         default:
> >             printf("Error: 无法识别的操作符!\n");
> >             return 1;  // 程序异常退出
> >     }
> >     printf("计算的结果是：%.2lf %c %.2lf = %.2lf\n", num1, operator, num2, result);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：计算器问题

> 在上面简单计算器题目的基础上，实现以下功能：
>
> 1.在进行完一次运算后，询问用户是否继续运算。只要用户输入y/Y就可以继续运算，而不是只能计算一次。
>
> 2.当用户的输入有误时，不退出程序，而是要求用户继续输入表达式计算。
>
> 参考的程序运行效果图如下：
>
> ![扩展计算器问题-运行截图3](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/01_C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/008_8147b21f-67c2-46b2-b738-8c15a372386a1721282362508.jpg)
>
> 提示：
>
> 可以考虑使用do...while循环结构，配合循环控制变量来解决，代码仍然都写在main函数中即可。
>
> 写完代码后，可以测试一下：在询问循环是否继续时输入"yyyyy"，会发生什么情况呢？如何解决？
>
> 参考代码如下：
>
> > ###### 参考代码
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     double num1, num2;
> >     char operator;
> >     double result;
> >     // 给予flag一个初始值y,使得第一个键盘录入失败时,循环能够继续进行
> >     char flag = 'y';
> >     do
> >     {
> >         printf("请输入需要计算的表达式（例如：1 + 1）: ");
> >         int ret = scanf("%lf %c %lf", &num1, &operator, &num2);
> >         if (ret != 3) {
> >             printf("Error: 输入的表达式格式不合法！请重新输入。\n\n");
> >             while (getchar() != '\n')
> >                 ; // 清空缓冲区至行尾，避免影响下次输入
> >             continue; // 继续下一次循环,重新开始输入表达式
> >         }
> >         switch (operator) {
> >         case '+':
> >             result = num1 + num2;
> >             break;
> >         case '-':
> >             result = num1 - num2;
> >             break;
> >         case '*':
> >             result = num1 * num2;
> >             break;
> >         case '/': {
> >             if (num2 != 0) {
> >                 result = num1 / num2;
> >             }
> >             else {
> >                 printf("Error: 除数为0!请重新输入表达式。\n\n");
> >                 continue;
> >             }
> >             break;
> >         }
> >         default:
> >             printf("Error: 无法识别的操作符!请重新输入表达式。\n\n");
> >             continue;
> >         }
> >         printf("计算的结果是：%.2lf %c %.2lf = %.2lf\n\n", num1, operator, num2, result);
> >
> >
> >         printf("是否继续计算？(输入'y/Y'继续，其他任意键结束): ");
> >         scanf(" %c", &flag);
> >         while (getchar() != '\n')   // 注意清空操作需要放在scanf下面,因为只有输入了才有垃圾需要清理
> >             ; // 清空缓冲区至行尾，避免影响下次输入
> >     } while (flag == 'y' || flag == 'Y');
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-02"></a>

## 02 数组阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/02_数组阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 数组基础编程练习题

> 固定投资的初始资金是100元，用户先输入年利率（rate）和要投资的年份（years），投资收益后的资产每年计算一次。
>
> 随后此程序将打印此利率在投资年份内每年的资产总价值，和紧随其后的4个更高的利率（总计5个利率）下投资的总价值。
>
> **余额考虑复利，第一年的余额是(本金 + 本金 \* 利率)，第二年则可以在第一年余额的基础上累加(本金 \* 利率)。**
>
> 程序的输入和输出示意图如下：
>
> ![题目1-演示示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/02_%E6%95%B0%E7%BB%84%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_image-20240516184342939.png)
>
> **请编写代码完成这个程序。**
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define RATE_NUMS 5
> > #define INITIAL_BALANCE 100.0
> >
> >
> > int main(void) {
> >     int rate, years;
> >     printf("请输入年利率: ");
> >     scanf("%d", &rate);
> >
> >
> >     printf("请输入要投资的年份: ");
> >     scanf("%d", &years);
> >
> >
> >     // 打印表头
> >     // 声明一个长度为5的double数组,用于存放5个利率下的5个余额
> >     double balances[RATE_NUMS];
> >     printf("\nYears");
> >     for (int i = 0; i < RATE_NUMS; i++){
> >         // 打印第一行的利率
> >         printf("  %9d%%", (rate + i));
> >         // 将每个利率下的初始金额存入数组
> >         balances[i] = INITIAL_BALANCE;
> >     }
> >
> >
> >     printf("\n");
> >     // 外层for控制行，i代表年份
> >     for (int i = 1; i <= years; i++){
> >         // 打印第一列的数据,也就是投资的年份,也就是1~years
> >         printf("%7d", i);
> >         // 内层for用于给balances数组赋值并打印列
> >         for (int j = 0; j < RATE_NUMS; j++) {
> >             // 计算每个利率下的第i年余额
> >             balances[j] += balances[j] * (rate + j) * 0.01;
> >             printf("%12.2lf", balances[j]);
> >         }
> >         // 打印完某一年多个利率下的余额，换行
> >         printf("\n");
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

#### 数组基础编程练习题2

> 编写一个程序，要求用户键盘录入十名学生的语文成绩(百分制)，然后存储在一个一维数组中。最后计算全班的平均成绩、最高分和最低分，并打印出来。
>
> 注意：
>
> 1. 要求使用一个int数组来存放成绩，平均成绩保留2位小数。
> 2. 如果你还不理解将数组作为参数传递的话，请不要提取函数，直接将所有代码写到main函数里。
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #define STUDS_NUM 10
> >
> >
> > int main(void) {
> >     int scores[STUDS_NUM];
> >     // 初始化总成绩、最高分以及最低分
> >     int sum = 0, max = -1, min = 101;
> >
> >
> >     printf("请输入十名学生的语文成绩(百分制):\n");
> >     for (int i = 0; i < STUDS_NUM; i++) {
> >         printf("学生 %d 的成绩: ", i + 1);
> >         scanf("%d", &scores[i]); 
> >         sum += scores[i];
> >
> >
> >         if (scores[i] > max) {
> >             max = scores[i]; // 更新最高分
> >         }
> >         if (scores[i] < min) {
> >             min = scores[i]; // 更新最低分
> >         }
> >     }
> >     // 这里可以用强转语法，使得结果是一个double类型
> >     double average = (double)sum / STUDS_NUM;
> >
> >
> >     printf("全班的平均成绩为: %.2lf\n", average);
> >     printf("最高分为: %d\n", max);
> >     printf("最低分为: %d\n", min);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 随机发牌小程序

> 现在有一副扑克牌，去掉大小王。请你写一个随机发牌程序，由用户指定发几张票，然后打印用户得到的手牌。
>
> 注：
>
> 1. 扑克牌的花色（suit）有四种：梅花（Club）、方块（Diamond）、红心（Heart）、黑桃（Spade）
> 2. 扑克牌的点数（point）有13种，2~10，J，Q，K，A
>
> 程序的输出示意图如下：
>
> ![题目3-演示示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/02_%E6%95%B0%E7%BB%84%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/002_image-20240516185930290.png)
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #include <time.h>
> > #include <stdlib.h>
> > #include <stdbool.h>
> >
> >
> > int main(void) {
> >     /*
> >     现在有一副扑克牌，去掉大小王。
> >     请你写一个随机发牌程序，由用户指定发几张票，然后打印用户得到的手牌。
> >
> >
> >     注：
> >     扑克牌的花色（suit）有四种：梅花（Club）、方块（Diamond）、红心（Heart）、黑桃（Spade）
> >     扑克牌的点数（point）有13种，2~10，J，Q，K，A
> >
> >
> >     程序的核心是随机生成手牌,需要随机数
> >
> >
> >     在C程序中生成一个随机数,按照以下步骤进行:
> >     1.包含头文件,<stdlib.h> <time.h>
> >     2.生成随机种子(种子固定,随机序列就固定):
> >         srand(time(NULL));
> >     3.生成伪随机数:
> >         rand();
> >         它会生成一个在[0, RAND_MAX]之间的随机整数
> >         RAND_MAX是<stdlib.h>标准库中定义的一个常量
> >     */
> >
> >
> >     printf("请输入您需要的手牌数量: \n");
> >     int cards_num;
> >
> >
> >     scanf("%d", &cards_num);
> >
> >
> >     printf("发牌中....\n");
> >     printf("发牌中....\n");
> >     printf("发牌中....\n");
> >     printf("发牌完成了,您的手牌是:\n");
> >
> >
> >     // 分别用2个一维数组来装扑克牌的花色和点数
> >     const char suits[4] = { 'C','D','H','S' };
> >     const char points[13] = { '2','3','4','5','6','7','8' ,'9','T','J' ,'Q','K','A' };
> >
> >
> >     // 声明一个布尔类型的二维数组,用来标记某张手牌是否已经发出,已发出的手牌标记为true,没有发出则是false
> >     // 默认都没有发出,所以该二维数组的初始化元素取值都是false 
> >     bool flags[4][13] = { {false } };
> >
> >
> >     // 生成随机数,用来作为数组的下标
> >     // time(NULL)函数调用用于获取当前时间戳的描述
> >     srand(time(NULL));
> >
> >
> >     // cards_num为0时,循环结束,刚好0代表false,非0代表true
> >     while (cards_num){
> >         // 随机生成一种卡牌
> >         // [0,4)
> >         int suit_index = rand() % 4;
> >         // [0,13)
> >         int point_index = rand() % 13;
> >
> >
> >         /*
> >         * 这张随机生成的牌必须是以往还没有发出的,因为相同的牌没有两张
> >         * 我们需要一种标记手段,来标记某站牌是否已经发出了
> >         */
> >         // 判断是没有发出的手牌,才打印发出这种牌
> >         if (!flags[suit_index][point_index]){
> >             printf("%c%c  ", suits[suit_index], points[point_index]);
> >             flags[suit_index][point_index] = true;
> >             cards_num--;
> >         }
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

#### 掷骰子小游戏

> **编写程序模拟掷骰子的游戏（每一次投掷，都投掷两个骰子）。每局游戏的规则如下：**
>
> 1. **第一次掷的时候：**
>     1. **如果点数之和为 7 或 11 则获胜；**
>     2. **如果点数之和为2、3或12则落败；**
>     3. **其他情况下的点数之和称为“目标”，继续投掷两个骰子。**
> 2. **在后续的投掷中：**
>     1. **如果玩家再次掷出“目标”点数则获胜；**
>     2. **如果掷出7则落败；**
>     3. **其他情况都忽略，继续投掷两个骰子。**
>
> **在每一局游戏结束时，程序都要询问用户是否再玩一次，如果用户输入的回答不是 y 或 Y ，那么就结束游戏，程序此时要打印显示胜败的次数。**
>
> **玩家游玩过程程序的输出，大体如下所示：**
>
> ```
> You rolled: 5
> Your point is 5
> You rolled: 7
> You lose!
>
>
> Play again?(y/Y means continue) y
> You rolled: 5
> Your point is 5
> You rolled: 4
> You rolled: 4
> You rolled: 9
> You rolled: 2
> You rolled: 7
> You lose!
>
>
> Play again?(y/Y means continue) y
> You rolled: 4
> Your point is 4
> You rolled: 7
> You lose!
>
>
> Play again?(y/Y means continue) n
>
>
> Wins: 0 Losses: 3
> ```
>
> **提示（请思考三个问题）：**
>
> **1.肯定需要使用随机数，那么srand设置种子值，这个函数调用应该放在哪里呢？**
>
> **2.在键盘录入是否继续游玩时，如果键盘输入的是"(空格)y"，会发生什么事情？怎么解决？**
>
> **3.在键盘录入是否继续游玩时，如果键盘输入的是"yyy"，会发生什么事情？怎么解决？**
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> >
> >
> > #include <stdio.h>
> > #include <stdbool.h>
> > #include <stdlib.h>
> > #include <time.h>
> >
> >
> > // 玩一次游戏，返回true表示赢，false表示输了
> > bool play_game(void);
> > // 掷一次骰子，一次扔两个骰子，返回掷出的结果
> > int roll_dice(void);
> >
> >
> > int main(void) {
> >     int wins = 0, losses = 0;// 记录胜利和输的次数
> >     char again; // 决定用户是否继续玩
> >     // 设置随机种子，只需要设置一次，所以放在主函数里
> >     srand(time(NULL));
> >     do {
> >         play_game() ? wins++ : losses++;
> >         printf("\nPlay again?(y/Y means continue) ");
> >         // %c前面必须加空格，因为要跳过前面的空格输入
> >         scanf(" %c", &again);
> >         // 清空一次键盘录入后剩余的垃圾数据，避免对下一次输入产生影响
> >         while (getchar() != '\n')
> >             ;
> >     } while (again == 'Y' || again == 'y'); // 如果用户输入'Y'或'y'，则继续玩
> >
> >
> >     // 游戏结束，打印赢和输的次数
> >     printf("\nWins: %d Losses: %d\n", wins, losses);
> >
> >
> >     return 0;
> > }
> >
> >
> > bool play_game(void) {
> >     int point = roll_dice();
> >     if (point == 7 || point == 11) {
> >         printf("You win!\n");
> >         return true;
> >     }
> >     if (point == 2 || point == 3 || point == 12) {
> >         printf("You lose!\n");
> >         return false;
> >     }
> >     // 第一次掷骰子不能决定输赢，于是继续掷骰子
> >     printf("Your point is %d\n", point); // 打印第一次掷出的结果，后续只要掷出它就赢了
> >     while (1) {     // 死循环，直到决定出输赢结束循环
> >         int tally = roll_dice(); // 再次掷骰子
> >         if (tally == point) { // 如果点数与之前相同，玩家赢
> >             printf("You win!\n");
> >             return true;
> >         }
> >         if (tally == 7) { // 如果掷出7点，玩家输
> >             printf("You lose!\n");
> >             return false;
> >         }
> >     }
> > }
> >
> >
> > int roll_dice() {
> >     int a = rand() % 6 + 1; 
> >     int b = rand() % 6 + 1; 
> >     printf("You rolled: %d\n", a + b); // 打印两个骰子点数之和
> >
> >
> >     return a + b; // 返回点数之和
> > }
> >
> >
> > ```
>
> 以上。

#### 二维数组基础练习——杨辉三角

> 杨辉三角（YangHui Triangle）指的是南宋时期数学家杨辉，根据北宋时期的数学家贾宪的作品（现已遗失），发现的一种几何排列规律，在数学中，它是二项式系数在三角形中的一种几何排列。
>
> 杨辉三角的大致图案如下：
>
> 1
>
> 1 1
>
> 1 2 1
>
> 1 3 3 1
>
> 1 4 6 4 1
>
> 1 5 10 10 5 1
>
> ........
>
> 在欧洲，这个表叫做帕斯卡三角形（Pascal's Triangle），法国数学家布莱士·帕斯卡（Blaise Pascal ）在1654年发现这一规律，相比于中国，比杨辉要迟393年，比贾宪迟600年。
>
> 杨辉三角从纯粹数字规律上来说，就是：
>
> 1. 每一行的元素和行数一样，即行数等于列数。第一行有一列，第二行有两列....
> 2. 第一行的元素从1开始，**且之后每个元素的值，都是上一行同列元素和上一行左边列的元素之和。**
> 3. 前两行的元素和每一行的首尾元素由于没有上一行同列元素或上一行左列元素，默认都是1。
>
> 现在请你用二维数组来存储杨辉三角的前十行(每一行就是一个一维数组)，并以杨辉三角的打印格式来最终打印杨辉三角。
>
> **注意：C语言的二维数组列长是一致的，所以实际上只能用二维数组的一半空间来存储元素，这一点要特别注意。**
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define ROWS 10
> >
> >
> > int main(void) {
> >     // 声明并初始化二维数组，只使用一半空间存储杨辉三角元素
> >     int triangle[ROWS][ROWS] = { 0 }; 
> >
> >
> >     // 构建杨辉三角
> >     for (int i = 0; i < ROWS; i++) {
> >         triangle[i][0] = 1; // 每一行的第一个数是1
> >         triangle[i][i] = 1; // 每一行的最后一个数也是1
> >
> >
> >         // 给中间元素赋值
> >         for (int j = 1; j < i; j++) {
> >             // 中间元素的值是上一行的前一列数据 + 上一行的当前列数据
> >             triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
> >         }
> >     }
> >
> >
> >     // 打印直角杨辉三角
> >     for (int i = 0; i < ROWS; i++) {
> >         for (int j = 0; j <= i; j++) {
> >             printf("%4d", triangle[i][j]);
> >         }
> >         printf("\n");
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

#### 数组基础语法以及伪随机数练习题

> **以下关于一维/二维数组的基础语法编程练习题，请编写代码完成。**
>
> 1. **给定一个宏定义N的值为10，声明一个长度为N的int数组，然后将数组元素初始化为它下标的平方，最后将数组元素全部累加到一起求和，并输出打印这个和。**
> 2. **给定两个宏定义N的值为5，M的值是3，声明一个N \* M的二维数组，然后生成伪随机数将该二维数组初始化，要求随机数的范围在 1 到 100 之间。紧接着：**
>     1. **以矩阵的样式遍历打印这个二维数组中的所有元素。**
>     2. **求出该二维数组每一行和每一列的元素和，并输出打印结果。**
>
> 第二题的运行结果如下图所示：
>
> ![题目6-效果示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/02_%E6%95%B0%E7%BB%84%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/003_image-20240516220547456.png)
>
> **提示：每一行和每一列的和可以用数组计算和存储起来，打印元素和求和可以一次嵌套循环完成，而不需要多次。**
>
> **注意：当下请不要提取函数，就把所有代码都写在main函数里。**
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> > ###### 参考代码：
> >
> > **第一题非常简单，实现如下：**
> >
> > ```c
> > #include <stdio.h>
> > #define N 10
> >
> >
> > int main(void) {
> >     int arr[N];
> >     int sum = 0;
> >
> >
> >     // 初始化这个一维数组的同时直接累加求和
> >     for (int i = 0; i < N; i++) {
> >         arr[i] = i * i;
> >         sum += arr[i];
> >     }
> >     printf("数组中所有元素的和是: %d\n", sum);
> >     return 0;
> > }
> > ```
> >
> > **第二题会稍微复杂一些，实现如下：**
> >
> > ```c
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <time.h>
> >
> >
> > #define N 5
> > #define M 3
> >
> >
> > int main(void) {
> >     // 声明一个 N * M 的二维数组
> >     int matrix[N][M];
> >     // 每一行的和组成一个数组,所以二维数组的行N就是此数组的长度, 初始化每行的和都是0
> >     int row_sum[N] = { 0 };
> >     // 每一列的和组成一个数组,所以二维数组的列M就是此数组的长度, 初始化每列的和都是0
> >     int col_sum[M] = { 0 };
> >
> >
> >     srand(time(NULL));
> >
> >
> >     printf("该二维数组的元素打印效果如下：\n");
> >     // 使用1到100之间的随机数初始化二维数组数组
> >     for (int i = 0; i < N; i++) {
> >         for (int j = 0; j < M; j++) {
> >             matrix[i][j] = rand() % 100 + 1;
> >             printf("%d\t", matrix[i][j]); // 打印矩阵的当前元素
> >             /*
> >              i代表行, 第i行的和就是将第i行的元素全部累加起来
> >              j代表列, 第j列的和就是将第j列的元素全部累加起来
> >          */
> >             row_sum[i] += matrix[i][j];
> >             col_sum[j] += matrix[i][j];
> >         }
> >         printf("\n"); // 每打印完一行（一个一维数组）后就换行
> >     }
> >     // 打印每行的和
> >     printf("\n每行的和:\n");
> >     for (int i = 0; i < N; i++) {
> >         printf("第 %d 行的和: %d\n", i + 1, row_sum[i]);
> >     }
> >     // 打印每列的和
> >     printf("\n每列的和:\n");
> >     for (int j = 0; j < M; j++) {
> >         printf("第 %d 列的和: %d\n", j + 1, col_sum[j]);
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-03"></a>

## 03 函数阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/03_函数阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 函数基础语法练习题

> 编写函数实现以下功能：
>
> 1. 键盘录入一个正整数，请判断它是否是一个素数，然后控制台输出对应的结果。要对键盘录入的数据做参数校验，素数是一个大于1的自然数，它仅能被1和自身整除。
> 2. 键盘录入**两个整数**：底(base)和幂指数(exponent)，计算base的exponent次幂，并打印输出对应的结果。（注意底和幂指数都可能是负数）
>
> 提示：求幂运算时，基础的思路就是先无脑把指数转换成正数，然后累乘，最后再根据指数是否是负数决定是否取倒数。
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **第一题，判断素数：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> > #include <math.h>
> >
> >
> > bool is_prime(int num) {
> >     // 如果num是1甚至比1还小，那它一定不是素数
> >     if (num <= 1) {
> >         return false;
> >     }
> >     // 将num从2开始除，一直除到该数的平方根
> >     for (int i = 2; i <= sqrt(num); i++) {
> >         if (num % i == 0) {
> >             // 此过程中只要有一个除尽了，那么就不是素数
> >             return false;
> >         }
> >
> >
> >     }
> >     // 没有被除尽,说明是素数
> >     return true;
> > }
> >
> >
> > int main(void) {
> >     int num;
> >     printf("请输入一个整数: ");
> >     scanf("%d", &num);
> >
> >
> >     if (is_prime(num)) {
> >         printf("%d是一个素数!\n", num);
> >     }
> >     else {
> >         printf("%d不是一个素数!\n", num);
> >     }
> >
> >
> >     return 0;
> > }
> > ```
> >
> > **第二题参考代码：**
> >
> > ```c
> > // 计算 base 的 exponent 次幂 - 循环累乘求解
> > double power(int base, int exponent) {
> >     double result = 1.0;    // 存储计算结果
> >     // 若幂指数是0，则直接返回1
> >     if (exponent == 0) {
> >         return result;
> >     }
> >     /*
> >         在计算幂运算的过程中
> >         幂指数有可能是负数，但为了简化计算可以先将指数转换成正数求解
> >         计算完毕后，若指数是一个负数则取倒数就可以了
> >     */
> >     int positive_exponent = exponent > 0 ? exponent : -exponent;  // 确保幂指数是一个正数
> >
> >
> >     // 累乘 base
> >     for (int i = 0; i < positive_exponent; i++) {
> >         result *= base;
> >     }
> >     // 如果原幂指数是一个负数，则取倒数
> >     if (exponent < 0) {
> >         result = 1.0 / result;
> >     }
> >     return result;
> > }
> >
> >
> > int main(void) {
> >     int base, exponent;
> >     printf("请输入底数和指数（用空格分隔）：");
> >     scanf("%d %d", &base, &exponent);
> >
> >
> >     double result = power(base, exponent);
> >     // 为了更好的显示负指数的小数结果，可以保留更多小数点后面的有效数字
> >     printf("%d 的 %d 次幂是 %.20lf\n", base, exponent, result);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 函数基础语法练习题2

> 键盘录入三个边长（整数即可），然后用海伦公式计算三角形的面积（如果它确实是一个三角形的话）
>
> 海伦公式求三角形面积：
>
> ![题目2-海伦公式](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/03_%E5%87%BD%E6%95%B0%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_b0761450-8c62-45e5-a639-94e038a9fed51712382082492.jpg)
>
> 要求基于下列两个函数完成这个编程题：
>
> ```c
> // 判断abc是否可以组成三角形，true表示可以组成，false表示不可以
> bool is_triangle(int a, int b, int c);
>
>
> // 利用海伦公式在abc可以构成三角形的前提下，求三角形面积
> double get_area(int a, int b, int c);
> ```
>
> **注意：不要忘记使用sqrt函数要包含头文件&lt;math.h&gt;**
>
> **非常简单且基础的语法练习题，如果这种题目都还有疑惑，说明代码量几乎为0，语法也几乎不熟悉，建议直接看参考代码先熟悉语法。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> > #include <math.h>
> >
> >
> >
> >
> > // 判断abc是否可以组成三角形，true表示可以组成，false表示不可以
> > bool is_triangle(int a, int b, int c);
> >
> >
> > // 利用海伦公式在abc可以构成三角形的前提下，求三角形面积
> > double get_area(int a, int b, int c);
> >
> >
> > bool is_triangle(int a, int b, int c) {
> >     // 任意两边之和必须大于第三边
> >     return (a + b > c) && (a + c > b) && (b + c > a);
> > }
> >
> >
> > double get_area(int a, int b, int c) {
> >     double s = (a + b + c) / 2.0; // 计算半周长
> >     return sqrt(s * (s - a) * (s - b) * (s - c)); // 使用海伦公式计算面积
> > }
> >
> >
> > int main(void) {
> >     int a, b, c; // 三角形的三个边长
> >     printf("请您键盘输入三角形的三个边长：");
> >     scanf("%d%d%d", &a, &b, &c);
> >
> >
> >     if (!is_triangle(a, b, c)){
> >         // 不能组成三角形
> >         printf("Error: 无法组成三角形!\n");
> >         return -1;
> >     }
> >
> >
> >     // 可以组成三角形，于是计算三角形的面积
> >     double area = get_area(a, b, c);
> >     printf("三角形的面积是: %.2lf\n", area);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 变量种类/值传递等读程序题

> 读下列一段程序代码，回答以下一些问题。
>
> ```c
> #include <stdio.h>
>
>
> static int global = 1;  // 全局变量
>
>
> void modify(int param) {
>  static int static_local = 1;  // 静态局部变量
>  int local = 1;                // 普通局部变量
>
>
>  // 修改函数传参的值
>  param *= 2;
>  // 修改全局变量
>  global *= 2;
>  static_local *= 2;    // 修改静态局部变量
>  local *= 2;    // 修改普通局部变量
>
>
>  printf("test函数内部：param=%d, global=%d, static_local=%d, local=%d\n",
>         param, global, static_local, local);
> }
>
>
> void modify_global(int global) {
>  global = 100;
> }
>
>
> int main(void) {
>  int param_a = 10;
>  int param_b = 20;
>  printf("初始值：param_a=%d, param_b=%d, global=%d\n\n", param_a, param_b, global);
>
>
>  modify(param_a);
>  printf("第一次调用后：param_a=%d, global=%d\n\n", param_a, global);
>
>
>  modify(param_b);
>  printf("第二次调用后：param_b=%d, global=%d\n\n", param_b, global);
>
>
>  modify_global(global);
>  printf("after modify_global global = %d\n", global);
>
>
>  return 0;
> }
> ```
>
> **问题一：**
>
> 通过modify函数调用，能不能修改"param\_a"和"param\_b"的取值呢？为什么？
>
> **问题二：**
>
> 能不能在main函数当中访问静态局部变量"static\_local"呢？为什么？
>
> **问题三：**
>
> 全局变量"global"使用static修饰，这里的static关键字是什么作用？
>
> **问题四：**
>
> modify函数的两次调用中，"printf"输出打印的**自身局部变量**"local"的取值是一样的吗？为什么？
>
> **问题五：**
>
> modify函数内部修改了全局变量"global"的取值，两次调用"printf"函数输出的结果是什么？为什么？
>
> **问题六：**
>
> modify函数内部修改了静态局部变量"static\_local"的取值，两次调用"printf"函数输出的结果是什么？为什么？
>
> **问题七：**
>
> modify\_global函数希望修改"global"全局变量的取值，可以修改成功吗？为什么？
>
> > ###### 参考回答如下：
> >
> > **问题一：**
> >
> > **通过 `modify` 函数调用，能不能修改 `param_a` 和 `param_b` 的取值呢？为什么？**
> >
> > **答：不能修改。**
> >
> > 因为 C 语言中函数参数是**值传递**，实参的值会被拷贝一份传递给形参 `param`，函数内部对 `param` 的任何修改都只作用于这份**拷贝**，而不会影响原变量 `param_a` 或 `param_b` 的值。
> >
> > **问题二：**
> >
> > **能不能在 `main` 函数当中访问静态局部变量 `static_local` 呢？为什么？**
> >
> > **答：不能访问。**
> >
> > 因为 `static_local` 是定义在 `test`函数 内部的**静态局部变量**，它的作用域仅限于该函数内部，**main 函数无法访问到它**，因为并不在作用域范围内。即便静态局部变量生命周期贯穿整个程序运行期间，但它依然无法在函数外部被访问，这就是作用域产生的影响。
> >
> > **问题三：**
> >
> > **全局变量 `global` 使用 `static` 修饰，这里的 `static` 关键字是什么作用？**
> >
> > **答：将该全局变量的作用域限制在当前问题内部，而不再是整个工程全局都可以访问的了。**
> >
> > 也就是说，`static int global = 1;` 这个变量**只能在当前源文件中使用**，不能被其他文件访问。
> >
> > 在这个语法中，static非常类似C++面向对象封装机制的访问权限修饰符，即private私有权限修饰符，用于限制变量的外部可见性。
> >
> > **问题四：**
> >
> > **`modify` 函数的两次调用中，`printf` 输出打印的自身局部变量 `local` 的取值是一样的吗？为什么？**
> >
> > **答：是一样的，都是2。**
> >
> > 在 `modify` 函数中，`local` 是一个**普通局部变量**，每次调用函数时都会**重新创建并初始化为 1**，然后执行 `local *= 2`。
> >
> > 而不同的函数调用之间，局部变量是独立不互相影响的。
> >
> > 所以不管调用多少次这个函数，其结果都是"local = 2"。
> >
> > **问题五：**
> >
> > **`modify` 函数内部修改了全局变量 `global` 的取值，两次调用 `printf` 函数输出的结果是什么？为什么？**
> >
> > **答：**
> >
> > 1. 第一次调用后，`global` 由 1 变为 2（`global *= 2`）；
> > 2. 第二次调用后，`global` 再次变为 4。
> >
> > **原因**：`global` 是一个全局变量，在函数中直接访问并修改，每次调用函数都会让其值翻倍，且值在全局作用域内持续保留。
> >
> > **问题六：**
> >
> > **`modify` 函数内部修改了静态局部变量 `static_local` 的取值，两次调用 `printf` 函数输出的结果是什么？为什么？**
> >
> > 答：
> >
> > 1. 第一次调用：`static_local = 1 × 2 = 2`
> > 2. 第二次调用：`static_local = 2 × 2 = 4`
> >
> > **原因**：`static_local` 是一个**静态局部变量**，其生命周期贯穿整个程序运行过程，在同一个函数的多次函数调用间**保持上次的值**，所以每次调用会继续累积变化。
> >
> > **问题七：**
> >
> > **`modify_global` 函数希望修改 `global` 全局变量的取值，可以修改成功吗？为什么？**
> >
> > 答：不能修改成功！
> >
> > `modify_global` 函数中的参数名是 `global`，它与全局变量同名，**会屏蔽（隐藏）全局变量**，函数内部操作的是这个**形参的副本**，而不是全局变量本身。
> >
> > 再加上是值传递，修改形参也不会影响实参，所以全局变量不会被改变。
>
> 以上。

#### 交互式简易计算器-函数/全局变量

> 实现一个终端交互式的简易计算器，交互的形式大体如下：
>
> ![题目3-示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/03_%E5%87%BD%E6%95%B0%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/002_e2d6c87d-d814-4d8a-ab1c-a451e778a9ca1712407470510.jpg)
>
> 要求至少提供四种运算加减乘除，如下：
>
> ```c
> int add(int a, int b);
> int subtract(int a, int b);
> int multiply(int a, int b);
> float divide(int a, int b);
> ```
>
> **并且在结束进程时，打印总共执行操作的次数。（也就是这些函数调用的次数）**
>
> **注意：除法的实现，要求判断除数不为0，并且在除数为0时使用exit表示异常退出进程。**
>
> **要求：需要编写一个函数，用于随时随地打印当前操作的执行次数，也就是打印上述四个函数的调用次数。**
>
> **思考一下：这个变量应该设置为什么变量呢？**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > // 全局变量，用于记录操作次数
> > // 设置为static修饰的全局变量,缩小作用域,更加安全
> > static int operation_count = 0;
> >
> >
> > // 函数声明
> > int add(int a, int b);
> > int subtract(int a, int b);
> > int multiply(int a, int b);
> > float divide(int a, int b);
> > void print_operation_count(void);
> >
> >
> > int main(void) {
> >  int a, b;
> >  char operator;
> >  char choice;
> >
> >
> >  do {
> >      printf("请输入要计算的表达式（例如，5 + 3）: ");
> >      scanf(" %d %c %d", &a, &operator, &b);
> >
> >
> >      switch (operator) {
> >          case '+':
> >              printf("结果: %d\n", add(a, b));
> >              break;
> >          case '-':
> >              printf("结果: %d\n", subtract(a, b));
> >              break;
> >          case '*':
> >              printf("结果: %d\n", multiply(a, b));
> >              break;
> >          case '/':
> >              printf("结果: %.2f\n", divide(a, b));
> >              break;
> >          default:
> >              printf("无效的运算符。\n");
> >      }
> >      // 询问用户是否继续
> >      printf("是否继续? (y/n): ");
> >      scanf(" %c", &choice);
> >      printf("\n");
> >  } while (choice == 'y' || choice == 'Y');
> >
> >
> >  print_operation_count();
> >  return 0;
> > }
> >
> >
> > int add(int a, int b) {
> >  operation_count++;
> >  return a + b;
> > }
> >
> >
> > int subtract(int a, int b) {
> >  operation_count++;
> >  return a - b;
> > }
> >
> >
> > int multiply(int a, int b) {
> >  operation_count++;
> >  return a * b;
> > }
> >
> >
> > float divide(int a, int b) {
> >  if (b == 0) {
> >      printf("error：除数为零！\n");
> >      exit(1);
> >  }
> >  operation_count++;
> >  return (float)a / b;
> > }
> >
> >
> > void print_operation_count(void) {
> >  printf("总共执行的操作次数为: %d次\n", operation_count);
> > }
> > ```
>
> 以上。

#### 递归练习题

> (1) 汉诺塔
>
> 有三根杆子A，B，C。A杆上有 N 个 (N&gt;1) 穿孔圆盘，盘的尺寸由下到上依次变小。要求按下列规则将所有圆盘移至 C 杆：
>
> 1. 每次只能移动一个圆盘;
> 2. 大盘不能叠在小盘上面。
>
> 利用递归的方式，打印出移动轨迹。运行结果如下图所示:
>
> ![题目4-示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/03_%E5%87%BD%E6%95%B0%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/003_bb6df6a3-1d0e-4e0c-9953-ffc9ba86f4cd1712481566486.jpg)
>
> (2) 十进制转换成二进制
>
> 给定任意一个**非负十进制整数**，请利用递归的方式，求解它的二进制表示方式
>
> 基本的思路是：把该整数除以2得到余数，然后倒着输出余数。
>
> **思考一下：如何实现倒着打印余数呢？**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **第一题，求解汉诺塔移动轨迹，参考代码：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > /*
> >     递归求解汉诺塔的移动轨迹
> >     假如有三座塔：A B C
> >
> >
> >     扩展：
> >     给定n个盘子，然后再给一个整数m，请你打印m + 1时，汉诺塔问题的移动轨迹
> > */
> >
> >
> > // n个盘子的时候 start是原始塔 target是目标塔 sup是辅助塔
> > void move(int n, char start, char target, char sup) {
> >     // 递归的出口
> >     // 当n=1时，直接将start上的唯一一个最大的盘子，移动到target上去
> >     if (n == 1) {
> >         printf("%c --> %c\n", start, target);
> >         return;
> >     }
> >     // 递归体
> >     // 1.第一步：把n-1个盘子从start移动到sup，这个过程需要target辅助
> >     // 第一步的n-1个盘子的时候 start是原始塔 sup是目标塔 target是辅助塔
> >     move(n - 1, start, sup, target);
> >
> >
> >     // 2.第二步：把最大的盘子从start移动到target
> >     printf("%c --> %c\n", start, target);
> >
> >
> >     // 3.第三步：把n-1个盘子从sup移动到target，这个过程需要start辅助
> >     // 第三步的n-1个盘子的时候 sup是原始塔 target是目标塔 start是辅助塔
> >     move(n - 1, sup, target, start);
> > }
> >
> >
> > void hanoi_track(int n) {
> >     long long steps = (1LL << n) - 1;
> >     printf("%d个盘子的汉诺塔问题，至少需要移动%lld步完成!\n", n, steps);
> >
> >
> >     // 该函数不能用于直接递归打印移动轨迹，所以需要一个辅助函数来完成递归，这种写法在递归中特别常见
> >     /*
> >         第二个参数是盘子的原始位置
> >         第三个参数是盘子移动完成汉诺塔问题的目标位置
> >         第四个参数是完成n个盘子汉诺塔问题时，需要的辅助塔
> >     */
> >     move(n, 'A', 'C', 'B');
> > }
> > int main(void) {
> >     // 4表示汉诺塔问题中盘子的个数
> >     hanoi_track(4);
> >     return 0;
> > }
> > ```
> >
> > **第二题，十进制转换成二进制参考代码：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > void decimal_to_binary(unsigned int n) {
> >     // 递归的出口
> >     // 0和1的十进制二进制表示是一样的
> >     if (n == 0 || n == 1) {
> >         printf("%u", n);
> >         return; // 直接返回，不再递归
> >     }
> >
> >
> >     // 递归体
> >     // 只要n不是0或1，那就递归调用除以2
> >     decimal_to_binary(n / 2);
> >
> >
> >     // 打印余数
> >     /*
> >      十进制转换成二进制
> >      最终要将余数进行倒读
> >      如何实现倒读余数呢？
> >      只需要将递归体放在打印余数的上面即可
> >
> >
> >      这种写法利用了栈的先进后出的特点
> >      先入栈也就是先求余数的，更大的数，反而最后打印余数
> >      后入栈也就是后求余数的，更小的数，反而最先打印余数
> >      这样就实现倒读余数
> >  */
> >     printf("%u", n % 2);
> > }
> >
> >
> >
> >
> > int main(void) {
> >     decimal_to_binary(777);
> >     printf("\n");
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：打印目标步骤汉诺塔移动轨迹

> **汉诺塔移动轨迹的扩展题，感兴趣且学有余力可以研究一下，不做统一要求。**
>
> 现在你已经知道如何打印n个盘子汉诺塔问题的移动轨迹了，那么在这个的基础上，我们进行以下扩展：
>
> 对于n个盘子的汉诺塔问题，给定一个整数m，要求在控制台打印出m + 1步的移动轨迹。
>
> 程序的运行图如下所示：
>
> ![扩展题1-示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/03_%E5%87%BD%E6%95%B0%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/004_6b57a510-c3c3-4b31-9d1b-61dff60944c61712483742227.jpg)
>
> **提示：**
>
> 既然要打印m + 1步的移动轨迹，那么肯定需要计数器记录移动的步骤，需要用什么变量呢？
>
> 核心思路就还是move函数的递归，但要加上一个计数器，实际编码时注意边界值就可以了。
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > /*
> >     curr_steps用于指示当前移动的步数
> >     用static修饰的全局变量可以限制此变量仅在文件内部生效
> >     为什么不用静态局部变量呢?
> >     如果在move函数内部使用静态局部变量, 那么就无法将它归1了
> > */
> > static int curr_steps;
> >
> >
> > void move(int n, int m, char start, char target, char sup) {
> >     // 递归的出口
> >     if (n == 0) {
> >         // 没有盘子啥也不做，直接结束递归
> >         return;
> >     }
> >     // 递归体
> >     // 分解成三步
> >     // 1.第一步: 将n-1个盘子,从start塔移动到sup塔,target塔用于辅助
> >     move(n - 1, m, start, sup, target);
> >
> >
> >     // 2.第二步: 将1个盘子,从start塔移动到target塔,这里可以直接打印
> >     if (curr_steps == m + 1) {
> >         printf("%c --> %c\n", start, target);
> >     }
> >     curr_steps++;
> >
> >
> >     // 3.第三部: 将n-1个盘子,从sup塔移动到target塔,start塔用于辅助
> >     move(n - 1, m, sup, target, start);
> > }
> > void next_move_track(int n, int m) {
> >     if (n <= 0) {
> >         printf("error: 盘子数量小于等于0.\n");
> >         return;
> >     }
> >     int total_steps = (1LL << n) - 1;
> >
> >
> >     if (m < 0 || m >= total_steps) {
> >         printf("error: %d个盘子的汉诺塔问题没有%d步.\n", n, (m + 1));
> >         return;
> >     }
> >     curr_steps = 1;
> >     printf("%d个盘子的汉诺塔问题, 第%d步的移动轨迹是: ", n, (m + 1));
> >     move(n, m, 'A', 'C', 'B');
> > }
> >
> >
> > int main(void) {
> >     next_move_track(2, 2);
> >     next_move_track(3, 2);
> >     next_move_track(4, 10);
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-04"></a>

## 04 指针和数组阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/04_指针和数组阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 数组与指针基础练习题1

> **以下题目功能，都要求编写函数将数组作为参数传递来实现：**
>
> 1.编写函数交换数组中两个下标的元素。函数声明如下：void swap(int \*arr, int i, int j) 。要求不使用\[\]运算符，将\[\]还原成解引用运算符和指针加法来完成。
>
> 2.数组元素的逆序。要求使用\[\]运算符以及纯粹指针操作两种方式来完成。
>
> 3.数组元素求和。要求使用"\*p++"语法结构来完成数组元素的累加 。
>
> 4.给定一个int数组以及一个目标值target，请编写函数找到这个目标值的下标，要求该函数没有返回值。（目标元素在数组中唯一，不考虑多次出现目标元素的情况）
>
> 5.编写一个函数，检查一个整数数组是否是回文，即正序与倒序相同。例如\[1,2,3,2,1\]就是回文的。要求使用指针的算术运算，不要使用取下标\[\]运算符。
>
> 6.给定一个非空整数数组src，再给定一个足够长的dest数组。编写一个函数 copy\_array，使用 \*p++ 复制src数组到dest数组。
>
> 注意：这道题目要把代码写得尽量简洁！！
>
> 7.给定一个整数数组，将所有奇数移到数组前面，偶数移到数组后面。（扩展题）
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **第一题非常简单，无非就是将"\[\]"运算符都还原成解引用的形式，参考代码如下：**
> >
> > ```c
> > // 使用指针操作交换数组中的两个元素
> > void swap(int *arr, int i, int j) {
> >     // 交换 arr[i] 和 arr[j]
> >     int temp = *(arr + i);   // tmp = arr[i]
> >     *(arr + i) = *(arr + j); // arr[i] = arr[j]
> >     *(arr + j) = temp;       // arr[j] = tmp
> > }
> > ```
> >
> > **第二题也非常简单，是上课讲过的，参考代码如下：**
> >
> > ```c
> > // 使用指针操作逆序数组中的元素
> > void reverse_by_ptr(int *arr, int n) {
> >     // 定义起始指针指向数组的第一个元素
> >     int *start_ptr = arr;
> >     // 定义结束指针指向数组的最后一个元素
> >     int *end_ptr = arr + n - 1;
> >
> >
> >     // 当起始指针小于结束指针时，执行循环
> >     while (start_ptr < end_ptr) {
> >         // 交换两个指针指向的元素
> >         int temp = *start_ptr;
> >         *start_ptr = *end_ptr;
> >         *end_ptr = temp;
> >
> >
> >         // 将起始指针后移一个元素，将结束指针前移一个元素
> >         start_ptr++;
> >         end_ptr--;
> >     }
> > }
> >
> >
> > // 先用纯粹的C基础代码来实现, 不用指针操作, 只用[]取下标运算
> > // 这个操作无需额外的临时数组, 直接原地交换就可以实现了
> > // 0 <-> len - 1, 1 <-> len - 2.... i <-> len - i - 1
> > void reverse_arr(int arr[], int len){
> >     for (int i = 0; i < len / 2; i++){
> >         int tmp = arr[i];
> >         arr[i] = arr[len - 1 - i];
> >         arr[len - 1 - i] = tmp;
> >     }
> > }
> > ```
> >
> > **第三题参考代码如下：**
> >
> > ```c
> > // 遍历求和数组
> > int sum_arr(int arr[], int len) {
> >     int* p = arr;
> >     int sum = 0;
> >     // 每循环一次累加一次元素并且刚好指针p移动一个位置
> >     while (p < arr + len) {
> >         sum += *p++;
> >     }
> >     return sum;
> > }
> > ```
> >
> > **第四题参考代码：**
> >
> > ```c
> > // 使用指针操作找到目标值的下标
> > void find_target_index(int *arr, int len, int target, int *result_index) {
> >     // 初始化下标为-1，表示未找到
> >     *result_index = -1;
> >
> >
> >     for (int i = 0; i < len; i++) {
> >         if (arr[i] == target) {
> >             // 如果找到目标值，更新结果下标并结束循环
> >             *result_index= i;
> >             break;
> >         }
> >     }
> >     // 如果循环结束还没找到，*resultIndex 仍为-1，表示目标值不在数组中
> > }
> > ```
> >
> > **第五题参考代码：**
> >
> > ```c
> > /*
> >  回文数组(palindrome array)即正读和反读一样的数组
> >  整个实现的过程非常类似于数组逆序
> >  用两个指针指向数组开头和末尾
> >  然后两个比较指针指向的元素，若任意元素不相等，就不是回文数组
> > */
> > bool is_palindrome(int* arr, int len) {
> >     int* start = arr;          // 指向数组首元素
> >     int* end = array + len - 1; // 指向数组尾元素
> >
> >
> >     // 首尾指针未相遇，那就继续移动指针比较两个元素的值
> >     while (start < end) {
> >         if (*start != *end) { // 如果两个指针指向的元素不相等，则不是回文数组
> >             return false;
> >         }
> >         start++; 
> >         end--;   
> >     }
> >     return true; // 所有对应元素检查结束，都相等，则是回文数组
> > }
> > ```
> >
> > **第六题参考代码：**
> >
> > ```c
> > // len是src源数组的长度
> > void copy_arr(int* src, int* dest, int len) {
> >     // 将源数组中所有元素复制过去，所以指针要移动len次
> >     while (len--) {
> >         *dest++ = *src++;
> >     }
> > }
> >
> >
> > int main(void) {
> >     int src[] = { 0, 2, 3, 4, 5 };
> >     int dest[10];
> >
> >
> >     copy_arr(src, dest, 5);
> >     return 0;
> > }
> > ```
> >
> > **第七题参考代码，需要使用双指针法求解：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
> > /*
> > * 所有的奇数都要移动到前面，所有的偶数都要移动到后面
> > * 我们采用双指针的思路解决这道题：
> > * 1.定义一个指针start指向数组首元素，它用于寻找数组左边的偶数
> > * 2.定义一个指针end指向数组尾元素，它用于寻找数组右边的奇数
> > * 接下来：
> > * start指针向右移动直到：
> > *   1.碰到一个偶数
> > *   2.或者与end相遇
> > * end指针向左移动直到：
> > *   1.碰到一个奇数
> > *   2.或者与start相遇
> > * 总之，当两个指针都停下来的时候：
> > *   1.start指向一个偶数且end指向一个奇数
> > *   2.start与end相遇
> > * 所以在start与end没相遇的前提下：
> > *   交换两个两个指针指向的元素
> > * 在最终两个指针相遇时，所有的奇数元素一定在前面
> > *
> > */
> > void separate_odd_even(int arr[], int len) {
> >     int* start = arr;
> >     int* end = arr + len - 1;
> >
> >
> >     // 只要不相遇就可能出现交换
> >     while (start < end) {
> >         // 只要没相遇并且没有找到偶数，就向右移动start
> >         while (start < end && (*start % 2 != 0)) {
> >             start++;
> >         }
> >         // 只要没相遇并且没有找到奇数，就向左移动end
> >         while (start < end && (*end % 2 == 0)) {
> >             end--;
> >         }
> >
> >
> >         // 如果未相遇说明start指向一个偶数，end指向一个奇数，需要交换
> >         if (start < end) {
> >             int tmp = *start;
> >             *start = *end;
> >             *end = tmp;
> >
> >
> >             // 交换元素后，指针继续移动
> >             start++;
> >             end--;
> >         }
> >     }
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 1,23,34,32,4,32,4,23,12,33,4,89,324,821,213,12,3,12,312,313,123,12 };
> >     separate_odd_even(arr, ARR_LEN(arr));
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 数组与指针基础练习题2

> **第一题：**
>
> 查找数组的最大值和最小值，但要将最大值作为返回值返回，最小值则依靠传入的指针完成赋值。
>
> **要求不能使用"\[\]"运算符。**
>
> 函数的声明如下：
>
> ```c
> int max_min(int *arr, int len, int *pmin);
> ```
>
> **第二题：**
>
> 求平均值，给定一个double数组，求平均值，并且返回。
>
> **要求使用while循环遍历数组，然后配合"\*p++"的语法实现。**
>
> 函数的声明如下：
>
> ```c
> double get_ave(double *arr, int len); 
> ```
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **第一题和课堂上讲的题目实现非常类似，参考代码如下：**
> >
> > ```c
> > int max_min(int *arr, int len, int *pmin) {
> >     int max = *arr; // 假设第一个元素是最大的
> >     *pmin = *arr; // 同样假设第一个元素是最小的
> >     int *p = arr + 1; // 指向数组的第二个元素
> >
> >
> >     while (p < arr + len) {
> >         if (*p > max) {
> >             max = *p;
> >         }
> >         if (*p < *pmin) {
> >             *pmin = *p;
> >         }
> >         p++; // 移动到下一个元素
> >     }
> >     return max;
> > }
> > ```
> >
> > **第二题参考代码：**
> >
> > ```c
> > double get_ave(double *arr, int len) {
> >     double sum = 0.0;
> >     double *p = arr;
> >
> >
> >     while (p < arr + len) {
> >         sum += *p++; // 取出当前指针指向的值，然后将指针向后移动
> >     }
> >
> >
> >     return sum / len; 
> > }
> > ```
>
> 以上。

#### 数组与指针基础练习题3

> 编写函数，查找一个int数组中的最大元素和第二大元素，并将它们分别存放在由 largest 和 second\_largest 指向的变量中。
>
> 按照下面的函数声明来实现这个函数。
>
> ```c
> void find_two_largest(int arr[], int n, int* largest, int* second_largest);
> ```
>
> **注意：为了简化实现，数组不存在重复元素，请不要考虑存在重复元素的情况。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > // 前提：arr数组不存在重复元素
> > void find_two_largest(int arr[], int n, int *largest, int *second_largest) {
> >     // 将数组的前两个元素设置为最大值和第二最大值
> >     *largest = arr[0] > arr[1] ? arr[0] : arr[1];
> >     *second_largest = arr[0] < arr[1] ? arr[0] : arr[1];
> >
> >
> >     for (int i = 2; i < n; i++) {   // 从第三个元素开始遍历
> >         if (arr[i] > *largest) {
> >             // 如果当前元素大于最大值，则更新最大值，并将原最大值赋给第二大值
> >             *second_largest = *largest;
> >             *largest = arr[i];
> >         }
> >         else if (arr[i] > *second_largest) {
> >             // 如果当前元素大于第二大值但小于最大值，则更新第二大值
> >             *second_largest = arr[i];
> >         }
> >     }
> > }
> >
> >
> > int main(void) {
> >     int largest, second_largest;
> >     int arr[] = { 9, 5, 2, 7, 1, 3, 4, 6, 8, 0 };
> >     find_two_largest(arr, 10, &largest, &second_largest);
> >     printf("largest = %d, second_largest = %d\n", largest, second_largest);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 数组与指针基础练习题4

> **基于以下函数声明，实现函数：**
>
> ```c
> void split_time(long total_sec, int* hour, int* minute, int* second);
> ```
>
> **形参中的 total\_sec 表示从凌晨00:00:00开始，到现在时间的秒数。**
>
> **请将 total\_sec 转化以时(0-23)、分(0-59)、秒(0-59)表示的时间，并存放到函数外部由指针 hour, minute, second 指向的变量中。**
>
> **并在函数调用的位置，打印出当前的时间。**
>
> **测试用例：**
>
> **total\_sec = 0，表示时间 00:00:00**
>
> **total\_sec = 9527，表示时间 02:38:47**
>
> **total\_sec = 3001，表示时间 00:50:01**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > void split_time(long total_sec, int *hour, int *minute, int *second) {
> >     // 计算秒数
> >     *second = total_sec % 60;
> >     // 计算分钟数
> >     *minute = (total_sec / 60) % 60;
> >     // 计算小时数
> >     *hour = (total_sec / 60 / 60) % 24;
> > }
> >
> >
> > int main() {
> >     long total_sec = 3001;  
> >     int hour, minute, second;
> >
> >
> >     split_time(total_sec, &hour, &minute, &second); 
> >
> >
> >     // 打印当前时间，%02d意味着如果整数小于2位，则在前面补0
> >     printf("当前时间为：%02d:%02d:%02d\n", hour, minute, second);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：数组分区思想

> 数组分区（Partitioning）是一种将数组元素重新排列的操作，使得符合某种条件的元素位于一侧，而不符合条件的元素位于另一侧。
>
> 数组分区在很多算法的实现当中，都是非常重要和关键的步骤，最典型的例子就是快速排序算法的实现。
>
> 除此之外，数组分区的应用还包括：
>
> 1. 将整数数组分为奇数和偶数两部分，比如移动奇数到数组前部，偶数到后部。
> 2. 分离负数和正数，将所有负数移至数组的一端，正数移到另一端。
> 3. 字符串中删除某个字符。
> 4. 荷兰国旗问题。
> 5. ...
>
> 这里我们就以int数组实现奇偶分区来探讨一下数组分区的思想以及实现。
>
> > 题目：
> >
> > 给定一个整数数组，将所有奇数移到数组前面，偶数移到数组后面。
>
> 首先，实现数组的分区操作，最容易想到且容易实现的应该是——利用临时数组实现分区。
>
> ```c
> /*
>     数组分区一个最简单粗暴,容易理解的实现是:
>     利用临时数组来进行分区:
>     1.分配一个临时数组,长度和原数组是一样的(动态内存分配)
>     2.遍历原数组, 将原数组中的所有奇数放入临时数组的前面
>     3.再遍历一次原数组, 将原数组中的所有偶数放入临时数组的后面
>     4.遍历临时数组, 将临时数组的元素全部覆盖到原数组
>
>
>     缺点:
>     1.需要额外的内存空间占用
>     2.需要多次遍历数组,显然效率也比较差
>
>
>     优点:
>     1.简单直接,易于理解
>     2.是稳定的(算法执行后,不会改变原始数据集元素的相对位置)
> */
> void separate_odd_even(int arr[], int len) {
>     int tmp[N];
>     int tmp_idx = 0;    // 临时数组的下标,从0开始,每将一个元素放入临时数组,下标就加1
>     // 遍历原数组,将奇数放入临时数组前面
>     for (int i = 0; i < len; i++) {
>         if (arr[i] % 2 != 0) {
>             tmp[tmp_idx++] = arr[i];
>         }
>     }
>
>
>     // 遍历原数组,将偶数放入临时数组后面
>     for (int i = 0; i < len; i++) {
>         if (arr[i] % 2 == 0) {
>             tmp[tmp_idx++] = arr[i];
>         }
>     }
>
>
>     // 将临时数组的元素全部复制回原数组
>     for (int i = 0; i < len; i++) {
>         arr[i] = tmp[i];
>     }
> }
> ```
>
> 从不使用额外空间和性能优化的角度出发，我们还有一种非常优秀的实现方式——双指针法。
>
> 所谓双指针法就是利用两个指针（数组可以基于双索引），来实现某些操作。双指针法在求解线性数据结构（数组/字符串/链表）的相关算法问题时，特别常用。
>
> 比如：
>
> 1. 数组的分区操作。数组快速排序，数组逆序、二分查找、回文检查等都可以基于双指针法实现。
> 2. 链表操作中的快慢指针法。可以用于求链表的中间结点，以及检查单链表是否有环等。
> 3. 字符串操作中的删除某个字符，也可以基于双指针实现。
>
> 下面我们将采用两种双指针法来实现数组奇偶分区。
>
> **方式一：双指针夹逼交换元素法**
>
> 参考代码如下：
>
> ```c
> /*
>     双指针法实现分区的思路一: 双指针夹逼交换元素法
>     创建两个指针: 左指针指向数组首元素, 右指针指向数组尾元素
>     左指针的目的是找到一个偶数,将它交换到数组末尾
>     右指针的目的是找到一个奇数,将它交换到数组开头
>
>
>     优点:不占用额外内存空间,而且只需要遍历数组一次,性能较好
>     缺点:不稳定,算法实现相对复杂
> */
> void separate_odd_even2(int arr[], int len) {
>     int *left = arr;
>     int *right = arr + len - 1;
>
>
>     // 左右指针不相遇那就继续往中间移动
>     while (left < right) {
>         // 左指针向右移动,直到找到一个偶数
>         // 细节: 在找的过程中, 左指针仍然不能越过右指针
>         while (left < right && (*left % 2 != 0)) {
>             left++;
>         }
>         // 右指针向左移动,直到找到一个奇数
>         while (left < right && (*right % 2 == 0)) {
>             right--;
>         }
>
>
>         // 代码运行到这里,说明左右指针都找到了目标元素,那就交换
>         if (left < right){
>             int tmp = *left;
>             *left = *right;
>             *right = tmp;
>
>
>             left++;
>             right--;
>         }
>     }
> }
> ```
>
> **方式二：双索引单向分区法**
>
> 参考代码如下：
>
> ```c
> /*
>     双指针单向分区交换元素法
>     由于数组本身就存在索引,所以双指针法的实现,并不一定就要创建指针
>     可以用索引模拟指针来实现双指针法
>
>
>     用索引还是用指针,从性能上来说,区别微乎其微,更多的是代码风格上的区别
>     双索引单向分区交换元素法的思路:
>     1.首先利用一个索引i来遍历整个数组,从0开始
>     2.再利用一个索引idx来指示下一个奇数应该放置的位置,从0开始
>     3.一旦i索引找到了一个奇数,那就把它交换到idx位置,这样就实现了把所有的奇数放到前面
>         当然这个交换的过程中,需要判断i和idx位置不同,位置不同才交换,否则没有交换的必要
>         (细节)当交换元素了或者两个索引指向同一个奇数时,都要向后移动idx索引的位置
>     4.当i索引遍历完整个数组时,奇数就都放置在了前面,偶数就都放在了后面
>
>
>     优点:不占用额外内存空间,而且只需要遍历数组一次,性能较好
>         奇数部分是稳定的
>     缺点:算法实现相对复杂,偶数部分不稳定
>
>
>     对于交换元素实现的算法,它的稳定与不稳定,可以考虑以下原则:
>     如果交换元素是连续的,相邻的元素交换,那么稳定性就可以保证,元素的相对位置就不会改变
>     如果交换元素是不连续的,是跨越长距离的交换,那么稳定性就难以保证了,可以认为是不稳定的
>     这个结论对后续学习比较排序算法是非常关键的
> */
> void separate_odd_even3(int arr[], int len) {
>     int idx = 0;    // 标记下一个奇数放置的位置
>     for (int i = 0; i < len; i++){
>         if (arr[i] %2 != 0) {
>             if (i != idx) {
>                 // 交换i和idx索引位置的元素
>                 int tmp = arr[i];
>                 arr[i] = arr[idx];
>                 arr[idx] = tmp;
>             }
>             idx++;
>         }
>     }
> }
> ```
>
> 以上。

#### 扩展：合并两个有序子数组

> 给定两个有序的整数子数组，然后将它们合并到一个足够长的新数组中，合并后的结果数组也应当是有序的。
>
> > 比如：
> >
> > 数组1：\[1, 3, 5, 6, 7\]
> >
> > 数组2：\[2, 3, 4, 8\]
> >
> > 合并后的结果数组3：\[1, 2, 3, 3, 4, 5, 6, 7, 8\]
>
> 提示：整个合并的过程类似"穿针引线"，利用两个索引逐一比较两个数组的元素大小，然后把较小元素放入数组3中。"穿针引线"结束，最终：
>
> 1. 一定会有一个数组元素被全部被赋值到数组3当中了
> 2. 另一个数组元素一定还有剩余
>
> 那就把剩余数组的元素全部复制到数组3的后面即可。
>
> **基于上述思想，参考代码如下：**
>
> > ###### 参考代码：
> >
> > ```c
> > #include <stdio.h>
> >
> >
> > #define N1 5  // 定义第一个数组的长度
> > #define N2 4  // 定义第二个数组的长度
> >
> >
> > // 合并两个有序数组的函数
> > void merge(const int arr1[], const int arr2[], int arr3[]) {
> >     // i是数组1的索引下标,j是数组2的,k是数组3的
> >     int i = 0, j = 0, k = 0;
> >
> >
> >     // 只要两个数组同时还有元素，那就比较对应位置元素，将较小元素放入数组3中
> >     while (i < N1 && j < N2) {
> >         /*
> >          这里使用<运算符意味着如果数组1和数组2中元素若一致
> >              则优先把数组2中的元素放入数组3
> >          这里如果使用<=运算符则意味着如果数组1和数组2中元素若一致
> >              优先把数组1中的元素放入数组3中
> >          这两种实现在这里是没有区别的，因为元素来自于两个独立的数组
> >          没有稳定性的概念，相同元素是数组1优先还是数组2优先没有区别
> >      */
> >         if (arr1[i] < arr2[j]) {    
> >             arr3[k++] = arr1[i++];
> >         }
> >         else {
> >             arr3[k++] = arr2[j++];
> >         }
> >     }
> >
> >
> >     // 如果第一个数组还有剩余，继续添加
> >     while (i < N1) {
> >         arr3[k++] = arr1[i++];
> >     }
> >
> >
> >     // 如果第二个数组还有剩余，继续添加
> >     while (j < N2) {
> >         arr3[k++] = arr2[j++];
> >     }
> > }
> >
> >
> > int main(void) {
> >     int arr1[N1] = { 1, 3, 5, 6, 7 };
> >     int arr2[N2] = { 2, 3, 4, 8 };
> >
> >
> >     // 用于存储结果的数组
> >     int arr3[N1 + N2];  
> >     merge(arr1, arr2, arr3);  // 调用合并函数
> >
> >
> >     // 打印合并后的数组
> >     for (int i = 0; i < N1 + N2; i++) {
> >         printf("%d ", arr3[i]);
> >     }
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：分离非负数以及正数

> 给定一个整数数组，请将**所有非正数(包含负数和0)**全部移到数组开头，正数则全部移到数组末尾，要求原地完成，不使用额外内存空间。
>
> > 比如：
> >
> > 数组\[1, -2, 3, 0, -9, 0, 10, 3\]
> >
> > 最终分组完成后的效果应该是\[非正数（包含0）, 正数\]（稳定性不做要求）
>
> 提示：仍然可以基于双指针单向分区或夹逼法求解。
>
> **参考代码如下：**
>
> > ###### 参考代码：
> >
> > **解法一：双索引单向分区法**
> >
> > ```c
> > // 函数用于将所有非正数移到数组的开头，所有正数移到数组的末尾
> > void separate_arr(int arr[], int size) {
> >     int idx = 0;  // 索引idx用于标记下一个非正数应该放置的位置
> >     for (int i = 0; i < size; i++) {
> >         // 如果当前元素是非正数（包括 0）
> >         if (arr[i] <= 0) {
> >             if (i != idx) {  // i和idx索引不是同一个位置时才交换元素
> >                 int tmp = arr[i];
> >                 arr[i] = arr[idx];
> >                 arr[idx] = tmp;
> >             }
> >             // idx位置加1，标记下一个位置为新的非正数应该放置的位置
> >             idx++;
> >         }
> >     }
> > }
> > ```
> >
> > **解法二：双索引双向夹逼交换元素法**
> >
> > ```c
> > // 左索引寻找正数，右索引寻找非正数，然后交换元素实现分区操作
> > void separate_arr2(int arr[], int size) {
> >     int left = 0;
> >     int right = size - 1;
> >
> >
> >     while (left < right) {
> >         while (left < right && arr[left] <= 0) {
> >             left++;  // 移动左索引，直到找到正数
> >         }
> >         while (left < right && arr[right] > 0) {
> >             right--;  // 移动右索引，直到找到非正数
> >         }
> >         if (left < right) {
> >             int tmp = arr[left];
> >             arr[left] = arr[right];
> >             arr[right] = tmp;
> >         }
> >     }
> > }
> > ```
>
> 以上。

#### 扩展：荷兰国旗问题

> 荷兰国旗问题（也称为三色排序问题）是一个计算机科学中的经典问题，常用于讨论快速排序算法的三向分区(three-way-partitioning)策略。
>
> 这个问题来源于荷兰国旗的三种颜色：红色、白色和蓝色，目标是将含有三种颜色的条带（通常用0, 1, 2来代表三种颜色）重新排序，使得同一颜色的条带聚集在一起，并且顺序是红、白、蓝（或0、1、2）。
>
> 现在给定一个整型数组，其中包含不确定数量的三个元素0、1、2，请将该整数数组分区为三个部分：0在前面，1在中间，2在最后面。
>
> > 举例：
> >
> > 整型数组为：\[0, 1, 2, 2, 1, 0, 0, 2, 1, 1, 0, 2\]
> >
> > 分区后的结果是：\[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2\]
>
> 由于进行的是三向分区，那么单纯的双指针法就无法实现了，这时要使用"三指针法"。其算法的思路是：
>
> 1. 创建一个**"左索引left"**指向数组左边界(首元素)，创建一个**"右索引right"**指向数组的右边界(尾元素)，创建一个**"中间索引mid"**开始时也指向数组首元素
> 2. 利用中间索引mid来遍历整个数组。
> 3. 左索引left的作用是：标记下一个0元素应该放置的位置（小于基准值的元素应放置的位置）
> 4. 中间索引mid的作用是：标记下一个1元素应该放置的位置（等于基准的元素应放置的位置）
> 5. 右索引right的作用是：标记下一个2元素应该放置的位置（大于基准的元素应放置的位置）
>
> 核心操作思路是：
>
> 遍历数组，条件是`mid <= high`，在这个过程中：
>
> 1. 如果 `mid` 位置的元素是0，则需要将mid位置和left位置的元素交换，然后 `left` 和 `mid`索引都加1。这里为什么两个索引都需要加1呢？请看下图：
>     ![荷兰国旗问题-图解1](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/04_%E6%8C%87%E9%92%88%E5%92%8C%E6%95%B0%E7%BB%84%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_image-20240521212824233.png)
> 2. 如果 `mid`位置的元素是1，那么不需要任何交换，只需要mid索引加1即可。这个很好理解，不解释了。
> 3. 如果mid位置的元素是2，则需要将mid位置和right位置的元素交换，然后 `right` 索引需要减1。这里的问题是：为什么mid索引就不需要加1了呢？仍然请看下图：
>     ![荷兰国旗问题-图解2](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/04_%E6%8C%87%E9%92%88%E5%92%8C%E6%95%B0%E7%BB%84%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/002_image-20240521213639285.png)
>
> 遍历结束时，数组的三个分区就分区完成了。
>
> 参考代码实现如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define SWAP(arr, i, j) { \
> >     int temp = arr[i]; \
> >     arr[i] = arr[j]; \
> >     arr[j] = temp; \
> > }
> >
> >
> > void three_partition(int arr[], int size) {
> >     int left = 0, mid = 0, right = size - 1;
> >     while (mid <= right) {
> >         switch (arr[mid]) {
> >             case 0:
> >                 if (mid != left) {
> >                     SWAP(arr, mid, left);
> >                 }
> >                 mid++;
> >                 left++;
> >                 break;
> >             case 1:
> >                 mid++;
> >                 break;
> >             case 2:
> >                 SWAP(arr, mid, right);
> >                 right--;
> >                 break;
> >         }
> >     }
> > }
> > ```
>
> 以上。

#### 扩展：三向分区负数、0以及正数

> 如果你已经搞清楚了荷兰国旗问题，那么这个问题就比较简单了。
>
> > 比如：
> >
> > 数组\[1, -2, 3, 0, -9, 0, 10, 3\]
> >
> > 最终分组完成后的效果应该是\[负数, 0, 0, 正数\]（稳定性不做要求）
>
> 思路是：仍然是三个索引：
>
> 1. left索引标记下一个负数放置的位置
> 2. mid索引用于遍历数组，并且标记0元素放置的位置
> 3. right索引用标记下一个正数放置的位置
>
> 核心操作逻辑是：
>
> 1. 当mid索引发现一个负数时，交换left和mid索引位置的元素，并后移1位mid和left索引（原理是一样的）
> 2. 当mid索引发现一个0时，不需要交换元素，仅需要mid索引后移1位
> 3. 当mid索引发现一个正数时，交换right和mid索引位置的元素，仅后移1位right索引，mid索引不动。
>
> 当mid索引遍历完整个数组，这个三向分区操作就完成了。
>
> 参考代码实现如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > void three_way_partition(int arr[], int size) {
> >     int left = 0, mid = 0, right = size - 1;
> >
> >
> >     while (mid <= right) {
> >         if (arr[mid] < 0) {
> >             // 交换arr[low]和arr[mid]，并移动low和mid索引
> >             if (mid != left) {
> >                 SWAP(arr, mid, left);
> >             }
> >             left++;
> >             mid++;
> >         }
> >         else if (arr[mid] == 0) {
> >             // 如果是0，只移动mid索引
> >             mid++;
> >         }
> >         else {
> >             // 交换arr[mid]和arr[high]，并移动high索引
> >             SWAP(arr, mid, right);
> >             right--;
> >         }
> >     }
> > }
> > ```
>
> 以上。

### The End

<a id="ch-05"></a>

## 05 字符串阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/05_字符串阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 手动实现字符串处理库函数

> **依照C语言的字符串标准库函数，手动实现以下函数：**
>
> ```c
> size_t my_strlen(const char *str);
> char *my_strcpy(char *dest, const char *src);
> char *my_strncpy(char *dest, const char *src, size_t n);
> char *my_strcat(char *dest, const char *src);
> char *my_strncat(char *dest, const char *src, size_t n);
> int my_strcmp(const char *str1, const char *str2);
> ```
>
> **函数的实现要模拟标准库函数中对应函数的行为，不要依据自己的理解来实现这些函数。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **第一题参考代码如下：**
> >
> > ```C
> > size_t my_strlen(const char* s) {
> >     // 用一个指针记录数组首元素
> >     const char* p = s;
> >     // 惯用法: 遍历直到字符串的末尾，
> >     while (*s) {
> >         s++;
> >     }   // 循环结束时，s指针指向了空字符，p指针指向数组首元素
> >
> >
> >     // 相当于空字符的下标减去首元素下标，结果就是字符串的长度
> >     return s - p;
> > }
> > ```
> >
> > **第二题参考代码如下：**
> >
> > ```c
> > char *my_strcpy(char *dest, const char *src) {
> >     char *tmp = dest;   // dest数组的首元素指针要作为返回值,所以要临时保存一下
> >     while (*dest++ = *src++)
> >         ;
> >     return tmp;
> > }
> > ```
> >
> > **第三题参考代码如下：**
> >
> > ```c
> > char *my_strncpy(char *dest, const char *src, size_t n) {
> >     char *tmp = dest;
> >     while (n > 0 && (*dest = *src)) { 
> >         dest++;
> >         src++;
> >         n--;
> >     }// while循环结束时，src指针指向指向空字符，dest指针也指向空字符
> >     while (n > 0) {
> >         *dest++ = '\0';
> >         n--;
> >     }
> >     return tmp;
> > }
> > ```
> >
> > **第四题参考代码：**
> >
> > ```c
> > char* my_strcat(char* dest, const char* src) {
> >     char* temp = dest;
> >     // 找到dest的末尾，也就是让dest指针指向空字符
> >     while (*dest) {
> >         dest++;
> >     }
> >     while ((*dest++ = *src++))
> >         ;
> >     return temp;  // 返回dest的起始地址
> > }
> > ```
> >
> > **第五题参考代码：**
> >
> > ```c
> > char* my_strncat(char* dest, const char* src, int n) {
> >     char* temp = dest;
> >     while (*dest) {
> >         dest++;
> >     }
> >     // 拷贝最多n个字符从src到dest的末尾
> >     while (n-- && (*src)) {
> >         *dest++ = *src++;
> >     }
> >     // 确保dest以空字符结尾,所以一定会将dest末尾置为空字符
> >     *dest = '\0';
> >     return temp;  // 返回dest的起始地址
> > }
> > ```
> >
> > **第六题参考代码：**
> >
> > ```c
> > int my_strcmp(const char* s1, const char* s2) {
> >     while (*s1 && (*s1 == *s2)) {
> >         // 移动两个指针，比较下一对字符
> >         s1++;
> >         s2++;
> >     }
> >     /*
> >     * while循环结束的条件是：
> >     * 1.s1指针指向了空字符
> >     * 2.或者s2指针指向了空字符
> >     * 3.或者s1和s2指针指向的字符不一致
> >     * 不管是哪一种情况，返回它们的编码值差就是结果
> >     */
> >     return *s1 - *s2;
> > }
> > ```
>
> 以上。

#### 统计字符串中的数字和字母数量

> **给定一个字符串，要求它可能包含数字和字母。**
>
> 请编写函数，统计该字符串中每个字符出现的次数，统计过程中忽略大小写的差异，并打印最终每个字符出现的次数。
>
> 提示：
>
> 用一个int数组存储字符出现的次数，可以用一个128长度的数组，这样数组下标位置的元素就是该编码值字符出现的次数，缺点是浪费空间，但你可以先写一个这样的实现。
>
> **（扩展）做完后，你可以思考一下：**
>
> 实际上只会有36个字符(10个数字和26个不区分大小写的字母)，所以int数组的长度实际上只需要36就可以了。
>
> 那么怎么把数组的长度缩短到36呢？
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **基础版本以及优化版本的实现，参考代码如下：**
> >
> > ```c
> > #include <stdio.h>
> > #define MAX_CHARS 128  // ASCII 编码表的大小
> > #define TOTAL_ALNUM 36  // 字母和数字一共36个
> >
> >
> > // 用128长度的数组,此时字符的编码值就是元素的下标,该下标位置的元素值就是该字符出现的次数
> > void count_characters(const char *str) {
> >     int count[MAX_CHARS] = { 0 };  // 初始化计数数组
> >
> >
> >     // 遍历字符串并统计每个字符出现的次数
> >     while (*str) {
> >         char ch = tolower(*str);  // 将字符转换为小写以忽略大小写差异
> >         if (isalnum(ch)) {  // 检查是否为字母或数字
> >             count[ch]++;
> >         }
> >         str++;
> >     }
> >
> >
> >     // 打印统计结果
> >     for (int i = 0; i < MAX_CHARS; i++) {
> >         if (count[i] > 0) {  // 只打印出现过的字符
> >             printf("'%c' 出现了 %d 次\n", i, count[i]);
> >         }
> >     }
> > }
> >
> >
> > /*
> >     实际上数组的长度只需要36个就够了
> >     因为有26个字母 + 10个数字
> >     但要计算一下编码值和数组下标的转换关系
> >     假如数组前10个元素存储的是数字，后26个元素存储的是字母，那么：
> >     字符是数字: 下标是编码值 - '0'
> >     字符是字母: 下标是编码值 - 'a' + 10(要把字母先都转换成小写,加10的原因是前面十个字符都是数字,字母的下标从10开始)
> > */
> > // 计算字符对应的数组索引
> > int char_to_index(char ch) {
> >     if (isdigit(ch)) {
> >         return ch - '0';  // 数字字符的索引从0开始
> >     }
> >     // 不是数字一定是字母
> >     ch = tolower(ch); // 转换为小写字母
> >     return ch - 'a' + 10;  // 字母的索引从10开始 (0-9已经被数字占用)
> > }
> >
> >
> > void count_characters2(const char *str) {
> >     int count[TOTAL_ALNUM] = { 0 };  // 初始化计数数组
> >
> >
> >     // 遍历字符串并统计每个字符出现的次数
> >     while (*str) {
> >         char ch = *str;
> >         if (isalnum(ch)) {  // 检查是否为字母或数字
> >             // 转换编码值为下标
> >             int idx = char_to_index(ch);
> >             count[idx]++;
> >         }
> >         str++;
> >     }
> >
> >
> >     // 打印统计结果
> >     for (int i = 0; i < TOTAL_ALNUM; i++) {
> >         if (count[i] > 0) {  // 只打印出现过的字符
> >             if (i < 10) {  // 数字
> >                 printf("'%c' 出现了 %d 次\n", '0' + i, count[i]);
> >             }
> >             else {  // 字母
> >                 printf("'%c' 出现了 %d 次\n", 'a' + i - 10, count[i]);
> >             }
> >         }
> >     }
> > }
> >
> >
> >
> >
> > int main(void) {
> >     const char *str = "aaa111bbb222ccc";
> >     count_characters(str);
> >     printf("-----------------------\n");
> >     count_characters2(str);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 统计字符串当中的单词数量

> **编写一个函数，计算一个字符串中单词的数量。这里，单词被定义为由空格分隔的字符序列。**
>
> 例如，对于字符串"hello world! word Excel space blank"
>
> 就应该输出有6个单词
>
> **注意：空格可能连续出现。**
>
> 思路参考:
>
> 1.整个过程就是跳过前面的所有空白字符，先找到一个非空字符，然后再跳过所有非空字符找到一个空白字符，于是确定找到一个单词。
>
> 2.第二种思路: 遍历整个字符串，如果字符是非空格制表符，那么就是单词的一部分，继续遍历直到碰到空字符或者空格制表符，意味着单词结束，计数器加1
>
> 两种思路皆可。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **两种思路的参考代码如下：**
> >
> > ```c
> > #include <stdio.h>
> > #include <ctype.h>
> >
> >
> > // 第一种思路
> > int count_words(const char* str) {
> >     int count = 0; // 初始化单词计数为0
> >
> >
> >     // 从头开始遍历字符串
> >     while (*str) {
> >         // 在遍历的过程中如果碰到空格,始终跳过它
> >         // 由于空格可能有多个连续出现,所以这里要嵌套循环遍历字符串.
> >         while (*str && isspace(*str)) {
> >             str++;
> >         }
> >
> >
> >         // 代码运行到这里,遍历到的字符肯定不是空字符也不是空格,于是找到一个单词
> >         if (*str) {
> >             count++; // 找到一个单词，计数器加1
> >             // 继续遍历字符串，直到我们再次遇到空格或字符串结束
> >             while (*str && !isspace(*str)) {
> >                 str++;
> >             }
> >         }
> >     }
> >
> >
> >     return count; // 遍历结束，返回单词总数
> > }
> >
> >
> > // 第二种思路
> > int count_words2(char *str) {
> >     int count = 0;
> >     // 遍历字符串直到遇到字符串的结束符
> >     for (int i = 0; str[i]; i++) {
> >         // 遇到一个非空格或制表符,意味着它是单词中的某个字符
> >         if (!isblank(str[i])) {
> >             // 如果发现下一个字符是空字符或者空格制表符,那么说明一个单词结束了
> >             if (isblank(str[i + 1]) || str[i + 1] == '\0') {
> >                 count++;    // 因此计数器加1
> >             }
> >         }
> >     }
> >     return count;
> > }
> >
> >
> > int main(void) {
> >     char str[] = "hello world!  word  Excel space blank";
> >     int count = count_words(str);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 检查字符串中的小括号是否匹配

> 编写一个函数，检查给定的字符串中的圆括号`()`是否正确匹配。**注意只考虑小括号，字符串中没有其它括号。**
>
> 如字符串：((Hello) (World))
>
> 函数会返回一个布尔值，表示匹配成功或失败
>
> **注意：只考虑英文小括号()，不需要考虑其它括号，更不需要考虑中文符号。**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **只考虑小括号的匹配，所以整个实现是比较简单的：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> >
> >
> > // 函数用于检查字符串中的圆括号是否正确匹配
> > bool check_parentheses(const char* str) {
> >     int count = 0;
> >     // 遍历整个字符串到空字符
> >     while (*str) {
> >         // 先找到左括号
> >         if (*str == '(') {
> >             // 统计左括号个数，遇到右括号就--
> >             count++;
> >         }
> >         else if (*str == ')') {
> >             if (count == 0) {
> >                 // 一开始就碰到右括号 匹配失败
> >                 return false;
> >             }
> >             count--;
> >         }
> >         str++;
> >     }
> >     return count == 0; // 检查是否所有左括号都被匹配了
> > }
> >
> >
> > int main(void) {
> >     const char* str = "((Hello) (World))";
> >     if (check_parentheses(str)) {
> >         printf("匹配成功！\n");
> >     }
> >     else {
> >         printf("匹配失败！\n");
> >     }
> >     return 0;
> > }
> > ```
>
> 以上。

#### 字符串数组基础练习题

> 在main函数当中，先写出下列代码，用两种不同的方式来定义实现字符串数组：
>
> ```c
> // char类型二维数组实现字符串数组
> char fruits1[][10] = {
> "apple",
> "banana",
> "cherry"
> };
>
>
> // char*指针数组实现字符串数组
> char *fruits2[] = {
> "apple",
> "banana",
> "cherry"
> };
> ```
>
> 请完成以下编程或者回答相应的问题。
>
> **题目一：**
>
> 请分别遍历 `fruits1` 和 `fruits2`这两个字符串数组，输出每个字符串的内容及其长度。
>
> **题目二：**
>
> 请分别将两个字符串数组中的第一个字符串，修改成"orange"。
>
> 首先你需要回答：基于"="运算符直接赋值修改，能不能完成这样的操作？如果不能为什么？
>
> **提示：通过一定的手段，两个都可以完成修改。参考代码仅提供一种实现方式，若你能够实现，亦可采用自己的实现。**
>
> **题目三：**
>
> 请分别将两个字符串数组中的第二个字符串"banana"中的第一个字符'b'，修改成'B'。
>
> 首先你需要回答：基于"="运算符直接赋值修改，能不能完成这样的操作？如果不能为什么？
>
> **提示：通过一定的手段，两个都可以完成修改。参考代码仅提供一种实现方式，若你能够实现，亦可采用自己的实现。**
>
> **题目四：**
>
> 请自行定义初始化一个字符串数组`fruits3`，使得这个字符串数组既可以通过"="直接修改整个字符串的内容，也可以利用"="修改某个字符串的某个字符。
>
> **提示：实现方式不唯一，参考代码仅提供一种实现参考。**
>
> > ###### 参考的回答和参考的代码如下：
> >
> > **题目一：**
> >
> > 就是简单普通的打印字符串数组内容，且输出字符串长度。
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <string.h>
> >
> >
> > int main(void) {
> >     char fruits1[][10] = { "apple", "banana", "cherry" };
> >     char *fruits2[] = { "apple", "banana", "cherry" };
> >
> >
> >     // fruits1字符串数组的长度
> >     int size1 = sizeof(fruits1) / sizeof(fruits1[0]);
> >     // fruits2字符串数组的长度
> >     int size2 = sizeof(fruits2) / sizeof(fruits2[0]);
> >
> >
> >     printf("Fruits1:\n");
> >     for (int i = 0; i < size1; ++i) {
> >         printf("第%d个字符串是:%s, 字符串长度是:%zu\n", (i + 1), fruits1[i], strlen(fruits1[i]));
> >     }
> >
> >
> >     printf("\nFruits2:\n");
> >     for (int i = 0; i < size2; ++i) {
> >         printf("第%d个字符串是:%s, 字符串长度是:%zu\n", (i + 1), fruits2[i], strlen(fruits2[i]));
> >     }
> >
> >
> >     return 0;
> > }
> > ```
> >
> > **题目二：**
> >
> > 能否可以直接使用 `=` 修改字符串？
> >
> > 1. `fruits1[0] = "orange";` **不允许**，因为 `fruits1[0]` 是数组名，数组名是不能用"="重新赋值的。
> > 2. `fruits2[0] = "orange";` **允许**，因为 `fruits2[0]` 就是一个指针元素，指针是可以用"="改变指向的。
> >
> > 既然"fruits1\[0\]"就是一个数组，不能用"="赋值，那么就可以考虑用字符串复制操作来修改它整体的内容，当然要确保复制不能出现越界。
> >
> > 参考代码如下：
> >
> > ```c
> > // fruits1[0] = "orange";   // 禁止直接用"="赋值
> > // 字符串复制修改 fruits1 的第一个字符串
> > strcpy(fruits1[0], "orange");
> >
> >
> > // 修改 fruits2 的第一个字符串指针（只改变指向）
> > fruits2[0] = "orange";
> > ```
> >
> > **题目三：**
> >
> > 能否可以直接使用 `=` 修改字符串的某个字符呢？
> >
> > 1. `fruits1[1][0] = 'B';` **允许**，因为二维数组实现的字符串数组，其内存空间直接申请在栈上，可以随意修改内容。
> > 2. `fruits2[1][0] = 'B';` **不允许**，因为指针元素指向的是字符串字面值，是一个常量，不能够被修改。
> >
> > `fruits2[1][0] = 'B';` **不允许**是因为`fruits2[1]`指针指向的是一个字面值常量，所以想要修改必须先要改变指向才行，比如指向一个自身栈区的字符串。
> >
> > 参考代码如下：
> >
> > ```c 
> > // 修改 fruits1 的第二个字符串的第一个字符
> > fruits1[1][0] = 'B';
> >
> >
> > // fruits2[1][0] = 'B'; // 禁止修改字符串字面值
> > char banana_str[] = "banana";   // 栈上存储的字符串"banana"
> > fruits2[1] = banana_str;    // 修改指针的指向
> > fruits2[1][0] = 'B';  //修改成功
> > ```
> >
> > **题目四：**
> >
> > 分析：这样的字符串数组，显然只能用指针数组的方式来实现，而且指针指向的应该是自身栈区。
> >
> > 参考代码如下：
> >
> > ```c
> > char apple[] = "apple";
> > char banana[] = "banana";
> > char cherry[] = "cherry";
> > char *fruits3[] = {
> >     apple, banana, cherry
> > };
> >
> >
> > // 修改整个字符串
> > fruits3[0] = "orange";
> >
> >
> > // 修改某个字符
> > fruits3[1][0] = 'B';
> > ```
>
> 以上。

#### 命令行参数与字符串类型的转换

> 请你通过命令行参数传递额外的三个参数：
>
> > 10 8.8 hello
>
> 其含义如下：
>
> 1. 第一个额外命令行参数10：整数10
> 2. 第二个额外命令行参数8.8：浮点数8.8
> 3. 第三个额外命令行参数hello：就是字符串hello
>
> 关于如何传递命令行参数，在Windows环境下可以有两种选择：
>
> 1. 直接在集成开发环境VS当中传递命令行参数。
> 2. 在Windows的命令行，也就是CMD黑窗口中启动程序，传递命令行参数。
>
> **关于这两种方式，具体如何来完成，请参考文档：《字符串》当中的《命令行参数》小节。**
>
> 请你完成下面的操作：
>
> **题目一：**
>
> 先输出一下当前命令行参数的个数，再循环打印一下命令行参数字符串数组，输出的格式你可以自己来决定。
>
> **题目二：**
>
> 使用`sscanf`函数将两个额外的命令行参数，转换成它们对应的基本数据类型（int和double）。
>
> **题目三：**
>
> 在完成前两个命令行参数的类型转换后，请计算它们之和。
>
> 然后利用`sprintf`函数，加上最后一个命令行参数字符串，按照下面的格式来构建字符串并输出到字符数组中：
>
> "10 + 8.8 = 18.80hello"
>
> 最后打印这个字符数组表示的字符串。
>
> 一个参考的代码输出如下图所示：
>
> ![命令行参数与字符串类型的转换-演示图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/05_%E5%AD%97%E7%AC%A6%E4%B8%B2%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_202505162118139.png)
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > int main(int argc, char *argv[]) {
> >  if (argc != 4) {
> >      printf("命令行参数数量不正确,请重新输入!\n");
> >      return;
> >  }
> >
> >
> >  printf("argc = %d\n", argc);
> >
> >
> >  // 打印所有命令行参数
> >  for (int i = 0; i < argc; ++i) {
> >      printf("argv[%d]: %s\n", i, argv[i]);
> >  }
> >
> >
> >  // 第1个参数：转换为int
> >  int int_num = 0;
> >  sscanf(argv[1], "%d", &int_num);
> >
> >
> >  // 第2个参数：转换为double
> >  double double_num = 0.0;
> >  sscanf(argv[2], "%lf", &double_num);
> >
> >
> >  // 第3个参数：字符串无需转换
> >  char *string = argv[3];
> >
> >
> >  // 计算和，并构建输出字符串
> >  char result[100];
> >  sprintf(result, "%d + %.1f = %.2f%s", int_num, double_num, int_num + double_num, string);
> >
> >
> >  // 打印最终结果
> >  printf("结果字符串：%s\n", result);
> >
> >
> >  return 0;
> > }
> >
> >
> > ```
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：字符串替换/删除/分组操作

> **第一题：**
>
> 将字符串中的空格替换成 %020 (假定原字符数组能够存放替换后的字符串)。
>
> ```c
> void substitute_space(char* str);
> 输入: "hello world how "
> 输出: "hello%020world%020how%020"
> ```
>
> **注意：只考虑字符串中存在空格字符，不考虑制表、换行等其它空白字符。**
>
> **第二题：**
>
> 删除字符串中指定的字符。
>
> ```c
> void delete_character(char* str, char c);
> 输入: "abcdaefaghiagkl", 'a'
> 输出: "bcdefghigkl"
> ```
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **第一题，字符串替换操作，参考代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <string.h>
> >
> >
> > #define MAX_STR_LEN 100
> >
> >
> > /*
> >     思路一：使用临时数组替换空格
> >     初始化一个足够长度的临时数组
> >     然后遍历原数组，将非空格字符正常复制，但在复制空格时将空格替换成%020
> >     最后将临时数组字符串复制回原始字符字符数组中
> > */
> > void substitute_space(char *str) {
> >     char tmp[MAX_STR_LEN + 1];
> >     char *s = str;
> >     int i = 0;  // 临时数组的下标，用于定位复制操作的位置
> >     while (*s) {
> >         if (*s == ' ') {
> >             // 当前字符是空格就复制%020并使得i索引后移4位
> >             tmp[i] = '%';
> >             tmp[i + 1] = '0';
> >             tmp[i + 2] = '2';
> >             tmp[i + 3] = '0';
> >             i += 4;
> >         }
> >         else {
> >             tmp[i++] = *s;
> >         }
> >         s++;
> >     }
> >     tmp[i] = '\0';  // 不要忘记加空字符
> >
> >
> >     strcpy(str, tmp);
> > }
> >
> >
> > /*
> >     思路二：原地替换字符，不占用额外内存空间
> >     替换过程字符串肯定会变长, 为了更好实现避免覆盖掉未操作的字符, 最好倒着遍历字符串
> >     遍历的过程中,将字符向后移动
> >
> >
> >     于是就有一个重要的问题, 字符向后移动几个位置呢?
> >     首先我们要统计一下空格的数量count, 很明显空格数量越多，向后移动的位置越多
> >     那么：
> >     count代表当前剩余未处理的空格的数量
> >     非空格字符需要向后移动： count * 3
> >     空格字符替换成:
> >     '%' 字符的位置是当前空格的原始位置。
> >     前面的'0' 字符的位置是 '%' 字符位置加1。
> >     '2' 字符的位置是 '0' 字符位置加1。
> >     后面的'0' 字符的位置是 '2' 字符位置加1。
> > */
> > void substitute_space2(char *str) {
> >     int count = 0;  // 空格字符的数量
> >     char *p = str;
> >     while (*p) {
> >         if (*p == ' ') {
> >             count++;
> >         }
> >         p++;
> >     }   // while循环结束时,p指向空字符的下一个字符
> >     p--;    // p指针回退一个位置
> >
> >
> >     // 倒着遍历字符串, 此时count代表未处理空格字符的数量
> >     while (p >= str) {
> >         char c = *p;
> >         if (c == ' ') {
> >             *(p + 3 * count) = '0';
> >             *(p + 3 * count - 1) = '2';
> >             *(p + 3 * count - 2) = '0';
> >             *(p + 3 * count - 3) = '%';
> >             count--;
> >         }
> >         else {
> >             *(p + 3 * count) = c;
> >         }
> >         p--;
> >     }
> > }
> >
> >
> > int main(void) {
> >     char str[100] = "hello world how "; // str数组必须要足够长
> >     substitute_space(str);
> >     puts(str);
> >     return 0;
> > }
> > ```
> >
> > **第二题：字符串删除，可以基于字符串分组来实现，参考代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <string.h>
> >
> >
> > #define MAX_STR_LEN 100
> >
> >
> > /*
> >  思路一: 临时数组法
> >  遍历原字符串, 遇到需要删除的字符, 就不复制到临时数组
> >  其余字符正常复制到临时数组
> >  最后将临时数组复制回原字符串数组
> > */
> > void delete_character(char *str, char c) {
> >     char tmp[MAX_STR_LEN + 1];
> >
> >
> >     char *s = str;
> >     int i = 0; // 用于在临时数组中定位
> >     while (*s) {
> >         if (*s != c) { 
> >             // 如果当前字符不是要删除的字符, 将它添加到临时数组中
> >             tmp[i++] = *s;
> >         }
> >         s++;
> >     }
> >     // 不要忘记加空字符
> >     tmp[i] = '\0';
> >
> >
> >     strcpy(str, tmp); // 将临时数组的内容复制回原字符串
> > }
> >
> >
> > /*
> >  思路二: 原地删除字符串, 仍然使用双指针法, 仍然是一个单向分区的思想
> >  p指针用于遍历字符串
> >  pstore指针用于指示那些不被删除的元素该放置的位置
> >  一开始两个指针都指向首字符
> >  只要p找到一个非删除字符,那么就把它直接覆盖到pstore指针位置, pstore后移一位
> >  直到遍历完整个字符串, 所有的非删除字符都被移到了前面, 所有的待删除字符都移到了后面, 这就完成了分区
> >  此时p指针指向空字符的下一个字符
> >  pstore指针则指向第一个待删除目标字符, 于是只要把pstore指针位置的元素设置为空字符就完成了字符串删除
> > */
> > void delete_character2(char *str, char c) {
> >     char *pstore = str; // 下一个不等于c的元素应该置于的位置
> >     char *p = str;
> >
> >
> >     while (*p) {
> >         if (*p != c) {
> >             char tmp = *pstore;
> >             *pstore = *p;
> >             *p = tmp;
> >             pstore++;
> >         }
> >         p++;
> >     }
> >     *pstore = '\0';   // 不要忘记最后要添加空字符
> > }
> > int main(void) {
> >     char str[] = "abcdaefaghiagkl";
> >     delete_character2(str, 'a');
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：字符串字符分组

> **请编写函数，将字符串中的字母和数字分开，使得字符串中前一部分是数字，后一部分是字母。**
>
> ```c
> void seperate(char* str);
> 输入: "h1ell2o3"
> 结果: "123hello"或者任意数字在前，字母在后的字符串
> ```
>
> 注意：要求字符串只包含字母和数字，字符串的长度不超过100，且分组要最终在原数组上完成。
>
> **提供几个参考的实现思路：**
>
> **1.临时数组法。用两个临时数组一个装数字，一个装字母，然后再将数据合并回原数组。**
>
> **2.双指针夹逼交换法。两个指针向中间逼近，一个找字母一个找数字，找到后交换，直到两个指针相遇。**
>
> **3.双指针单向分区交换法。**
>
> **一个指针p用于遍历字符串，另一个指针p\_num从头开始向后移动，用于标记下一个数字应该插入的位置。**
>
> **p指针每发现一个数字，就把它交换到p\_num位置，然后p\_num指针后移。**
>
> **直到遍历完字符串，所有的数字都会被交换到前面，所有字母都会被交换到后面。**
>
> **最后，上面提到的双指针法，既可以用真正意义上的指针，也可以直接用索引。两者没有本质上的区别，更多是代码风格上的区别。**
>
> **基于上述思想，参考代码如下：**
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define MAX_STR_LEN 100
> >
> >
> > /*
> >     方式一：利用临时数组实现分组
> >     这种方式能保证字符相对位置不变
> >     但缺点是占用额外内存空间，且效率不高
> > */
> > void separate(char *str) {
> >     // 两个临时数组一个装字母一个装数字
> >     // 虽然一个临时数组也可以实现，但会比较麻烦，建议用双临时数组
> >     char digits[MAX_STR_LEN + 1];
> >     char alphas[MAX_STR_LEN + 1];
> >     char *s = str;
> >     int i = 0, j = 0;
> >     while (*s) {
> >         if (isdigit(*s)) {
> >             digits[i++] = *s;
> >         }
> >         else if (isalpha(*s)) {
> >             alphas[j++] = *s;
> >         }
> >         s++;
> >     }
> >     // 在后面添加空字符
> >     digits[i] = '\0';
> >     alphas[j] = '\0';
> >
> >
> >     strcpy(str, digits);
> >     strcat(str, alphas);
> > }
> > /*
> >     方式二：双指针法夹逼交换法
> >     使用两个指针left和right
> >     left指针从字符串开头向后遍历寻找字母，right指针从字符串末尾向前遍历寻找数字。
> >     当left找到一个字母且right找到一个数字时，交换它们的位置
> >     重复这个过程直到left和right指针相遇。
> > */
> > void separate2(char *str) {
> >     char *left = str; // 从字符串开始处向后寻找字母
> >     char *right = str + strlen(str) - 1; // 从字符串结束处向前寻找数字
> >
> >
> >     while (left < right) {
> >         // 向后寻找直到找到一个字母
> >         while (left < right && !isalpha(*left)) {
> >             left++;
> >         }
> >         // 向前寻找直到找到一个数字
> >         while (left < right && !isdigit(*right)) {
> >             right--;
> >         }
> >         // 交换数字和字母
> >         if (left < right) {
> >             char temp = *left;
> >             *left = *right;
> >             *right = temp;
> >         }
> >     }
> > }
> >
> >
> >
> >
> > /*
> >     方式三：双指针单向分区交换法
> >     思路：
> >     先初始化一个临时指针 p 指向首字符，用于遍历字符串
> >     再初始化另一个临时指针 p_num 指向首字符，该指针用于指示一个数字字符应该放置的位置（因为数字要放到前面）
> >     在遍历字符串的过程中，一旦 p指针 指向一个数字字符，那么就交换两个指针位置的元素，然后将p_num向后移
> >     这样直到遍历完整个字符串，所有的数字就都会被交换到前面
> >
> >
> >     这里提到的分区思想是：
> >     一个指针用于遍历，另一个指针标记插入位置
> >     这种做法是数组分区分组更常见的思想策略
> > */
> > void separate3(char *str) {
> >     char *p = str; // p指针用于遍历字符串
> >     char *p_num = str; // p_num 指向下一个数字应该放置的位置
> >
> >
> >     // 利用p指针遍历字符串直到结束
> >     while (*p) {
> >         // 如果当前字符是数字
> >         if (isdigit(*p)) {
> >             // 只有当 p 和 p_num 指向不同位置时才需要交换
> >             if (p != p_num) {
> >                 // 交换 *p 和 *p_num 指向的值
> >                 char temp = *p_num;
> >                 *p_num = *p;
> >                 *p = temp;
> >             }
> >             p_num++; // 移动 p_num 到下一个位置
> >         }
> >         p++; // 移动p继续遍历字符串
> >     }
> > }
> >
> >
> > /*
> >     数组本身是有索引的，可以利用索引来模拟指针，这样也可以实现"双指针"
> >     两种方式在性能的差异上微乎其微
> >     更多的是代码风格上的区别
> > */
> > void separate4(char *str) {
> >     int i = 0; // i 用于遍历字符串中的每个字符
> >     int j = 0; // j 指向下一个数字应该放置的位置
> >     // 遍历字符串直到结束
> >     while (str[i]) {
> >         // 如果当前字符是数字
> >         if (isdigit(str[i])) {
> >             // 如果 i 不等于 j，则需要交换字符
> >             if (i != j) {
> >                 // 交换 `str[i]` 和 `str[j]`
> >                 char temp = str[j];
> >                 str[j] = str[i];
> >                 str[i] = temp;
> >             }
> >             j++; // j索引++，模拟指针向后移动
> >         }
> >         i++; // i索引++，模拟指针向后移动，继续遍历字符串
> >     }
> > }
> >
> >
> > int main(void) {
> >     char str[] = "h1ell2o3";
> >     separate2(str);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-06"></a>

## 06 结构体和枚举阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/06_结构体和枚举阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 结构体基础语法练习1

> 定义一个Date结构体，包含年、月、日数据项。编写一个函数，计算两个日期之间的天数差。
>
> 不考虑平年闰年，不考虑月份天数不同。
>
> 假设每个月都是30天，每年是360天，以简化计算。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **这个问题非常简单，参考代码如下：**
> >
> > ```c
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > // 日期结构体,存储年月日数据
> > typedef struct {
> >     int year;
> >     int month;
> >     int day;
> > } Date;
> >
> >
> > // 简化计算,一年360天,一个月30天
> > int calculate_days_between_dates(Date d1, Date d2) {
> >     // 第一个日期的总天数
> >     int days1 = d1.year * 360 + (d1.month - 1) * 30 + d1.day;
> >     // 第二个日期的总天数
> >     int days2 = d2.year * 360 + (d2.month - 1) * 30 + d2.day;
> >     return abs(days1 - days2);  // 返回两者之间的绝对差值
> > }
> >
> >
> > int main(void) {
> >     Date date1 = { 2024, 2, 1 };
> >     Date date2 = { 2022, 3, 1 };
> >     int diff = calculate_days_between_dates(date1, date2);
> >     printf("The difference in days: %d\n", diff);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 结构体基础语法练习2

> **第一题：**
>
> 下面结构体类型的变量的内存布局是怎样的？请使用VS的Debug模式查看它的内存布局
>
> ```c
> typedef struct stundent_s {
>     int number;
>     char name[25];
>     char gender;
>     int chinese;
>     int math;
>     int english;
> } Student;
>
>
> // 结构体对象的声明和初始化
> Student s1 = { 1, "Jack", 'm', 100, 100, 100 };
> ```
>
> **要求：截图展示内存窗口中的对齐填充，然后提交截图。**
>
> **第二题：**
>
> 基于上述的结构体类型的定义，实现以下功能：
>
> 1.从键盘输入5个学生的信息，将这些同学的信息采用结构体数组的方式存储起来。（代码直接写在main函数里）
>
> 2.编写一个函数，用于打印单个结构体信息。然后在main函数里调用该函数，打印这个结构体数组。
>
> 3.编写一个函数，用于求三个学科的平均分。然后在main函数里调用该函数，打印这三个学科的平均分。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **参考代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #define STUS_NUM 5
> >
> >
> > typedef struct student_s {
> >     int number;
> >     char name[25];
> >     char gender;
> >     int chinese;
> >     int math;
> >     int english;
> > } Student;
> >
> >
> > void print_student(Student student); // 打印单个学生信息
> > void print_averages(Student students[], int length); // 打印三门学科平均分
> >
> >
> > int main(void) {
> >     Student students[STUS_NUM];
> >
> >
> >     // 从键盘输入5个学生的信息
> >     printf("请输入5个学生的信息（学号 姓名 性别（M/F）语文成绩 数学成绩 英语成绩）:\n");
> >     for (int i = 0; i < STUS_NUM; i++) {
> >         printf("现在录入第%d个学生的信息: ", (i + 1));
> >         scanf("%d %s %c %d %d %d",
> >               &students[i].number,
> >               students[i].name,
> >               &students[i].gender,
> >               &students[i].chinese,
> >               &students[i].math,
> >               &students[i].english);
> >     }
> >
> >
> >     // 打印所有学生的信息
> >     printf("\n学生信息列表：\n");
> >     for (int i = 0; i < STUS_NUM; i++) {
> >         print_student(students[i]);
> >     }
> >
> >
> >     // 打印三门学科的平均分
> >     print_averages(students, STUS_NUM);
> >
> >
> >     return 0;
> > }
> >
> >
> > // 打印单个学生信息的函数
> > void print_student(Student student) {
> >     printf("学号：%d, 姓名：%s, 性别：%c, 语文：%d, 数学：%d, 英语：%d\n", student.number, student.name, student.gender, student.chinese, student.math, student.english);
> > }
> >
> >
> > // 计算并打印三门学科平均分的函数
> > void print_averages(Student students[], int length) {
> >     int total_chinese = 0, total_math = 0, total_english = 0;
> >     for (int i = 0; i < length; i++) {
> >         total_chinese += students[i].chinese;
> >         total_math += students[i].math;
> >         total_english += students[i].english;
> >     }
> >     printf("\n语文平均分：%f\n数学平均分：%f\n英语平均分：%f\n", (double)total_chinese / length, (double)total_math / length, (double)total_english / length);
> > }
> >
> >
> > ```
>
> 以上。

#### 枚举类型基础语法练习

> 定义一个枚举类型Month（别名），包含一年中12个月份的英文单词。并从一月份开始，为枚举成员分配一个从1开始的数字值。
>
> **例如：JANUARY=1，FEBRUARY=2，依此类推....**
>
> 编写一个函数，接收Month类型的参数，返回该月份有多少天。
>
> 注意：
>
> 1. 不考虑平年闰年，2月份一律输出28天。
> 2. 不要把12个case分支做12个处理，那也太笨了！
> 3. 枚举值应当采用英文单词字母全部大写的命名风格，类似宏定义。
>
> **提示：可以用switch对枚举类型进行选择。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **参考代码如下：**
> >
> > ```c
> > #include <stdio.h>
> >
> >
> > // 定义枚举类型Month
> > typedef enum {
> >     JANUARY = 1,
> >     FEBRUARY,
> >     MARCH,
> >     APRIL,
> >     MAY,
> >     JUNE,
> >     JULY,
> >     AUGUST,
> >     SEPTEMBER,
> >     OCTOBER,
> >     NOVEMBER,
> >     DECEMBER
> > } Month;
> >
> >
> > // 定义函数，根据Month枚举返回该月的天数
> > int days_in_month(Month month) {
> >     // 利用case穿越,减少代码量
> >     switch (month) {
> >         case JANUARY:
> >         case MARCH:
> >         case MAY:
> >         case JULY:
> >         case AUGUST:
> >         case OCTOBER:
> >         case DECEMBER:
> >             return 31;
> >         case APRIL:
> >         case JUNE:
> >         case SEPTEMBER:
> >         case NOVEMBER:
> >             return 30;
> >         case FEBRUARY:
> >             return 28;
> >         default:
> >             // 错误处理
> >             return -1;
> >     }
> > }
> >
> >
> > int main(void) {
> >     Month month = FEBRUARY;
> >     printf("Days in February: %d\n", days_in_month(month));
> >
> >
> >     month = APRIL;
> >     printf("Days in April: %d\n", days_in_month(month));
> >     return 0;
> > }
> > ```
>
> 以上。

#### 结构体和枚举类型综合练习

> 编写一个程序，管理图书馆中的书籍信息。每本书籍的信息包含以下内容：
>
> 1. 书籍编号（整型）
> 2. 书籍名称（字符串）
> 3. 书籍作者（字符串）
> 4. 书籍类别（枚举类型）
>
> 请定义一个**Book书籍结构体类型**来存储一本书的信息，以及**Genre**这个**书籍类别枚举类型**。
>
> 书籍类别的枚举类型包含以下类别：
>
> 1. 科幻（SCIENCE\_FICTION）
> 2. 文学（LITERATURE）
> 3. 历史（HISTORY）
> 4. 科技（TECHNOLOGY）
> 5. 其他（OTHER）
>
> 现在给定你一个Book结构体对象数组的数据，一共十本书：
>
> ```c
> #define MAX_BOOKS 10
> Book books[MAX_BOOKS] = {
>     {1, "三体", "刘慈欣", SCIENCE_FICTION},
>     {2, "红楼梦", "曹雪芹", LITERATURE},
>     {3, "中国通史", "吕思勉", HISTORY},
>     {4, "时间简史", "史蒂芬·霍金", TECHNOLOGY},
>     {5, "围城", "钱钟书", LITERATURE},
>     {6, "傲慢与偏见", "简·奥斯汀", LITERATURE},
>     {7, "呼啸山庄", "艾米莉·勃朗特", LITERATURE},
>     {8, "活着", "余华", LITERATURE},
>     {9, "明朝那些事儿", "当年明月", HISTORY},
>     {10, "乌合之众", "古斯塔夫·勒庞", OTHER}
> };
> ```
>
> 请实现以下功能：
>
> 1. 程序启动，即打印所有书籍的信息。
> 2. 根据用户输入的书籍类别编号，查找并输出该类别的所有书籍信息。
>
> 程序的运行结果如下图所示：
>
> ![题目4-程序执行示意图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/06_%E7%BB%93%E6%9E%84%E4%BD%93%E5%92%8C%E6%9E%9A%E4%B8%BE%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_image-20240522215352313.png)
>
> **提示，建议提取下列三个函数来实现整个程序的功能：**
>
> ```c
> void print_book_info(Book *books, int count);   // 打印所有书籍信息
> void find_books_by_genre(Book *books, int count, Genre genre);  // 根据书籍类别打印书籍
> char *get_genre_name(Genre genre);    // 将书籍类别的枚举值转换成中文表示的类别
> ```
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **可以直接用上面题目中给出的数据，不需要自己编数据了：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define MAX_BOOKS 10
> > #define TITLE_LENGTH 100
> > #define AUTHOR_LENGTH 50
> >
> >
> > // 定义书籍类别的枚举类型
> > typedef enum {
> >     SCIENCE_FICTION,    // 科幻
> >     LITERATURE,         // 文学
> >     HISTORY,            // 历史
> >     TECHNOLOGY,         // 科技
> >     OTHER               // 其他
> > } Genre;
> >
> >
> > // 定义书籍结构体类型
> > typedef struct {
> >     int id;
> >     char title[TITLE_LENGTH];
> >     char author[AUTHOR_LENGTH];
> >     Genre genre;
> > } Book;
> >
> >
> > void print_book_info(Book *books, int count);   // 打印所有书籍信息
> > void find_books_by_genre(Book *books, int count, Genre genre);  // 根据书籍类别打印书籍
> > char *get_genre_name(Genre genre);    // 将书籍类别的枚举值转换成中文表示的类别
> >
> >
> > int main() {
> >     Book books[MAX_BOOKS] = {
> >         {1, "三体", "刘慈欣", SCIENCE_FICTION},
> >         {2, "红楼梦", "曹雪芹", LITERATURE},
> >         {3, "中国通史", "吕思勉", HISTORY},
> >         {4, "时间简史", "史蒂芬·霍金", TECHNOLOGY},
> >         {5, "围城", "钱钟书", LITERATURE},
> >         {6, "傲慢与偏见", "简·奥斯汀", LITERATURE},
> >         {7, "呼啸山庄", "艾米莉·勃朗特", LITERATURE},
> >         {8, "活着", "余华", LITERATURE},
> >         {9, "明朝那些事儿", "当年明月", HISTORY},
> >         {10, "乌合之众", "古斯塔夫·勒庞", OTHER}
> >     };
> >
> >
> >     int count = MAX_BOOKS;
> >
> >
> >     // 打印所有书籍的信息
> >     print_book_info(books, count);
> >
> >
> >     // 用户输入书籍类别编号并查找该类别的书籍
> >     int genre;
> >     printf("请输入书籍类别编号 (0: 科幻, 1: 文学, 2: 历史, 3: 科技, 4: 其他)来查询书籍: ");
> >     scanf("%d", &genre);
> >     find_books_by_genre(books, count, (Genre)genre);
> >
> >
> >     return 0;
> > }
> >
> >
> > // 打印所有书籍的信息
> > void print_book_info(Book *books, int count) {
> >     printf("---------------所有的书籍信息---------------\n\n");
> >     for (int i = 0; i < count; i++) {
> >         printf("编号: %d, 书名: %s, 作者: %s, 类别: %s\n",
> >                books[i].id, books[i].title, books[i].author, get_genre_name(books[i].genre));
> >     }
> >     printf("\n");
> > }
> >
> >
> > // 根据书籍类别查找并打印该类别的所有书籍信息
> > void find_books_by_genre(Book *books, int count, Genre genre) {
> >     printf("类别为 %s 的书籍有:\n", get_genre_name(genre));
> >     for (int i = 0; i < count; i++) {
> >         if (books[i].genre == genre) {
> >             printf("编号: %d, 书名: %s, 作者: %s\n",
> >                    books[i].id, books[i].title, books[i].author);
> >         }
> >     }
> > }
> >
> >
> > // 将书籍类别的枚举值转换成中文表示的类别
> > const char *get_genre_name(Genre genre) {
> >     switch (genre) {
> >         case SCIENCE_FICTION: return "科幻";
> >         case LITERATURE: return "文学";
> >         case HISTORY: return "历史";
> >         case TECHNOLOGY: return "科技";
> >         case OTHER: return "其他";
> >         default: return "未知";
> >     }
> > }
> > ```
>
> 以上。

### The End

<a id="ch-07"></a>

## 07 指针高级阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/07_指针高级阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 实现动态拼接字符串

> 标准库函数strcat会将一个字符串追加到另一个字符串的末尾。
>
> 现在我们编写一个函数把两个字符串拼接起来，返回拼接的结果，但要求不改变其中任何一个字符串。其函数声明如下：
>
> ```c
> char* my_strcat(const char* prefix, const char* suffix);
> ```
>
> 形参prefix表示前缀，suffix表示后缀，拼接的结果是prefix + suffix
>
> 比如：my\_strcat("abc", "d")，拼接的结果是"abcd"。
>
> 思路：
>
> 1. 在堆上分配内存空间，用于存储结果字符串。
> 2. 将prefix和suffix两个字符串的字符信息复制进去。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **这个问题非常简单，是一个基础的动态内存分配问题。参考代码如下：**
> >
> > ```c
> > // 在堆上动态分配内存拼接两个字符串
> > char* dynamic_strcat(const char* prefix, const char* suffix) {
> >     // 计算拼接后字符串的长度
> >     int new_str_len = strlen(prefix) + strlen(suffix);
> >     char *new_str = malloc(new_str_len + 1);    // char在各平台上长度都是1，所以不用乘了
> >
> >
> >     if (new_str == NULL) {
> >         printf("ERROR: malloc failed in dynamic_strcat!\n");
> >         exit(1);
> >     }
> >
> >
> >     // 长度是精确计算得出的，不用担心越界访问
> >     strcat(strcpy(new_str, prefix), suffix);
> >
> >
> >     return new_str;
> > }
> >
> >
> > int main(void) {
> >     char str1[] = "hello";
> >     char str2[] = " world!";
> >     char* result_str = dynamic_strcat(str1, str2);  // 注意只要涉及动态内存分配，一律用指针类型。这里不能用数组类型
> >
> >
> >     puts(result_str);
> >
> >
> >     // 现在不再使用result字符串了，不要忘记free它
> >     free(result_str);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 堆数组的创建与释放（基础语法练习题）

> 编写程序，从键盘输入输入中读取一个整数`n`，动态分配一个长度为`n`的整型数组，将数组元素初始化为`1, 2, 3, ..., n`，并输出打印数组内容，最后释放内存。
>
> 注意:
>
> 1. 初始化内存块时可以直接使用下标来操作内存块。
> 2. 遍历打印数组元素取值时，请使用指针来实现操作。
>
> **非常简单且基础的语法练习题，如果还不太会做，不妨直接查看参考代码。**
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > int main(void) {
> >     int n;
> >     printf("请输入数组长度：");
> >     scanf("%d", &n);
> >
> >
> >     int *arr = (int *)malloc(n * sizeof(int));
> >     if (arr == NULL) {
> >         printf("内存分配失败！\n");
> >         return 1;
> >     }
> >
> >
> >     // 初始化内存块
> >     for (int i = 0; i < n; i++) {
> >         arr[i] = i + 1;
> >     }
> >
> >
> >     // 遍历打印数组内容
> >     printf("数组内容：");
> >     int *temp = arr;
> >     while (temp < arr + n) {
> >         printf("%d ", *temp++);
> >     }
> >     printf("\n");
> >
> >
> >     free(arr);
> >     arr = NULL; // 避免野指针
> >     return 0;
> > }
> > ```
>
> 以上。

#### 内存重分配语法练习（基础语法练习题）

> 先在堆上申请创建一个长度为10的int数组，编写一个函数用于以"\[xx, xx, ..., xx\]"的格式打印这个int数组。
>
> 紧接着执行以下操作：
>
> 1. 在申请int数组成功后，直接调用函数打印这个int数组，思考一下：应该用哪个函数来申请创建这个数组？
> 2. 截断这个int数组，将其变为长度为5的int数组，然后再打印这个数组。
> 3. 将长度为5的int数组，再次扩容回10个元素，将最后五个元素初始化为888，最后再次打印这个数组。
> 4. 最后不要忘记free释放内存块。
>
> **非常简单且基础的语法练习题，如果还不太会做，不妨直接查看参考代码。**
>
> **重点需要注意realloc函数的调用格式！**
>
> > ###### 参考代码：
> >
> > ```c
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > // 打印数组函数的声明
> > void print_array(int *arr, int len);
> >
> >
> > int main(void) {
> >  // 分配长度为10的int数组
> >     int *arr = (int *)calloc(10, sizeof(int));
> >     if (arr == NULL) {
> >         printf("error: calloc failed in main.\n");
> >         exit(-1);
> >     }
> >
> >
> >  printf("初始数组：");
> >     print_array(arr, 10);
> >
> >
> >  // 截断int数组
> >     int *temp = (int *)realloc(arr, 5 * sizeof(int));
> >     if (temp == NULL) {
> >         printf("error: realloc truncation failed in main.\n");
> >         free(arr);
> >         exit(-1);
> >     }
> >     arr = temp;
> >     printf("截断数组后：");
> >     print_array(arr, 5);
> >
> >
> >  // 扩容int数组
> >     temp = (int *)realloc(arr, 10 * sizeof(int));
> >     if (temp == NULL) {
> >         printf("error: realloc expansion  failed in main.\n");
> >         free(arr);
> >         exit(-1);
> >     }
> >     arr = temp;
> >     // 扩容后初始化后5个元素
> >     temp = arr + 5;
> >     while (temp < arr + 10) {
> >         *temp++ = 888;
> >     }
> >
> >
> >  printf("扩容数组后：");
> >     print_array(arr, 10);
> >
> >
> >  free(arr);
> >     return 0;
> > }
> >
> >
> > // 打印数组函数的实现
> > void print_array(int *arr, int len) {
> >  printf("[");
> >     for (int i = 0; i < len; i++) {
> >         printf("%d, ", arr[i]);
> >     }
> >     printf("\b\b]\n");
> > }
> > ```
>
> 以上。

#### 手动实现动态数组Vector

> 手动实现动态数组Vector，基于以下结构体定义和函数声明：
>
> ```c
> typedef int ElementType;
>
>
> typedef struct {
>     ElementType *data;   // 指向堆空间的数组
>     int size;   // 元素的个数
>     int capacity; // 数组的容量
> } Vector;
>
>
> // 请实现下面方法
>
>
> // 初始化一个Vector动态数组
> Vector *vector_create(void);
>
>
> // 销毁一个Vector动态数组，释放内存。
> void vector_destroy(Vector *v);
>
>
> // 向动态数组末尾添加一个元素
> void vector_push_back(Vector *v, ElementType val);
>
>
> // 在动态数组最前面添加元素，所有元素依次后移
> void vector_push_front(Vector *v, ElementType val);
>
>
> // 将元素val添加到索引为idx的位置，idx后面的元素依次后移
> void vector_insert(Vector *v, int idx, ElementType val);
>
>
> // 遍历打印整个Vector动态数组
> void vector_print(Vector *v);
> ```
>
> **注意：**
>
> **你应该将上述代码放在头文件中，并且自己添加头文件保护语法。**
>
> **提交作业时，你应该提交头文件，实现Vector的源文件，测试源文件三个文件的代码**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **头文件加上保护语法，代码如下：**
> >
> > ```c
> > #ifndef VECTOR_H
> > #define VECTOR_H
> >
> >
> > typedef int ElementType;
> >
> >
> > typedef struct {
> >     ElementType *data;   // 指向堆空间的数组
> >     int size;   // 元素的个数
> >     int capacity; // 数组的容量
> > } Vector;
> >
> >
> > // 请实现下面方法
> >
> >
> > // 初始化一个Vector动态数组
> > Vector *vector_create(void);
> >
> >
> > // 销毁一个Vector动态数组，释放内存。
> > void vector_destroy(Vector *v);
> >
> >
> > // 向动态数组末尾添加一个元素
> > void vector_push_back(Vector *v, ElementType val);
> >
> >
> > // 在动态数组最前面添加元素，所有元素依次后移
> > void vector_push_front(Vector *v, ElementType val);
> >
> >
> > // 将元素val添加到索引为idx的位置，idx后面的元素依次后移
> > void vector_insert(Vector *v, int idx, ElementType val);
> >
> >
> > // 遍历打印整个Vector动态数组
> > void vector_print(Vector *v);
> >
> >
> > #endif // !VECTOR_H
> > ```
> >
> > **实现源文件代码：**
> >
> > ```c
> > #include "vector.h"
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > #define DEFAULT_CAPACITY 8
> > #define THRESHOLD 1024
> >
> >
> >
> >
> > // 在C语言中,static修饰函数表示此函数仅在当前文件内部生效
> > // 类似于C++或Java中的访问权限修饰符private
> > static void vector_resize(Vector *v) {
> >     // 只要调用这个函数肯定就是需要扩容的
> >     int old_capacity = v->capacity;
> >
> >
> >     int new_capacity = (old_capacity < THRESHOLD) ?
> >         (old_capacity << 1) :   // 容量还未超出阈值每次扩容2倍
> >     (old_capacity + (old_capacity >> 1));       // 容量超出阈值每次扩容1.5倍
> >
> >
> >     // 利用realloc重新分配动态数组
> >     // realloc惯用法
> >     ElementType *tmp = realloc(v->data, new_capacity * sizeof(ElementType));    
> >     if (tmp == NULL) {
> >         printf("realloc failed in resize_vector.\n");
> >         exit(1);    // 扩容失败，退出整个程序。或者也可以做别的处理
> >     }
> >     // 扩容成功，重新赋值Vector成员
> >     v->data = tmp;
> >     v->capacity = new_capacity;
> > }
> >
> >
> > // 初始化一个Vector动态数组
> > Vector *vector_create(void) {
> >     // 先在堆上申请结构体
> >     Vector *v = calloc(1, sizeof(Vector));
> >     if (v == NULL) {
> >         printf("calloc failed in vector_create.\n");
> >         return NULL;    // 创建失败返回空指针
> >     }
> >
> >
> >     // 申请动态数组，并初始化Vector的data成员
> >     v->data = calloc(DEFAULT_CAPACITY, sizeof(ElementType));
> >     if (v->data == NULL) {
> >         printf("malloc failed in vector_create.\n");
> >         // 不要忘记free结构体Vector，否则会导致内存泄漏
> >         free(v);
> >         return NULL;    // 创建失败返回空指针
> >     }
> >
> >
> >     // 继续初始化Vector的其它成员
> >     v->capacity = DEFAULT_CAPACITY;
> >
> >
> >     return v;
> > }
> >
> >
> > // 销毁一个Vector动态数组，释放内存。
> > void vector_destroy(Vector *v) {
> >     free(v->data);
> >     free(v);
> > }
> >
> >
> > // 向动态数组末尾添加一个元素
> > void vector_push_back(Vector *v, ElementType val) {
> >     // 先判断是否需要扩容
> >     if (v->capacity == v->size) {
> >         vector_resize(v);
> >     }
> >     // 扩容完成后或不需要扩容，即向末尾添加元素
> >     v->data[v->size] = val;
> >     v->size++;
> > }
> >
> >
> > // 在动态数组最前面添加元素，所有元素依次后移
> > void vector_push_front(Vector *v, ElementType val) {
> >     // 先判断是否需要扩容
> >     if (v->capacity == v->size) {
> >         vector_resize(v);
> >     }
> >     // 扩容完成后或不需要扩容，即从首元素开始将所有元素向后移动
> >     // 倒着遍历数组方便向后移动元素
> >     for (int i = v->size - 1; i >= 0; i--) {
> >         v->data[i + 1] = v->data[i];
> >     }
> >     // 新增的元素成为首元素
> >     v->data[0] = val;
> >     v->size++;
> > }
> >
> >
> > // 将元素val添加到索引为idx的位置，idx后面的元素依次后移
> > void vector_insert(Vector *v, int idx, ElementType val) {
> >     // 先做参数校验，避免传入非法索引
> >     if (idx < 0 || idx > v->size) {     // 做插入操作时索引合法范围是[0, size]
> >         printf("Illegal argument: idx = %d, size = %d\n", idx, v->size);
> >         exit(1);    // 直接退出进程，也可以用别的方式进行错误处理
> >     }
> >     // 判断是否需要扩容
> >     if (v->capacity == v->size) {
> >         vector_resize(v);
> >     }
> >     // 扩容完成后或不需要扩容，即从原本的idx元素开始将所有元素向后移动
> >     for (int i = v->size - 1; i >= idx; i--) {
> >         v->data[i + 1] = v->data[i];
> >     }
> >     // idx位置空出来,将它放进去
> >     v->data[idx] = val;
> >     v->size++;
> > }
> >
> >
> > // 遍历打印整个Vector动态数组
> > void vector_print(Vector *v) {
> >     printf("[");
> >     for (int i = 0; i < v->size; i++){
> >         printf("%d, ", v->data[i]);
> >     }
> >     printf("\b\b]\n");
> > }
> > ```
> >
> > **测试用例代码：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include "vector.h"
> >
> >
> > #define N 100
> > int main(void) {
> >     Vector *v = vector_create();
> >     if (v == NULL) {
> >         printf("error: vector_create failed in main.\n");
> >         exit(1);
> >     }
> >
> >
> >     // 测试自动扩容机制
> >     for (int i = 0; i < N; ++i) {
> >         vector_push_back(v, i + 1);
> >     }
> >     vector_print(v);    // 期望打印结果: 1-100
> >
> >
> >     // 测试头部插入新元素
> >     vector_push_front(v, 0);
> >     vector_print(v);    // 期望打印结果: 0, 1-100
> >
> >
> >     // 测试根据索引插入新元素
> >     vector_insert(v, 0, -1);
> >     vector_print(v);    // 期望打印结果: -1, 0, 1-100
> >
> >
> >     vector_destroy(v);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 二级指针基础练习题

> 在main函数中定义两个局部变量：
>
> ```c
> int a = 10;
> int b = 20;
> ```
>
> 请实现以下两个函数，用于完成局部变量a和b的交换：
>
> ```c
> void swap(int *pa, int *pb);
> void swap2(int **pa, int **pb);
> ```
>
> 这两个函数都应该可以实现交换a和b的值。
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > // 函数声明
> > void swap(int *pa, int *pb);
> > void swap2(int **pa, int **pb);
> >
> >
> > int main(void) {
> >     int a = 10;
> >     int b = 20;
> >     int *ptrA = &a;
> >     int *ptrB = &b;
> >
> >
> >     printf("初始值：a = %d, b = %d\n", a, b);
> >
> >
> >     // 使用一级指针交换值
> >     swap(&a, &b);
> >     printf("使用 swap 函数第一次交换后：a = %d, b = %d\n", a, b);
> >
> >
> >     // 使用二级指针交换指针
> >     swap2(&ptrA, &ptrB);
> >     printf("使用 swap2 函数再次交换后：a = %d, b = %d\n", *ptrA, *ptrB);
> >
> >
> >     return 0;
> > }
> >
> >
> > void swap(int *pa, int *pb) {
> >     int temp = *pa;
> >     *pa = *pb;
> >     *pb = temp;
> > }
> >
> >
> > void swap2(int **pa, int **pb) {
> >     int temp = **pa;
> >     **pa = **pb;
> >     **pb = temp;
> > }
> > ```
>
> 以上。

#### 二级指针/单链表练习题

> 基于以下链表结点结构体类型的定义:
>
> ```c
> typedef int ElementType;
> typedef struct node {
>     int data;
>     struct node* next;
> } Node;
> ```
>
> 在main函数中定义一个head头指针等于NULL代表此时单链表为空：
>
> ```c
> Node *head = NULL;
> ```
>
> 利用**二级指针**语法实现以下函数：
>
> ```c
> // 头插法新增一个结点
> void insert_head(Node** head, ElementType new_val);
> // 修改第一个结点的元素值，如果链表为空，则用new_val初始化第一个结点
> void modify_first_node(Node** head, int new_val);
> // 尾插法新增一个结点
> void insert_tail(Node** head, ElementType new_val);
> // 打印单链表 格式为：1 -> 2 -> 3 ->...
> void print_list(Node *head);
> ```
>
> 注：尾插法会稍微麻烦一些，可以放在最后实现。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **参考代码如下：**
> >
> > ```c
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > typedef struct node {
> >     int data;
> >     struct node *next;
> > } Node;
> >
> >
> > // 单链表的头插法
> > void insert_head(Node **head, int new_val) {
> >     // 1.创建新节点
> >     Node *new_node = malloc(sizeof(Node));
> >     if (new_node == NULL) {
> >         printf("malloc failed in insert_head.\n");
> >         exit(1);
> >     }
> >     // 2.初始化新节点的数据域
> >     new_node->data = new_val;
> >     // 3.新结点的next指针指向原本第一个节点
> >     new_node->next = *head;
> >     // 4.将头指针指向新结点
> >     *head = new_node;
> > }
> >
> >
> > // 修改第一个结点的元素值
> > void modify_first_node(Node **head, int new_val) {
> >     if (*head == NULL) {
> >         // 当前单链表为空，此时为头插法
> >         *head = malloc(sizeof(Node));
> >         if (*head == NULL) {
> >             printf("malloc failed in modify_first_node.\n");
> >             exit(1);
> >         }
> >         (*head)->data = new_val;
> >         (*head)->next = NULL;
> >     }
> >     else {
> >         (*head)->data = new_val;
> >     }
> > }
> >
> >
> > // 优化：既然头插法已经实现了，那么也可以直接调用，而不是重新实现
> > void modify_first_node2(Node **head, int new_val) {
> >     if (*head == NULL) { // 链表为空时，初始化第一个节点
> >         insert_head(head, new_val);
> >     }
> >     else { // 链表非空时，修改第一个节点的数据
> >         (*head)->data = new_val;
> >     }
> > }
> >
> >
> > // 尾插法新增一个结点
> > void insert_tail(Node **head, int val) {
> >     // 创建新结点
> >     Node *new_node = (Node *)malloc(sizeof(Node));
> >     if (new_node == NULL) {
> >         printf("malloc failed in insert_tail.\n");
> >         exit(-1);
> >     }
> >     new_node->data = val; // 设置新节点的数据
> >     new_node->next = NULL; // 新节点将成为尾节点，其下一个节点指针为NULL
> >
> >
> >     if (*head == NULL) {
> >         // 如果链表为空，新节点即为第一个结点
> >         *head = new_node;
> >     }
> >     else {
> >         // 遍历找到当前链表的最后一个结点
> >         Node *curr = *head;
> >         while (curr->next != NULL) {
> >             curr = curr->next;
> >         }
> >         curr->next = new_node; // 将新节点追加到链表尾部
> >     }
> > }
> >
> >
> > // 打印单链表 格式为：1 -> 2 -> 3 ->...
> > void print_list(Node *head) {
> >     Node *curr = head;
> >     while (curr != NULL) {  // 遍历此单链表
> >         printf("%d", curr->data);
> >         if (curr->next != NULL) {
> >             printf(" -> ");
> >         }
> >         curr = curr->next;
> >     }
> >     printf("\n");
> > }
> >
> >
> > // 测试用例
> > int main(void) {
> >     // 初始化一个空链表
> >     Node *head = NULL;
> >     insert_head(&head, 5);
> >     insert_head(&head, 4);
> >     insert_head(&head, 3);
> >     insert_head(&head, 2);
> >     insert_head(&head, 1);
> >
> >
> >     modify_first_node(&head, 100);
> >     insert_tail(&head, 6);
> >     print_list(head);
> >     return 0;
> > }
> > ```
>
> 以上。

#### qsort函数基础语法练习

> 给你下面一个Student，学生结构体类型的定义:
>
> ```c
> // Student学生结构体类型定义
> typedef struct {
>     char name[25];
>     int score;
> } Student;
> ```
>
> 假设你有一个学生结构体对象数组，如下所示:
>
> ```c
> Student stus[] = {
>     {"Alice", 85},
>     {"Bob", 92},
>     {"Charlie", 85},
>     {"David", 85},
>     {"Eve", 92},
>     {"Frank", 75},
>     {"Grace", 85},
>     {"Hannah", 95},
>     {"Ivy", 78},
>     {"Jack", 85}
> };
> ```
>
> **你的任务是使用`qsort`函数对这个结构体数组进行排序：**
>
> 1. **规则1：将全体结构体对象，按照学生成绩从高到低进行排序。**
> 2. **规则2：先将全体结构体对象，按照学生成绩从低到高进行排序，如果成绩一致，则那么按照名字的字典顺序进行排序。**
>
> 最后，你还需要实现一个函数用于打印整个学生数组：
>
> ```c
> void print_students(Student stus[], int size);
> ```
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **可以直接用上面题目中给出的数据，不需要自己编数据了：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <string.h>
> > #define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
> >
> >
> > typedef struct {
> >     char name[25];
> >     int score;
> > } Student;
> >
> >
> >
> >
> > // 比较函数1：按成绩从高到低排序
> > int compare_scores_desc(const void *a, const void *b) {
> >     Student *stu1 = (Student *)a;
> >     Student *stu2 = (Student *)b;
> >     return stu2->score - stu1->score;  // 逆序排列
> > }
> >
> >
> > // 比较函数2：按成绩从低到高排序，成绩相同则按名字字典顺序排序
> > int compare_scores_asc(const void *a, const void *b) {
> >     Student *stu1 = (Student *)a;
> >     Student *stu2 = (Student *)b;
> >     if (stu1->score == stu2->score) {
> >         return strcmp(stu1->name, stu2->name);  // 字典序比较名字
> >     }
> >     return stu1->score - stu2->score;  // 正序排列
> > }
> >
> >
> > // 打印学生数组的全部对象
> > void print_students(Student stus[], int size) {
> >     for (int i = 0; i < size; i++) {
> >         printf("Name: %s, Score: %d\n", stus[i].name, stus[i].score);
> >     }
> >     printf("\n");
> > }
> >
> >
> > int main(void) {
> >     Student stus[] = {
> >         {"Alice", 85},
> >         {"Bob", 92},
> >         {"Charlie", 85},
> >         {"David", 85},
> >         {"Eve", 92},
> >         {"Frank", 75},
> >         {"Grace", 85},
> >         {"Hannah", 95},
> >         {"Ivy", 78},
> >         {"Jack", 85}
> >     };
> >     int len = ARR_SIZE(stus);
> >
> >
> >     printf("原始学生数组是:\n");
> >     print_students(stus, len);
> >
> >
> >     // 按规则1排序：成绩从高到低
> >     qsort(stus, len, sizeof(Student), compare_scores_desc);
> >     printf("将学生按照成绩由高到低排序:\n");
> >     print_students(stus, len);
> >
> >
> >     // 按规则2排序：成绩从低到高，成绩相同按名字排序
> >     qsort(stus, len, sizeof(Student), compare_scores_asc);
> >     printf("将学生按照成绩和名字综合排序:\n");
> >     print_students(stus, len);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：动态字符串Vector

> **你已经手动实现了一个自己的Vector，很好，这很酷。那么请思考和完成以下扩展的题目。**
>
> 现在请你回答第一个问题：
>
> **原本的动态数组用于存储int类型元素，是int类型动态数组。现在我希望你能把它变成字符串动态数组，应该怎么改代码吗？**
>
> 如果仅在原本代码的基础上修改ElementType的类型，那么请你思考第二个问题：
>
> **此时Vector虽然能存字符串了，但只能存什么字符串呢？**
>
> 把以上问题都考虑清楚后，请完成以下测试工作：
>
> 使用push\_back函数向动态字符串数组中**循环添加100个**字符串元素，这些字符串依次是：
>
> > "0"
> >
> > "01"
> >
> > "012"
> >
> > "0123"
> >
> > ...... "01234567890"
> >
> > "012345678901"
> >
> > "0123456789012"
> >
> > ....
>
> 添加完成后，请遍历打印这个动态字符串数组。请将这段测试动态字符串数组Vector的代码贴在答案里。
>
> Vector的其它实现代码不需要贴进来。
>
> **注意，实现这个需求时，不需要考虑字符串的生命周期问题。**
>
> 参考回答如下：
>
> > ###### 参考代码：
> >
> > **前两个问题的答案：**
> >
> > 1. 只需要把ElementType的类型从`int`改为`char *`就可以了。
> > 2. 如果只是改变ElementType的类型，那么从最佳实践出发：
> >     1. 这个Vector最好存储字面值字符串、全局变量等静态存储期限的字符。因为不用考虑它们的生命周期问题，它们在整个程序运行期间都生效。
> >     2. 如果存储局部变量字符串，那么这个Vector将不能跨函数使用。
> >     3. 如果存堆字符串，那么这个Vector需要管理它存储的字符串的生命周期，这就比较麻烦了。
> >
> > 但对于我们下面的这个需求而言：由于需要动态构建字符串，所以不可能使用字符串字面值，局部变量/全局变量字符串也不可用，所以比较好是实现就是使用堆字符串。
> >
> > 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include "vector.h"
> > #define N 100
> >
> >
> > int main(void) {
> >     // 在栈上创建一个Vector指针，指向堆上的结构体对象
> >     Vector* v = vector_create();
> >     if (v == NULL) {
> >         printf("Error: vector_create failed.\n");
> >         return 1;
> >     }
> >     for (int i = 0; i < N; i++) {   // 循环100次向动态字符串数组中插入字符串
> >         // 用calloc更好,它会自动初始化所有元素是空字符.这对字符串而言很关键,因为第一个空字符作为结束标志
> >         int str_len = i + 1;
> >         char* str = calloc(1, (str_len + 1));
> >         if (str == NULL) {
> >             printf("Error: calloc str failed.\n");
> >             return 1;
> >         }
> >         for (int j = 0; j <= i; j++) {
> >             str[j] = '0' + j % 10;
> >         }
> >         vector_push_back(v, str);
> >     }
> >
> >
> >     for (int i = 0; i < N; i++) {
> >         printf("%s\n", v->data[i]);
> >     }
> >
> >
> >     // 销毁动态字符串数组指向的所有堆字符串
> >     for (int i = 0; i < N; i++) {
> >         free(v->data[i]);
> >     }
> >
> >
> >     // 用完了销毁Vector
> >     vector_destroy(v);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：错误处理宏函数

> 规范的代码应该对内存分配函数malloc、calloc、realloc的返回值做判NULL处理。因为这些函数的返回值是NULL时意味着内存分配失败，函数出错，需要做错误处理。
>
> 后续的学习中，我们还会学习很多这样的函数，需要对它们的返回值做错误处理。
>
> 如果每次都需要将错误处理的结构都重新写一遍，那确实很折磨。为了更好的复用代码，简化操作，我们建议大家把这个结构用宏函数定义出来。
>
> 可以基于以下结构定义宏函数：
>
> ```c
> if (p == NULL) {
>     printf("error: calloc failed in main.\n");
>     exit(1);
> }
> ```
>
> 提示，为了更好的复用性，这个宏函数最好有三个参数：
>
> 1.函数返回值。错误处理是依据函数返回值进行的，所以需要函数返回值作为参数。也就是上述结构中的p
>
> 2.函数返回值的错误标志。当返回值是这个错误标志时，做错误处理。上述代码结构中就是NULL
>
> 3.msg。错误处理时打印的报错信息。也就是"calloc failed in main."这一段。
>
> **这个宏函数的实现不唯一，也不可能做到一个宏函数统一处理所有的情况，大家可以自己想一想写一下，也可以直接参考我给的实现。**
>
> 最后，你可以将这个宏函数放到你的代码模板中，这样就更方便了。
>
> 参考实现如下：
>
> > ###### 参考代码实现：
> >
> > ```c
> > #define ERROR_CHECK(ret, error_flag, msg) \
> >  do { \
> >      if ((ret) == (error_flag)) { \
> >          printf("error: %s\n", msg); \
> >          exit(1); \
> >      } \
> >  } while(0)
> >
> >
> > int main(void) {
> >     int *p = malloc(10 * sizeof(int));
> >     ERROR_CHECK(p, NULL, "malloc failed in main.");
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：动态内存分配以及qsort函数

> **（扩展题，可以放到最后做）**
>
> 编写一个C语言程序，完成以下任务：
>
> 首先，从键盘录入一个整数，表示接下来要录入的字符串的数量。
>
> 紧接着根据这个数量，从键盘连续录入字符串，每次都会将一整行键盘录入成一个字符串
>
> **这些被录入的字符串需要存入一个字符串数组，然后将该字符串数组按照以下两种规则排序遍历打印：**
>
> 1.按照字符串的长度，从长到短排序
>
> 2.先按照字符串的长度从短到长排序，长度一致的字符串按照字典顺序排序。
>
> 程序的执行图，大致如下：
>
> ![扩展题3-图](C%E8%AF%AD%E8%A8%80_assets/V0_C%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A%E6%B1%87%E6%80%BB/07_%E6%8C%87%E9%92%88%E9%AB%98%E7%BA%A7%E9%98%B6%E6%AE%B5%E4%BD%9C%E4%B8%9A/001_56b28ced-f40a-45af-a4ba-1b2f52d4bc081712969088009.jpg)
>
> **注意：**
>
> **使用fgets读一整行字符串的话，不要忘记去除字符串中的换行符。**
>
> **假设每个字符串的长度都不会超过1024。**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <string.h>
> > #include <stdlib.h>
> >
> >
> > #define MAX_STRLEN 1024
> >
> >
> > // 字符串比较函数：按长度从长到短排序
> > int compare_length_desc(const void *a, const void *b) {
> >     /*
> >         a 和 b 是指向数组中两个待比较元素的指针。
> >         数组中的元素是char*字符串类型，指向它的指针也就是char**二级指针类型
> >         所以这里应该将a和b强转成(char**)类型，然后解引用一次
> >         才能够得到两个待比较的字符串
> >     */
> >     const char *str1 = *(const char **)a;
> >     const char *str2 = *(const char **)b;
> >     int len1 = strlen(str1);
> >     int len2 = strlen(str2);
> >     if (len1 != len2) {
> >         return len2 - len1;  // 从长到短排序
> >     }
> >     return strcmp(str1, str2);  // 如果长度相同，则按字典顺序排序
> > }
> >
> >
> > // 字符串比较函数：先按长度从短到长排序，长度一样则按字典序
> > int compare_length_asc(const void *a, const void *b) {
> >     const char *str1 = *(const char **)a;
> >     const char *str2 = *(const char **)b;
> >     int len1 = strlen(str1);
> >     int len2 = strlen(str2);
> >     if (len1 != len2) {
> >         return len1 - len2;  // 从短到长排序
> >     }
> >     return strcmp(str1, str2);  // 如果长度相同，则按字典顺序排序
> > }
> >
> >
> > int main() {
> >     int str_num;
> >     printf("请输入您要输入的字符串的个数：");
> >     scanf("%d", &str_num);
> >     // 为了避免回车符对下面录入字符串产生影响，清空缓冲区
> >     while (getchar() != '\n');
> >
> >
> >     /*
> >         申请长度是str_num的char指针数组
> >         返回值类型是void*，在接收返回值也必须给一个指针类型进行类型转换
> >         所以不能直接写char *arr[]
> >         而需要写指向指针的指针类型，也就是char**，二级指针
> >     */
> >     char **str_array = malloc(str_num * sizeof(char *));
> >     for (int i = 0; i < str_num; i++) {
> >         // 每个字符串的长度都不超过1024
> >         str_array[i] = malloc(MAX_STRLEN + 1);
> >         printf("请输入第 %d 个字符串：", i + 1);
> >         fgets(str_array[i], MAX_STRLEN + 1, stdin);
> >         // 使用strlen检查并移除换行符
> >         int length = strlen(str_array[i]);
> >         if (length > 0 && str_array[i][length - 1] == '\n') {
> >             str_array[i][length - 1] = '\0';
> >         }
> >     }
> >
> >
> >     // 按长度从长到短排序并打印
> >     qsort(str_array, str_num, sizeof(char *), compare_length_desc);
> >     printf("按长度从长到短排序的结果：\n");
> >     for (int i = 0; i < str_num; i++) {
> >         printf("%s\n", str_array[i]);
> >     }
> >
> >
> >     // 先按长度从短到长排序，长度一样则按字典序排序
> >     qsort(str_array, str_num, sizeof(char *), compare_length_asc);
> >     printf("按长度从短到长排序，长度一致时按字典顺序的结果：\n");
> >     for (int i = 0; i < str_num; i++) {
> >         printf("%s\n", str_array[i]);
> >     }
> >
> >
> >     // 释放内存
> >     for (int i = 0; i < str_num; i++) {
> >         free(str_array[i]);
> >     }
> >     free(str_array);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：动态拼接字符串数组以及qsort函数

> 首先给定以下字符数组：
>
> ```c
> char* strings[] = {
>     "4show ",
>     "1code.",
>     "5cheap, ",
>     "6is ",
>     "7Talk ",
>     "2the ",
>     "3me "
> };
> ```
>
> 请你先利用`qsort`函数将此字符串数组，按照**逆字典顺序**排序。然后将这个字符串数组中的每一个字符串，按照从前到后的顺序，拼接组装成一个新字符串，并且在拼接时删除每个子字符串的第一个字符。
>
> 这样你将得到Linux之父Linus Torvalds的名言：“Talk is cheap, show me the code.”
>
> 要求使用动态分配内存来存储结果字符串，函数声明如下：
>
> ```c
> char* concat_strs(char* strings[], int count);
> ```
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <string.h>
> > #define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
> >
> >
> > // 函数声明
> > char *concat_strs(char *strings[], int count);
> > int cmp_ruler(const void *a, const void *b);
> >
> >
> > int main(void) {
> >     char *strings[] = {
> >         "4show ",
> >         "1code.",
> >         "5cheap, ",
> >         "6is ",
> >         "7Talk ",
> >         "2the ",
> >         "3me "
> >     };
> >     int count = ARR_SIZE(strings);  // 字符串数组的长度
> >
> >
> >     // 使用 qsort 对字符串数组进行逆字典序排序
> >     qsort(strings, count, sizeof(char *), cmp_ruler);
> >
> >
> >     // 调用 concat_strs 函数进行拼接合并
> >     char *result = concat_strs(strings, count);
> >     printf("拼接并排序后的字符串: %s\n", result);
> >
> >
> >     return 0;
> > }
> >
> >
> > // 字符串逆字典序比较函数
> > int cmp_ruler(const void *a, const void *b) {
> >     const char *str1 = *(const char **)a;
> >     const char *str2 = *(const char **)b;
> >     return strcmp(str2, str1);  // 逆字典顺序，所以传参要反过来
> > }
> >
> >
> > // 拼接并排序字符串数组
> > char *concat_strs(char *strings[], int count) {
> >     // 计算所有字符串的总长度，去掉每个字符串的第一个字符
> >     int total_length = 0;
> >     for (int i = 0; i < count; i++) {
> >         total_length += strlen(strings[i]) - 1; // 减去第一个字符
> >     }
> >     // 动态分配内存
> >     char *result = (char *)calloc(total_length + 1, sizeof(char)); // +1 用于存储末尾的空字符
> >     if (result == NULL) {
> >         printf("error: malloc failed in concat_strs.\n");
> >         exit(-1);
> >     }
> >
> >
> >     // 拼接所有排序后的字符串，去掉每个字符串的第一个字符
> >     for (int i = 0; i < count; i++) {
> >         strcat(result, strings[i] + 1); // 跳过第一个字符
> >     }
> >
> >
> >     return result;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-08"></a>

## 08 链表阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/08_链表阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 手动实现一条单链表（基础题/重点）

> **基于以下头文件，手动实现一条单链表：**
>
> ```c
> // 头文件保护语法
> #ifndef LINKED_LIST_H
> #define LINKED_LIST_H
>
>
> // 包含linked_list.h头文件也会同步包含它包含的其它头文件
> // 根据这一特点, 可以选择将一些共用的头文件包含在此头文件中
> #include <stdbool.h>
> #include <stdlib.h>
> #include <stdio.h>
>
>
> typedef int DataType;
>
>
> // 定义链表结点结构
> typedef struct node {
>     DataType data;      // 数据域
>     struct node *next;  // 指针域
> } Node;
>
>
> // 定义链表结构本身
> typedef struct {
>     Node *head;     // 头指针
>     Node *tail;     // 尾结点指针
>     int size;       // 用于记录链表的长度
> } LinkedList;
>
>
> // 创建一个空的链表
> LinkedList *create_linked_list();
> // 销毁链表
> void destroy_linked_list(LinkedList *list);
> // 头插法
> bool add_before_head(LinkedList *list, DataType new_data);
> // 尾插法
> bool add_behind_tail(LinkedList *list, DataType new_data);
> // 根据索引插入一个新结点
> bool add_by_idx(LinkedList *list, int idx, DataType new_data);
> // 根据索引搜索一个结点
> Node *search_by_idx(LinkedList *list, int idx);
> // 根据数据搜索一个结点
> Node *search_by_data(LinkedList *list, DataType data);
> // 根据数据删除一个结点
> bool delete_by_data(LinkedList *list, DataType data);
> // 扩展: 根据索引删除一个结点
> bool delete_by_idx(LinkedList *list, int idx);
> // 打印单链表 格式为：1 -> 2 -> 3 ->...
> void print_list(LinkedList *list);
>
>
> #endif // !LINKED_LIST_H
> ```
>
> **手动实现单链表是后续一切数据结构学习的前提和基础，所以一定要重视单链表的实现，一定要自己百分百手动将这里面的函数全部实现。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "linkedlist.h"
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > // 创建一个空的链表
> > LinkedList *create_linked_list() {
> >     return calloc(1, sizeof(LinkedList));
> > }
> > // 销毁链表
> > void destroy_linked_list(LinkedList *list) {
> >     // 遍历整条链表,包括最后一个结点,然后逐一free
> >     Node *curr = list->head;
> >     while (curr != NULL) {
> >         Node *tmp = curr->next;
> >         free(curr);
> >         curr = tmp;
> >     }
> >     free(list);
> > }
> >
> >
> > // 头部插入结点
> > bool add_before_head(LinkedList *list, DataType data) {
> >     // 1.分配一个新结点,初始化它
> >     Node *new_node = malloc(sizeof(Node));
> >     if (new_node == NULL) {
> >         printf("error: malloc failed in add_before_head.\n");
> >         return false;
> >     }
> >     new_node->data = data;
> >     // 2.让新结点指向原本的第一个结点
> >     new_node->next = list->head;
> >
> >
> >     // 3.更新头指针
> >     list->head = new_node;
> >
> >
> >     // 考虑特殊情况
> >     //if(list->size == 0)
> >     if (list->tail == NULL) {
> >         // 说明头插之前链表为空, 更新尾指针
> >         list->tail = new_node;
> >     }
> >     list->size++;
> >     return true;
> > }
> > // 尾部插入结点
> > bool add_behind_tail(LinkedList *list, DataType data) {
> >     // 1.分配一个新结点,初始化它
> >     Node *new_node = malloc(sizeof(Node));
> >     if (new_node == NULL) {
> >         printf("error: malloc failed in add_behind_tail.\n");
> >         return false;
> >     }
> >     new_node->data = data;
> >     new_node->next = NULL;
> >
> >
> >     // 2.判断链表插入之前是否为空
> >     if (list->size == 0) {
> >         // 尾插之前链表为空
> >         list->head = new_node;
> >         list->tail = new_node;
> >         list->size++;
> >         return true;
> >     }
> >     // 链表尾插之前不为空
> >     list->tail->next = new_node;
> >     list->tail = new_node;
> >     list->size++;
> >     return true;
> > }
> > // 按索引插入结点
> > /*
> >     对于链表来说,第一个结点的索引规定是0,那么链表的结点索引合法范围是[0, size-1]
> >     分析:
> >     1.参数校验,对错误的参数进行错误的处理
> >     index在这个函数中,合法的取值范围是[0, size]
> >     其中0表示头插, size表示尾插
> >
> >
> >     2.处理特殊值,尾插和头插直接调用已实现的函数
> >     3.在index合法,且不是头插尾插,即在中间插入结点时
> > */
> > bool add_by_idx(LinkedList *list, int index, DataType data) {
> >     if (index < 0 || index > list->size) {
> >         printf("Illegal Arguments: index = %d\n", index);
> >         return false;
> >     }
> >     if (index == 0) {
> >         return add_before_head(list, data);
> >     }
> >     if (index == list->size) {
> >         return add_behind_tail(list, data);
> >     }
> >
> >
> >     // 处理中间插入结点的情况
> >     Node *new_node = malloc(sizeof(Node));
> >     if (new_node == NULL) {
> >         printf("error: malloc failed in add_index.\n");
> >         return false;
> >     }
> >     new_node->data = data;
> >
> >
> >     // 遍历链表,找到index-1位置的结点
> >     Node *prev = list->head;
> >     for (int i = 0; i < index - 1; i++) {
> >         prev = prev->next;
> >     }   // for循环结束时,prev指针指向index索引的前驱结点
> >
> >
> >     // 让新结点指向prev的后继结点
> >     new_node->next = prev->next;
> >     // 让prev指向新结点
> >     prev->next = new_node;
> >     list->size++;
> >     return true;
> > }
> >
> >
> > // 根据索引搜索结点
> > Node *search_by_idx(LinkedList *list, int index) {
> >     if (index < 0 || index > list->size - 1) {  // size-1就是最后一个结点
> >         printf("Illegal Arguments: index = %d\n", index);
> >         return NULL;
> >     }
> >     // 索引合法
> >     Node *curr = list->head;
> >     for (size_t i = 0; i < index; i++)  // 小于index就表示寻找index索引的结点
> >     {
> >         curr = curr->next;
> >     }   // for循环结束时,curr指针指向index索引位置的结点
> >     return curr;
> > }
> >
> >
> > // 根据数据搜索结点
> > Node *search_by_data(LinkedList *list, DataType data) {
> >     // 惯用法遍历每一个结点,遍历过程中判断即可
> >     Node *curr = list->head;
> >     while (curr != NULL) {
> >         if (curr->data == data) {
> >             // 找到了
> >             return curr;
> >         }
> >         curr = curr->next;
> >     }
> >     // 遍历结束都没有return 说明没有找到
> >     return NULL;
> > }
> >
> >
> > // 根据数据删除结点
> > /*
> >     对于一条单链表来说, 在一个确定的结点的后面进行删除/新增操作, 它的时间复杂度是O(1)
> >     链表的结点删除,哪些是O(1)的呢?
> >     1.删除第一个结点是不是? 是,因为这个过程基本只需要改变头指针的指向就可以了
> >     2.删除最后一个结点是不是呢? 不是, 因为删除最后一个结点,需要找到倒数第二个结点,这需要遍历数组,时间复杂度是O(n)
> >     3.删除中间的结点是不是呢? 肯定不是,因为需要遍历找到这个结点
> >     于是将单链表的删除分解成两个步骤:
> >     1.假如删除的是第一个结点
> >     2.如果删除的是第一个结点外的其它结点
> >
> >
> > */
> > bool delete_by_data(LinkedList *list, DataType data) {
> >     // 校验: 如果链表为空,不删除了
> >     if (list->head == NULL) {
> >         printf("链表为空,无法删除!\n");
> >         return false;
> >     }
> >     Node *curr = list->head;    // 该指针用于遍历整条单链表
> >     // 1.处理删除的是第一个结点的情况
> >     if (curr->data == data) {
> >         list->head = curr->next;    // 这步操作不论链表是否只有一个结点 都是要做的
> >         if (list->head == NULL) {
> >             // 说明链表仅有一个结点,删除后,要同步更新尾指针
> >             list->tail = NULL;
> >         }
> >         free(curr);
> >         list->size--;
> >         return true;
> >     }
> >
> >
> >     // 2.处理其他结点的删除情况
> >     // 已经有一个指针,叫curr,它目前指向第一个结点
> >     Node *prev = curr;
> >     curr = curr->next;
> >
> >
> >     while (curr != NULL) {  // 从第二个结点开始,遍历完整条单链表
> >         if (curr->data == data) {
> >             // 找到了待删除目标结点,curr指向它,此时prev指向它的前驱
> >             prev->next = curr->next;
> >             if (curr->next == NULL) {
> >                 // 待删除结点是尾结点
> >                 list->tail = prev;
> >             }
> >             free(curr);
> >             list->size--;
> >             return true;
> >         }
> >         prev = curr;
> >         curr = curr->next;
> >     } // while循环结束时,curr指针指向NULL,prev指向链表的最后一个结点
> >
> >
> >     // while循环结束都没有return, 说明没找到目标data的结点,删除失败
> >     return false;
> > }
> >
> >
> > // 根据索引删除结点
> > bool delete_by_idx(LinkedList *list, int idx) {
> >     if (list->head == NULL) {
> >         printf("链表为空,无法删除!\n");
> >         return false;
> >     }
> >
> >
> >     // 检查链表是否为空或索引是否越界
> >     if (idx < 0 || idx >= list->size) {
> >         printf("Illegal Arguments: index = %d\n", idx);
> >         return false;
> >     }
> >
> >
> >     Node *curr = list->head;
> >     Node *prev = NULL;
> >
> >
> >     // 如果要删除的是第一个结点
> >     if (idx == 0) {
> >         list->head = curr->next;  // 更新头指针
> >         // 若删除的结点是唯一的结点
> >         if (list->size == 1) {
> >             list->tail = NULL;  // 更新尾指针
> >         }
> >         free(curr);
> >         list->size--;
> >         return true;
> >     }
> >
> >
> >     // 如果删除的结点不是第一个结点
> >     for (int i = 0; i < idx; i++) {
> >         prev = curr;
> >         curr = curr->next;
> >     }
> >
> >
> >     // 让前驱结点指向后继结点
> >     prev->next = curr->next;
> >
> >
> >     // 如果要删除的是尾结点, 则需要更新尾指针
> >     if (idx == list->size - 1) {
> >         list->tail = prev;
> >     }
> >
> >
> >     free(curr);
> >     list->size--;
> >     return true;
> > }
> >
> >
> > // 打印单链表 格式为：1 -> 2 -> 3 ->...
> > void print_list(LinkedList *list) {
> >     Node *curr = list->head;
> >     // 遍历此单链表
> >     while (curr != NULL) {
> >         printf("%d", curr->data);
> >         // 如果不是链表的最后一个结点，就打印箭头
> >         if (curr->next != NULL) {
> >             printf(" -> ");
> >         }
> >         curr = curr->next;
> >     }
> >     printf("\n");
> > }
> > ```
> >
> > **再给出一个测试用例，如下：**
> >
> > ```c
> > int main(void) {
> >     // 创建一个空的链表
> >     LinkedList *list = create_linked_list();
> >
> >
> >     // 测试头部插入
> >     add_before_head(list, 10);
> >     add_before_head(list, 20);
> >     add_before_head(list, 30);
> >
> >
> >     printf("在头部插入30, 20, 10后:\n");
> >     print_list(list); // 预期输出: 30 -> 20 -> 10
> >
> >
> >     // 测试尾部插入
> >     add_behind_tail(list, 40);
> >     add_behind_tail(list, 50);
> >
> >
> >     printf("在尾部插入40, 50后:\n");
> >     print_list(list); // 预期输出: 30 -> 20 -> 10 -> 40 -> 50
> >
> >
> >     // 测试按索引插入
> >     add_by_idx(list, 2, 25); // 在索引2的位置插入25
> >
> >
> >     printf("在索引2插入25后:\n");
> >     print_list(list); // 预期输出: 30 -> 20 -> 25 -> 10 -> 40 -> 50
> >
> >
> >     // 测试按索引搜索
> >     Node *node = search_by_idx(list, 2);
> >     printf("索引2处的元素: %d\n", node->data); // 预期输出: 25
> >
> >
> >     // 测试按数据搜索
> >     node = search_by_data(list, 40);
> >     printf("找到数据40的结点: %d\n", node->data); // 预期输出: 40
> >
> >
> >     // 测试按数据删除
> >     delete_by_data(list, 25);
> >     printf("删除数据25后:\n");
> >     print_list(list); // 预期输出: 30 -> 20 -> 10 -> 40 -> 50
> >
> >
> >     // 测试按索引删除
> >     delete_by_idx(list, 0); // 删除索引0处的元素
> >     printf("删除索引0处的元素后:\n");
> >     print_list(list); // 预期输出: 20 -> 10 -> 40 -> 50
> >
> >
> >     // 销毁链表
> >     destroy_linked_list(list);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 链表基础面试题：快慢指针法

> 基于链表的结点定义：
>
> ```c
> typedef struct node {
>     int data;
>     struct node *next;
> } Node;
> ```
>
> 以及相应的二级指针尾插法构建单链表：
>
> ```c
> // 实现尾插法构建链表
> void insert_tail(Node **head, int new_data) {
>     // 1.分配新结点，初始化它
>     Node *new_node = malloc(sizeof(Node));
>     if (new_node == NULL) {
>         printf("error: malloc failed in insert_tail.\n");
>         exit(1);
>     }
>     new_node->data = new_data;
>     new_node->next = NULL;
>     // 3.链表非空时,让原本最后一个结点指向新结点
>     if (*head != NULL) {
>         // 2.遍历找到最后一个结点
>         Node *end = *head;
>         while (end->next != NULL) {
>             end = end->next;
>         } // while循环结束时, end指向最后一个结点
>         end->next = new_node;
>         return;
>     }
>     // 链表尾插之前是空的,那就直接更新头指针就行了
>     *head = new_node;
> }
> ```
>
> **后续单链表的面试题，也请基于此链表结点的定义，以及尾插法构建链表实现。**
>
> 利用**快慢指针法**，直接求解下列两个问题：
>
> 1.求链表中间结点的值
>
> 2.判断单链表是否有环
>
> 注意：
>
> **不仅要定义函数实现对应功能，还需要编写测试用例，进行测试。尤其是测试单链表有环，要自己构建出一条有环的单链表进行测试。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **求链表中间结点的值以及相应测试代码：**
> >
> > ```c
> > int find_mid_ele(Node *head) {
> >     Node *fast = head, *slow = head;
> >     /*
> >         fast != NULL意味着偶数链表长度时,fast没有到终点
> >         fast->next != NULL意味着奇数链表长度时,fast没有到终点
> >     */
> >     while (fast != NULL && fast->next != NULL) {
> >         // fast指针没有到达终点
> >         slow = slow->next;
> >         fast = fast->next->next;
> >     }   // while循环结束时,fast到达终点了,slow指向中间结点
> >     return slow->data;
> > }
> > // 测试代码
> > int main(void) {
> >     Node *head = NULL;  // head代表链表的头指针，此时是一条空链表
> >     insert_tail(&head, 1);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 3);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 5);
> >     int ret = find_mid_ele(head);   // ret的值为3
> >     insert_tail(&head, 6);
> >     insert_tail(&head, 7);
> >     insert_tail(&head, 8);
> >     int ret2 = find_mid_ele(head);  // ret2的值为5
> >     return 0;
> > }
> > ```
> >
> > **判断单链表有环以及相应测试代码：**
> >
> > ```c
> > bool has_circle(Node *list) {
> >     Node *fast = list;
> >     Node *slow = list;
> >
> >
> >     while (fast != NULL && fast->next != NULL) {
> >         slow = slow->next;
> >         fast = fast->next->next;
> >         if (slow == fast) {
> >             return true;    // 相遇了就表示有环
> >         }
> >     }
> >     // 如果循环能够结束, 说明没有环
> >     return false;
> > }
> >
> >
> > // 测试代码
> > int main(void) {
> >     Node *head = NULL;  // head代表链表的头指针，此时是一条空链表
> >     insert_tail(&head, 1);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 3);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 5);
> >
> >
> >     /*
> >     构建出一条有环单链表
> >     1 -> 2 -> 3 -> 4 -> 5 -> 2 -> 3 -> 4 ....
> >     如何构建呢？
> >     1.找到单链表的尾结点（last指针来寻找它）
> >     2.在寻找尾结点的过程中, 记录一下结点2(用second指针记录)
> >     3.让last结点指向second结点
> >     */
> >     Node *last = head;
> >     Node *second = head;
> >     int count = 0;
> >     while (last->next != NULL) {
> >         count++;
> >         if (count == 2) {
> >             second = last;  // 记录一下结点2
> >         }
> >         last = last->next;
> >     }   // while循环结束时,second指针指向结点2, last指针指向结点5
> >     last->next = second;
> >     bool ret = has_circle(head);    // ret等于true，表示单链表有环
> >     return 0;
> > }
> > ```
>
> 以上。

#### 链表基础面试题：反转单链表

> 给定一条单链表，请反转这条单链表。
>
> 举例：
>
> 输入: 1 --&gt; 2 --&gt; 3
>
> 输出: 3 --&gt; 2 --&gt; 1
>
> 基于以下函数的声明实现：
>
> ```c
> Node* reverse(Node *list); // 反转当前单链表并返回新的头指针
> ```
>
> 注意：
>
> **请采用递归和循环迭代两种方式求解这个问题。**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **两种方式实现反转单链表，参考代码如下：**
> >
> > ```c
> > /*
> >     循环迭代的方式实现单链表的反转操作：三指针法
> >     在循环的过程中：
> >     让curr结点指向prev结点
> >     然后向后移动三个指针
> > */
> > Node *reverse_list_loop(Node *head) {
> >     Node *prev = NULL;
> >     Node *curr = head;
> >     /*
> >         next如果定义在循环的外面，那么在while循环当中就需要手动来更新next指针
> >             next = curr -> next
> >             而且这个更新还需要判断，curr不是空指针
> >         next如果定义在循环的内部，那么在while循环当中就不需要手动来更新next指针了
> >             因为每循环一次就重新给next指针赋值，而这个赋值就是next = curr->next
> >             而且也不用给curr判NULL了，因为curr是NULL时，循环停止了，进不到循环体
> >     */
> >     //Node *next = curr->next;
> >     while (curr != NULL) {
> >         Node *next = curr->next;
> >         curr->next = prev;  // 反转的核心操作
> >         prev = curr;
> >         curr = next;
> >         /*if (curr != NULL) {
> >             next = curr->next;
> >         }*/
> >     }
> >     return prev;
> > }
> >
> >
> > // 递归的方式反转单链表
> > Node *reverse_list_recursion(Node *head) {
> >     // 1.递归的出口
> >     if (head == NULL || head->next == NULL) {
> >         return head;
> >     }
> >     // 2.递归体
> >     // 1.先完成n-1个结点的反转
> >     Node *ret = reverse_list_recursion(head->next);
> >     // 2.让原本的第二个结点指向原本的第一个结点
> >     head->next->next = head;
> >     // 3.反转第一个结点
> >     head->next = NULL;
> >     return ret;
> > }
> > ```
> >
> > **测试用例如下：**
> >
> > ```c
> > int main(void) {
> >  Node *head = NULL; // head代表链表的头指针，此时是一条空链表
> >     insert_tail(&head, 1);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 3);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 5);
> >
> >
> >  // 单链表的反转，最终得到单链表 5 -> 4 -> 3 -> 2 -> 1 
> >     // head = reverse_list_loop(head);
> >     // head = reverse_list_recursion(head);
> >
> >
> >      return 0;
> > }
> > ```
>
> 以上。

#### 链表基础面试题：合并两条有序单链表

> **合并两条有序的单向链表，使得合并后的链表也是有序的 (要求: 不能额外申请堆内存空间)。**
>
> > 输入：
> >
> > list1: 1 --&gt; 3 --&gt; 5
> >
> > list2: 2 --&gt; 4 --&gt; 6
> >
> > 输出：
> >
> > 1 --&gt; 2 --&gt; 3 --&gt; 4 --&gt; 5 --&gt; 6
>
> 可以直接基于以下函数声明来进行实现。
>
> ```c
> Node* merge_two_lists(Node* list1, Node* list2);    // 合并两条有序单链表，并返回合并后新链表的头指针
> ```
>
> 要求使用递归和循环迭代两种方式实现这个功能。
>
> **注：循环实现时，可以思考一下加头结点的实现与不加的区别。**
>
> **不仅要定义函数实现对应功能，还需要编写测试用例，进行测试。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **循环迭代方式实现合并有序单链表，不带头结点的实现：**
> >
> > ```c
> > // 合并两条有序单链表，并且返回新链表的头指针
> > Node *merge_lists(Node *list1, Node *list2) {
> >     // 1.处理链表为空的情况
> >     /*if (list1 == NULL){
> >         return list2;
> >     }
> >     if (list2 == NULL){
> >         return list1;
> >     }*/
> >     if (!list1 || !list2) { // 如果list1或者list2为NULL
> >         return list1 ? list1 : list2;
> >     }
> >     // 2.对两条单链表的第一个结点做判断处理,找到较小结点,用来初始化head和tail指针
> >     Node *head = NULL, *tail = NULL;
> >     if (list1->data < list2->data) {
> >         // list1的第一个结点是最小结点,它就是合并后单链表的第一个结点,也就是返回值头指针
> >         head = tail = list1;
> >         list1 = list1->next;
> >     }
> >     else {
> >         // list2的第一个结点是最小结点或者它们两第一个结点是一样的
> >         // 这时list2的第一个结点就是合并后单链表的第一个结点,也就是返回值头指针
> >         head = tail = list2;
> >         list2 = list2->next;
> >     }
> >
> >
> >     // 3.后续结点可以统一用循环处理,不需要单独处理了
> >     while (list1 != NULL && list2 != NULL) {    // 只要两条单链表都同时还有结点,那就继续"穿针引线"
> >         if (list1->data < list2->data) {
> >             // list1指向的结点是相对较小的结点,那就先"穿针引线"它
> >             tail->next = list1;
> >             tail = list1;
> >             list1 = list1->next;
> >         }
> >         else {
> >             // list2指向的结点是相对较小的结点或者两个结点取值一样,那就先"穿针引线"它
> >             tail->next = list2;
> >             tail = list2;
> >             list2 = list2->next;
> >         }
> >     }   // while循环结束时,两条单链表一定有一条是空的,一定有一条是非空的,但都不知道是哪一条
> >     // 但无所谓, 我们只需要判断一下,然后让tail结点指向非空单链表的剩余结点
> >     if (list1 != NULL) {
> >         tail->next = list1;
> >     }
> >     if (list2 != NULL) {
> >         tail->next = list2;
> >     }
> >     // 不要忘记给返回值
> >     return head;
> > }
> > ```
> >
> > **循环迭代方式实现合并有序单链表，带头结点的实现：**
> >
> > ```c
> > // 带有头结点,以合并两条有序单链表
> > Node *merge_lists2(Node *list1, Node *list2) {
> >     // 1.处理链表为空的情况
> >     if (!list1 || !list2) { // 如果list1或者list2为NULL
> >         return list1 ? list1 : list2;
> >     }
> >
> >
> >     // 2.创建虚拟头结点,初始化head和tail指针
> >     Node head_node = { 0, NULL };
> >     Node *head = &head_node, *tail = &head_node;
> >
> >
> >     // 3.循环遍历两条单链表,逐一比较对应位置的结点值,将较小的结点链接到tail结点的后面
> >     while (list1 != NULL && list2 != NULL) {    // 只要两条单链表都同时还有结点,那就继续"穿针引线"
> >         if (list1->data < list2->data) {
> >             // list1结点较小,它被合并到新链表中
> >             tail->next = list1;
> >             tail = list1;
> >             list1 = list1->next;
> >         }
> >         else {
> >             // list2结点较小或者两个位置的结点取值一样,它被合并到新链表中
> >             tail->next = list2;
> >             tail = list2;
> >             list2 = list2->next;
> >         }
> >     }   // while循环结束时,必然有一条链表为空,另一条不为空
> >
> >
> >     // 4.循环合并结束后,总会有一条链表为空,另一条非空,判断一下将非空链表链接到tail结点后面
> >     if (list1 != NULL) {
> >         tail->next = list1;
> >     }
> >     if (list2 != NULL) {
> >         tail->next = list2;
> >     }
> >
> >
> >     // 5.不要忘记给出函数的返回值
> >     return head->next;  // 函数出栈后,head_node这个局部变量结点就被销毁了
> > }
> > ```
> >
> > **递归方式实现合并有序单链表，参考实现代码如下：**
> >
> > ```c
> > // 递归的方式合并两条单链表
> > Node *merge_lists_recursion(Node *list1, Node *list2) {
> >     // 1.递归的出口
> >     if (!list1 || !list2) { // 如果list1或者list2为NULL
> >         return list1 ? list1 : list2;
> >     }
> >
> >
> >     // 2.递归体
> >     // 比较两条链表的第一个结点取值,然后取较小的结点作为合并单链表的第一个结点,而且它还是函数的返回值
> >     if (list1->data < list2->data) {
> >         // list1指向的结点是较小的,list1就是合并后新链表的第一个结点
> >         list1->next = merge_lists_recursion(list1->next, list2);
> >         return list1;
> >     }
> >     else {
> >         // list2指向的结点是较小或者两个结点相等,list2就是合并后新链表的第一个结点
> >         list2->next = merge_lists_recursion(list1, list2->next);
> >         return list2;
> >     }
> > }
> > ```
> >
> > **测试代码如下：**
> >
> > ```c
> > int main(void) {
> >     Node *list1 = NULL;
> >     Node *list2 = NULL;
> >     insert_tail(&list1, 1);
> >     insert_tail(&list1, 3);
> >     insert_tail(&list1, 5);
> >     insert_tail(&list1, 7);
> >
> >
> >     insert_tail(&list2, 2);
> >     insert_tail(&list2, 4);
> >     insert_tail(&list2, 6);
> >     insert_tail(&list2, 8);
> >     insert_tail(&list2, 9);
> >
> >
> >     // 合并成功后的单链表是 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9
> >     // Node *ret = merge_lists(list1, list2);   
> >     // Node *ret2 = merge_lists2(list1, list2);
> >     // Node *ret3 = merge_lists_recursion(list1, list2);
> > }
> > ```
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。
>
> 以下单链表的扩展编程题，都基于以下链表结点的定义，以及一个尾插法构建单链表的实现：
>
> ```c
> typedef struct Node {
>     int data;
>     struct Node *next;
> } Node;
>
>
> // 尾插法
> void insert_tail(Node **head, int val) {
>     Node *new_node = calloc(1, sizeof(Node));   // 用calloc避免忘记设置next域为NULL
>     if (new_node == NULL) {
>         printf("malloc failed in insert_tail.\n");
>         exit(1);
>     }
>     new_node->data = val;
>     if (*head == NULL) {
>         *head = new_node;
>     }
>     else {
>         Node *curr = *head;
>         while (curr->next != NULL) {
>             curr = curr->next;
>         }
>         curr->next = new_node;
>     }
> }
> ```
>
> 接下来请你实现以下一些功能。

#### 扩展：删除连续重复结点

> 删除单链表中**连续出现**的重复节点，具体来说，当链表中有相邻的两个或多个节点的值相同时，删除后续的重复节点，只保留**第一个**出现的节点。
>
> 举例：
>
> > 单链表：1 -&gt; 2 -&gt; 2 -&gt; 3 -&gt; 4 -&gt; 4 -&gt; 4 -&gt; 5
> >
> > 删除后将得到链表：1 -&gt; 2 -&gt; 3 -&gt; 4 -&gt; 5
> >
> > 单链表：1 -&gt; 1 -&gt; 2 -&gt; 3 -&gt; 3 -&gt; 3 -&gt; 4
> >
> > 删除后将得到链表：1 -&gt; 2 -&gt; 3 -&gt; 4
>
> 请基于以下函数声明实现这个功能：
>
> ```c
> void del_continuous_repeat(Node *head);
> ```
>
> 注：该函数不会修改头指针，所以使用一级指针传参且函数也没有返回值。
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > ```c
> > // 删除连续的重复节点，注意链表结点定义以及尾插函数已经被省略了
> > void del_continuous_repeat(Node *head) {
> >     // 如果链表为空或仅有一个结点,则无事发生
> >     if (head == NULL || head->next == NULL) {
> >         return;
> >     }
> >     Node *curr = head;
> >     while (curr->next != NULL) {
> >         if (curr->data == curr->next->data) {
> >             /*
> >                 如果当前结点curr和后继结点curr->data的data相同, 则出现连续重复结点
> >                 此时需要删除一个结点,并free
> >                 那么删除哪一个结点呢?
> >                 删除curr结点还是curr->next结点呢?
> >                 当然是删除curr->next结点
> >                 因为单链表的删除只能在确定结点的后面执行删除操作, 才是O(1)时间复杂度
> >             */
> >             Node *tmp = curr->next; // 记录curr->next结点,后续用于free
> >             /*
> >                 删除curr->next结点
> >                 需要curr->next结点的前驱结点指向curr->next的后继结点,也就是从链表中将curr->next结点绕过去
> >                 curr->next结点前驱是curr结点
> >                 curr->next结点后继是curr->next->next结点,也就是tmp->next
> >             */
> >             curr->next = tmp->next;     // 删除核心逻辑代码
> >             free(tmp);
> >         }
> >         else {
> >             // 没有重复结点,继续遍历结点
> >             curr = curr->next;
> >         }
> >     }
> > }
> >
> >
> > // 以下是测试代码，链表结点定义以及尾插代码省略了
> > int main(void) {
> >     Node *head = NULL;
> >     insert_tail(&head, 1);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 3);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 5);
> >     // 此时单链表是：1 -> 2 -> 2 -> 3 -> 4 -> 4 -> 4 -> 5
> >
> >
> >     del_continuous_repeat(head);    // 删除操作后，单链表是 1 -> 2 -> 3 -> 4 -> 5
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：检查回文单链表

> 给定一条单链表，请检查它是否为回文单链表。所谓回文单链表，即从头到尾和从尾到头数据都相同的单链表。
>
> 举例：
>
> > 1 -&gt; 2 -&gt; 3 -&gt; 2 -&gt; 1 就是一条回文单链表
> >
> > 1 -&gt; 2 -&gt; 2 -&gt; 1 也是一条回文单链表
>
> 请基于以下函数声明实现这个功能：
>
> ```c
> bool is_palindrome_list(Node *head);
> ```
>
> 注意：
>
> 1. **针对单链表进行回文检查，不应改变此链表的结构。若程序必须改变链表结构，需在判断完成后还原。**
> 2. **空链表或只有一个结点的链表默认就是回文链表。**
>
> 提示，检查回文链表只需要以下几步就可以实现了：
>
> 1. 找到单链表的中间结点
> 2. 将链表的后半部分反转（思考反转的起点是哪一个结点？）
> 3. 将反转后半部分的结点和前半部分逐一比较，如果数据都相同则是回文链表，若有任一结点不同则不是回文链表。
> 4. 此过程会改变链表结构，所以需要考虑还原。（如何实现这个还原操作呢？）
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > ```c
> > // 反转单链表
> > Node *reverse(Node *head) {
> >     Node *prev = NULL;
> >     Node *current = head;
> >
> >
> >     while (current != NULL) {
> >         Node *next = current->next;
> >         current->next = prev;
> >         prev = current;
> >         current = next;
> >     }
> >     return prev;
> > }
> >
> >
> > // 快慢指针法找到链表中间节点
> > Node *find_mid_node(Node *head) {
> >     if (head == NULL) {
> >         return NULL;
> >     }
> >     Node *slow = head, *fast = head;
> >     while (fast != NULL && fast->next != NULL) {
> >         slow = slow->next;
> >         fast = fast->next->next;
> >     }
> >     return slow;
> > }
> >
> >
> > // 检查链表是否为回文
> > bool is_palindrome_list(Node *head) {
> >     if (head == NULL || head->next == NULL) {
> >         // 空链表或单个节点的链表默认是回文的
> >         return true;
> >     }
> >     // 找到中间节点
> >     Node *mid_node = find_mid_node(head);
> >
> >
> >     Node *second_half = reverse(mid_node);  // 反转后，后半部分链表的头指针
> >     // 记录后半部分链表的头指针，用于后续恢复链表
> >     Node *tmp_second = second_half;
> >
> >
> >     // 比较前后两部分的节点数据
> >  Node *first_half = head;
> >     bool is_palindrome = true;  // 用于作为返回值
> >     while (second_half != NULL) {   // 遍历后半部分链表
> >         if (first_half->data != second_half->data) {
> >             // 前后部分链表结点取值有任一不同，不是回文单链表
> >             is_palindrome = false;
> >         }
> >         first_half = first_half->next;
> >         second_half = second_half->next;
> >     }
> >     // 恢复原始链表
> >     reverse(tmp_second);    // 反转后半部分即可
> >     return is_palindrome;    // 返回是否是回文单链表
> > }
> >
> >
> > // 以下是测试代码，链表结点定义以及尾插代码省略了
> > int main(void) {
> >     // 测试用例 1：偶数长度回文链表
> >     Node *head1 = NULL;
> >     insert_tail(&head1, 1);
> >     insert_tail(&head1, 2);
> >     insert_tail(&head1, 3);
> >     insert_tail(&head1, 3);
> >     insert_tail(&head1, 2);
> >     insert_tail(&head1, 1);
> >     bool ret1 = is_palindrome_list(head1);
> >     printf("list1 is_palindrome_list: %s\n", ret1 ? "True" : "False");
> >
> >
> >     // 测试用例 2：奇数长度回文链表
> >     Node *head2 = NULL;
> >     insert_tail(&head2, 1);
> >     insert_tail(&head2, 2);
> >     insert_tail(&head2, 3);
> >     insert_tail(&head2, 4);
> >     insert_tail(&head2, 3);
> >     insert_tail(&head2, 2);
> >     insert_tail(&head2, 1);
> >     bool ret2 = is_palindrome_list(head2);
> >     printf("list2 is_palindrome_list: %s\n", ret2 ? "True" : "False");
> >
> >
> >     // 测试用例 3：偶数长度非回文链表
> >     Node *head3 = NULL;
> >     insert_tail(&head3, 1);
> >     insert_tail(&head3, 2);
> >     insert_tail(&head3, 3);
> >     insert_tail(&head3, 4);
> >     insert_tail(&head3, 2);
> >     insert_tail(&head3, 1);
> >     bool ret3 = is_palindrome_list(head3);
> >     printf("list3 is_palindrome_list: %s\n", ret3 ? "True" : "False");
> >
> >
> >     // 测试用例 4：奇数长度非回文链表
> >     Node *head4 = NULL;
> >     insert_tail(&head4, 1);
> >     insert_tail(&head4, 2);
> >     insert_tail(&head4, 3);
> >     insert_tail(&head4, 4);
> >     insert_tail(&head4, 5);
> >     bool ret4 = is_palindrome_list(head4);
> >     printf("list4 is_palindrome_list: %s\n", ret4 ? "True" : "False");
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：实现真正意义上的链表结点去重

> 给定一个单链表，请编写一个函数来删除链表中所有重复的节点，只保留第一次出现的节点，**注意这里不再强调重复结点连续出现，允许间断出现。**
>
> 举例：
>
> > 输入: 1 -&gt; 2 -&gt; 3 -&gt; 2 -&gt; 4 -&gt; 3 -&gt; 5
> >
> > 输出: 1 -&gt; 2 -&gt; 3 -&gt; 4 -&gt; 5
>
> **注意：要求在O(n)的时间复杂度内，完成这个问题的求解。**
>
> 提示：计数去重，这是非常典型的哈希表的应用场景，不妨考虑使用哈希表来完成这个操作。
>
> > ###### 参考代码
> >
> > **首先给出单链表和哈希表实现的头文件：**
> >
> > ```c
> > #ifndef HASH_TABLE_H
> > #define HASH_TABLE_H
> >
> >
> > #include <stdbool.h>
> > #include <stdint.h>
> > // 为了能够针对单链表结点去重，所以包含单链表头文件，以包含单链表的相关定义
> > #include "linked_list.h"
> >
> >
> > #define DEFAULT_CAPACITY 8  // 哈希表的初始默认容量是8
> >
> >
> > // 哈希表的结点类型
> > typedef struct hash_node {
> >     ElementType key;    // 哈希表只存储key，key是单链表中的元素，实现去重时，它是唯一的
> >     struct hash_node *next;
> > } HashNode;
> >
> >
> > // 由于链表的长度不确定，所以我们使用一个动态哈希表
> > typedef struct {
> >     HashNode **buckets; 
> >     int size;               // 键值对的个数
> >     int capacity;           // 哈希表底层数组的长度
> >     uint32_t hash_seed;     // 哈希函数需要的种子值
> > } DynamicHashMap;
> >
> >
> > // 创建一个空的初始容量是8的哈希表
> > DynamicHashMap *create_hashmap();
> >
> >
> > // 销毁哈希表
> > void destroy_hashmap(DynamicHashMap *map);
> >
> >
> > // 向哈希表添加元素
> > bool put(DynamicHashMap *map, ElementType key);
> >
> >
> > // 检查哈希表是否包含某个元素
> > bool is_contains(DynamicHashMap *map, ElementType key);
> >
> >
> > #endif // HASH_TABLE_H
> >
> >
> >
> >
> > // ------------------------------------------------- //
> >
> >
> > #include <stdio.h>
> > typedef int ElementType;
> >
> >
> > typedef struct list_node {
> >     ElementType data;
> >     struct list_node *next;
> > } Node;
> >
> >
> > // 二级指针尾插法构建单链表
> > void insert_tail(Node **head, ElementType val);
> > ```
> >
> > **紧接着是哈希表的实现源文件：**
> >
> > ```c
> > #include "hash_map.h"
> >
> >
> > #define LOAD_FACTOR_THRESHOLD  0.75     // 负载因子的阈值
> > #define CAPACITY_THRESHOLE 1024     // 数组容量的阈值
> >
> >
> > /* murmur_hash2 */
> > static uint32_t hash(const void *key, int len, uint32_t seed) {
> >     const uint32_t m = 0x5bd1e995;
> >     const int r = 24;
> >     uint32_t h = seed ^ len;
> >     const unsigned char *data = (const unsigned char *)key;
> >
> >
> >     while (len >= 4) {
> >         uint32_t k = *(uint32_t *)data;
> >         k *= m;
> >         k ^= k >> r;
> >         k *= m;
> >         h *= m;
> >         h ^= k;
> >         data += 4;
> >         len -= 4;
> >     }
> >
> >
> >     switch (len) {
> >         case 3: h ^= data[2] << 16;
> >         case 2: h ^= data[1] << 8;
> >         case 1: h ^= data[0];
> >             h *= m;
> >     };
> >
> >
> >     h ^= h >> 13;
> >     h *= m;
> >     h ^= h >> 15;
> >
> >
> >     return h;
> > }
> >
> >
> > static void rehash(HashNode *curr, HashNode **new_table, int new_capacity, uint32_t seed) {
> >     // 计算 key 的哈希值
> >     int idx = hash(&(curr->key), sizeof(ElementType), seed) % new_capacity;
> >     // 头插法
> >     curr->next = new_table[idx];
> >     new_table[idx] = curr;
> > }
> >
> >
> > // 对哈希表进行扩容操作
> > static void grow_capacity(DynamicHashMap *map) {
> >     /*
> >     * 扩容策略：
> >     * 1.如果容量没有达到阈值，那就每次将长度扩大为原先的2倍
> >     * 2.如果容量达到阈值，此时哈希表已经很长了，为了避免扩容过程性能损耗过大
> >     *   所以扩容保守一些，每次只扩容阈值长度的容量
> >     *
> >     * 扩容的过程：
> >     * 1.每个键值对结点都要重新计算哈希值，重新映射到新哈希桶中(新数组)
> >     * 2.原先的动态数组的链表很复杂，难以进行重哈希操作，建议直接丢弃它
> >     * 重新创建一个新动态数组
> >     */
> >     int new_capacity =
> >         (map->capacity <= CAPACITY_THRESHOLE) ?
> >         (map->capacity << 1) :
> >     (map->capacity + CAPACITY_THRESHOLE);
> >
> >
> >     // 动态数组扩容需要使用 calloc
> >     HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode *));
> >     if (new_buckets == NULL) {
> >         printf("Error: calloc failed in grow_capacity\n");
> >         exit(1);
> >     }
> >     // 每次扩容都更改一次哈希种子，提高安全性
> >     uint32_t seed = time(NULL);
> >
> >
> >     // 将所有键值对重新映射到新数组中
> >     for (int i = 0; i < map->capacity; i++) {
> >         HashNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             HashNode *next = curr->next;
> >             // 重新进行哈希映射
> >             rehash(curr, new_buckets, new_capacity, seed);
> >             curr = next;
> >         }
> >     }
> >     // 将旧动态数组free，但是注意不要free键值对结点，结点已经被链接到新数组中了。
> >     free(map->buckets);
> >     // 更新 HashMap 的信息
> >     map->buckets = new_buckets;
> >     map->capacity = new_capacity;
> >     map->hash_seed = seed;
> > }
> >
> >
> > // 创建一个空的初始容量是8的哈希表
> > DynamicHashMap *create_hashmap() {
> >     DynamicHashMap *map = malloc(sizeof(DynamicHashMap));
> >     if (map == NULL) {
> >         printf("Error: malloc failed in hashmap_create\n");
> >         exit(1);
> >     }
> >     map->buckets = calloc(DEFAULT_CAPACITY, sizeof(HashNode *));
> >     if (map->buckets == NULL) {
> >         // 不要忘记先free结构体
> >         free(map);
> >         printf("Error: calloc failed in hashmap_create\n");
> >         exit(1);
> >     }
> >     // 初始化其它成员
> >     map->size = 0;
> >     map->capacity = DEFAULT_CAPACITY;
> >     map->hash_seed = time(NULL);
> >     return map;
> > }
> >
> >
> > // 销毁哈希表
> > void destroy_hashmap(DynamicHashMap *map) {
> >     // 1.先遍历动态数组销毁链表的每一个结点
> >     for (int i = 0; i < map->capacity; i++) {
> >         HashNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             HashNode *tmp = curr->next;
> >             free(curr);
> >             curr = tmp;
> >         }
> >     }
> >     // 2.再销毁动态数组
> >     free(map->buckets);
> >     // 3.最后销毁哈希表结构体
> >     free(map);
> > }
> >
> >
> > // 向哈希表添加元素
> > bool put(DynamicHashMap *map, ElementType key) {
> >     // 计算key的哈希值确定存储位置
> >     int idx = hash(&key, sizeof(ElementType), map->hash_seed) % (map->capacity);
> >
> >
> >     // 遍历链表
> >     HashNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (key == curr->key) {
> >             // 此结点取值已经存在，不存入直接返回false
> >             return false;
> >         }
> >         curr = curr->next;
> >     } // while循环结束时, curr是一个NULL
> >
> >
> >     // 键值对不存在，即需要将键值对插入
> >     // 插入操作前需要计算当前哈希表的负载因子
> >     double load_factor = (1.0 * map->size) / (map->capacity);
> >     if (load_factor >= LOAD_FACTOR_THRESHOLD) {
> >         // 当前哈希表负载因子已达到阈值，将动态数组进行扩容
> >         grow_capacity(map);
> >         // 数组长度已变，需要再哈希确定当前键值对的存储位置
> >         idx = hash(&key, sizeof(ElementType), map->hash_seed) % (map->capacity);
> >     }
> >     // 开始插入新键值对
> >     HashNode *new_node = malloc(sizeof(HashNode));
> >     if (new_node == NULL) {
> >         printf("Error: malloc failed in hashmap_put\n");
> >         exit(1);
> >     }
> >     // 初始化结点
> >     new_node->key = key;
> >     // 链表的头插法
> >     new_node->next = map->buckets[idx];
> >     map->buckets[idx] = new_node;
> >
> >
> >     // 不要忘记更新size
> >     map->size++;
> >     return true;
> > }
> >
> >
> > // 检查哈希表是否包含某个元素
> > bool is_contains(DynamicHashMap *map, ElementType key) {
> >     // 计算key的哈希值确定存储位置
> >     int idx = hash(&key, sizeof(ElementType), map->hash_seed) % (map->capacity);
> >
> >
> >     // 遍历链表
> >     HashNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (key == curr->key) {
> >             // 此结点取值已经存在，返回true
> >             return true;
> >         }
> >         curr = curr->next;
> >     } // while循环结束时, 说明没找到目标结点值
> >     return false;
> > }
> > ```
> >
> > **紧接着是链表的实现源文件：**
> >
> > ```c
> > #include "linked_list.h"
> >
> >
> > // 二级指针单链表尾插法
> > void insert_tail(Node **head, int val) {
> >     Node *new_node = calloc(1, sizeof(Node));   // 用calloc避免忘记设置next域为NULL
> >     if (new_node == NULL) {
> >         printf("malloc failed in insert_tail.\n");
> >         exit(1);
> >     }
> >     new_node->data = val;
> >     if (*head == NULL) {
> >         *head = new_node;
> >     }
> >     else {
> >         Node *curr = *head;
> >         while (curr->next != NULL) {
> >             curr = curr->next;
> >         }
> >         curr->next = new_node;
> >     }
> > }
> > ```
> >
> > **最后是实现单链表去重，以及相关的测试代码：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <string.h>
> > #include "hash_map.h"
> >
> >
> > // 删除链表中的重复节点
> > void remove_duplicates(Node *head) {
> >     if (head == NULL) {
> >         return;
> >     }
> >     // 创建哈希表
> >     DynamicHashMap *map = create_hashmap();
> >     // 接下来需要执行单链表删除操作,所以需要prev和curr两个指针
> >     Node *curr = head;
> >     Node *prev = NULL;
> >     while (curr != NULL) {
> >         if (is_contains(map, curr->data)) {
> >             // 当前节点的值已存在，删除当前节点
> >             prev->next = curr->next; // 单链表删除结点的核心操作
> >             free(curr);
> >             curr = prev->next;  // 删除结点后,让curr指向prev的后继结点,此时prev和curr仍然保持跟随关系
> >         }
> >         else {
> >             // 当前节点的值不存在，将此结点值存入哈希表
> >             put(map, curr->data);
> >             prev = curr;
> >             curr = curr->next;
> >         }
> >     }
> >     // 销毁哈希表
> >     destroy_hashmap(map);
> > }
> >
> >
> > // 打印链表
> > void print_list(Node *head) {
> >     Node *current = head;
> >     while (current != NULL) {
> >         printf("%d", current->data);
> >         if (current->next != NULL) {
> >             printf(" -> ");
> >         }
> >         current = current->next;
> >     }
> >     printf("\n");
> > }
> >
> >
> > int main(void) {
> >     // 构建出一条有重复结点的单链表
> >     Node *head = NULL;
> >     insert_tail(&head, 1);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 3);
> >     insert_tail(&head, 2);
> >     insert_tail(&head, 4);
> >     insert_tail(&head, 3);
> >     insert_tail(&head, 5);
> >
> >
> >     printf("原始单链表1是: ");
> >     print_list(head);
> >     remove_duplicates(head);    // 去重的最终结果是: 1 -> 2 -> 3 -> 4 -> 5
> >     printf("去重后单链表1是: ");
> >     print_list(head);
> >     printf("\n");
> >
> >
> >     Node *head2 = NULL;
> >     // 构建一个200个结点的链表,但其中有100个结点是重复的
> >     for (int i = 0; i < 100; i++) {
> >         insert_tail(&head2, i % 10);  // 插入一些重复元素
> >         insert_tail(&head2, i);       // 插入一些唯一元素
> >     }
> >     printf("原始单链表2是: ");
> >     print_list(head2);
> >
> >
> >     remove_duplicates(head2);   // 去重的最终结果是: 1 -> 2 -> ... -> 99
> >     printf("去重后单链表2是: ");
> >     print_list(head2);
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-09"></a>

## 09 队列和栈阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/09_队列和栈阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 手动实现链式栈

> **基于以下头文件，手动实现一个链式栈：**
>
> ```c
> #ifndef LINKED_STACK_H
> #define LINKED_STACK_H
> #include <stdbool.h>
> #include <stdio.h>
> #include <stdlib.h>
>
>
> typedef int ElementType;
>
>
> // 栈的一个结点栈帧,类型定义
> typedef struct node_s {
>     ElementType data;
>     struct node_s *next;
> }StackFrame;    
>
>
> typedef struct {
>     StackFrame *top;    // 栈顶指针
> }LinkedStack;
>
>
> // 基本操作
> // 创建链式栈
> LinkedStack *stack_create();
> // 销毁链式栈
> void stack_destroy(LinkedStack *stack);
> // 判空
> bool is_empty(LinkedStack *stack);
> // 入栈
> void stack_push(LinkedStack *stack, ElementType data);
> // 出栈并返回栈顶元素
> ElementType stack_pop(LinkedStack *stack);
> // 访问栈顶元素
> ElementType stack_peek(LinkedStack *stack);
>
>
> #endif // !LINKED_STACK_H
> ```
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "linked_stack.h"
> >
> >
> > // 新建一个空栈
> > LinkedStack *stack_create() {
> >     // callock可以不用手动初始化空指针
> >     return calloc(1, sizeof(LinkedStack));
> > }
> > // 对于链式栈而言，销毁栈就是销毁链表
> > void stack_destroy(LinkedStack *stack) {
> >     // 相当于遍历链表(出栈)然后在遍历中逐个free结点
> >     StackFrame *curr = stack->top;
> >     while (curr != NULL) {
> >         StackFrame *tmp = curr->next;   // 保存后继结点
> >         free(curr);
> >         curr = tmp;
> >     }
> >     // 最后free栈结构体
> >     free(stack);
> > }
> >
> >
> > bool is_empty(LinkedStack *stack) {
> >     return stack->top == NULL;
> > }
> >
> >
> > // 相当于链表头插法插入结点，栈顶指针相当于链表的头指针
> > void stack_push(LinkedStack *stack, ElementType data) {
> >     // 1.新建一个栈帧结点
> >     StackFrame *new_frame = malloc(sizeof(StackFrame));
> >     if (new_frame == NULL) {
> >         printf("malloc failed in stack_push.\n");
> >         exit(1);
> >     }
> >     // 2.初始化新栈帧
> >     new_frame->data = data;
> >     new_frame->next = stack->top;
> >     // 3.更新栈顶指针
> >     stack->top = new_frame;
> > }
> >
> >
> > // 相当于链表在头部删除第一个结点,栈顶指针相当于链表的头指针
> > ElementType stack_pop(LinkedStack *stack) {
> >     // 1.栈判空处理
> >     if (is_empty(stack)) {
> >         printf("error: stack is empty.\n");
> >         exit(1);
> >     }
> >     // 2.出栈返回栈顶元素,并free结点,更新栈顶指针
> >     StackFrame *curr = stack->top;
> >     ElementType data = curr->data;
> >     stack->top = curr->next;
> >     free(curr);
> >     return data;
> > }
> > ElementType stack_peek(LinkedStack *stack) {
> >     if (is_empty(stack)) {
> >         printf("error: stack is empty.\n");
> >         exit(1);
> >     }
> >     return stack->top->data;
> > }
> > ```
> >
> > **测试用例代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <string.h>
> > #include "linked_stack.h"
> >
> >
> > int main(void) {
> >     // 创建一个空栈
> >     LinkedStack *stack = stack_create();
> >     if (stack == NULL) {
> >         printf("Failed to create stack.\n");
> >         return -1;
> >     }
> >
> >
> >     // 入栈操作
> >     stack_push(stack, 1);
> >     stack_push(stack, 2);
> >     stack_push(stack, 3);
> >
> >
> >     // 查看栈顶元素
> >     printf("当前栈顶元素是: %d\n", stack_peek(stack)); // 应该输出 3
> >
> >
> >     // 出栈操作，并打印出栈的元素
> >     printf("依次出栈以下元素:\n");
> >     while (!is_empty(stack)) {
> >         printf("%d\n", stack_pop(stack)); // 应该依次输出 3, 2, 1
> >     }
> >
> >
> >     // 再次尝试查看栈顶元素，预期会触发错误提示
> >     printf("栈为空时,尝试访问栈顶元素:\n");
> >     stack_peek(stack);  // 应该输出错误信息并退出
> >
> >
> >     // 销毁栈
> >     stack_destroy(stack);   return 0;
> > }
> > ```
>
> 以上。

#### 手动实现动态数组循环队列

> **基于以下动态数组队列的头文件定义，实现一个动态数组队列：**
>
> ```c
> #ifndef DYNAMIC_QUEUE_H
> #define DYNAMIC_QUEUE_H
>
>
> #include <stdbool.h>
> #include <stdlib.h>
> #include <stdio.h>
>
>
> typedef int ElementType;    // 该队列当前存储int元素
> #define DEFAULT_CAPACITY 10 // 数组队列的初始长度是10
> #define THRESHOLD 1000  // 超过阈值每次扩容1.5倍扩，否则2倍的扩
>
>
> // 定义队列结构体
> typedef struct {
>     ElementType *data;   // 动态数组存储队列元素
>     int front;           // 标记队头元素的索引
>     int rear;            // 标记队尾元素下一个位置的索引
>     int size;            // 当前队列中元素数量
>     int capacity;        // 队列容量
> } DynamicQueue;
>
>
> // 队列基本操作函数声明
> // 创建动态数组队列
> DynamicQueue *create_queue();
> // 销毁动态数组队列
> void destroy_queue(DynamicQueue *q);
> // 判空
> bool is_empty(DynamicQueue *q);
> // 判满
> bool is_full(DynamicQueue *q);
> // 入队列
> bool enqueue(DynamicQueue *q, ElementType data);
> // 出队列并且返回队头元素
> ElementType dequeue(DynamicQueue *q);
>
>
> #endif // DYNAMIC_QUEUE_H
> ```
>
> **注意：你要实现一个循环队列，而不是一个普通队列。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "dynamic_queue.h"
> >
> >
> > // 创建并初始化队列
> > DynamicQueue *create_queue() {
> >     DynamicQueue *q = calloc(1, sizeof(DynamicQueue));
> >     if (q == NULL) {
> >         printf("error: calloc failed in create_queue.\n");
> >         return NULL;
> >     }
> >     // front、rear、size自动初始化0值，无需再手动初始化了
> >     q->data = calloc(DEFAULT_CAPACITY, sizeof(ElementType));    // 使用calloc避免随机值
> >     if (q->data == NULL) {
> >         printf("error: calloc failed in create_queue.\n");
> >         free(q);
> >         return NULL;
> >     }
> >     q->capacity = DEFAULT_CAPACITY;
> >     return q;
> > }
> >
> >
> > // 销毁队列
> > void destroy_queue(DynamicQueue *q) {
> >     free(q->data);
> >     free(q);
> > }
> >
> >
> > // 检查队列是否为空
> > bool is_empty(DynamicQueue *q) {
> >     return q->size == 0;
> > }
> >
> >
> > // 检查队列是否已满
> > bool is_full(DynamicQueue *q) {
> >     return q->size == q->capacity;
> > }
> >
> >
> > /*
> >     这里采用一种简单粗暴的扩容手段:
> >     直接分配新容量的内存块
> >     然后遍历旧内存块中的队列元素,将这些元素全部从头开始复制到新内存块中
> >     这样的操作在完成后,需要更新front索引和rear索引
> > */
> > static bool resize_queue(DynamicQueue *q) {
> >     int old_capacity = q->capacity;
> >     int new_capacity = (old_capacity < THRESHOLD) ?
> >         (old_capacity << 1) :
> >     (old_capacity + (old_capacity >> 1));
> >
> >
> >     // 重新分配一个新的,更长的动态数组
> >     ElementType *new_data = malloc(new_capacity * sizeof(ElementType));
> >     if (new_data == NULL) {
> >         printf("error: realloc failed in resize_queue.\n");
> >         return false;
> >     }
> >
> >
> >     int curr = q->front;    // curr索引用于遍历整个队列中的元素
> >     int index = 0;
> >     while (index < q->size) {
> >         new_data[index] = q->data[curr];
> >         curr = (curr + 1) % q->capacity;
> >         index++;
> >     } // while循环结束时,new_data就从头开始包含了队列的所有元素 
> >     free(q->data);
> >     q->data = new_data;
> >     q->front = 0;
> >     q->rear = q->size;
> >     q->capacity = new_capacity;
> >     return true;
> > }
> >
> >
> > // 入队操作
> > bool enqueue(DynamicQueue *q, ElementType data) {
> >     if (is_full(q)) {
> >         if (!resize_queue(q)) {
> >             printf("error: 扩容失败.\n");
> >             return false; // 队列扩容失败,入队也同步失败
> >         }
> >     }
> >     q->data[q->rear] = data;
> >     q->rear = (q->rear + 1) % q->capacity;  // 循环队列
> >     q->size++;
> >     return true;
> > }
> >
> >
> > // 出队操作
> > ElementType dequeue(DynamicQueue *q) {
> >     if (is_empty(q)) {
> >         printf("error: 队列为空，无法出队。\n");
> >         exit(1);
> >     }
> >     ElementType item = q->data[q->front];
> >     q->front = (q->front + 1) % q->capacity; // 循环队列
> >     q->size--;
> >     return item;
> > }
> > ```
> >
> > **测试用例代码：**
> >
> > ```c
> > #include "dynamic_queue.h"
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     // 创建队列
> >     DynamicQueue *queue = create_queue();
> >     if (queue == NULL) {
> >         printf("创建队列失败。\n");
> >         return 1;
> >     }
> >
> >
> >     // 入队测试
> >     for (int i = 0; i < 15; i++) {
> >         if (enqueue(queue, i)) {
> >             printf("已入队: %d\n", i);
> >         }
> >         else {
> >             printf("入队失败: %d\n", i);
> >         }
> >     }
> >
> >
> >     // 打印队列容量和大小
> >     printf("队列容量: %d, 队列大小: %d\n", queue->capacity, queue->size);
> >
> >
> >     // 出队测试
> >     printf("正在出队...\n");
> >     while (!is_empty(queue)) {
> >         printf("已出队: %d\n", dequeue(queue));
> >     }
> >
> >
> >     // 销毁队列
> >     destroy_queue(queue);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 栈的应用：括号匹配问题

> **在上述已实现的一个链式栈（数组栈也行）的基础上，编写代码完成字符串括号的匹配校验。**
>
> 括号都是英文字符括号，而且有三类：{}、\[\]、()
>
> **注：**
>
> **1.若字符串中没有括号，也算做括号匹配成功。**
>
> **2.思路可以参考文档《栈》**
>
> 参考代码如下：
>
> > ###### 参考代码如下：
> >
> > **首先是链式栈的头文件，该文件中需要修改栈中元素的类型为char类型：**
> >
> > ```c
> > #ifndef LINKED_STACK_H
> > #define LINKED_STACK_H
> > #include <stdbool.h>
> > #include <stdio.h>
> > #include <stdlib.h>
> >
> >
> > // 由于栈中要存储字符，所以元素类型要改成char类型
> > typedef char ElementType;
> >
> >
> > // 栈的一个结点栈帧,类型定义
> > typedef struct node_s {
> >  ElementType data;
> >  struct node_s *next;
> > }StackFrame;
> >
> >
> > typedef struct {
> >  StackFrame *top;   // 栈顶指针
> > }LinkedStack;
> >
> >
> > // 基本操作
> > // 创建链式栈
> > LinkedStack *stack_create();
> > // 销毁链式栈
> > void stack_destroy(LinkedStack *stack);
> > // 判空
> > bool is_empty(LinkedStack *stack);
> > // 入栈
> > void stack_push(LinkedStack *stack, ElementType data);
> > // 出栈并返回栈顶元素
> > ElementType stack_pop(LinkedStack *stack);
> > // 访问栈顶元素
> > ElementType stack_peek(LinkedStack *stack);
> >
> >
> > #endif // !LINKED_STACK_H
> > ```
> >
> > **链式栈的实现代码：**
> >
> > ```c
> > #include "linked_stack.h"
> >
> >
> > // 新建一个空栈
> > LinkedStack *stack_create() {
> >     // callock可以不用手动初始化空指针
> >     return calloc(1, sizeof(LinkedStack));
> > }
> > // 对于链式栈而言，销毁栈就是销毁链表
> > void stack_destroy(LinkedStack *stack) {
> >     // 相当于遍历链表(出栈)然后在遍历中逐个free结点
> >     StackFrame *curr = stack->top;
> >     while (curr != NULL) {
> >         StackFrame *tmp = curr->next;   // 保存后继结点
> >         free(curr);
> >         curr = tmp;
> >     }
> >     // 最后free栈结构体
> >     free(stack);
> > }
> >
> >
> > bool is_empty(LinkedStack *stack) {
> >     return stack->top == NULL;
> > }
> >
> >
> > // 相当于链表头插法插入结点，栈顶指针相当于链表的头指针
> > void stack_push(LinkedStack *stack, ElementType data) {
> >     // 1.新建一个栈帧结点
> >     StackFrame *new_frame = malloc(sizeof(StackFrame));
> >     if (new_frame == NULL) {
> >         printf("malloc failed in stack_push.\n");
> >         exit(1);
> >     }
> >     // 2.初始化新栈帧
> >     new_frame->data = data;
> >     new_frame->next = stack->top;
> >     // 3.更新栈顶指针
> >     stack->top = new_frame;
> > }
> >
> >
> > // 相当于链表在头部删除第一个结点,栈顶指针相当于链表的头指针
> > ElementType stack_pop(LinkedStack *stack) {
> >     // 1.栈判空处理
> >     if (is_empty(stack)) {
> >         printf("error: stack is empty.\n");
> >         exit(1);
> >     }
> >     // 2.出栈返回栈顶元素,并free结点,更新栈顶指针
> >     StackFrame *curr = stack->top;
> >     ElementType data = curr->data;
> >     stack->top = curr->next;
> >     free(curr);
> >     return data;
> > }
> > ElementType stack_peek(LinkedStack *stack) {
> >     if (is_empty(stack)) {
> >         printf("error: stack is empty.\n");
> >         exit(1);
> >     }
> >     return stack->top->data;
> > }
> > ```
> >
> > **括号匹配函数以及相关的测试代码：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <ctype.h>
> > #include <stdbool.h>
> > #include "linked_stack.h"   // 已实现的链式栈
> >
> >
> > char get_right_bracket(char ch) {
> >     switch (ch) {
> >         case '{': return '}';
> >         case '[': return ']';
> >         case '(': return ')';
> >         default: return 0;
> >     }
> > }
> > bool is_left_bracket(char ch) {
> >     return ch == '{'
> >         || ch == '['
> >         || ch == '(';
> > }
> >
> >
> > bool is_right_bracket(char ch) {
> >     return ch == '}'
> >         || ch == ']'
> >         || ch == ')';
> > }
> >
> >
> > bool is_matching(char *str, LinkedStack *stack) {
> >     while (*str) {
> >         // 排除非括号字符
> >         if (is_left_bracket(*str)) {
> >             // 字符是左括号,于是将它对应的右括号入栈
> >             char right_bracket = get_right_bracket(*str);
> >             stack_push(stack, right_bracket);
> >         }
> >         if (is_right_bracket(*str)) {
> >             // 如果遇到右括号时栈为空,说明右括号在前面,匹配失败
> >             // 如果栈不为空就出栈,和当前字符比较,如果不一致就匹配失败
> >             if (is_empty(stack) || stack_pop(stack) != *str) {
> >                 return false;
> >             }
> >         }
> >         str++;
> >     }
> >     // 字符串遍历完成,判断栈是否空
> >     return is_empty(stack);
> > }
> >
> >
> > int main(void) {
> >     LinkedStack *stack = stack_create();
> >     char *str = "1()23{[}";
> >     if (is_matching(str, stack)) {
> >         printf("匹配成功!\n");
> >     }
> >     else {
> >         printf("匹配失败!\n");
> >     }
> >     stack_destroy(stack);
> >     return 0;
> > }
> > ```
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：手动实现动态数组栈

> **基于以下头文件，手动实现一个动态数组栈：**
>
> ```c
> #ifndef DYNAMIC_STACK_H
> #define DYNAMIC_STACK_H
> #include <stdio.h>
> #include <stdlib.h>
> #include <stdbool.h>
>
>
> typedef int ElementType;
>
>
> typedef struct {
>     ElementType *elements;   // 指向动态数组首元素的指针
>     int size;   // 元素的个数
>     int capacity; // 数组的容量，也就是栈的容量
> } DynamicStack;
>
>
> // 创建动态数组栈
> DynamicStack *stack_create();
> // 销毁动态数组栈
> void stack_destroy(DynamicStack *s);
> // 入栈
> void stack_push(DynamicStack *s, ElementType val);
> // 出栈并返回栈顶元素
> ElementType stack_pop(DynamicStack *s);
> // 访问栈顶元素
> ElementType  stack_peek(DynamicStack *s);
> // 判空
> bool is_empty(DynamicStack *s);
>
>
> #endif // !DYNAMIC_ARR_STACK_H
> ```
>
> **当栈中元素已满时，就需要扩容此数组，扩容策略可以自行拟定。**
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "dynamic_stack.h"
> > #define DEFAULT_CAPACITY 8  // 动态栈的默认容量
> > #define THRESHOLD 1024  // 扩容阈值
> >
> >
> > // 实现扩容机制
> > static void grow_capacity(DynamicStack *s) {
> >     // 扩容策略: 超过阈值则1.5倍的扩容，否则2倍的扩容
> >     int new_capacity = (s->capacity >= THRESHOLD) ?
> >         (s->capacity + (s->capacity >> 1)) :
> >     (s->capacity << 1);
> >
> >
> >     // 使用realloc函数实现扩容，重新分配内存
> >     ElementType *new_arr = realloc(s->elements, new_capacity * sizeof(ElementType));
> >     if (new_arr == NULL) {
> >         printf("Error: realloc failed in grow_capacity\n");
> >         exit(1);
> >     }
> >     // 更新动态数组栈结构体的信息
> >     s->elements = new_arr;
> >     s->capacity = new_capacity;
> > }
> > // 创建一个动态数组栈
> > DynamicStack *stack_create() {
> >     DynamicStack *s = malloc(sizeof(DynamicStack));
> >     if (s == NULL) {
> >         printf("malloc failed in stack_create.\n");
> >         return NULL;
> >     }
> >     // 初始化动态数组  
> >     s->size = 0;
> >     s->capacity = DEFAULT_CAPACITY;
> >     s->elements = malloc(DEFAULT_CAPACITY * sizeof(ElementType));
> >     if (s->elements == NULL) {
> >         free(s);
> >         printf("malloc failed in stack_create.\n");
> >         return NULL;
> >     }
> >     return s;
> > }
> > // 销毁一个栈
> > void stack_destroy(DynamicStack *s) {
> >     // 先释放动态数组
> >     free(s->elements);
> >     // 再释放栈结构体
> >     free(s);
> > }
> >
> >
> > // 将数组末尾视为栈顶，将size属性作为新插入结点的下标，这就是入栈
> > void stack_push(DynamicStack *s, ElementType val) {
> >     if (s->capacity == s->size) {
> >         // 栈满了,需要扩容
> >         grow_capacity(s);
> >     }
> >
> >
> >     // 可以直接把size作为入栈出栈的操作索引
> >     s->elements[s->size] = val;
> >     s->size++;
> >     // 上面的两行代码可以合并成一行
> >     // s->elements[s->size++] = val;
> > }
> >
> >
> > // 将数组末尾视为栈顶，将size属性减1，这就是出栈。元素取值并不用改变
> > ElementType stack_pop(DynamicStack *s) {
> >     if (is_empty(s)) {
> >         printf("Error: stack is empty\n");
> >         exit(1);
> >     }
> >     s->size--;
> >     return s->elements[s->size];
> >
> >
> >     // 上面的两行代码可以合并成一行
> >     // return s->elements[--(s->size)];
> > }
> > // 访问栈顶元素
> > ElementType stack_peek(DynamicStack *s) {
> >     if (is_empty(s)) {
> >         printf("Error: stack is empty\n");
> >         exit(1);
> >     }
> >     return s->elements[s->size - 1];
> > }
> > // 判空
> > bool is_empty(DynamicStack *s) {
> >     return s->size == 0;
> > }
> > ```
> >
> > **测试用例代码如下：**
> >
> > ```c
> > #include "dynamic_stack.h"
> >
> >
> > int main(void) {
> >     DynamicStack *s = stack_create();
> >     // 入队列1000个元素
> >     for (int i = 0; i < 1000; i++) {
> >         stack_push(s, i);
> >     }
> >     // 出队列直到队列为空
> >     while (!is_empty(s)) {
> >         ElementType ele = stack_peek(s);
> >         printf("%d ", ele); // 预期会将999-0倒着输出打印
> >         stack_pop(s);
> >     }
> >     printf("\n");
> >     // 再次尝试出栈, 此时会打印错误提示信息
> >     stack_pop(s);
> >     // 销毁队列
> >     stack_destroy(s);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 扩展：手动实现链式队列

> **基于以下头文件，手动实现一个链式队列：**
>
> ```c
> #ifndef LIST_QUEUE_H
> #define LIST_QUEUE_H
>
>
> #include <stdbool.h>
> #include <stdio.h>
> #include <stdlib.h>
>
>
> // 定义队列中的元素类型
> typedef int ElementType;
>
>
> // 队列节点的结构
> typedef struct node_s {
>     ElementType data;
>     struct node_s *next;
> } QueueNode;
>
>
> // 队列的结构
> typedef struct {
>     QueueNode *front;  // 队头结点指针
>     QueueNode *rear;   // 队尾结点指针
> } LinkedListQueue;
>
>
> // 函数声明
> // 创建链式队列
> LinkedListQueue *create_queue();
> // 销毁链式队列
> void destroy_queue(LinkedListQueue *q);
> // 入队列
> bool enqueue(LinkedListQueue *q, ElementType element);
> // 出队列并返回队头元素
> ElementType dequeue(LinkedListQueue *q);
> // 访问队头元素
> ElementType peek_queue(LinkedListQueue *q);
> // 判空
> bool is_empty(LinkedListQueue *q);
>
>
> #endif // !LIST_QUEUE_H
> ```
>
> **注意：链式队列显然不具有满的概念，所以也不需要执行判满操作。**
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "list_queue.h"
> >
> >
> > // 函数声明
> > LinkedListQueue *create_queue() {
> >     return calloc(1, sizeof(LinkedListQueue));
> > }
> >
> >
> > void destroy_queue(LinkedListQueue *q) {
> >     // 从队头开始遍历链表，销毁每一个结点
> >     QueueNode *current = q->front;
> >     while (current != NULL) {
> >         QueueNode *temp = current->next;
> >         free(current);
> >         current = temp;
> >     }
> >     // 销毁队列结构体
> >     free(q);
> > }
> >
> >
> > bool is_empty(LinkedListQueue *q) {
> >     // 队头指针是空指针，即表示空队列
> >     return q->front == NULL;
> > }
> >
> >
> > // 入队操作: 只能在队尾插入一个结点
> > // 由于已存在尾指针，所以这里的操作就是链表尾插
> > bool enqueue(LinkedListQueue *q, ElementType element) {
> >     QueueNode *new_node = malloc(sizeof(QueueNode));
> >     if (new_node == NULL) {
> >         printf("Error: malloc failed in enqueue.\n");
> >         return false;
> >     }
> >     // 初始化新结点
> >     new_node->data = element;
> >     new_node->next = NULL;
> >
> >
> >     // 开始进行尾插法插入一个结点
> >     // 分两种情况：如果尾插插入的是第一个结点需要同步更新头指针，否则仅需要更新尾指针
> >     if (q->front == NULL) {
> >         // 插入的是第一个结点
> >         q->front = new_node;
> >         q->rear = new_node;
> >     }
> >     else {
> >         // 插入的不是第一个结点
> >         q->rear->next = new_node;
> >         q->rear = new_node;
> >     }
> >     return true;
> > }
> >
> >
> > // 出队，在队头删除一个结点。也就是在删除链表的第一个结点
> > ElementType dequeue(LinkedListQueue *q) {
> >     if (is_empty(q)) {
> >         printf("Error: queue is empty.\n");
> >         exit(1);
> >     }
> >
> >
> >     QueueNode *tmp = q->front;
> >     // 将出队的结点数据保存
> >     ElementType remove_data = tmp->data;
> >
> >
> >     // 更新队头指针
> >     q->front = tmp->next;
> >     if (q->front == NULL) {
> >         // 如果队头更新后,队列为空,说明出队的就是最后一个元素
> >         // 于是同步更新队尾指针
> >         q->rear = NULL;
> >     }
> >
> >
> >     free(tmp);
> >     return remove_data;
> > }
> >
> >
> > // 访问队头元素但不出队
> > ElementType peek_queue(LinkedListQueue *q) {
> >     if (is_empty(q)) {
> >         printf("Error: queue is empty.\n");
> >         exit(1);
> >     }
> >     return q->front->data;
> > }
> > ```
> >
> > **测试用例代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include "list_queue.h"
> > #include <stdio.h>
> >
> >
> > int main(void) {
> >     LinkedListQueue *q = create_queue();
> >     // 逐一入队列
> >     enqueue(q, 1);
> >     enqueue(q, 2);
> >     enqueue(q, 3);
> >     enqueue(q, 4);
> >     enqueue(q, 5);
> >     enqueue(q, 6);
> >     // 先进先出，出队列全部元素直到队列为空
> >     while (!is_empty(q)) {
> >         int val = peek_queue(q);
> >         printf("%d ", val); // 预期出队列顺序:1 2 3 4 5 6
> >         dequeue(q);
> >     }
> >     printf("\n");
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-10"></a>

## 10 哈希表和BST阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/10_哈希表和BST阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 手动实现固长哈希表

> **请手动实现一个固定长度，基于拉链法的哈希表。**
>
> **可以基于以下头文件来实现：**
>
> ```c
> #ifndef HASH_MAP_H
> #define HASH_MAP_H
>
>
> #include <stdint.h> // 包含它是为了使用别名uint32_t
> #include <stdbool.h>
> #include <stdlib.h>
> #include <stdio.h>
> #include <string.h>
> #define HASHMAP_CAPACITY 10 // 哈希表中数组的长度固定是10
>
>
> // 此时哈希表用于存储字符串类型的键值对
> typedef char *KeyType;
> typedef char *ValueType;
>
>
> // 键值对结点
> typedef struct node_s {
>     KeyType key;
>     ValueType val;
>     struct node_s *next;
> } KeyValueNode;
>
>
> typedef struct {
>     // 哈希桶
>     KeyValueNode *buckets[HASHMAP_CAPACITY];    // 直接给定哈希桶的数量是10个
>     // 哈希函数需要的种子值
>     uint32_t hash_seed;
> } HashMap;
>
>
> // 创建一个固定容量的哈希表
> HashMap *hashmap_create();
> // 销毁一个哈希表
> void hashmap_destroy(HashMap *map);
> // 插入一个键值对
> ValueType hashmap_put(HashMap *map, KeyType key, ValueType val);
> // 查询一个键值对
> ValueType hashmap_get(HashMap *map, KeyType key);
> // 删除某个键值对
> bool hashmap_remove(HashMap *map, KeyType key);
>
>
> #endif // !HASH_MAP_H
> ```
>
> **注：此哈希表底层数组的长度是固定的，键值对元素的类型都是字符串类型。**
>
> > ###### 参考代码：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "hash_map.h"
> >
> >
> > /* murmur_hash2 */
> > static uint32_t hash(const void *key, int len, uint32_t seed) {
> >     const uint32_t m = 0x5bd1e995;
> >     const int r = 24;
> >     uint32_t h = seed ^ len;
> >     const unsigned char *data = (const unsigned char *)key;
> >
> >
> >     while (len >= 4) {
> >         uint32_t k = *(uint32_t *)data;
> >         k *= m;
> >         k ^= k >> r;
> >         k *= m;
> >         h *= m;
> >         h ^= k;
> >         data += 4;
> >         len -= 4;
> >     }
> >
> >
> >     switch (len) {
> >         case 3: h ^= data[2] << 16;
> >         case 2: h ^= data[1] << 8;
> >         case 1: h ^= data[0];
> >             h *= m;
> >     };
> >
> >
> >     h ^= h >> 13;
> >     h *= m;
> >     h ^= h >> 15;
> >
> >
> >     return h;
> > }
> >
> >
> > // 创建一个固定容量的哈希表，并且此时哈希表是空的
> > HashMap *hashmap_create() {
> >     HashMap *map = calloc(1, sizeof(HashMap));
> >     if (map == NULL) {
> >         printf("error: calloc failed in hashmap_create.\n");
> >         return NULL;
> >     }
> >     map->hash_seed = time(NULL);
> >     return map;
> > }
> >
> >
> > // 销毁一个哈希表
> > void hashmap_destroy(HashMap *map) {
> >     // 遍历每一个哈希桶(也就是遍历数组的每一个元素)，逐一销毁链表结点，最后结构体自身
> >     for (int i = 0; i < HASHMAP_CAPACITY; i++) {
> >         KeyValueNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             KeyValueNode *tmp = curr->next;
> >             free(curr);
> >             curr = tmp;
> >         }
> >     }
> >     free(map);
> > }
> >
> >
> > /*
> >     插入一个键值对
> >     由于键值对的key是唯一的
> >     所以插入操作具有两种可能性：
> >     1.插入的key已经重复了，那么插入行为表现为更新value，并且返回旧的value值
> >     2.插入的key没有重复，那就将这个键值对插入哈希表当中，返回NULL
> > */
> > ValueType hashmap_put(HashMap *map, KeyType key, ValueType val) {
> >     // 1.计算key的哈希值并且确定哈希桶的位置
> >     int idx = hash(key, strlen(key), map->hash_seed) % HASHMAP_CAPACITY;
> >
> >
> >     // 2.遍历这个哈希桶,检查key是否重复
> >     KeyValueNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (strcmp(key, curr->key) == 0) {
> >             // 当前key已经存在于哈希表中了,于是更新value,并返回旧value
> >             ValueType old_val = curr->val;
> >             curr->val = val;
> >             return old_val;
> >         }
> >         curr = curr->next;
> >     }   // while循环结束时,curr指向NULL,这说明哈希表当中key是不存在的,于是开始插入此键值对
> >
> >
> >     // 3.新分配一个键值对结点,并且初始化它
> >     KeyValueNode *new_node = malloc(sizeof(KeyValueNode));
> >     if (new_node == NULL) {
> >         printf("error: malloc failed in hashmap_put.\n");
> >         exit(-1);
> >     }
> >     new_node->key = key;    // 由于key和val都是字符串,都是char*指针类型,所以用=是可以的
> >     new_node->val = val;
> >
> >
> >     // 4.执行链表的头插法,将新结点链接到链表中
> >     new_node->next = map->buckets[idx];
> >     map->buckets[idx] = new_node;
> >
> >
> >     return NULL;
> > }
> >
> >
> > // 查询一个键值对
> > ValueType hashmap_get(HashMap *map, KeyType key) {
> >     // 1.计算key的哈希值并且确定哈希桶的位置
> >     int idx = hash(key, strlen(key), map->hash_seed) % HASHMAP_CAPACITY;
> >
> >
> >     // 2.遍历这个哈希桶,检查key是否存在,如果存在就说明找到了目标键值对
> >     KeyValueNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (strcmp(key, curr->key) == 0) {
> >             // 找到了目标键值对结点
> >             return curr->val;
> >         }
> >         curr = curr->next;
> >     }   // while循环结束时,curr指向NULL,这说明哈希表当中key是不存在的,查找失败
> >     return NULL;
> > }
> >
> >
> > // 删除某个键值对
> > bool hashmap_remove(HashMap *map, KeyType key) {
> >     // 1.计算key的哈希值并且确定哈希桶的位置
> >     int idx = hash(key, strlen(key), map->hash_seed) % HASHMAP_CAPACITY;
> >
> >
> >     // 2.初始化两个指针，用来遍历哈希桶
> >     KeyValueNode *curr = map->buckets[idx];
> >     KeyValueNode *prev = NULL;
> >     while (curr != NULL) {
> >         if (strcmp(key, curr->key) == 0) {
> >             // 找到了目标键值对结点，开始执行它的删除操作
> >             if (prev == NULL){
> >                 // 删除的是第一个结点，更新头指针
> >                 map->buckets[idx] = curr->next;
> >             }
> >             else{
> >                 // 删除的不是第一个结点，此时不需要更新头指针
> >                 prev->next = curr->next;
> >             }
> >             // 以上操作使得待删除结点从链表结构中被移除了，于是free这个结点
> >             free(curr);
> >             return true;    // 删除成功
> >         }
> >         prev = curr;    // prev要紧跟curr的步伐
> >         curr = curr->next;
> >     }   // while循环结束时,curr指向NULL,这说明哈希表当中key是不存在的,没有目标结点，删除失败
> >
> >
> >     return false;
> > }
> > ```
> >
> > **测试代码如下：**
> >
> > ```c
> > #include "hash_map.h"
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <string.h>
> >
> >
> > int main(void) {
> >     // 创建哈希表
> >     HashMap *map = hashmap_create();
> >     if (map == NULL) {
> >         printf("哈希表创建失败。\n");
> >         return 1;
> >     }
> >
> >
> >     // 插入键值对
> >     hashmap_put(map, "key1", "value1");  // 首次插入，应成功
> >     hashmap_put(map, "key2", "value2");  // 再插一个新键值对，应成功
> >     char *old_value = hashmap_put(map, "key1", "value3");  // 更新已存在的键值对，应返回旧值"value1"
> >     printf("更新键值对时返回的旧值应为value1，实际返回：%s\n", old_value);
> >
> >
> >     // 查询键值对
> >     char *value = hashmap_get(map, "key1");
> >     printf("期待得到value3，实际得到：%s\n", value);  // 预期输出value3
> >     value = hashmap_get(map, "key2");
> >     printf("期待得到value2，实际得到：%s\n", value);  // 预期输出value2
> >     value = hashmap_get(map, "key3");
> >     if (value == NULL) {
> >         printf("如预期，key3未找到\n");  // 预期找不到key3
> >     }
> >
> >
> >     // 删除键值对
> >     bool deleted = hashmap_remove(map, "key1");  // 删除key1, 预期删除成功
> >     if (deleted) {
> >         printf("key1成功删除。\n");
> >     }
> >     deleted = hashmap_remove(map, "key3");  // 尝试删除不存在的key3, 预期删除失败
> >     if (!deleted) {
> >         printf("key3未找到且未删除，符合预期。\n");
> >     }
> >
> >
> >     // 销毁哈希表
> >     hashmap_destroy(map);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 哈希表应用：判断单链表有环

> 判断单链表有环的最佳实现是利用快慢指针法，但哈希表也是一个不算太差的求解方式。你可以在遍历链表的过程中，将链表的每一个结点存入哈希表，若发现有重复结点被存入哈希表，则确定单链表有环。
>
> **你可以基于下面头文件来实现哈希表：**
>
> ```c
> #include <stdint.h>
> #include <stdio.h>
> #include <stdlib.h>
> #include <time.h>
> #include <stdbool.h>
>
>
> #define CAPACITY 10  // 哈希表的底层数组长度是10
>
>
> typedef struct node {
>     int data;
>     struct node *next;
> }Node;  // 哈希表当中存储的链表结点类型
>
>
> // 此哈希表只存储键,不存储value
> // key值存储链表结点的指针
> typedef Node *KeyType;
>
>
> // 键值对结点，此时无需存储值了
> typedef struct node_s {
>     KeyType key;    // 键
>     struct node_s *next;
> } HashNode; // 键值对结点类型
>
>
> typedef struct {
>     HashNode *buckets[CAPACITY];
>     uint32_t hash_seed;
> } HashMap;    // 哈希表结构体类型
>
>
> // 创建一个固定容量的哈希表
> HashMap *hashmap_create();
> // 销毁哈希表
> void hashmap_destroy(HashMap *map);
>
>
> /*
>     尝试将链表结点的指针(地址)插入哈希表
>     若发现结点已存入哈希表, 则函数返回true
>     若结点未存入, 则将结点地址存入哈希表并返回false
> */
> bool hashmap_put(HashMap *map, KeyType key);
> ```
>
> **构建有环单链表的代码如下：**
>
> ```c
> // 实现尾插法
> void insert_behind_tail(Node **head, int data) {
>     // 1.新建结点
>     Node *new_node = malloc(sizeof(Node));
>     if (new_node == NULL) {
>         printf("malloc failed in insert_behind_tail.\n");
>         exit(1);
>     }
>     // 初始化新结点
>     new_node->next = NULL;
>     new_node->data = data;
>
>
>     // 2.判断尾插前链表是否为空
>     if (*head == NULL) {
>         // 链表尾插之前为空
>         *head = new_node;
>         return;
>     }
>     // 链表尾插时 不为空
>     Node *tail = *head;
>     while (tail->next != NULL) {
>         tail = tail->next;
>     }   // while循环结束时, tail指向当前的尾结点
>     tail->next = new_node;
> }
>
>
> int main(void) {
>     Node *head = NULL;  // 头指针是空指针, 表示链表为空
>     insert_behind_tail(&head, 1);
>     insert_behind_tail(&head, 2);
>     insert_behind_tail(&head, 3);
>     insert_behind_tail(&head, 4);
>     insert_behind_tail(&head, 5);
>
>
>     // 希望构建一个 8->3 的有环链表 希望尾结点指向链表的第三个结点, 第三个结点索引是2
>     int count = 0;
>     Node *third_node = NULL;
>     Node *tail = head;
>     while (tail->next != NULL) {
>         count++;
>         if (count == 3) {
>             // tail就指向了第三个结点
>             third_node = tail;
>         }
>         tail = tail->next;
>     }   // 循环结束时, tail指向尾结点, third_node指向链表第三个结点
>     tail->next = third_node;
>
>
>     return 0;
> }
> ```
>
> 请编写代码，检测单链表是否有环。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **此哈希表的实现代码如下：**
> >
> > ```c
> > #include "hash_map.h"
> >
> >
> > /* murmur_hash2 */
> > static uint32_t hash(const void *key, int len, uint32_t seed) {
> >     const uint32_t m = 0x5bd1e995;
> >     const int r = 24;
> >     uint32_t h = seed ^ len;
> >     const unsigned char *data = (const unsigned char *)key;
> >
> >
> >     while (len >= 4) {
> >         uint32_t k = *(uint32_t *)data;
> >         k *= m;
> >         k ^= k >> r;
> >         k *= m;
> >         h *= m;
> >         h ^= k;
> >         data += 4;
> >         len -= 4;
> >     }
> >
> >
> >     switch (len) {
> >         case 3: h ^= data[2] << 16;
> >         case 2: h ^= data[1] << 8;
> >         case 1: h ^= data[0];
> >             h *= m;
> >     };
> >
> >
> >     h ^= h >> 13;
> >     h *= m;
> >     h ^= h >> 15;
> >
> >
> >     return h;
> > }
> >
> >
> > // 创建一个固定容量的哈希表
> > HashMap *hashmap_create() {
> >     HashMap *map = calloc(1, sizeof(HashMap));
> >     if (map == NULL) {
> >         printf("error: calloc failed in hashmap_create.\n");
> >         return NULL;
> >     }
> >     map->hash_seed = time(NULL);
> >     return map;
> > }
> >
> >
> > // 销毁哈希表
> > void hashmap_destroy(HashMap *map) {
> >     // 遍历每一个哈希桶(也就是遍历数组的每一个元素)，逐一销毁链表结点，最后销毁结构体自身
> >     for (int i = 0; i < CAPACITY; i++) {
> >         HashNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             HashNode *tmp = curr->next;
> >             free(curr);
> >             curr = tmp;
> >         }
> >     }
> >     free(map);
> > }
> >
> >
> > /*
> >     该函数会将链表结点的地址作为一个结点key值,存入哈希表当中
> >     在存入的过程中,如果发现key值重复,说明有环,直接返回true
> >     如果key值不重复,那就将key结点正常存入哈希表,并且返回false
> > */
> > bool hashmap_put(HashMap *map, KeyType key) {
> >     // 1.根据key这个结点地址数据来计算哈希值,确定哈希桶的位置
> >     int idx = hash(key, sizeof(KeyType), map->hash_seed) % CAPACITY;
> >     // 2.遍历哈希桶,确定这个结点地址是否已经出现
> >     HashNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (key == curr->key) {
> >             // 当前结点已经重复出现了,说明有环
> >             return true;
> >         }
> >         curr = curr->next;
> >     }
> >     // 3.key是不存在的,于是新增这个结点
> >     HashNode *new_node = malloc(sizeof(HashNode));
> >     if (new_node == NULL) {
> >         printf("error: malloc failed in hashmap_put.\n");
> >         exit(-1);
> >     }
> >     new_node->key = key;    // 由于key是Node结点指针类型,是地址,所以可以直接用=赋值
> >
> >
> >     // 4.执行链表的头插法,将新结点链接到链表中
> >     new_node->next = map->buckets[idx];
> >     map->buckets[idx] = new_node;
> >
> >
> >     return false;   // 表示当前结点还没有重复,所以插入哈希表成功了
> > }
> > ```
> >
> > **检查有环以及相关测试代码如下：**
> >
> > ```c
> > // 利用哈希表来判断单链表有环
> > bool has_circle(Node *head) {
> >     // 1.创建一个哈希表
> >     HashMap *map = hashmap_create();
> >     // 2.遍历整条单链表,并且将每一个结点的地址存入哈希表
> >     Node *curr = head;
> >     while (curr != NULL) {
> >         if (hashmap_put(map, curr)) {
> >             // 已经存储了重复结点,有环
> >             hashmap_destroy(map);
> >             return true;
> >         }
> >         curr = curr->next;
> >     }
> >     // 如果while循环能够结束,且能够执行到这里,说明链表没环
> >     hashmap_destroy(map);
> >     return false;
> > }
> >
> >
> > int main(void) {
> >     Node *head = NULL;  // 头指针是空指针, 表示链表为空
> >     insert_behind_tail(&head, 1);
> >     insert_behind_tail(&head, 2);
> >     insert_behind_tail(&head, 3);
> >     insert_behind_tail(&head, 4);
> >     insert_behind_tail(&head, 5);
> >
> >
> >     // 希望构建一个 8->3 的有环链表 希望尾结点指向链表的第三个结点, 第三个结点索引是2
> >     int count = 0;
> >     Node *third_node = NULL;
> >     Node *tail = head;
> >     while (tail->next != NULL) {
> >         count++;
> >         if (count == 3) {
> >             // tail就指向了第三个结点
> >             third_node = tail;
> >         }
> >         tail = tail->next;
> >     }   // 循环结束时, tail指向尾结点, third_node指向链表第三个结点
> >     tail->next = third_node;
> >
> >
> >     bool ret = has_circle(head);    // 有环，返回true
> >     return 0;
> > }
> > ```
>
> 以上。

#### 手动实现BST的增删查操作

> 请手动实现BST的**增删查**操作，可以基于以下头文件：
>
> ```c
> #ifndef BST_H
> #define BST_H
>
>
> #include<stdbool.h>
>
>
> typedef int KeyType;
>
>
> typedef struct node {
>     KeyType key;        // 结点key值,具有唯一性
>     struct node *left;  // 左子树
>     struct node *right; // 右子树
> } TreeNode;
>
>
> // 推荐定义一个二叉搜索树的结构体,这样更便于扩展
> typedef struct {
>     TreeNode *root; // 根结点指针
> }BST;
>
>
> // 基础操作
> // 创建一棵空的BST
> BST *bst_create();
> // 销毁一棵BST
> void bst_destroy(BST *tree);
>
>
> // 根据key插入一个新结点
> bool bst_insert(BST *tree, KeyType key);
> // 根据key搜索某个结点并返回
> TreeNode *bst_search(BST *tree, KeyType key);
> // 根据key删除一个结点
> bool bst_delete(BST *tree, KeyType key);
>
>
> #endif // !BST_H
> ```
>
> **创建二叉搜索树的操作可以一并实现了。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > // 创建一棵空的BST
> > BST *bst_create() {
> >     return calloc(1, sizeof(BST));
> > }
> >
> >
> > /*
> >     根据key插入一个新结点
> >     有两种情况:
> >     1.若key值已经存在,则不进行插入操作,插入失败,返回false
> >     2.若key值不存在,则进行插入操作,插入成功,返回true
> > */
> > bool bst_insert(BST *tree, KeyType key) {
> >     // 1.初始化两个指针,用来遍历查找key是否重复
> >     TreeNode *curr = tree->root;
> >     TreeNode *parent = NULL;
> >
> >
> >     // 2.根据key值的大小关系,来遍历这棵树的结点
> >     while (curr != NULL) {  // 这一点模拟了单链表的遍历,因为搜索路径就是一条单链表
> >         int diff = key - curr->key;
> >         if (diff > 0) {
> >             // 待插入结点key值比当前结点key值要大,于是去右子树中遍历查找
> >             parent = curr;
> >             curr = curr->right;
> >         }
> >         else if (diff < 0) {
> >             // 待插入结点key值比当前结点key值要小,于是去左子树中遍历查找
> >             parent = curr;
> >             curr = curr->left;
> >         }
> >         else {
> >             // 待插入结点key值和当前结点key值相等,说明key值重复,插入失败
> >             return false;
> >         }
> >     }   // while循环结束若函数没有返回,说明curr肯定指向NULL,它找到了插入位置,而parent指向插入位置的父结点
> >     // 3.说明key值不重复,要新增一个结点,初始化它
> >     TreeNode *new_node = calloc(1, sizeof(TreeNode));   // 用calloc避免左右子树是野指针
> >     if (new_node == NULL) {
> >         printf("error: malloc failed in bst_insert.\n");
> >         exit(-1);
> >     }
> >     new_node->key = key;
> >
> >
> >     // 4.判断插入之前,树是否为空
> >     if (parent == NULL) {
> >         // 插入之前,树为空,只需要更新根节点指针即可
> >         tree->root = new_node;
> >         return true;    //插入成功,返回函数
> >     }
> >     // 5.将新结点链接到父结点下面
> >     int diff = key - parent->key;
> >     if (diff > 0) {
> >         // 新结点链接到右子树
> >         parent->right = new_node;
> >     }
> >     else {
> >         // 新结点链接到左子树
> >         parent->left = new_node;
> >     }
> >     // 插入成功
> >     return true;
> > }
> > // 根据key搜索某个结点并返回
> > TreeNode *bst_search(BST *tree, KeyType key) {
> >     // 1.初始化curr指针,用来遍历查找目标key结点
> >     TreeNode *curr = tree->root;
> >
> >
> >     // 2.根据key值的大小关系,来遍历这棵树的结点
> >     while (curr != NULL) {  // 这一点模拟了单链表的遍历,因为搜索路径就是一条单链表
> >         int diff = key - curr->key;
> >         if (diff > 0) {
> >             // 待查找的key值比当前结点的key值要大，去右子树中寻找
> >             curr = curr->right;
> >         }
> >         else if (diff < 0) {
> >             // 待查找的key值比当前结点的key值要小，去左子树中寻找
> >             curr = curr->left;
> >         }
> >         else {
> >             // 找到了目标结点，返回目标结点
> >             return curr;
> >         }
> >     }   // while循环结束时，curr指向NULL，说明目标key值在BST中是不存在的
> >     return NULL;
> > }
> >
> >
> > // 根据key删除一个结点
> > bool bst_delete(BST *tree, KeyType key) {
> >     // 1.利用curr和parent两个指针找到待删除结点以及它的父节点
> >     TreeNode *curr = tree->root;
> >     TreeNode *parent = NULL;
> >
> >
> >     // 2.根据key值的大小关系,来遍历这棵树的结点
> >     while (curr != NULL) {  // 这一点模拟了单链表的遍历,因为搜索路径就是一条单链表
> >         int diff = key - curr->key;
> >         if (diff > 0) {
> >             // 待删除key值比当前结点key值要大,于是去右子树中遍历查找
> >             parent = curr;
> >             curr = curr->right;
> >         }
> >         else if (diff < 0) {
> >             // 待删除key值比当前结点key值要小,于是去左子树中遍历查找
> >             parent = curr;
> >             curr = curr->left;
> >         }
> >         else {
> >             // 找到待删除结点,下面就开始删除该结点的操作
> >             break;
> >         }
> >     }
> >     /*
> >         while循环结束,有两种可能性:
> >         1.找到了目标key结点,依赖break结束循环
> >             此时curr指针指向待删除结点,parent指向它的父结点
> >
> >
> >         2.没找到目标key结点,依赖curr变成NULL结束循环
> >             此时curr指针是NULL相当于找到了这个不存在key结点的插入位置
> >             而parent就指向插入位置的父结点
> >         以上两种情况,如果是第一种情况,我们就继续删除
> >         但如果是第二种情况,目标结点不存在,删除就失败了
> >     */
> >     if (curr == NULL) {
> >         return false;
> >     }
> >     // 2.根据度不同来进行不同的处理,使得待删除结点从树结构中断开
> >     // 2.1 判断结点的度是否为2, 如果度为2, 进行降级处理
> >     if (curr->left != NULL && curr->right != NULL) {
> >         // 删除的结点是度为2的,于是将它降低为删除度为0或1
> >         TreeNode *min_node = curr->right;   // 寻找待删除结点的右子树最小结点,从curr的右子树结点开始
> >         TreeNode *min_parent = curr;    // 寻找待删除结点的右子树最小结点的父结点
> >         while (min_node->left != NULL) {
> >             min_parent = min_node;
> >             min_node = min_node->left;
> >         }   // while循环结束时,min_node指向右子树最小结点,min_parent指向min_node结点的父结点
> >
> >
> >         // 将右子树最小结点的值替换给curr结点,并且后续将删除右子树最小结点
> >         curr->key = min_node->key;
> >         // 后续的删除操作都是基于curr指针和parent指针的,所以这里要进行一步赋值操作
> >         curr = min_node;
> >         parent = min_parent;
> >     }
> >     // 接下来待删除的结点就是curr结点,它的父结点就是parent,而且这个结点的度一定是0或1
> >     // 2.2 统一处理度为0或1结点的删除操作
> >
> >
> >     // 核心操作: parent -> left/right = curr -> left/right
> >     // 先确定parent指向待删除结点的左子树还是右子树
> >     TreeNode *child = (curr->left != NULL) ? curr->left : curr->right;
> >
> >
> >     /*
> >         考虑特殊情况:
> >         删除的结点是度为0或1的根结点
> >         此时需要更新根结点指针
> >     */
> >     if (parent == NULL) {
> >         // 删除的结点是根结点,此根结点度为0或1
> >         tree->root = child;
> >     }
> >     else {
> >         // 删除的结点不是根结点
> >         // 执行核心操作: parent -> left/right = child;
> >         if (parent->left == curr) {
> >             // 待删除结点是父结点的左子树,那么就让父结点的左子树指向child
> >             parent->left = child;
> >         }
> >         else {
> >             // 待删除结点是父结点的右子树,那么就让父结点的右子树指向child
> >             parent->right = child;
> >         }
> >     }
> >     // 3.free这个结点
> >     free(curr); // 删除成功
> >     return true;
> > }
> > ```
>
> 以上。

#### 手动实现BST的深度优先遍历

> 可以紧接着上面"手动实现BST的增删查操作"的代码，在头文件中添加以下深度优先遍历函数的声明：
>
> ```c
> // 深度优先-先序遍历
> void bst_preorder(BST *tree);   
> // 深度优先-中序遍历
> void bst_inorder(BST *tree);    
> // 深度优先-后序遍历
> void bst_postorder(BST *tree);  
> ```
>
> **然后，实现这三个深度优先遍历的操作。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **这三个深度优先遍历操作的实现代码如下：**
> >
> > ```c
> > /*
> > * 利用递归实现BST的先序遍历
> > * root参数表示此一轮递归调用中的根结点  
> > * 先序遍历是: DLR
> > * 分解的思路是:
> > * 对于任何一棵树root来说:
> > * 1.总是先输出根结点的值
> > * 2.然后递归遍历它的左子树
> > * 3.最后递归遍历它的右子树
> > * preoder(root) = D + preorder(root->left) + preorder(root->right)
> > * 这就是递归体
> > * 这样的分解不会无休止进行,如果分解成一棵空树,也就是root是空指针时,返回函数
> > * 这就是递归的出口
> > */
> > static void preorder(TreeNode* root) {
> >     // 1.递归的出口
> >     if (root == NULL) {
> >         return;
> >     }
> >     // 2.递归体
> >     printf("%d ", root->key);
> >     preorder(root->left);
> >     preorder(root->right);
> > }
> >
> >
> > void bst_preorder(BST* tree) {
> >     if (tree == NULL) {
> >         // 树为空直接返回
> >         return;
> >     }
> >     // 利用辅助函数递归实现BST的先序遍历
> >     preorder(tree->root);
> >     printf("\n");
> > }
> >
> >
> >
> >
> > /*
> > * 利用递归实现BST的中序遍历
> > * root参数表示此一轮递归调用中的根结点
> > * 中序遍历是: LDR
> > * 分解的思路是:
> > * 对于任何一棵树root来说:
> > * 1.总是先递归遍历它的左子树
> > * 1.然后再输出根结点的值
> > * 3.最后递归遍历它的右子树
> > * inorder(root) = inorder(root->left) + D + inorder(root->right)
> > * 这就是递归体
> > * 这样的分解不会无休止进行,如果分解成一棵空树,也就是root是空指针时,返回函数
> > * 这就是递归的出口
> > */
> > static void inorder(TreeNode* root) {
> >     // 1.递归的出口
> >     if (root == NULL) {
> >         return;
> >     }
> >     // 2.递归体
> >     inorder(root->left);
> >     printf("%d ", root->key);
> >     inorder(root->right);
> > }
> > void bst_inorder(BST* tree) {
> >     if (tree == NULL) {
> >         // 树为空直接返回
> >         return;
> >     }
> >     // 利用辅助函数递归实现BST的中序遍历
> >     inorder(tree->root);
> >     printf("\n");
> > }
> >
> >
> > /*
> > * 利用递归实现BST的后序遍历
> > * root参数表示此一轮递归调用中的根结点
> > * 中序遍历是: LRD
> > * 分解的思路是:
> > * 对于任何一棵树root来说:
> > * 1.总是先递归遍历它的左子树
> > * 3.然后递归遍历它的右子树
> > * 3.最后再输出根结点的值
> > * postorder(root) = postorder(root->left) + postorder(root->right) + D
> > * 这就是递归体
> > * 这样的分解不会无休止进行,如果分解成一棵空树,也就是root是空指针时,返回函数
> > * 这就是递归的出口
> > */
> > static void postorder(TreeNode* root) {
> >     // 1.递归的出口
> >     if (root == NULL) {
> >         return;
> >     }
> >     // 2.递归体
> >     postorder(root->left);
> >     postorder(root->right);
> >     printf("%d ", root->key);
> > }
> > void bst_postorder(BST* tree) {
> >     if (tree == NULL) {
> >         // 树为空直接返回
> >         return;
> >     }
> >     // 利用辅助函数递归实现BST的后序遍历
> >     postorder(tree->root);
> >     printf("\n");
> > }
> > ```
>
> 以上。

#### 队列应用：BST的层次遍历

> 广度优先搜索（Breadth-First Search，BFS）策略，指的是按照树的层次结构从上到下、从左到右依次访问每个结点，所以也叫**层次遍历**。
>
> 层次遍历在实现时，一个最优的选择就是借助队列来实现：将一个二叉搜索树的元素从根结点开始入队，然后入队左子树结点，右子树结点。这样在出队时，就可以实现根结点，左子树结点，右子树结点逐层出队输出的结果。
>
> **给定一个链式队列，头文件如下：**
>
> ```c
> #ifndef LIST_QUEUE_H
> #define LIST_QUEUE_H
>
>
> #include <stdbool.h>
> #include <stdio.h>
> #include <stdlib.h>
>
>
> // 定义队列中的元素类型
> typedef int ElementType;
>
>
> // 队列节点的结构
> typedef struct node_s {
>     ElementType data;
>     struct node_s *next;
> } QueueNode;
>
>
> // 队列的结构
> typedef struct {
>     QueueNode *front;  // 队头结点指针
>     QueueNode *rear;   // 队尾结点指针
> } LinkedListQueue;
>
>
> // 函数声明
> // 创建链式队列
> LinkedListQueue *create_queue();
> // 销毁链式队列
> void destroy_queue(LinkedListQueue *q);
> // 入队列
> bool enqueue(LinkedListQueue *q, ElementType element);
> // 出队列并返回队头元素
> ElementType dequeue(LinkedListQueue *q);
> // 访问队头元素
> ElementType peek_queue(LinkedListQueue *q);
> // 判空
> bool is_empty(LinkedListQueue *q);
>
>
> #endif // !LIST_QUEUE_H
> ```
>
> **此队列实现代码如下：**
>
> ```c
> #include "list_queue.h"
>
>
> // 函数声明
> LinkedListQueue *create_queue() {
>     return calloc(1, sizeof(LinkedListQueue));
> }
>
>
> void destroy_queue(LinkedListQueue *q) {
>     // 从队头开始遍历链表，销毁每一个结点
>     QueueNode *current = q->front;
>     while (current != NULL) {
>         QueueNode *temp = current->next;
>         free(current);
>         current = temp;
>     }
>     // 销毁队列结构体
>     free(q);
> }
>
>
> bool is_empty(LinkedListQueue *q) {
>     // 队头指针是空指针，即表示空队列
>     return q->front == NULL;
> }
>
>
> // 入队操作: 只能在队尾插入一个结点
> // 由于已存在尾指针，所以这里的操作就是链表尾插
> bool enqueue(LinkedListQueue *q, ElementType element) {
>     QueueNode *new_node = malloc(sizeof(QueueNode));
>     if (new_node == NULL) {
>         printf("Error: malloc failed in enqueue.\n");
>         return false;
>     }
>     // 初始化新结点
>     new_node->data = element;
>     new_node->next = NULL;
>
>
>     // 开始进行尾插法插入一个结点
>     // 分两种情况：如果尾插插入的是第一个结点需要同步更新头指针，否则仅需要更新尾指针
>     if (q->front == NULL) {
>         // 插入的是第一个结点
>         q->front = new_node;
>         q->rear = new_node;
>     }
>     else {
>         // 插入的不是第一个结点
>         q->rear->next = new_node;
>         q->rear = new_node;
>     }
>     return true;
> }
>
>
> // 出队，在队头删除一个结点。也就是在删除链表的第一个结点
> ElementType dequeue(LinkedListQueue *q) {
>     if (is_empty(q)) {
>         printf("Error: queue is empty.\n");
>         exit(1);
>     }
>
>
>     QueueNode *tmp = q->front;
>     // 将出队的结点数据保存
>     ElementType remove_data = tmp->data;
>
>
>     // 更新队头指针
>     q->front = tmp->next;
>     if (q->front == NULL) {
>         // 如果队头更新后,队列为空,说明出队的就是最后一个元素
>         // 于是同步更新队尾指针
>         q->rear = NULL;
>     }
>
>
>     free(tmp);
>     return remove_data;
> }
>
>
> // 访问队头元素但不出队
> ElementType peek_queue(LinkedListQueue *q) {
>     if (is_empty(q)) {
>         printf("Error: queue is empty.\n");
>         exit(1);
>     }
>     return q->front->data;
> }
> ```
>
> **请修改此链式队列的部分代码，实现BST的层次遍历，基于以下函数声明：**
>
> ```c
> // 广度优先-层次遍历
> void bst_levelorder(BST *tree); 
> ```
>
> 请将这个声明，加到上面实现的BST代码头文件中，然后在源文件中实现。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > 首先，你需要在队列的头文件中包含BST的头文件，然后将队列中元素的类型改为：`TreeNode*`类型。即队列中要存放树结点的指针（地址）
> >
> > 对于指针类型而言，完全可以用`=`进行赋值操作，所以实现代码就没有必要修改了。
> >
> > **层次遍历的第一个版本实现代码是：**
> >
> > ```c
> > // 层次遍历
> > // 要包含队列对应的头文件且要修改队列中元素的类型为TreeNode*类型
> > void bst_levelorder(BST *tree) {
> >     LinkedListQueue *q = create_queue(); // 创建一个队列
> >     // 1.首先让根结点入队
> >     enqueue(q, tree->root);
> >     // 2.当队列不为空时，执行循环
> >     // 在这个循环中，我们将会逐个访问每一层的节点，并将它们的子节点加入队列
> >     while (!is_empty(q)) {
> >         TreeNode *node = dequeue(q); // 出队获取当前结点
> >         printf("%d ", node->key);    // 打印当前节点的键值
> >
> >
> >         // 如果当前节点的左子节点存在，将左子节点加入队列
> >         if (node->left != NULL) {
> >             enqueue(q, node->left);
> >         }
> >
> >
> >         // 如果当前节点的右子节点存在，将右子节点加入队列
> >         if (node->right != NULL) {
> >             enqueue(q, node->right);
> >         }
> >     }
> >     printf("\n");
> >     destroy_queue(q); // 完成遍历后，销毁队列释放资源
> > }
> > ```
> >
> > 这个版本的实现效果是：从上到下，从左到右依次遍历打印结点值。
> >
> > **第一个版本代码打印效果是：30 10 40 5 15 35 70 3 12 75**
> >
> > 这个层次遍历，没有体现出"层次"的效果，若希望打印完一层结点值就换行这样的效果，可以做以下修改：
> >
> > 修改队列结构体的定义，添加一个`size`属性，用来记录队列中结点元素的个数：
> >
> > ```c
> > // 队列的结构
> > typedef struct {
> >     QueueNode* front;  // 队列的头部
> >     QueueNode* rear;   // 队列的尾部
> >     int size;   // 队列中元素的个数
> > } LinkedListQueue;
> > ```
> >
> > 同样还需要在出队、入队操作函数中增加size操作的代码。（size--或size++）
> >
> > **第二个版本实现代码如下：**
> >
> > ```c
> > // 优化：层次遍历时将BST树的每一层的层级输出出来
> > void bst_levelorder2(BST *tree) {
> >     LinkedListQueue *q = create_queue(); // 创建一个队列
> >     // 1.首先让根结点入队
> >     enqueue(q, tree->root);
> >     // 2.当队列不为空时，执行循环
> >     // 在这个循环中，我们将会逐个访问每一层的节点，并将它们的子节点加入队列
> >     while (!is_empty(q)) {
> >         // 刚进入while循环时,队列的size属性就是这一层结点的个数
> >         int level_size = q->size;   // 当前层次结点的个数
> >         // 于是下面循环出队列n次，就是出队打印完所有本层结点，并将所有下一层结点都入队
> >         for (int i = 0; i < level_size; i++) {
> >             TreeNode *node = dequeue(q); // 出队获取当前结点
> >             printf("%d ", node->key);    // 打印当前节点的键值
> >
> >
> >             // 如果当前节点的左子节点存在，将左子节点加入队列
> >             if (node->left != NULL) {
> >                 enqueue(q, node->left);
> >             }
> >
> >
> >             // 如果当前节点的右子节点存在，将右子节点加入队列
> >             if (node->right != NULL) {
> >                 enqueue(q, node->right);
> >             }
> >         }
> >         // 出队打印完一层，换行
> >         printf("\n");
> >     }
> >     printf("\n");
> >     destroy_queue(q); // 完成遍历后，销毁队列释放资源
> > }
> > ```
> >
> > 第二个版本代码打印效果如下：
> >
> > **30**
> >
> > **10 40**
> >
> > **5 15 35 70**
> >
> > **3 12 75**
>
> 以上。

### 扩展题篇

> 以下题目都属于扩展题。

#### 扩展：手动实现动态哈希表

> 用动态数组和链表，基于拉链法来设计哈希桶，实现一个动态哈希表。要求能够基于负载因子，进行自动扩容。
>
> **可以基于以下头文件来实现：**
>
> ```c
> #ifndef DYNAMIC_HASHMAP_H
> #define DYNAMIC_HASHMAP_H
>
>
> typedef char *KeyType;
> typedef char *ValueType;
>
>
> #include <stdint.h>
>
>
> typedef struct node_s {
>     KeyType key;
>     ValueType val;
>     struct node_s *next;
> } KeyValueNode;
>
>
> typedef struct {
>     KeyValueNode **buckets;     // 此时哈希桶是一个动态数组，指向char*元素的指针，所以是一个二级指针
>     int size;               // 键值对的个数
>     int capacity;           // 数组的长度
>     uint32_t hash_seed;     // 哈希函数需要的种子值
> } DynamicHashMap;
>
>
> // 创建一个固定容量的哈希表
> DynamicHashMap *hashmap_create();
> // 销毁一个哈希表
> void hashmap_destroy(DynamicHashMap *map);
> // 插入一个键值对
> ValueType hashmap_put(DynamicHashMap *map, KeyType key, ValueType val);
> // 查询一个键值对
> ValueType hashmap_get(DynamicHashMap *map, KeyType key);
> // 删除某个键值对
> bool hashmap_remove(DynamicHashMap *map, KeyType key);
>
>
> #endif // !DYNAMIC_HASHMAP_H
> ```
>
> **注意：该哈希表底层的数组是可以自动扩容的，键值对元素的类型是字符串类型。**
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > **以下是实现源文件的代码，即所有函数的实现如下：**
> >
> > ```c
> > #include "dynamic_hashmap.h"
> > #define DEFAULT_CAPACITY 8  // 哈希表的初始默认容量是8
> > #define LOAD_FACTOR_THRESHOLD  0.75     // 负载因子的阈值
> > #define CAPACITY_THRESHOLE 1024     // 数组容量的阈值
> >
> >
> > /* murmur_hash2 */
> > static uint32_t hash(const void* key, int len, uint32_t seed) {
> >     const uint32_t m = 0x5bd1e995;
> >     const int r = 24;
> >     uint32_t h = seed ^ len;
> >     const unsigned char* data = (const unsigned char*)key;
> >
> >
> >     while (len >= 4) {
> >         uint32_t k = *(uint32_t*)data;
> >         k *= m;
> >         k ^= k >> r;
> >         k *= m;
> >         h *= m;
> >         h ^= k;
> >         data += 4;
> >         len -= 4;
> >     }
> >
> >
> >     switch (len) {
> >         case 3: h ^= data[2] << 16;
> >         case 2: h ^= data[1] << 8;
> >         case 1: h ^= data[0];
> >             h *= m;
> >     };
> >
> >
> >     h ^= h >> 13;
> >     h *= m;
> >     h ^= h >> 15;
> >
> >
> >     return h;
> > }
> >
> >
> > static void rehash(KeyValueNode *curr, KeyValueNode **new_table, int new_capacity, uint32_t seed) {
> >     // 计算 key 的哈希值
> >     int len = strlen(curr->key);
> >     int idx = hash(curr->key, len, seed) % new_capacity;
> >     // 头插法
> >     curr->next = new_table[idx];
> >     new_table[idx] = curr;
> > }
> >
> >
> > // 对哈希表进行扩容操作
> > static void grow_capacity(DynamicHashMap *map) {
> >     /*
> >     * 扩容策略：
> >     * 1.如果容量没有达到阈值，那就每次将长度扩大为原先的2倍
> >     * 2.如果容量达到阈值，此时哈希表已经很长了，为了避免扩容过程性能损耗过大
> >     *   所以扩容保守一些，每次只扩容阈值长度的容量
> >     *
> >     * 扩容的过程：
> >     * 1.每个键值对结点都要重新计算哈希值，重新映射到新哈希桶中(新数组)
> >     * 2.原先的动态数组的链表很复杂，难以进行重哈希操作，建议直接丢弃它
> >     * 重新创建一个新动态数组
> >     */
> >     int new_capacity =
> >         (map->capacity <= CAPACITY_THRESHOLE) ?
> >         (map->capacity << 1) :
> >     (map->capacity + CAPACITY_THRESHOLE);
> >
> >
> >     // 动态数组扩容需要使用 calloc
> >     KeyValueNode **new_buckets = calloc(new_capacity, sizeof(KeyValueNode *));
> >     if (new_buckets == NULL) {
> >         printf("Error: calloc failed in grow_capacity\n");
> >         exit(1);
> >     }
> >     // 每次扩容都更改一次哈希种子，提高安全性
> >     uint32_t seed = time(NULL);
> >
> >
> >     // 将所有键值对重新映射到新数组中
> >     for (int i = 0; i < map->capacity; i++) {
> >         KeyValueNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             KeyValueNode *next = curr->next;
> >             // 重新进行哈希映射
> >             rehash(curr, new_buckets, new_capacity, seed);
> >             curr = next;
> >         }
> >     }
> >     // 将旧动态数组free，但是注意不要free键值对结点，结点已经被链接到新数组中了。
> >     free(map->buckets);
> >     // 更新 HashMap 的信息
> >     map->buckets = new_buckets;
> >     map->capacity = new_capacity;
> >     map->hash_seed = seed;
> > }
> >
> >
> > // 创建一个固定容量的哈希表
> > DynamicHashMap *hashmap_create() {
> >     DynamicHashMap *map = malloc(sizeof(DynamicHashMap));
> >     if (map == NULL) {
> >         printf("Error: malloc failed in hashmap_create\n");
> >         exit(1);
> >     }
> >     map->buckets = calloc(DEFAULT_CAPACITY, sizeof(KeyValueNode *));
> >     if (map->buckets == NULL) {
> >         // 不要忘记先free结构体
> >         free(map);
> >         printf("Error: calloc failed in hashmap_create\n");
> >         exit(1);
> >     }
> >     // 初始化其它成员
> >     map->size = 0;
> >     map->capacity = DEFAULT_CAPACITY;
> >     map->hash_seed = time(NULL);
> >     return map;
> > }
> >
> >
> > // 销毁一个哈希表
> > void hashmap_destroy(DynamicHashMap *map) {
> >     // 1.先遍历动态数组销毁链表的每一个结点
> >     for (int i = 0; i < map->capacity; i++) {
> >         KeyValueNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             KeyValueNode *tmp = curr->next;
> >             free(curr);
> >             curr = tmp;
> >         }
> >     }
> >     // 2.再销毁动态数组
> >     free(map->buckets);
> >     // 3.最后销毁哈希表结构体
> >     free(map);
> > }
> >
> >
> > // 插入一个键值对
> > // 1. 如果key不存在，则添加键值对结点
> > // 2. 如果key存在，则更新val，将旧的val返回
> > ValueType hashmap_put(DynamicHashMap *map, KeyType key, ValueType val) {
> >     // 计算key的哈希值确定存储位置
> >     int idx = hash(key, strlen(key), map->hash_seed) % (map->capacity);
> >
> >
> >     // 遍历链表
> >     KeyValueNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (strcmp(key, curr->key) == 0) {
> >             // 更新 key 关联的 val, 并将旧的value返回
> >             ValueType old_val = curr->val;
> >             curr->val = val;
> >             return old_val;
> >         }
> >         curr = curr->next;
> >     } // while循环结束时, curr是一个NULL
> >
> >
> >     // 键值对不存在，即需要将键值对插入
> >     // 插入操作前需要计算当前哈希表的负载因子
> >     double load_factor = (1.0 * map->size) / (map->capacity);
> >     if (load_factor >= LOAD_FACTOR_THRESHOLD) {
> >         // 当前哈希表负载因子已达到阈值，将动态数组进行扩容
> >         grow_capacity(map);
> >         // 数组长度已变，需要再哈希确定当前键值对的存储位置
> >         idx = hash(key, strlen(key), map->hash_seed) % (map->capacity);
> >     }
> >     // 开始插入新键值对
> >     KeyValueNode *new_node = malloc(sizeof(KeyValueNode));
> >     if (new_node == NULL) {
> >         printf("Error: malloc failed in hashmap_put\n");
> >         exit(1);
> >     }
> >     // 初始化结点
> >     new_node->key = key;
> >     new_node->val = val;
> >     // 链表的头插法
> >     new_node->next = map->buckets[idx];
> >     map->buckets[idx] = new_node;
> >
> >
> >     // 不要忘记更新size
> >     map->size++;
> >     return NULL;
> > }
> >
> >
> > // 查询一个键值对
> > ValueType hashmap_get(DynamicHashMap *map, KeyType key) {
> >     // 计算key的哈希值，从而确定哈希桶
> >     int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
> >     // 遍历哈希桶的链表，判断 key 是否存在
> >     KeyValueNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (strcmp(key, curr->key) == 0) {
> >             // 找到目标键值对
> >             return curr->val;
> >         }
> >         curr = curr->next;
> >     } // curr == NULL
> >     // 没找到目标键值对
> >     return NULL;
> > }
> >
> >
> > // 删除某个键值对
> > bool hashmap_remove(DynamicHashMap *map, KeyType key) {
> >     // 计算key的哈希值，从而确定哈希桶
> >     int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
> >     // 初始化两个指针，一个指向链表当前结点，一个指向当前结点的前驱
> >     KeyValueNode *prev = NULL;
> >     KeyValueNode *curr = map->buckets[idx];
> >     while (curr != NULL) {
> >         if (strcmp(key, curr->key) == 0) {
> >             // 找到了要删除的节点
> >             if (prev == NULL) {
> >                 // 删除的是哈希桶的第一个节点，于是更新头指针
> >                 map->buckets[idx] = curr->next;
> >             }
> >             else {
> >                 // 删除的是哈希桶中的非第一个节点，只需要让当前结点的前驱结点指向当前结点的后继
> >                 prev->next = curr->next;
> >             }
> >             free(curr);
> >             map->size--;
> >             return true;
> >         }
> >         // 继续遍历链表
> >         prev = curr;
> >         curr = curr->next;
> >     }
> >     // 没找到指定key的节点
> >     return false;
> > }
> > ```
> >
> > **测试用例代码如下：**
> >
> > ```c
> > #include "dynamic_hashmap.h"
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <string.h>
> >
> >
> > int main(void) {
> >     // 创建哈希表
> >     DynamicHashMap *map = hashmap_create();
> >     if (map == NULL) {
> >         printf("哈希表创建失败。\n");
> >         return 1;
> >     }
> >
> >
> >     // 插入一些键值对
> >     hashmap_put(map, "key1", "value1");  // 首次插入，预期成功
> >     hashmap_put(map, "key2", "value2");  // 再插入一个新键值对，预期成功
> >     ValueType old_value = hashmap_put(map, "key1", "value3");  // 更新已存在的键值对，预期返回"value1"
> >     printf("更新'key1'的值时返回的旧值应为'value1'，实际返回: %s\n", old_value);
> >
> >
> >     // 查询键值对
> >     ValueType value = hashmap_get(map, "key1");
> >     printf("查询'key1'，预期得到'value3'，实际得到：%s\n", value);
> >     value = hashmap_get(map, "key2");
> >     printf("查询'key2'，预期得到'value2'，实际得到：%s\n", value);
> >     value = hashmap_get(map, "key3");
> >     if (value == NULL) {
> >         printf("如预期，'key3'未找到\n");
> >     }
> >
> >
> >     // 删除键值对
> >     bool deleted = hashmap_remove(map, "key1");  // 删除'key1'，预期删除成功
> >     if (deleted) {
> >         printf("'key1'成功删除。\n");
> >         // 验证删除后，'key1'不应该被找到
> >         value = hashmap_get(map, "key1");
> >         if (value == NULL) {
> >             printf("删除后，'key1'不再存在，符合预期。\n");
> >         }
> >     }
> >     deleted = hashmap_remove(map, "key3");  // 尝试删除不存在的'key3'，预期删除失败
> >     if (!deleted) {
> >         printf("'key3'未找到且未删除，符合预期。\n");
> >     }
> >
> >
> >     // 销毁哈希表
> >     hashmap_destroy(map);
> >
> >
> >     return 0;
> > }
> > ```
> >
> > **如果你希望测试动态哈希表的扩容机制，可以使用下列代码：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include "dynamic_hashmap.h"
> > #include <stdio.h>
> > #include <stdlib.h>
> > #include <string.h>
> >
> >
> > #define N 100 // 初始容量是8，设置为10足以触发一次扩容
> >
> >
> > int main() {
> >     // 创建哈希表
> >     DynamicHashMap *map = hashmap_create();
> >     if (map == NULL) {
> >         printf("哈希表创建失败。\n");
> >         return 1;
> >     }
> >
> >
> >     // 插入多个键值对以触发扩容
> >     char tmp_key[1024], tmp_val[1024];
> >     for (int i = 0; i < N; i++) {
> >         /*
> >             sprintf是一个将格式化的数据输出到一个字符数组中，并最终保存为字符串的标准库函数
> >             第一个参数是输出的目的地字符串
> >             后面的参数则和printf使用方式一样
> >         */
> >         sprintf(tmp_key, "key%d", i);
> >         sprintf(tmp_val, "value%d", i);
> >
> >
> >         // 使用 calloc 分配和复制键值对
> >         char *key = calloc(strlen(tmp_key) + 1, sizeof(char));
> >         char *val = calloc(strlen(tmp_val) + 1, sizeof(char));
> >         strcpy(key, tmp_key);
> >         strcpy(val, tmp_val);
> >
> >
> >         hashmap_put(map, key, val);
> >         printf("插入 %s: %s\n", key, val);
> >     }
> >
> >
> >     // 检查扩容前后的数据一致性
> >     bool flag = true;
> >     for (int i = 0; i < N; i++) {
> >         sprintf(tmp_key, "key%d", i);
> >         ValueType ret_val = hashmap_get(map, tmp_key);
> >         sprintf(tmp_val, "value%d", i);
> >         if (ret_val == NULL || strcmp(ret_val, tmp_val) != 0) {
> >             printf("错误：数据不一致，键 %s 应有的值为 %s，检索得到的值为 %s\n",
> >                    tmp_key, tmp_val,
> >                    ((ret_val != NULL) ? ret_val : "null"));
> >             flag = false;   // 若数据插入有问题，则修改标志为false
> >         }
> >     }
> >
> >
> >     if (flag) {
> >         printf("所有数据在扩容后仍正确无误。\n");
> >     }
> >
> >
> >     // free所有堆上分配的字符串
> >     for (int i = 0; i < map->capacity; i++) {
> >         KeyValueNode *curr = map->buckets[i];
> >         while (curr != NULL) {
> >             free(curr->key);   // 释放键字符串
> >             free(curr->val);   // 释放值字符串
> >             curr = curr->next; 
> >         }
> >     }
> >
> >
> >     // 销毁哈希表
> >     hashmap_destroy(map);
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-11"></a>

## 11 算法基础阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/11_算法基础阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 手动实现三个简单排序算法

> 请自己手动实现三个基础的排序算法：
>
> ```c
> // 选择排序
> void selection_sort(int arr[], int len);
> // 冒泡排序
> void bubble_sort(int arr[], int len);
> // 插入排序
> void insertion_sort(int arr[], int len);
> ```
>
> **然后给定一个int数组，实现将它从小到大进行排序。**
>
> > ###### 参考代码：
> >
> > **选择排序代码实现：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
> > #define SWAP(arr, i, j ) {      \
> > int tmp = arr[i];           \
> > arr[i] = arr[j];            \
> > arr[j] = tmp;               \
> > }
> >
> >
> > void print_arr(int arr[], int len) {
> >   for (int i = 0; i < len; i++) {
> >         printf("%d ", arr[i]);
> >   }
> >   printf("\n");
> > }
> >
> >
> > // 选择排序
> > void selection_sort(int arr[], int len) {
> >   /*
> >     * i表示未排序序列的开头元素
> >     * 最后一轮选择排序时, 未排序序列的开头元素是数组倒数第二个元素
> >     * i的每个取值都表示一轮选择排序
> >     * 也就是选择排序一共执行9趟
> >     */ 
> >     for (int i = 0; i < len - 1; i++) {
> >         // 不妨直接假设未排序序列的开头i位置元素就是最小值
> >         int min_index = i;
> >         // 遍历未排序数组序列,找出真正的最小值下标,此时应遍历最后一个元素
> >         for (int j = i + 1; j < len; j++) {
> >             if (arr[j] < arr[min_index]) {
> >                 min_index = j;  // 记录较小值的下标
> >             }
> >         }   // for循环结束时，未排序序列的最小值下标就是min_index
> >
> >
> >         // 交换min_index和下标i的元素
> >         SWAP(arr, min_index, i);
> >         // 选择排序一趟打印一次数组
> >         print_arr(arr, len);
> >     }
> > }
> >
> >
> > int main(void) {
> >     // 测试选择排序
> >     int arr[] = { 1,10,2,5,3,4,5,6,3,2 };
> >     int len = ARR_LEN(arr);
> >     selection_sort(arr, len);
> >     return 0;
> > }
> > ```
> >
> > **冒泡排序代码实现：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdbool.h>
> >
> >
> > #define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
> >
> >
> > #define SWAP(arr, i, j ) {      \
> >     int tmp = arr[i];           \
> >     arr[i] = arr[j];            \
> >     arr[j] = tmp;               \
> > }
> >
> >
> > void print_arr(int arr[], int len) {
> >     for (int i = 0; i < len; i++) {
> >         printf("%d ", arr[i]);
> >     }
> >     printf("\n");
> > }
> >
> >
> > void bubble_sort(int arr[], int len) {
> >     // 外层for的i表示第几轮冒泡排序,最多需要进行len-1轮
> >     for (int i = 1; i < len; i++) {
> >         // 标记在这一次冒泡排序中有没有交换,false表示没有交换
> >         bool swapped = false;
> >         /*
> >         * j表示两两比较元素中的第一个元素的下标
> >         * 第一轮j的最大取值是数组倒数第二个元素,并且逐步减小
> >         * 所以j的条件是小于 (len - i)
> >         */ 
> >         for (int j = 0; j < len - i; j++) {
> >             if (arr[j] > arr[j + 1]) {
> >                 SWAP(arr, j, j + 1);
> >                 // 发生了交换改变标记
> >                 swapped = true;
> >             }
> >         }
> >         // 在一轮冒泡排序中没有任何交换,则排序已经完成,终止循环
> >         if (!swapped) {
> >             break;
> >         }
> >         // 打印一轮冒泡排序后数组的元素排列
> >         print_arr(arr, len);
> >     }
> > }
> >
> >
> > int main(void) {
> >     // 测试冒泡排序
> >     int arr[] = { 16, 1, 45, 23, 99, 2, 18, 67, 42, 10 };
> >     int len = ARR_LEN(arr);
> >     bubble_sort(arr, len);
> >
> >
> >     return 0;
> > }
> > ```
> >
> > **插入排序代码实现：**
> >
> > ```c
> > // 插入排序 优化: 用向后移动腾出插入位置,然后插入实现插入排序
> > void insertion_sort(int arr[], int len) {
> >     // 现在第一个元素就是第一张手牌,从第二个元素开始就是每一次要摸的牌
> >     // 外层for循环代表每一轮摸到的新手牌, 也就是每一轮插入排序
> >     for (int i = 1; i < len; i++) {
> >         // 先记录一下新手牌的值, 便于后续的插入操作
> >         int tmp = arr[i];
> >         int j = i - 1;
> >         for (;j >= 0; j--) {
> >             if (arr[j] > tmp) { // 注意:不能加=,加了就不是稳定排序算法了
> >                 arr[j + 1] = arr[j];    // 将旧手牌中大于新手牌的所有牌都向后移
> >             }
> >             else
> >             {
> >                 break;  // 只要发现一张旧手牌更小或相等, 就说明已经找到新手牌的插入位置了
> >             }
> >         }
> >         /*
> >             现在还有一件事情没做:新手牌要插入,需要确定插入位置
> >             分析: for循环什么时候结束?
> >             两种情况:
> >             1.j=-1时,循环结束,说明新手牌是最小的,所以插入到0这个位置,也就是j+1
> >             2.arr[j] <= tmp 也就是旧手牌更小或相等,此时新手牌放在j+1的位置
> >         */
> >         arr[j + 1] = tmp;
> >         print_arr(arr, len);    // 每一轮摸牌后查看排序后的数组
> >     }
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 1, 21, 45, 231, 99, 2, 18, 7, 4, 9 };
> >     int len = ARR_SIZE(arr);
> >     insertion_sort(arr, len);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 手动实现希尔排序算法

> **请手动实现希尔排序算法:**
>
> ```c
> void shell_sort(int arr[], int n);
> ```
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **希尔排序的实现代码如下：**
> >
> > ```c
> > #include <stdio.h>
> >
> >
> > #define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
> >
> >
> > void print_arr(int arr[], int len) {
> >     for (int i = 0; i < len; i++) {
> >         printf("%d ", arr[i]);
> >     }
> >  printf("\n");
> > }
> >
> >
> > // 希尔排序: 缩小增量排序, 其实就是多人摸牌, 逐渐减少摸牌人数
> > // 希尔排序中, 增量序列的设计非常重要,这里采取简单的gap序列: 长度减半..一直减半,直到为1
> > // gap为1时就是一个在数组元素基本有序情况下的,插入排序
> > void shell_sort(int arr[], int len) {
> >     // 第一个元素是第一个人的初始手牌,一直到第gap个元素都是初始手牌
> >     int gap = len >> 1;
> >     while (gap > 0) {
> >         // 外层for的i仍然代表新摸到的手牌的下标,i从gap开始,直到摸完整个数组元素
> >      for (int i = gap; i < len; i++) {
> >             // 先记录一下新手牌的值, 便于后续的插入操作
> >             int tmp = arr[i];
> >             int j = i - gap;    // 代表每一个人旧手牌的最后一张牌
> >             for (; j >= 0; j -= gap) {
> >                 // 内层for代表 每个人每摸到一张新手牌,都会和原本的旧手牌比较,但由于gap存在,所以需要减去gap
> >                 if (arr[j] > tmp) { // 注意:不能加=,加了就不稳定了
> >                  arr[j + gap] = arr[j]; // 将旧手牌中大于新手牌的所有牌都向后移
> >                 }
> >                 else
> >                 {
> >                  break; // 只要发现一张旧手牌更小或相等, 就说明已经找到新手牌的插入位置了
> >                 }
> >          }
> >          arr[j + gap] = tmp;
> >          print_arr(arr, len);   // 每一轮摸牌后查看排序后的数组
> >      }
> >         gap >>= 1; // 每一轮希尔排序,增量都减半
> >     }
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 16, 1, 45, 23, 99, 2, 18, 67, 42, 10 };
> >     int arr_len = ARR_LEN(arr);
> >  shell_sort(arr, arr_len);
> >  return 0;
> > }
> > ```
>
> 以上。

#### 手动实现归并排序算法

> 请手动实现归并排序算法：
>
> ```c
> void merge_sort(int arr[], int len)
> ```
>
> **如果学有余力，不妨尝试一下多种临时数组的方式：**
>
> **1.局部变量数组**
>
> **2.全局变量数组**
>
> **3.堆数组**
>
> **提交答案只需要使用其中一种即可。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **归并排序实现代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <stdlib.h>
> > #define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
> >
> >
> > // 打印数组的函数
> > void print_arr(int arr[], int left, int right) {
> >     for (int i = left; i <= right; i++) {
> >         printf("%d ", arr[i]);
> >     }
> >     printf("\n");
> > }
> >
> >
> > /*
> >    * 合并的思路:
> > * 1.把左右子数组中元素按照顺序合并到临时数组中,过程类似"穿针引线"
> >    * 2.将排好序的临时数组元素按照下标赋值给原数组
> >    * 注：临时数组和原数组共有一套下标
> >    * 传入函数逻辑上的左右子数组是有序的,相当于合并两个有序的左右子数组
> >    */
> > static void merge(int arr[], int left, int mid, int right, int* tmp) {
> >     /*
> >     * tmp_idx: 用于存放合并结果的临时数组的开始下标
> >     * left_idx: 左子数组的开始下标
> >     * right_idx: 右子数组的开始下标
> >     */
> >     int tmp_idx = left, left_idx = left, right_idx = mid + 1;
> >
> >
> >     // 只要左右子数组同时还有元素
> >     while (left_idx <= mid && right_idx <= right) {
> >         // 捉对比较左右子数组的元素,按照从小到大放入临时数组
> >         // <=判断不会改变相同元素的相对位置,是稳定算法。反之则不是稳定算法
> >         if (arr[left_idx] <= arr[right_idx]) {
> >             tmp[tmp_idx++] = arr[left_idx++];
> >         }
> >         else {
> >             tmp[tmp_idx++] = arr[right_idx++];
> >         }
> >     }   
> >     // while结束时，左右子数组必然有一个没有元素了,此时另一个数组必然还有元素
> >     // 也就是说只会有一个数组是空的
> >     // 但我们无法确定是哪个数组没有元素了
> >     // 所以我们都判断一下将左右子数组还剩余的元素取出来
> >     while (left_idx <= mid) {
> >         // 说明左数组还有元素
> >         tmp[tmp_idx++] = arr[left_idx++];
> >     }
> >     while (right_idx <= right) {
> >         // 说明右数组还有元素
> >         tmp[tmp_idx++] = arr[right_idx++];
> >     }
> >
> >
> >     // 将临时数组中已排序好的元素复制到原始数组中
> >     for (int i = left; i <= right; i++) {
> >         arr[i] = tmp[i];
> >     }
> >     // 打印此一轮归并排序的元素
> >     print_arr(arr, left, right);
> > }
> >
> >
> > /*
> > * 辅助函数,实现对[left, right]范围内的数组递归分解合并
> > * left表示递归分解的区间起点,right表示递归分解区间的终点,是一个闭区间
> >    * 递归分解的思路是:
> >    * 对[left, right]区间元素的排序,可以分解成:
> > * [left, mid]区间,和[mid + 1, right]区间的排序合并
> >    * 递归的出口是:
> >    * 如果区间仅有一个元素或没有元素,递归结束
> >    */
> > static void divide_merge(int arr[], int left, int right, int* tmp) {
> >     // 递归的出口
> >     if (left >= right) {
> >         return;
> >     }
> >
> >
> >     // 递归体
> >     // 计算中间索引
> >     int mid = left + (right - left >> 1);
> >     // 分解,规定左数组是[left, mid]
> >     // 右数组是[mid + 1, right]
> >     divide_merge(arr, left, mid, tmp);
> >     divide_merge(arr, mid + 1, right, tmp);
> >
> >
> >     /*
> >     * 归并，归并排序的核心操作
> >     * 需要一个临时数组完成此操作
> >     * 这个临时数组至少要和原先的数组一般大
> >     * 有两种方案：
> >     * 1.用全局变量数组或局部变量,该方式简洁易实现,无需考虑内存回收
> >     *   但缺点是
> >     *   a.必须编译时期确定数组长度,无法运行时期动态分配
> >     *   b.栈区和数据段都无法创建长数组,在大数据集下容易产生溢出错误
> >     * 为了解决这两个缺点,我们可以在堆上动态分配数组
> >     *   但同样也有缺点:
> >     *   a.内存管理风险
> >     *   b.动态分配数组会带来额外性能开销
> >     */
> >     merge(arr, left, mid, right, tmp);
> >
> >
> > }
> >
> >
> > void merge_sort(int arr[], int len) {
> >     // 临时数组
> >     int* tmp = calloc(len, sizeof(int));
> >     if (tmp == NULL){
> >         printf("calloc failed in merge_sort.\n");
> >         return;
> >     }
> >
> >
> >     // 将整个数组进行递归分解合并,即完成归并排序
> >     divide_merge(arr, 0, len - 1, tmp);
> >
> >
> >     // 不要忘记free释放资源
> >     free(tmp);
> > }
> >
> >
> > // 测试归并排序
> > int main() {
> >     int arr[] = { 8, 3, 2, 6, 9, 7, 1, 0, 4, 5 };
> >     int arr_size = ARR_SIZE(arr);
> >
> >
> >     merge_sort(arr, arr_size);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 手动实现快速排序算法

> 请手动实现快速排序算法，包括单向分区以及双向分区：
>
> ```c
> // 单向分区快速排序算法
> void quick_sort_one_way(int arr[], int len);
> // 双向分区快速排序算法
> void quick_sort_two_way(int arr[], int len);
> ```
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **单向分区快排算法的实现代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #include <time.h>
> > #include <stdlib.h>
> >
> >
> > #define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
> > #define SWAP(arr, i, j) {   \
> >     int tmp = arr[i];       \
> >     arr[i] = arr[j];        \
> >     arr[j] = tmp;           \
> > }
> >
> >
> > // 打印数组的函数
> > void print_arr(int arr[], int left, int right) {
> >     for (int i = left; i <= right; i++) {
> >         printf("%d ", arr[i]);
> >     }
> >     printf("\n");
> > }
> >
> >
> > // 分区核心操作实现,返回一轮快排选择的pivot的下标
> > int partition(int arr[], int left, int right) {
> >     // 1.随机选择一个基准值,然后把它先放到数组末尾
> >     int pivot_idx = left + rand() % (right - left + 1); // 得到一个[left, right]范围内的随机索引
> >     int pivot = arr[pivot_idx];
> >     SWAP(arr, pivot_idx, right);
> >
> >
> >     // 2.设置一个partition_idx索引,指示小于pivot的元素应该插入的位置
> >     // 同时该索引最终表示分区的界限索引,所以命名为partition_idx
> >     int partition_idx = left;
> >
> >
> >     // 3.遍历整个数组,当元素小于pivot时,将它和partition_idx位置元素交换,partition_idx加1
> >     // 希望遍历结束时，i指向数组末尾的pivot，所以i < right
> >     for (int i = left; i < right; i++) {
> >         if (arr[i] < pivot) {
> >             SWAP(arr, i, partition_idx);
> >             partition_idx++;
> >         }
> >     }
> >     // 4.遍历结束后,将pivot元素(最后一个元素)交换到partition_idx位置
> >     SWAP(arr, right, partition_idx);
> >
> >
> >     printf("此一轮分区操作,选择的pivot是: %d\n分区结束后的数组是: ", pivot);
> >     print_arr(arr, left, right);
> >
> >
> >     // 5.返回基准值的位置索引
> >     return partition_idx;
> > }
> >
> >
> > /*
> > * 辅助函数
> > * 用于对对[left, right]区间中的元素进行递归分区操作
> > */
> > void partition_recursion(int arr[], int left, int right) {
> >     // 递归出口
> >     if (left >= right) {
> >         return;
> >     }
> >     // 递归体
> >     int idx = partition(arr, left, right);  // 分区操作,找到pivot元素的下标位置
> >     partition_recursion(arr, left, idx - 1);
> >     partition_recursion(arr, idx + 1, right);
> > }
> >
> >
> > void quick_sort_one_way(int arr[], int len) {
> >     // 初始化随机数生成器,time(NULL)获取当前时间戳
> >     // 用于生成随机索引
> >     srand(time(NULL));
> >     // 调用辅助函数进行递归分解
> >     partition_recursion(arr, 0, len - 1);
> > }
> >
> >
> > int main(void) {
> >     // 测试单向分区快速排序
> >     int arr[] = { 8,3,2,6,9,5 };
> >     int len = ARR_SIZE(arr);
> >     quick_sort_one_way(arr, len);
> >
> >
> >     return 0;
> > }
> > ```
> >
> > **双向分区快排算法的实现代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
> >
> >
> > // 打印数组的函数
> > void print_arr(int arr[], int left, int right) {
> >     for (int i = left; i <= right; i++) {
> >         printf("%d ", arr[i]);
> >     }
> >     printf("\n");
> > }
> >
> >
> > // 双向分区操作函数用于快速排序
> > int partition(int arr[], int left, int right) {
> >     // 选择左端元素作为基准值
> >     int pivot = arr[left];
> >
> >
> >     // 初始化指针：low 指向数组起始，high 指向数组末尾
> >     int low = left;
> >     int high = right;
> >
> >
> >     // 当 low 和 high 未重合时，执行分区操作
> >     while (low < high) {
> >         // 从右向左找到第一个小于基准值的元素
> >         while (low < high && arr[high] >= pivot) {
> >             high--;
> >         }
> >         // 找到后，将其放到 low 的位置
> >         arr[low] = arr[high]; // 这里不需要判断 low < high，因为外层循环已保证
> >
> >
> >         // 从左向右找到第一个大于等于基准值的元素
> >         while (low < high && arr[low] < pivot) {
> >             low++;
> >         }
> >         // 找到后，将其放到 high 的位置
> >         arr[high] = arr[low]; // 同样，这里不需要再次判断 low < high
> >     }
> >
> >
> >     // 当 low 和 high 重合，确定了基准元素的最终位置，将基准值放回数组中
> >     arr[low] = pivot;
> >
> >
> >     // 打印本轮分区后的数组状态，仅为了演示和调试
> >     printf("此轮分区操作，选择的基准是: %d\n分区结束后的数组是: ", pivot);
> >     print_arr(arr, left, right); // 假设 print_arr 正确实现
> >
> >
> >     // 返回基准值的最终位置
> >     return low;
> > }
> >
> >
> > // 对[left, right]区间进行递归分区操作
> > void partition_recursion(int arr[], int left, int right) {
> >     // 递归出口
> >     if (left >= right) {
> >         return;
> >     }
> >     // 递归体
> >     int idx = partition(arr, left, right);  // 分区操作,找到pivot下标位置
> >     partition_recursion(arr, left, idx - 1);
> >     partition_recursion(arr, idx + 1, right);
> > }
> >
> >
> > void quick_sort_two_way(int arr[], int len) {
> >     partition_recursion(arr, 0, len - 1);
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 8,3,2,6,9,5 };
> >     int len = ARR_SIZE(arr);
> >     // 测试双向分区-快速排序
> >     quick_sort_two_way(arr, len);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 手动实现堆排序算法

> 请手动实现堆排序算法:
>
> ```c
> void heap_sort(int arr[], int len);
> ```
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **堆排序算法实现代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define ARR_SIZE(a) (sizeof(a)/sizeof(a[0]))
> > #define SWAP(arr, i, j) {   \
> >     int tmp = arr[i];       \
> >     arr[i] = arr[j];        \
> >     arr[j] = tmp;           \
> > }
> >
> >
> > void print_arr(int arr[], int n) {
> >  for (int i = 0; i < n; i++) {
> >      printf("%d ", arr[i]);
> >  }
> >  printf("\n");
> > }
> >
> >
> > // idx是可能违反大顶堆规则的父结点的下标
> > // 在一开始idx结点的左右子树必然都是大顶堆
> > static void heapify(int arr[], int heap_len, int idx) {
> >  while (1) {
> >      // 找出idx结点的左右子树,比较,确定最大结点,如果最大结点不是idx那就进行交换操作
> >      int max_idx = idx; // 假设父节点就是最大结点
> >      int lchild_idx = (idx << 1) + 1;   // 左子树的索引
> >      int rchild_idx = (idx << 1) + 2;   // 右子树的索引
> >
> >
> >      // 如果左子树存在并且大于最大值
> >      if (lchild_idx < heap_len && arr[lchild_idx] > arr[max_idx]) {
> >          max_idx = lchild_idx;
> >      }
> >
> >
> >      // 如果右子树存在并且大于最大值
> >      if (rchild_idx < heap_len && arr[rchild_idx] > arr[max_idx]) {
> >          max_idx = rchild_idx;
> >      }
> >
> >
> >      // 代码运行到这里,就找到了父节点和左右子树结点的最大值
> >      if (max_idx != idx) {
> >          // 父节点不是最大值，交换元素
> >          SWAP(arr, idx, max_idx);
> >          // max_idx此时发生了元素交换,此结点可能会违反大顶堆的规则
> >          // 更新idx，继续循环这一过程，直到不再出现元素交换。堆化才全部完成
> >          idx = max_idx;
> >      }
> >      else {
> >          // 父节点就是最大结点，此时堆化过程全部结束
> >          break;
> >      }
> >  }
> > }
> >
> >
> > void build_heap(int arr[], int len) {
> >  /*
> >     * 从数组最后一个非叶子结点开始，对每个非叶子结点做堆化处理
> >     * (最后一个非叶子结点向前遍历到数组首元素，过程中的结点都是非叶子结点)
> >     * 也就是自下而上处理所有的非叶子结点, 使得所有非叶子结点都符合大顶堆的规则
> >     * 这样整个数组就会构建成为一个大顶堆
> >     *
> >     * 那么最后一个非叶子结点的元素下标是多少呢?
> >     * 假设最后一个非叶子结点,它的索引是i
> >     * 那么它至少有一颗左子树,左子树的索引是2i + 1
> >     * 数组索引的取值范围是[0, len - 1]
> >     * 2i + 1 <= len - 1
> >     * i <= (len - 2) / 2
> >     * 所以数组中最后一个非叶子结点的下标就是(len - 2) / 2
> >     */
> >     int last_idx = len - 2 >> 1;
> >     for (int i = last_idx; i >= 0; i--) {
> >         heapify(arr, len, i);
> >     }
> >     print_arr(arr, len);
> > }
> >
> >
> > void heap_sort(int arr[], int len) {
> >     // 1.将原数组构建成一个大顶堆
> >     build_heap(arr, len);
> >
> >
> >     // 2.反复移除堆顶元素, 并重建大顶堆
> >     int heap_len = len; // 堆的逻辑大小,一开始将整个数组当成一个大顶堆
> >     // 只要堆的逻辑大小大于1, 就需要重复堆排序的过程
> >     while (heap_len > 1) {
> >         // 交换堆逻辑上的首尾元素
> >         SWAP(arr, 0, heap_len - 1);
> >         heap_len--;     // 堆逻辑大小减1
> >         // 重构大顶堆
> >         /*
> >         * 此函数的三个参数：
> >         * 1.arr是作为大顶堆的数组
> >         * 2.heap_len决定数组中哪部分元素作为大顶堆处理
> >         * 3.0是堆逻辑上的根结点,由于每次堆顶元素都会交换改变
> >         *   所以在堆排序的过程中，只有此元素的存在可能会违反大顶堆的规则
> >         *   也就是说该索引是堆化过程中可能需要处理的结点的索引
> >         */
> >         heapify(arr, heap_len, 0);
> >         print_arr(arr, len);
> >     }   // while结束时,heap_len = 1,堆排序结束
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 4, 10, 3, 5, 1 };
> >     int len = ARR_SIZE(arr);
> >     print_arr(arr, len);
> >
> >
> >     heap_sort(arr, len);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 手动实现简单二分查找算法

> 请手动实现**简单二分查找**算法，要求使用递归和循环迭代两种方式实现：
>
> ```c
> int binary_search(int arr[], int len, int target);
> ```
>
> **所谓简单二分查找，指的是利用二分查找算法，查找目标元素，只要找到目标元素即返回目标元素的下标。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **递归实现简单二分查找：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #define ARR_LEN(arr) ( sizeof(arr) / sizeof(arr[0]) )
> >
> >
> > // 递归实现简单二分查找
> > int bs_recursion(int arr[], int left, int right, int target) {
> >     // 递归的出口
> >     // 如果区间已不存在, 则二分查找结束, 没找到目标元素
> >     if (left > right) {
> >         return -1;
> >     }
> >
> >
> >     // 递归体
> >     // 如果区间存在，则递归分解进行二分查找
> >     int mid = left + (right - left >> 1);   // 计算中间索引
> >     int diff = target - arr[mid];
> >     if (diff > 0) {
> >         // 递归查找右区间
> >         return bs_recursion(arr, mid + 1, right, target);
> >     }
> >     if (diff < 0) {
> >         // 递归查找左区间
> >         return bs_recursion(arr, left, mid - 1, target);
> >     }
> >     // diff等于0，中间元素就是目标元素
> >     return mid;
> > }
> >
> >
> > int binary_search(int arr[], int len, int target) {
> >     // 利用辅助函数完成递归二分查找数组的过程
> >     // 此函数调用表示对arr数组[0, len-1]区间的元素进行二分查找
> >     return bs_recursion(arr, 0, len - 1, target);
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 0,3,5,7,7,9,10, 20,100 };
> >     int len = ARR_LEN(arr);
> >     int target = 7;
> >
> >
> >     int idx = binary_search(arr, len, target);
> >
> >
> >     printf("查找目标元素%d, 它在数组中的索引是%d\n", target, idx);
> >
> >
> >     return 0;
> > }
> > ```
> >
> > **循环迭代实现二分查找：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > // 定义一个宏,用于计算数组的长度
> > #define ARR_LEN(arr) ((int)sizeof(arr) / sizeof(arr[0]))
> >
> >
> >
> >
> > // 循环实现简单二分查找
> > int binary_search(int arr[], int len, int target) {
> >     // 定义二分查找过程中数组的左右界限
> >     int left = 0, right = len - 1;
> >
> >
> >     while (left <= right) { // 只要区间还有一个元素,就进行二分查找
> >         int mid = left + (right - left >> 1);   // 计算中间索引
> >         int diff = target - arr[mid];
> >
> >
> >         if (diff > 0) {
> >             // 查找右半区间
> >             left = mid + 1;
> >         }
> >         else if (diff < 0) {
> >             // 查找左半区间
> >             right = mid - 1;
> >         }
> >         else {
> >             // 已找到目标元素
> >             return mid;
> >         }
> >     }
> >
> >
> >     // while循环即left > right，说明数组中没有目标元素
> >     return -1;
> > }
> >
> >
> > int main(void) {
> >     int arr[] = { 0,3,5,7,7,9,10, 20,100 };
> >     int len = ARR_LEN(arr);
> >     int target = 100;
> >
> >
> >     int idx = binary_search(arr, len, target);
> >     printf("查找目标元素%d, 它在数组中的索引是%d\n", target, idx);
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

#### 手动实现二分查找的变种

> 基于循环迭代的实现方式，利用二分查找的算法思想，实现：
>
> 1. 查找数组中最后一个与目标值相等的元素
> 2. 查找数组中最后一个小于等于目标值的元素
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > **查找数组中最后一个与目标值相等的元素，实现参考代码如下：**
> >
> > ```c
> > // 查找最后一个等于目标值的元素
> > int binary_search_last(int arr[], int len, int target) {
> >     int left = 0, right = len - 1;
> >
> >
> >     while (left <= right) {
> >         int mid = left + (right - left >> 1);
> >
> >
> >         if (arr[mid] < target) {
> >             left = mid + 1;
> >         }
> >         else if (arr[mid] > target) {
> >             right = mid - 1;
> >         }
> >         else {
> >             if (mid == right || arr[mid + 1] > target) {
> >                 // 如果mid是数组的最后一个元素，或者mid的下一个元素大于目标值
> >                 // 那么mid就是target最后一次在数组中出现的下标
> >                 return mid;
> >             }
> >             // 只要不能断定mid是最后一次出现的索引，就继续向右半区间进行二分查找
> >             left = mid + 1;
> >         }
> >     }
> >     // 没找到目标元素
> >     return -1;
> > }
> > ```
> >
> > **查找最后一个小于等于目标值的元素，实现参考代码如下：**
> >
> > ```c
> > // 查找最后一个小于等于目标值的元素
> > int binary_search(int arr[], int len, int target) {
> >     int left = 0, right = len - 1;
> >
> >
> >     while (left <= right) {
> >         int mid = left + (right - left >> 1);
> >
> >
> >         if (arr[mid] > target) {
> >             // 中间值大于目标值, 于是去左区间中查找
> >             right = mid - 1;
> >         }else{
> >             // 中间值小于等于目标值的，于是mid就是一个备选返回值
> >             // 但是要先判断mid是不是最后一个小于等于目标值的元素
> >             if (mid == right || arr[mid + 1] > target) {
> >                 // mid是数组最后一个元素或者mid就是最后一个小于等于目标值的元素
> >                 return mid;
> >             }
> >             // mid不是最后一个, 于是去右区间中查找
> >             left = mid + 1;
> >         }
> >     }
> >
> >
> >     // 没找到目标元素
> >     return -1;
> > }
> > ```
>
> 以上。

#### 利用二分查找思想改进插入排序

> 在数据较多的情况下，使用插入排序会导致"旧手牌"序列比较长，此时若仍然相邻元素两两比较后移是比较耗时的，可以考虑使用"二分查找算法思想"进行改进。
>
> 请你实现这个改进。
>
> 参考代码如下：
>
> > ###### 参考代码实现如下：
> >
> > 利用二分查找，找到最后一个小于等于"新手牌"值的元素，这样就可以直接将它后面的所有元素后移一位，然后再它后面直接插入"新手牌"。
> >
> > **参考实现代码如下：**
> >
> > ```c
> > #include <stdio.h>
> >
> >
> > #define ARR_LEN(arr) ((int)sizeof(arr) / sizeof(arr[0]))
> >
> >
> > // 使用二分查找在有序数组[left, right]区间内中找到最后一个小于等于目标值的元素的位置
> > int binary_search(int arr[], int left, int right, int key) {
> >     while (left <= right) {
> >         // 计算中间位置
> >         int mid = left + (right - left >> 1);
> >         // 比较中间位置的元素和目标值
> >         int cmp = arr[mid] - key;
> >         // 如果中间值和目标值相等或中间值更小，那mid就是一个可能的结果
> >         if (cmp <= 0) {
> >             // 判断mid是不是最后一个
> >             if (mid == right || arr[mid + 1] > key) {   
> >                 // 如果它已经是区间的最后一个元素
> >                 // 或者它不是最后一个元素但mid后面的一个元素已经比目标值大了
> >                 // 都可以断定mid是最后一个小于等于目标值的元素
> >                 return mid;
> >             }
> >             // 如果不是最后一个，那就继续去右边区间查找
> >             left = mid + 1;
> >         } else {
> >             // 如果中间值比目标值大，那就去左边区间二分查找
> >             right = mid - 1;
> >         }
> >     } // left > right 
> >
> >
> >     return -1;
> > }
> >
> >
> > void binary_insertion_sort(int arr[], int n) {
> >     for(int i = 1; i < n; i++) {
> >         int value = arr[i];
> >         // 使用二分查找找到应插入的位置
> >         // idx(不包括)后面的所有元素都有后移一位，idx + 1是value要插入的位置
> >         int idx = binary_search(arr, 0, i-1, value);    
> >         int j = i - 1;  // j在这里赋值为有序数组的最后一个元素
> >         while (j > idx) {       // 有序数组中的元素只要下标大于idx就后移 也就是不包括idx，但idx后面的所有元素都要后移
> >             arr[j+1] = arr[j];
> >             j--;
> >         } // j == idx;
> >         arr[j + 1] = value;
> >     }
> > }
> >
> >
> > int main(void) {
> >     int arr[] = {9, 5, 2, 7, 1, 3, 4, 0, 8, 6};
> >     int len = ARR_LEN(arr);
> >     binary_insertion_sort(arr, len);
> >
> >
> >     for(int i = 0; i < len; i++) {
> >         printf("%d ", arr[i]);
> >     }
> >     printf("\n");
> >
> >
> >     return 0;
> > }
> > ```
>
> 以上。

### The End

<a id="ch-12"></a>

## 12 文件流阶段作业

> 本节原文：http://8.136.0.191:8080/stm32/C/V0/12_文件流阶段作业.html?ws=off&reset=true&toc=0

### 基础题篇

> 下面都是一些基础的语法、概念编程练习题。

#### 手动实现文件流基础操作

> 请自行熟悉文件流的操作函数，实现以下文件流基础操作：
>
> **1.逐字符文本文件复制，函数声明是：**
>
> ```c
> void copy_file_char(const char* src_file, const char* dest_file);
> ```
>
> **2.逐行文本文件复制，函数声明式：**
>
> ```c
> void copy_file_line(const char* src_file,const char* dest_file);
> ```
>
> **3.用fread和fwrite函数实现二进制文件的复制, 函数声明如下：**
>
> ```c
> void binary_file_cpy(const char* src_file, const char* dest_file);
> ```
>
> **4.用fread和fwrite函数实现二进制的序列化和反序列化操作。此操作可以不提取函数，直接在main函数中实现即可。但只允许使用一个FILE流。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **逐字符文本文件复制，实现代码如下：**
> >
> > ```c
> > void copy_file_char(const char* src_file, const char* dest_file) {
> >     // 以只读模式打开源文件
> >     FILE* src = fopen(src_file, "r");
> >     // 处理打开失败的情况
> >     if (src == NULL) {
> >         printf("error: 打开文件 %s 失败！\n", src_file);
> >         exit(1);
> >     }
> >     // 以只写模式打开目的文件
> >     FILE* dest = fopen(dest_file, "w");
> >     // 处理打开失败的情况
> >     if (dest == NULL) {
> >         // 不要忘记关闭src文件流
> >         fclose(src);
> >         printf("error: 打开文件 %s 失败！\n", dest_file);
> >         exit(1);
> >     }
> >     // 循环读和写，复制操作惯用法
> >     int ch;
> >     while ((ch = fgetc(src)) != EOF) {
> >         fputc(ch, dest);
> >     }
> >
> >
> >     // 关闭流
> >     fclose(src);
> >     fclose(dest);
> > }
> >
> >
> > int main(void) {
> >     // 调用函数进行文件复制
> >     copy_file("1.txt", "2.txt");
> >     return 0;
> > }
> > ```
> >
> > **逐行文本文件复制，实现代码如下：**
> >
> > ```c
> > #define MAX_CHARS 1024
> >
> >
> > void copy_file(const char* src_file, const char* dest_file) {
> >     // 以只读模式打开源文件
> >     FILE* src = fopen(src_file, "r");
> >     // 处理打开失败的情况
> >     if (src == NULL) {
> >         printf("error: 打开文件 %s 失败！\n", src_file);
> >         exit(1);
> >     }
> >     // 以只写模式打开目的文件
> >     FILE* dest = fopen(dest_file, "w");
> >     // 处理打开失败的情况
> >     if (dest == NULL) {
> >         // 不要忘记关闭src文件流
> >         fclose(src);
> >         printf("error: 打开文件 %s 失败！\n", dest_file);
> >         exit(1);
> >     }
> >
> >
> >     // 循环读和写，复制操作惯用法
> >     char str[MAX_CHARS];
> >     while (fgets(str, sizeof(str), src) != NULL) {
> >         fputs(str, dest);
> >     }
> >
> >
> >     // 关闭流
> >     fclose(src);
> >     fclose(dest);
> > }
> >
> >
> >
> >
> > int main(void) {
> >     copy_file("1.txt", "2.txt");
> >     return 0;
> > }
> > ```
> >
> > **fread/fwrite文件复制，实现代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> > #define BUFFER_SIZE 4096
> >
> >
> > void bfile_cpy(const char* src_file, const char* dest_file) {
> >     // 只读模式打开源文件用于读取，注意要明确以b为后缀
> >     FILE* src_fp = fopen(src_file, "rb");   // 在Windows平台下rb必不可少
> >     if (src_fp == NULL) {
> >         fprintf(stderr, "无法打开源文件 %s\n", src_file);
> >         exit(1);
> >     }
> >
> >
> >     // 只写模式打开目标文件用于写入，注意要明确以b为后缀
> >     FILE* dest_fp = fopen(dest_file, "wb");
> >     if (dest_fp == NULL) {
> >         fprintf(stderr, "无法打开目标文件 %s\n", dest_file);
> >         fclose(src_fp);  // 关闭已经打开的源文件
> >         exit(1);
> >     }
> >
> >
> >     // 定义缓冲区的大小,一般会稍微定义大一些，这里是4Kb
> >     char buffer[BUFFER_SIZE];
> >
> >
> >     // 循环读取源文件，然后写入目标文件
> >     // 二进制文件复制 惯用法
> >     int read_count;
> >     while ((read_count = fread(buffer, 1, BUFFER_SIZE, src_fp)) > 0) {
> >         fwrite(buffer, 1, read_count, dest_fp);
> >     }
> >
> >
> >     // 写操作后及时刷新
> >     fflush(dest_fp);
> >
> >
> >     // 关闭流资源
> >     fclose(src_fp);
> >     fclose(dest_fp);
> > }
> >
> >
> > int main(void) {
> >     bfile_cpy("a.jpg", "b.jpg");
> >     return 0;
> > }
> > ```
> >
> > **二进制序列化反序列化，实现代码如下：**
> >
> > ```c
> > #define _CRT_SECURE_NO_WARNINGS
> > #include <stdio.h>
> >
> >
> > #include <stdlib.h>
> >
> >
> > typedef struct {
> >     char name[25];
> >     int age;
> >     char gender;
> > } Student;
> >
> >
> > int main(void) {
> >     Student s1 = { "hello", 18, 'm' };
> >
> >
> >     // 序列化：将结构体对象写入文件
> >     FILE* fp = fopen("1.dat", "wb");
> >     if (fp == NULL) {
> >         fprintf(stderr, "无法打开文件 1.bin 用于写入\n");
> >         exit(1);
> >     }
> >     // 用fwrite进行序列化操作更简洁，效率也会更高
> >     fwrite(&s1, sizeof(s1), 1, fp);
> >     fclose(fp); // 序列化结束关闭文件
> >
> >
> >     // 用fread进行反序列化操作更简洁，效率也会更高
> >     fp = fopen("1.dat", "rb");  // 重新打开文件，确保文件指针处于文件开头
> >     if (fp == NULL) {
> >         fprintf(stderr, "无法打开文件 1.bin 用于读取\n");
> >         exit(1);
> >     }
> >     Student s2;
> >     fread(&s2, sizeof(s2), 1, fp);
> >     fclose(fp);
> >
> >
> >     // 打印读取的数据，以验证反序列化是否成功
> >     printf("Name: %s\nAge: %d\nGender: %c\n", s2.name, s2.age, s2.gender);
> >     return 0;
> > }
> > ```
>
> 以上。

#### 将文件内容读到字符串中

> 用户输入文件名，将整个文件的内容读入到字符数组中，并在后面添加空字符'\\0'。
>
> ```c
> char* read_file(const char* path);
> ```
>
> **分析思路：**
>
> 1.打开文件，以只读模式打开即可。不要忘记进行打开失败，错误处理。**（在Windows平台下，应该以rb只读模式打开）**
>
> **2.此案例中文件的大小只能在运行时期确定，所以需要动态内存分配一个字符数组用于存储结果字符串。**
>
> **3.结果字符串的长度 = 文件字节大小 + 1**
>
> **4.文件字节大小怎么算？用`ftell`函数配合`fseek`函数即可计算。**
>
> **5.利用`fread`函数一次性将整个文件中的数据，全部读到结果字符数组中，然后自己在末尾加一个空字符。**
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > **参考实现代码如下：**
> >
> > ```c
> > char* read_file(const char* path) {
> >     // 只读模式打开源文件
> >     FILE *file = fopen(path, "rb");
> >     if (file == NULL) {
> >         fprintf(stderr, "Open %s failed.\n", path);
> >         return NULL;
> >     }
> >     // 移动文件指针到文件末尾以确定文件大小
> >     fseek(file, 0, SEEK_END);
> >     long file_size = ftell(file);
> >     rewind(file);   // 文件指针回到文件开头，以进行接下来的读操作
> >
> >
> >     // 分配一个存储结果字符串的字符数组，它的长度 = 文件大小 + 1
> >     char *buffer = (char*)malloc(file_size + 1);
> >     if (buffer == NULL) {
> >         fprintf(stderr, "malloc failed in readFile.\n");
> >         fclose(file);       // 不要忘记关闭已打开的流
> >         return NULL;
> >     }
> >     // 利用fread直接将整个文件的数组读到结果字符数组中
> >     fread(buffer, 1, file_size, file);
> >     buffer[file_size] = '\0'; // 手动在文件内容后添加空字符
> >
> >
> >     // 关闭文件
> >     fclose(file);
> >     return buffer;
> > }
> > ```
>
> 以上。

#### C语言错误处理机制练习

> 编写一个C程序，实现以下功能：
>
> 1.程序尝试以**"r"模式**，打开一个名为 "1.txt" 的文件进行**读操作**。
>
> 2.如果文件成功打开，程序则读取文件的第一行内容，并将其输出到终端上。
>
> 3.如果文件打开失败，程序应使用 `perror` 函数打印此文件名以及相关错误信息，并输出 `errno` 当前的值。
>
> **把代码编写完成后，执行以下操作从而测试代码：**
>
> 1.一开始，1.txt文件不存在，观察程序的输出。
>
> 2.在工作目录下创建1.txt文件，并在文件开头手动写入一行字符串，再观察程序的输出。
>
> 3.将1.txt文件的权限改成**只读模式**，然后将打开模式改成"a"**模式**，尝试写入一行字符串，观察程序的输出。
>
> 4.将1.txt文件的权限重新改为正常模式，再尝试写入一行字符串，观察程序的输出。
>
> 参考代码如下：
>
> > ###### 参考代码：
> >
> > ```c
> > #include <stdio.h>
> > #include <errno.h>  // 包含 errno 变量
> >
> >
> > int main(void) {
> >     // 尝试打开文件
> >     FILE *file_ptr = fopen("1.txt", "r");
> >
> >
> >     // 检查文件是否成功打开
> >     if (file_ptr == NULL) {
> >         // 文件打开失败，使用 perror 打印错误信息
> >         perror("1.txt");
> >         // 打印 errno 当前的值
> >         printf("errno: %d\n", errno);
> >         return 1; // 结束程序并返回错误代码
> >     }
> >
> >
> >     char buffer[256];
> >     // 文件成功打开，读取第一行
> >     if (fgets(buffer, 256, file_ptr) != NULL) {
> >         printf("文件第一行内容是： %s", buffer);  // 输出读取的内容
> >     }
> >     else {
> >         printf("读取文件时发生错误。\n");
> >     }
> >     // 关闭文件
> >     fclose(file_ptr);
> >     return 0; // 程序成功结束
> > }
> > ```
>
> 以上。

### The End
