
//#define MOVE_OPTIMIZATION

#include "TrackingValue.h"
#include "WorkFile/FunctionPrinter.h"

template<typename T>
LogController *TrackingValue<T>::Log_Controller;

#define FUNCTION_TMP FunctionPrinter fnc(TrackingInt::Log_Controller, __PRETTY_FUNCTION__);
#define VAR(type, name, value) TrackingValue<type> name(value, #name)


TrackingInt NRVO(){
    FUNCTION_TMP
    VAR(int, nrvo, 10);
    return nrvo;
}

void Test1(){
    FUNCTION_TMP
    VAR(int, a, 0);
    a = NRVO();
}

TrackingInt NoNRVO(TrackingInt val){
    FUNCTION_TMP
    return val;
}

void Test2(){
    FUNCTION_TMP
    VAR(int, a, 0);
    VAR(int, c, 2);
    c = NoNRVO(a);
}

TrackingInt Sum(TrackingInt &val1, TrackingInt &val2, TrackingInt &val3){
    FUNCTION_TMP
    VAR(int, res, val1 + val2 + val3);
    return res;
}

TrackingInt GetVal(){
    FUNCTION_TMP
    VAR(int, val, 10);
    return val;
}

void Test3(){
    FUNCTION_TMP
    VAR(int, a, 1);
    VAR(int, b, 2);
    VAR(int, c, GetVal());
    VAR(int, d, Sum(a, b, c));
    a = b * GetVal();
}

TrackingInt Sum2(TrackingInt &val1, TrackingInt &val2){
    FUNCTION_TMP
    VAR(int, res, val1 + val2);
    return res;
}

void Test4(){
    FUNCTION_TMP
    VAR(int, a, 0);
    VAR(int, b, 0);
    VAR(int, c, Sum2(a, b));
}

int main(){
    LogController log_controller = {};
    TrackingInt::Log_Controller = &log_controller;
    FUNCTION_TMP
    Test2();
    return 0;
}

