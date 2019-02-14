#pragma once 

#include<iostream>
using namespace std;

template <class T>
class ObjectPool
{
  struct BlockNode
  {
     void * _memory;  // 指向一块内存
     BlockNode* _next; //指向下一个结点
     size_t _objectnum; // 内存中对象的个数
     
     BlockNode(size_t objectnum)
       :_next(NULL)
        ,_objectnum(objectnum)
    {
       _memory = malloc(objectnum*SingleObjNum);
    }
  ~BlockNode()
  {
    free(_memory);
    _memory = NULL;
    _next = NULL;
    _objectnum = 0;
  }

  };
  protected:
   static size_t SingleObjNum; // 单个对象的大小
   BlockNode *_start; // 内存链表的初始位置
   BlockNode * _end; // 内存链表的尾部位置
   size_t _cout ;// 内存链表结点的个数
};

int main()
{
  return 0;
}
