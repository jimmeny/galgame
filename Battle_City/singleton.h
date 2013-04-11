#ifndef SINGLETON_H_
#define SINGLETON_H_

template<class T>
class Singleton
{
public:
    static T& Instance();
protected:
    Singleton(){}
    virtual ~Singleton() {}	
private:
    Singleton(const Singleton&);
    Singleton& operator= (const Singleton&);
};


template<class T>
T& Singleton<T>::Instance()
{
    static T instance;
    return instance;
}

#endif