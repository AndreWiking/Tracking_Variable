
#ifndef DOT_CONTROLLER_H
#define DOT_CONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>


class DotController {
public:
    DotController();
    ~DotController();

    std::string ValueLabel(const std::string &var_name, size_t id, const std::string &hex_address, int value, size_t tag_num) &;

    void AddConstructor(const std::string &title, const std::string &fillcolor,
                        const std::string &var_name1, size_t id1, const std::string &hex_address1, int value1,
                        const std::string &var_name2 = "", size_t id2 = 0, const std::string &hex_address2 = "", int value2 = 0);

    void AddOperation(const std::string &title, const std::string &fillcolor,
                      const std::string &var_name1, size_t id1, const std::string &hex_address1, int value1,
                      const std::string &var_name2 = "", size_t id2 = 0, const std::string &hex_address2 = "", int value2 = 0);

    void AddNode(const std::string &name, const std::string &label, const std::string &fillcolor = "white",
                 const std::string &style = "rounded, filled");

    void SaveOrder(const std::string &name);

    void AddArrow(const std::string &from, const std::string &to, const std::string &color = "black",
                  const std::string &style = "solid", size_t weight = 1);

    static constexpr char ResultDotName[] = "Graph.svg";
private:
    std::fstream dot_stream;
    std::string last_node{};
    size_t node_id = 0;
    std::vector<std::string> VariableTable{};
    static constexpr char DotName[] = "Graph.dot";
    static constexpr char StartDot[] = "digraph G {\n"
                                       "    graph [rankdir = \"HR\"];\n"
                                       "    node [shape=record];\n";

    static constexpr char EndDot[] = "\n}\n";

    static constexpr char VariablePreName[] = "Val_";
    static constexpr char NodePreName[] = "Node_";

    static constexpr char VariableColor[] = "darkcyan";
    static constexpr char InvisibleColor[] = "transparent";

    void CompileDot(){
        int fd_out;
        pid_t proc = fork();
        if (proc == 0) {

            execlp("dot", "dot", "-Tsvg", DotName , "-o", ResultDotName, NULL);

            perror("exec");
            _exit(1);
        } else if (proc == -1) {
            perror("fork");
            _exit(1);
        } else {
            int status = 0;
            waitpid(proc, &status, 0);

            _exit(WEXITSTATUS(status));
        }
    }
};


#endif
