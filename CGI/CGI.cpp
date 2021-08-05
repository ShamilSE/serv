#include "CGI.hpp"

CGI::CGI(Request& request): request(request) {}

// void CGI::setEnv() {
//     this->_env["REDIRECT_STATUS"] = "200"; //Security needed to execute php-cgi
// 	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
// 	// this->_env["SCRIPT_NAME"] = config.getPath();
// 	this->_env["SCRIPT_FILENAME"] = config.getPath();
// 	this->_env["REQUEST_METHOD"] = request.getMethod();
// 	this->_env["CONTENT_LENGTH"] = to_string(this->_body.length());
// 	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
// 	this->_env["PATH_INFO"] = request.getPath(); //might need some change, using config path/contentLocation
// 	this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
// 	this->_env["QUERY_STRING"] = request.getQuery();
// 	this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
// 	this->_env["REMOTE_IDENT"] = headers["Authorization"];
// 	this->_env["REMOTE_USER"] = headers["Authorization"];
// 	this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();
// 	if (headers.find("Hostname") != headers.end())
// 		this->_env["SERVER_NAME"] = headers["Hostname"];
// 	else
// 		this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
// 	this->_env["SERVER_PORT"] = to_string(config.getHostPort().port);
// 	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
// 	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

// }

void CGI::execute() {
    std::cout << "execve" << std::endl;
}
