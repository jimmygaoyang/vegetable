#ifndef SINGLETON_H
#define SINGLETON_H

#include "stm32f10x.h"
 
//////////////////Singleton定义
/**
* @class CSingleton
* @brief 实现类把该类作为友元, 并且把构造函数作为非公有
*         如:
*          Class C
*          {
*          friend class CSingleton<C>;
*          protected:
*              C(){};
*          }
*/
template<class T>
class CSingleton
{
public:
    static T* instance()
    {
        if (!m_pInstance)
        {

            if (!m_pInstance)
            {
                m_pInstance = new T;
            }
        }
        return m_pInstance;
    };
  
protected:
    CSingleton(){}; //防止产生实例
    CSingleton(const CSingleton&){}; //防止拷贝构造另一个实例
//    CSingleton &operator =(const CSingleton&){}; //防止赋值构造出另一个实例
    virtual ~CSingleton()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    };
  
private:
    static T* m_pInstance; //类的唯一实例
};
  
  
//////////////////Singleton实现部分
template<class T> T* CSingleton<T>::m_pInstance = NULL;

#endif
