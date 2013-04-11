#ifndef SINGLETON_H_
#define SINGLETON_H_

template<class T>
class singleton
{
public:
    static T& Instance();
protected:
    singleton(){}
    virtual ~singleton() {}	
private:
    singleton(const singleton&);
    singleton& operator= (const singleton&);
};


template<class T>
T& singleton<T>::Instance()
{
    static T instance_;
    return instance_;
}

#endif