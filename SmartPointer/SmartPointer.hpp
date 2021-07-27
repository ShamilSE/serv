#pragma once

template<class T>
class SmartPointer {
private:
    T* _pointer;

public:
    SmartPointer(T* pointer = nullptr): _pointer(pointer) {}
    ~SmartPointer() {delete _pointer;}

    T* getPointer() const {return _pointer;}

    T& operator*() const {return *_pointer;}
    T* operator->() const {return _pointer;}
};