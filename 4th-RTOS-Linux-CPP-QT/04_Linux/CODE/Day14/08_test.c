#include <header.h>

// 0  -1 -2  -3

// 接口文档

/* "函数作用"
 *
 * 参数说明: 
 *
 * 返回值: 
 *
 */
int a(){
    // 写文件
    
    // 1, 文件不存在
    // 2, 没有权限
    // 3, 要写的数据有问题

}

int main(int argc, char *argv[argc]){
    ARGS_CHECK(argc, 2);

    int num = 0;
    int ret = a();


    printf("num: %s \n", argv[1]);

    return 0;
}

