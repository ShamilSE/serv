#include "CGI.hpp"

CGI::CGI(Request& request): request(request) {
    setEnv();
    _char_env = mapToCharArray(_env);
}

void CGI::setEnv() {
    // this->_env["REDIRECT_STATUS"] = "200"; //Security needed to execute php-cgi
	// this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	// this->_env["SCRIPT_NAME"] = config.getPath();
	// this->_env["SCRIPT_FILENAME"] = config.getPath();
	this->_env["REQUEST_METHOD"] = request.getMethod();
	this->_env["CONTENT_LENGTH"] = request.getHeaderByKey("Content-Length");
	this->_env["CONTENT_TYPE"] = request.headers["Content-Type"];
	// this->_env["PATH_INFO"] = request.getPath(); //might need some change, using config path/contentLocation
	// this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
	this->_env["QUERY_STRING"] = request.getPath();
	// this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
    this->_env["SERVER_NAME"] = request.getHeaderByKey("Host").substr(1, request.getHeaderByKey("Host").find(":"));
	// if (headers.find("Hostname") != headers.end())
	// 	this->_env["SERVER_NAME"] = headers["Hostname"];
	// else
		// this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
	// this->_env["SERVER_PORT"] = to_string(config.getHostPort().port);
	this->_env["SERVER_PROTOCOL"] = request.getProtocolV();
	this->_env["SERVER_SOFTWARE"] = "webserv";

}

void CGI::freeCharEnv() {
    for (size_t index = 0; _char_env[index]; index++)
        free(_char_env[index]);
    free(_char_env);
}

void CGI::execute() {
    // 1 fd is to std out
    // 0 fd is to std in
    int save_stdout = dup(1);
    if (save_stdout == -1) {
        perror("dup");
        exit(1);
    }

    if (dup2(_fd, STDERR_FILENO) == -1) {
        perror("dup2(1)");
        exit(1);
    }

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
