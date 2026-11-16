#include <header.h>

int main(int argc, char *argv[argc]){

    //int nums[5]= {1,2,3,4,5};

    int sum = 0;
    for(int i=0; i< 100; i++){

        if(i%2 == 0){
            sum +=i;
        }
    }

    printf("sum: %d \n", sum);



    return 0;
}

