#include "CGI.hpp"

CGI::CGI(Request& request, Configuration* config): request(request), serverConfiguration(config) {
    initEnv();
    _char_env = mapToCharArray(_env, "=");
}

void CGI::setEnv(std::string key, std::string value) {_env[key] = value;}

void CGI::initEnv() {
	setEnv("GATEWAY_INTERFACE", "CGI/1.1");
	// this->_env["SCRIPT_NAME"] = config.getPath();
	// this->_env["SCRIPT_FILENAME"] = config.getScriptPath();
	setEnv("REQUEST_METHOD", request.getMethod());
	setEnv("CONTENT_LENGTH", request.getHeaderByKey("Content-Length"));
	setEnv("CONTENT_TYPE", request.getHeaderByKey("Content-Type"));
	// this->_env["PATH_INFO"] = request.getPath(); //might need some change, using config path/contentLocation
	// this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
	setEnv("QUERY_STRING", request.getPath());
	// this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
    setEnv("SERVER_NAME", request.getClientServerName());
	setEnv("SERVER_PORT", request.getClientServerPort());
	setEnv("SERVER_PROTOCOL", request.getProtocolV());
	setEnv("SERVER_SOFTWARE", "webserv");
}

void CGI::freeCharEnv() {
    for (size_t index = 0; _char_env[index]; index++) {
        delete (_char_env[index]);
    }
    delete [] (_char_env);
}

void CGI::execute() {
    // 1 fd is to std out
    // 0 fd is to std in
    int save_stdout = dup(1);
    if (save_stdout == -1) {
        perror("dup");
        exit(1);
    }

    // if (dup2(_fd, STDERR_FILENO) == -1) {
    //     perror("dup2(1)");
    //     exit(1);
    // }

    int child, status;
    if ((child = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    else if (child == 0) {
        // child proccess
        if (execve("helloworld", NULL, _char_env) == -1) {
            perror("execve");
            exit(1);
        }
        std::cout << "execve" << std::endl;
    }
    // parent proccess
    waitpid(child, &status, 0);
    if (dup2(save_stdout, 1) == -1) {
        perror("dup2(2)");
        exit(1);
    }
    freeCharEnv();
}
