
#ifndef LOG_CONTROLLER_H
#define LOG_CONTROLLER_H

#include <iostream>
#include <fstream>
#include "DotController.h"

static size_t CopyCount = 0;
static size_t MoveCount = 0;
static size_t TmpCount = 0;

std::string hex_to_string(unsigned long long val);

class LogController {
public:
    LogController() : log_stream(LogName, std::ios::out) {
        if (!log_stream.is_open()){
            std::cerr << "File open failed\n";
        }
        log_stream << StartHtml;
        AddImage(CodeImagePath);
        AddImage(DotController::ResultDotName, 50);

    }
    ~LogController() {
        NewLine();NewLine();
        PrintText("Copy count = " + std::to_string(CopyCount) + "<br>", StatisticColor);
        PrintText("Move count = " + std::to_string(MoveCount) + "<br>", StatisticColor);
        PrintText("Temporary objects count = " + std::to_string(TmpCount), StatisticColor);
        log_stream << EndHtml;
        log_stream.close();
    }

    std::fstream& GetSteam(){
        return log_stream;
    }

    void NewLine(){
        log_stream << "\n";
        PrintOffset();
    }

    void PrintText(const std::string &text, const char color[]){
        log_stream << "<font color = " << color <<  ">" << text << "</font>";
    }
    void PrintText(const std::string &text, const char color[], bool isBold){
        if (isBold) {
            log_stream << "<b>";
            PrintText(text, color);
            log_stream << "</b>";
        }
        else PrintText(text, color);
    }

    void PrintComments(const std::string &text){
        NewLine();
        PrintText(text, CommentsColor);
    }

    void AddImage(const std::string &path, size_t width = 50){
        log_stream << "<img src=\"" + path + "\" width=\"" << std::to_string(width) << "%\" alt=\"source code\">\n";
    }

    void PrintCurFunction(const char name[]){
        log_stream << "<br>\n";
        PrintOffset();
        log_stream <<  name << " {";
        ++cur_offset;
    }
    void EndCurFunction(){
        log_stream << "\n";
        --cur_offset;
        PrintOffset();
        log_stream << "}";
    }

    DotController dot_controller{};
private:
    std::fstream log_stream;
    int cur_offset = 0;

    void PrintOffset(){
        for (int i = 0; i < cur_offset; ++i)
            log_stream << '\t';
    }

    static constexpr char StatisticColor[] = "DimGray";
    static constexpr char CommentsColor[] = "Green";

    static constexpr char CodeImagePath[] = "Code.png";
    static constexpr char LogName[] = "Log.html";
    static constexpr char StartHtml[] = "<style type=\"text/css\">\n"
                                        "    .main {\n"
                                        "        font-size: 20px;\n"
                                        "        color: Black;\n"
                                        "        line-height: 2.1;\n"
                                        "        tab-size: 4;\n"
                                        "    }\n"
                                        "   img { border: 3px dashed #E5E7E9; }\n"
                                        "</style>\n"
                                        "<pre>\n"
                                        "    <div class = \"main\">\n";
    static constexpr char EndHtml[] = "\n\t</div>\n</pre>";

};

#endif
