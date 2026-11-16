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
    const char * sql = "delete from student where id=9";
    int ret = mysql_real_query(pconn, sql, strlen(sql));
    if(ret) {
        printf("(%d, %s)\n", mysql_errno(pconn), mysql_error(pconn));
        mysql_close(pconn);
        return EXIT_FAILURE;
    }

    //4. 查询成功, 写操作成功
    printf("Query OK, %ld row(s) affected.\n", mysql_affected_rows(pconn));

    //5. 释放连接
    mysql_close(pconn);

    return 0;
}

