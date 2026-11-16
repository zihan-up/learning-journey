#include <header.h>


void func(int num, const char *funname, const char *name){
        printf("%s: %s: %d \n", name, funname, num);
        
}
int main(int argc,char*argv[])
{
    func(__LINE__, __FUNCTION__, __FILE__);



    func(__LINE__, __FUNCTION__, __FILE__);




    printf(": ");
    return 0;
    
}
