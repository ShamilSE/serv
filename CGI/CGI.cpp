#include "CGI.hpp"

CGI::CGI(std::string exepath): exepath(exepath) {}

void CGI::execute() {
    char args[2][5] = {"ls", "-la"};
    execve("ls", args, NULL);
}
