#include <iostream>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define MAXSIZE 30

typedef int datatype;
typedef int status;

struct Seqlist
{
    datatype* elem;
    int length;
};

status ListInit(Seqlist *ptr)
{
    ptr->elem = new datatype[MAXSIZE];
    if(!ptr->elem)
        return ERROR;
    ptr -> length = 0;
    return OK;
}

status ListInsert(Seqlist *ptr,int pos,datatype element)
{
    if(ptr->length == MAXSIZE || pos < 1 || pos > ptr->length+1)
        return ERROR;
    if(pos < ptr->length+1)
        for(int temp = ptr->length-1;temp >= pos-1;temp--)
            ptr->elem[temp+1] = ptr->elem[temp];
    ptr->elem[pos-1] = element;
    ptr->length++;
    return OK;
}

status ListDelete(Seqlist *ptr,int pos)
{
    if(ptr->length == 0 || pos < 1 || pos > ptr->length)
        return ERROR;
    if(pos < ptr->length)
        for(int temp = pos;temp < ptr->length;temp++)
            ptr->elem[temp-1] = ptr->elem[temp];
    ptr->length--;
    return OK;
}

status ListGet(Seqlist *ptr,int pos,datatype *get)
{
    if(ptr->length == 0 || pos < 1 || pos > ptr->length+1)
        return ERROR;
    *get = ptr->elem[pos-1];
    return OK;
}

void Output(Seqlist seq)
{
    std::cout << seq.length << std::endl;
    for(int temp = 0;temp < seq.length;temp++)
        std::cout << seq.elem[temp] << " ";
    std::cout << std::endl;
}