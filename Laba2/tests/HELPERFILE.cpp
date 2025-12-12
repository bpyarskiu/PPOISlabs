#include <iostream>
#include <string>
#include <sstream>

class StdoutRedirect {
private:
    std::streambuf* oldCoutBuffer;
    std::stringstream newBuffer;

public:
    StdoutRedirect() {
        oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(newBuffer.rdbuf());
    }
    
    ~StdoutRedirect() {
        std::cout.rdbuf(oldCoutBuffer);
    }
    
    std::string getOutput() const {
        return newBuffer.str();
    }
};