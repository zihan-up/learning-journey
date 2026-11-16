#include <header.h>

// 函数用于计算数组元素的平均值
double compute_average(int *arr, int len) {
    int sum = 0;
    for (int i = 0; i <= len; i++) { // 注意这里有一个错误
        sum += arr[i];
    }
    return sum / (double)len;
}

int main(void) {
    int nums[] = {1, 2, 3, 4, 5};
    int len = sizeof(nums) / sizeof(nums[0]);
    double average = compute_average(nums, len);
    printf("The average is: %f\n", average);

    // 打印5行3列的$图案                                        
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            printf("$");
        }
        printf("\n");
    }
    return 0;
}

