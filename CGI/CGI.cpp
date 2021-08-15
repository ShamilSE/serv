#include "CGI.hpp"

CGI::CGI(Request& request, Configuration* config)
: 
    request(request),
    serverConfiguration(config),
    _fd(request.getClientFD())
{
    initEnv();
    _char_env = mapToCharArray(_env, "=");
}

void CGI::setEnv(std::string key, std::string value) {_env[key] = value;}

void CGI::initEnv() {
	setEnv("GATEWAY_INTERFACE", "CGI/1.1");
	// this->_env["SCRIPT_NAME"] = config.getPath();
    // setEnv("SCRIPT_NAME", "/Users/mismene/Desktop/serv/CGI");
	// this->_env["SCRIPT_FILENAME"] = config.getScriptPath();
    // setEnv("SCRIPT_FILENAME", "formHandler");
	setEnv("REQUEST_METHOD", "\"" + request.getMethod() + "\"");
	setEnv("CONTENT_LENGTH", "\"" + request.getHeaderByKey("Content-Length") + "\"");
	setEnv("CONTENT_TYPE", "\"" + request.getHeaderByKey("Content-Type") + "\"");
	// this->_env["PATH_INFO"] = request.getPath(); //might need some change, using config path/contentLocation
    // setEnv("SCRIPT_NAME", "/Users/mismene/Desktop/serv/CGI");
	// this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
    // setEnv("SCRIPT_NAME", "/Users/mismene/Desktop/serv/CGI");
	setEnv("QUERY_STRING", "\"" + request.getPath() + "\"");
	// this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
    // setEnv("REMOTEAddr", 0);
    setEnv("SERVER_NAME", "\"" + request.getClientServerName() + "\"");
	setEnv("SERVER_PORT", "\"" + request.getClientServerPort() + "\"");
	setEnv("SERVER_PROTOCOL", "\"" + request.getProtocolV() + "\"");
	setEnv("SERVER_SOFTWARE", "\"webserv\"");
}

void CGI::freeCharEnv() {
    for (size_t index = 0; _char_env[index]; index++) {
        delete (_char_env[index]);
    }
    delete [] (_char_env);
}

int CGI::execute(std::string binpath) {
    // 1 fd is to std out
    // 0 fd is to std in
    int save_stdout = dup(1);
    if (save_stdout == -1) {
        perror("dup");
        exit(1);
    }

    int child, status;
    if ((child = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    else if (child == 0) {
        if (dup2(_fd, STDOUT_FILENO) == -1) {
            perror("dup2(1)");
            exit(1);
        }
        // child proccess
        if (execve(binpath.c_str(), NULL, _char_env) == -1) {
            perror("execve");
            exit(1);
        }
    }
    // parent proccess
    waitpid(child, &status, 0);
    freeCharEnv();
    return 1;
}
