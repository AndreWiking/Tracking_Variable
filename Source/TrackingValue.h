
#ifndef TRACKING_VALUE_H
#define TRACKING_VALUE_H

#include <iostream>
#include <string>
#include "WorkFile/LogController.h"

static size_t IdCount = 0;

#define UNAR_OPERATOR(opr) TrackingValue<T> operator opr () const { return {opr value}; }

#define BIN_OPERATOR(opr) \
    friend TrackingValue<T> operator opr (const TrackingValue<T> &lhs, const TrackingValue<T> &rhs) { \
        PrintTrackingOperator("[BIN]", BinColor, DotBinColor, #opr, lhs, rhs);                                     \
        return {lhs.value opr rhs.value};                                                             \
    }

#define COMP_OPERATOR(opr) \
    friend bool operator opr (const TrackingValue<T> &lhs, const TrackingValue<T> &rhs) {             \
        PrintTrackingOperator("[BIN]", BinColor, DotBinColor, #opr, lhs, rhs);                                     \
        return lhs.value opr rhs.value;                                                               \
    }

template<typename T>
class TrackingValue {
public:
    static constexpr char ConstructorColor[] = "Blue", CopyColor[] = "DarkRed", MoveColor[] = "DarkGreen",
            OperatorColor[] = "DarkBlue", DestructorColor[] = "FireBrick", BinColor[] = "DarkGoldenrod";

    static constexpr char NormColor[] = "Black", NameColor[] = "CadetBlue", ValueColor[] = "DarkOliveGreen",
            DotDestructorColor[] = "#FFDED7", DotMoveColor[] = "#03C500", DotCopyColor[] = "#FF6E50",
            DotBinColor[] = "Yellow", DotConstructorColor[] = "darkcyan";


    ~TrackingValue();

    TrackingValue(T value = 0, const std::string &_name = "");

    TrackingValue(const TrackingValue &source, const std::string &_name = "");


    TrackingValue &operator=(const TrackingValue<T> &rhs) {
        PrintTrackingOperator("[COPY]", CopyColor, DotCopyColor, "=", *this, rhs);
        ++CopyCount;
        if (this != &rhs) {
            value = rhs.value;
        }
        return *this;
    }

#ifdef MOVE_OPTIMIZATION

    TrackingValue &operator=(TrackingValue<T> &&rhs) noexcept {
        ++MoveCount;
        PrintTrackingOperator("[MOVE]", MoveColor, DotMoveColor, "=", *this, rhs);

        value = std::exchange(rhs.value, 0);
        return *this;
    }

    TrackingValue(TrackingValue &&source, const std::string &_name = "") noexcept: value(std::exchange(source.value, 0)),
                                                                                   name(_name), id(IdCount++) {
        ++MoveCount;
        WorkTmp();
        Log_Controller->NewLine();
        Log_Controller->PrintText("[MOVE] ", MoveColor, true);
        Log_Controller->PrintText("Constructor ", ConstructorColor);
        PrintTrackingValue(*this);
        Log_Controller->PrintText(" form ", ConstructorColor);
        PrintTrackingValue(source);

        TrackingValue<T>::Log_Controller->dot_controller.AddConstructor("Move Constructor", DotMoveColor,
                                                                        name, id, hex_to_string((unsigned long long) (this)),
                                                                        value,
                                                                        source.name, source.id,
                                                                        hex_to_string((unsigned long long) (&source)),
                                                                        source.value);
    }

#endif

    UNAR_OPERATOR(-)
    UNAR_OPERATOR(+)

    BIN_OPERATOR(+)
    BIN_OPERATOR(-)
    BIN_OPERATOR(*)
    BIN_OPERATOR(/)
    BIN_OPERATOR(%)

    COMP_OPERATOR(<)
    COMP_OPERATOR(>)
    COMP_OPERATOR(<=)
    COMP_OPERATOR(>=)
    COMP_OPERATOR(==)
    COMP_OPERATOR(!=)

    static LogController *Log_Controller;
    T value = 0;
    std::string name = "?";
    size_t id = 0;
private:

    void WorkTmp() {
        if (name.empty())
            name = "tmp_" + std::to_string(++TmpCount);
    }
};

template<typename T>
TrackingValue<T>::~TrackingValue() {
    Log_Controller->NewLine();
    Log_Controller->PrintText("Destructor ", DestructorColor);
    PrintTrackingValue(*this);
    TrackingValue<T>::Log_Controller->dot_controller.AddOperation("Destructor", DotDestructorColor,
                                                                  name, id, hex_to_string((unsigned long long) (this)),
                                                                  value);
}

template<typename T>
TrackingValue<T>::TrackingValue(T value, const std::string &_name) : value(value), name(_name), id(IdCount++) {
    WorkTmp();
    Log_Controller->NewLine();
    Log_Controller->PrintText("Constructor ", ConstructorColor);
    PrintTrackingValue(*this);
    TrackingValue<T>::Log_Controller->dot_controller.AddConstructor("Constructor", DotConstructorColor,
                                                                    name, id, hex_to_string((unsigned long long) (this)),
                                                                    value);
}

template<typename T>
TrackingValue<T>::TrackingValue(const TrackingValue &source, const std::string &_name) : value(source.value), name(_name), id(IdCount++) {
    WorkTmp();
    ++CopyCount;
    Log_Controller->NewLine();
    Log_Controller->PrintText("[COPY] ", CopyColor, true);
    Log_Controller->PrintText("Constructor ", ConstructorColor);
    PrintTrackingValue(*this);
    Log_Controller->PrintText(" form ", ConstructorColor);
    PrintTrackingValue(source);

    TrackingValue<T>::Log_Controller->dot_controller.AddConstructor("Copy Constructor", DotCopyColor,
                                                                    name, id, hex_to_string((unsigned long long) (this)),
                                                                    value,
                                                                    source.name, source.id,
                                                                    hex_to_string((unsigned long long) (&source)),
                                                                    source.value);
}

typedef TrackingValue<int> TrackingInt;

template<typename T>
void PrintTrackingValue(const TrackingValue<T> &val);

template<typename T>
void PrintTrackingOperator(const std::string &type, const char type_color[], const std::string &_operator,
                           const TrackingValue<T> &val1,
                           const TrackingValue<T> &val2);

template<typename T>
void PrintTrackingArray(TrackingValue<T> *array, size_t size);

template<typename T>
void PrintTrackingValue(const TrackingValue<T> &val) {
    TrackingValue<T>::Log_Controller->PrintText(val.name, val.NameColor);
    TrackingValue<T>::Log_Controller->PrintText(
            "[#" + std::to_string(val.id) + "](0x" + hex_to_string((unsigned long long) (&val)) + ")", val.NormColor);

    TrackingValue<T>::Log_Controller->PrintText("&lt;value=" + std::to_string(val.value) + "&gt;", TrackingValue<T>::ValueColor);

}

template<typename T>
void PrintTrackingOperator(const std::string &type, const char type_color[], const char dot_color[], const std::string &_operator,
                           const TrackingValue<T> &val1,
                           const TrackingValue<T> &val2) {
    TrackingValue<T>::Log_Controller->NewLine();
    TrackingValue<T>::Log_Controller->PrintText(type + " ", type_color, true);
    PrintTrackingValue(val1);
    TrackingValue<T>::Log_Controller->PrintText(" " + _operator + " ", TrackingValue<T>::OperatorColor);
    PrintTrackingValue(val2);

    TrackingValue<T>::Log_Controller->dot_controller.AddOperation(type + " " + _operator, dot_color,
                                                                  val1.name, val1.id, hex_to_string((unsigned long long) (&val1)),
                                                                  val1.value,
                                                                  val2.name, val2.id, hex_to_string((unsigned long long) (&val2)),
                                                                  val2.value);
}

template<typename T>
void PrintTrackingArray(TrackingValue<T> *array, size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << array[i].value << ' ';
    std::cout << '\n';
}

#endif
