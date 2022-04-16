
#ifndef FUNCTION_PRINTER_H
#define FUNCTION_PRINTER_H


#include "LogController.h"

class FunctionPrinter {
public:
    FunctionPrinter(LogController *_log_controller, const char name[]) : log_controller(_log_controller) {
        log_controller->PrintCurFunction(name);
    }
    ~FunctionPrinter(){
        log_controller->EndCurFunction();
    }
private:
    LogController *log_controller;
};


#endif
