#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

#include <cstddef>
#include <iostream>
class Person
{
public:
    explicit Person(size_t id=0) : m_id(id) {}
    bool operator==(const Person& other) {return m_id==other.m_id;}
    bool operator!=(const Person& other) {return m_id!=other.m_id;}
    void speak() {std::cout<<m_id<<" person speaks"<<std::endl;}

private:
    size_t m_id;
};

class Student : public Person
{
public:
    explicit Student(char g='a') : m_grade(g) {}
private:
    char m_grade;
};

template <typename T>
class SmartPtr
{
public:
    explicit SmartPtr(T* ptr) : m_ptr(ptr) {}
    SmartPtr(const SmartPtr& other) {m_ptr=other.m_ptr;}
    T* operator->() {return m_ptr;}
    T& operator*() {return *m_ptr;}
    ~SmartPtr() {delete m_ptr; }

private:
    T* m_ptr;
};

template <typename T>
class UniquePtr : public SmartPtr<T>
{
public:
    explicit UniquePtr(T* ptr) : SmartPtr<T>(ptr) {}
private:
    UniquePtr(const UniquePtr& other) {}
    UniquePtr&operator=(const UniquePtr& other) {return *this; }
};

template <typename  T>
class SharedPtr
{
public:
    explicit SharedPtr(T* ptr = NULL);
    ~SharedPtr();

    template <typename U>
    SharedPtr(const SharedPtr<U>&);
    SharedPtr(const SharedPtr<T>&);

    template <typename U>
    SharedPtr& operator=(const SharedPtr<U>& other);
    SharedPtr& operator=(const SharedPtr<T>& other);

    T* operator->() {return m_ptr;}
    T& operator*() {return *m_ptr;}

    bool operator!() const;
    operator bool()const;
    size_t* getCount()const {return m_count;}
    T* getPtr()const {return m_ptr;}

private:
    void delete_or_decrease();
    T* m_ptr;
    size_t* m_count;
};

template <typename  T>
inline SharedPtr<T>::~SharedPtr() {
    delete_or_decrease();
}
template<typename T>
inline SharedPtr<T>::SharedPtr(T *ptr) : m_ptr(ptr), m_count(new size_t(1)) {}

template<typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T> & other):
        m_ptr(other.m_ptr), m_count(other.m_count){
    (*m_count)++;
}


template<typename T>
template <typename U>
inline SharedPtr<T>::SharedPtr(const SharedPtr<U> & other):
    m_ptr(other.getPtr()), m_count(other.getCount()){
    (*m_count)++;
}

template<typename T>
inline void SharedPtr<T>::delete_or_decrease()
{
    if(*m_count > 1)
        (*m_count)--;
    else
    {
        delete m_count;
        delete m_ptr;
    }
}

template <typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &other) {
    if (*this != other)
    {
        delete_or_decrease();
        m_count = other.getCount();
        m_ptr = other.getPtr();
        (*m_count)++;
    }
    return *this;
}

template <typename T>
template <typename U>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U> &other) {
    if (*this != other)
    {
        delete_or_decrease();
        m_count = other.getCount();
        m_ptr = other.getPtr();
        (*m_count)++;
    }
    return *this;
}

template<typename T, typename U>
bool operator==(const SharedPtr<T>& sp1, const SharedPtr<U>& sp2)
{
    return sp1.getPtr() == sp2.getPtr();
}

template<typename T,typename U>
bool operator!=(const SharedPtr<T>& sp1, const SharedPtr<U>& sp2)
{
    return !(sp1.getPtr() == sp2.getPtr());
}

template<typename T>
bool SharedPtr<T>::operator!() const {
    return (m_ptr == NULL);
}

template<typename T>
inline SharedPtr<T>::operator bool() const{
    return m_ptr!=NULL;
}

#endif //__SHAREDPTR_H__