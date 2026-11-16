#include "computer.h"
void Computer::setBrand(const char * brand){
    strcpy(_brand, brand);
}

void Computer::setPrice(float price){
    _price = price;
}
