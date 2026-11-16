#include <cstdlib>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>


int main()
{
    MYSQL conn;
    //1. 初始化MYSQL结构体
    MYSQL * pconn = mysql_init(&conn);
    printf("&conn: %p, pconn: %p\n", &conn, pconn);
    const char * host = "localhost";
    const char * user = "root";
    const char * passwd = "1234";
    const char * db = "4th";
    //2. 建立连接
    pconn = mysql_real_connect(pconn, host, user, passwd, db, 0, NULL, 0);
    if(!pconn) {
        printf("%s\n", mysql_error(&conn));
        return EXIT_FAILURE;
    }

    //3. 准备SQL语句
    const char * sql = "select *from student where id < 5";
    int ret = mysql_real_query(pconn, sql, strlen(sql));
    if(ret) {
        printf("(%d, %s)\n", mysql_errno(pconn), mysql_error(pconn));
        mysql_close(pconn);
        return EXIT_FAILURE;
    }

    //4. 查询成功, 读操作成功
    //当使用mysql_use_result时，调用成功之后，
    //不会直接获取数据; 如果需要进一步的获取数据
    //必须要调用mysql_fetch_row函数
    MYSQL_RES * result = mysql_use_result(pconn);
    if(result) {
        //4.1 先打印行数和列数
        int rows = mysql_num_rows(result);//为0
        int cols = mysql_num_fields(result);
        printf("result: (%d, %d)\n", rows, cols);

        //4.2 打印字段名信息
        MYSQL_FIELD * pfields = mysql_fetch_fields(result);
        for(int i = 0; i < cols; ++i) {
            printf("%s\t", pfields[i].name);
        }
        printf("\n");
        //4.3 打印每一行数据
        MYSQL_ROW row;
        //每一次获取数据时，都需要调用mysql_fetch_row，
        //在这里完成数据的传输
        while((row = mysql_fetch_row(result)) != NULL) {
            for(int i = 0; i < cols; ++i) {
                printf("%s\t", row[i]);
            }
            printf("\n");
        }
    }
    //4.4 释放结果集
    mysql_free_result(result);
    //5. 释放连接
    mysql_close(pconn);
    return 0;
}

