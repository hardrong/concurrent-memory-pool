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
   size_t _cout ;// 当前节点在用的个数
   T* _lastDelete; // 指向最后一个释放的对象
   size_t _maxcap;  //单个结点的最大容量

   public:
           ObjectPool(size_t num = 62,size_t maxcap = 1000)
              :_cout(0)
               ,_lastDelete(NULL)
               ,_maxcap(1000)

           {
                   _start = _end = new BlockNode(num);
           }
           ~ObjectPool()
           {
             Destory();
           }
           T*New()
           {
             if(_lastDelete)
             {
               T*object = _lastDelete;
               _lastDelete =*((T**)(_lastDelete));
               return new(object) T();
             }
             if(_cout >= _end->_objectnum)
             {
                  size_t size = 2*_cout;
                  if(size > _maxcap)
                  {
                    size = _maxcap;
                  }
                  _end->_next = new BlockNode(size);
                  _end = _end->next;
                  _cout = 0;
             }
             T*object = (T*)((char*)_end->_memory+_cout*SingleObjNum);
             _cout++;
             return new(object) T();

           }
           void Destory()
           {
             BlockNode *cur = _start;
             while(cur != NULL)
             {
               BlockNode *del = cur;
                 cur = cur->next;
                 delete del;
             }
             _start = _end = NULL;
           }
           void Delete(T*object)
           {
             if(object)
             {
               object->~T();
               *((T**)object) = _lastDelete;
               _lastDelete = object;
             }

             }
protected:
           static size_t GetSinglesize()
           {
              if(sizeof(T) > sizeof(T*))
              {
                return sizeof(T);
              }
              else 
              {
                return sizeof(T*);
              }
           }
};
template <class T>
size_t ObjectPool<T>::SingleObjNum = ObjectPool<T>::GetSinglesize();

int main()
{
  return 0;
}
