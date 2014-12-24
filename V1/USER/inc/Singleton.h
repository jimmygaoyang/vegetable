#ifndef SINGLETON_H
#define SINGLETON_H

#include "stm32f10x.h"
 
//////////////////Singleton����
/**
* @class CSingleton
* @brief ʵ����Ѹ�����Ϊ��Ԫ, ���Ұѹ��캯����Ϊ�ǹ���
*         ��:
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
    CSingleton(){}; //��ֹ����ʵ��
    CSingleton(const CSingleton&){}; //��ֹ����������һ��ʵ��
    CSingleton &operator =(const CSingleton&){}; //��ֹ��ֵ�������һ��ʵ��
    virtual ~CSingleton()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    };
  
private:
    static T* m_pInstance; //���Ψһʵ��
};
  
  
//////////////////Singletonʵ�ֲ���
template<class T> T* CSingleton<T>::m_pInstance = NULL;

#endif
