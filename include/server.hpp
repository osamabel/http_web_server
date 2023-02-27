/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:29:55 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/27 18:25:13 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
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


class Server
{
private:
	std::map<std::string, std::vector<std::string> > 	__config;
public:
	Server();
	~Server();
};

class Web
{
private:
	typedef void (Web::*handler)();
	std::map<std::string, handler>		__handlers;
	std::vector<Server>	 				__servers;			//array of servers
	std::vector<std::string> 			__line_splited;
	std::ifstream						__file;
	bool								__curly_server;
	bool								__curly_location;
	bool								__location_zone;

	void __server();
	void __listen();
	void __location();
	void __server_name();
	void __cgi();
	void __root();
	void __index();
	void __redirect();
	void __autoindex();
	void __error_page();
	void __upload_dir();
	void __methods();
	void __client_body_max_size();
public:
	Web();
	void __parse(std::string &__config_path);

	~Web();
};

