#ifndef COMPUTER_H 
#define COMPUTER_H
#include <string.h>
class Computer{
public:
    void setBrand(const char * brand);
    void setPrice(float price);

private:
    char _brand[20];
    float _price;
};

#endif

