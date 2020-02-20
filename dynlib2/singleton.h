#pragma once

class Singleton {
public:
    static Singleton& GetInstance(void);
public:
    ~Singleton() {}
    int Do(void);
private:
    Singleton() {};
    Singleton(const Singleton&);
    Singleton& operator =(const Singleton&);
};

