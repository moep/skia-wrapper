#include "FooType.h"
#include <stdio.h>

FooType::FooType(int val)
{
//  printf("[C++] FooType(%d)\r\n", val);
  this->mVal = val;
}

FooType::~FooType()
{

}

int
FooType::getVal()
{
//  printf("[C++] getVal()\r\n");
  return this->mVal;
}
