
#pragma once

template <typename T>
class CSingletonT {
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }

protected:
    CSingletonT() {};
    ~CSingletonT() {};
};
