#include <string>

namespace miniCSemanticAnalyzer
{
    class SemanticError : public std::exception
    {
    private:
        std::string message;

    public:
        SemanticError(std::string msg) : message(msg) {}
        const char *what() const throw()
        {
            return message.c_str();
        }
    };
}
