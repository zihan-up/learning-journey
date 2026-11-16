#include <header.h>

int getparameter(char *key, char *value){

    FILE * file = fopen("config.ini", "r");
    while(1){
        char line[100];
        bzero(line, sizeof(line));
        // 读一行数据
        char *res = fgets(line, sizeof(line), file);
        if(res == NULL){
            char buf[] = "没有要找的内容 \n";
            memcpy(value, buf, strlen(buf));
            return -1;
        }
        // 处理数据
        char *line_key = strtok(line, "=");
        if(strcmp(key, line_key) == 0){
            // 要找的内容
            char *line_value = strtok(NULL, "=");
            memcpy(value, line_value, strlen(line_value));
            return 0;
        }
    }

    return 0;
}
int main(int argc,char*argv[])
{
    char ip[100];
    bzero(ip, sizeof(ip));
    getparameter("ip", ip);
    printf("ip is = %s", ip);

    char port[100];
    bzero(port, sizeof(port));
    getparameter("port", port);
    printf("port is = %s", port);

    return 0;
}
