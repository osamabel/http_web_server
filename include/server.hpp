/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:29:55 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/26 19:05:21 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>

// "listen"
// "server_name"
// "cgi"
// "root"
// "index"
// "redirect"
// "autoindex"
// "error_page"
// "upload_dir"
// "accepted_methods"
// "client_body_max_size"
// class Server
// {
// private:
// 	int __id;
// 	std::map<std::string, std::vector<std::string> > 	__config;
// public:
// 	Server(std::string &)
// 	{
// 	}
// 	void __parse(std::string);
// 	void __listen(std::string);
// 	void __server_name(std::string);
// 	void __cgi(std::string);
// 	void __root(std::string);
// 	void __index(std::string);
// 	void __redirect(std::string);
// 	void __autoindex(std::string);
// 	void __error_page(std::string);
// 	void __upload_dir(std::string);
// 	void __accepted_methods(std::string);
// 	void __client_body_max_size(std::string);
	
// 	~Server();
// };

class Web
{
private:
	// std::vector<Server>	 		__servs;					//array of servers
	std::ifstream				__file;
	std::string					__config_path;
public:
	Web(std::string &__config);
	~Web();
	void __parse();
	std::string __extract_parameters(std::string &old);
};