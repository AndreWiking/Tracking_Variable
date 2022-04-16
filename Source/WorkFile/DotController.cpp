
#include "DotController.h"

DotController::DotController() : dot_stream(DotName, std::ios::out){
    if (!dot_stream.is_open()){
        std::cerr << "File open failed\n";
    }
    dot_stream << StartDot;

}

DotController::~DotController() {
    dot_stream << EndDot;
    dot_stream.close();
    CompileDot();
}

std::string
DotController::ValueLabel(const std::string &var_name, size_t id, const std::string &hex_address, int value, size_t tag_num) &{

    return "{ <f" + std::to_string(tag_num) + "> " + var_name + " |  #" + std::to_string(id) + " | 0x" + hex_address +
           "  | value = " + std::to_string(value) + "} ";
}

void
DotController::AddConstructor(const std::string &title, const std::string &fillcolor, const std::string &var_name1, size_t id1,
                              const std::string &hex_address1, int value1, const std::string &var_name2, size_t id2,
                              const std::string &hex_address2, int value2) {

    std::string label = title + " | " + ValueLabel(var_name1, id1, hex_address1, value1, 1);
    if (!var_name2.empty()) label += " | " + ValueLabel(var_name2, id2, hex_address2, value2, 2);
    std::string name = NodePreName + std::to_string(++node_id);
    AddNode(name, label, fillcolor, "filled");
    VariableTable.push_back(name + ":f1");
}

void DotController::AddOperation(const std::string &title, const std::string &fillcolor, const std::string &var_name1, size_t id1,
                                 const std::string &hex_address1, int value1, const std::string &var_name2, size_t id2,
                                 const std::string &hex_address2, int value2) {

    std::string label = title + " | " + ValueLabel(var_name1, id1, hex_address1, value1, 1);
    if (!var_name2.empty()) label += " | " + ValueLabel(var_name2, id2, hex_address2, value2, 2);
    std::string name = NodePreName + std::to_string(++node_id);
    AddNode(name, label, fillcolor);

    AddArrow(name + ":f1", VariableTable[id1], "grey", "dashed");
    if (!var_name2.empty()) AddArrow(name + ":f2", VariableTable[id2], "gray", "dashed");
}

void
DotController::AddNode(const std::string &name, const std::string &label, const std::string &fillcolor, const std::string &style) {
    dot_stream << name << "[label=\"" << label << "\" fillcolor = \"" << fillcolor << "\" style = \""
               << style << "\"]\n";
    SaveOrder(name);
}

void DotController::SaveOrder(const std::string &name) {
    if (!last_node.empty())
        AddArrow(last_node, name, "blue", "solid", 100);
    last_node = name;
}

void DotController::AddArrow(const std::string &from, const std::string &to, const std::string &color, const std::string &style,
                             size_t weight) {
    dot_stream << from << " -> " << to << "[ color = " << color << " " << "style = " << style << " " << "weight = " << weight <<  " ];\n";
}
