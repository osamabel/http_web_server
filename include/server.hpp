/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:29:55 by obelkhad          #+#    #+#             */
/*   Updated: 2023/03/01 09:36:09 by obelkhad         ###   ########.fr       */
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

class Location
{
private:
	std::map<std::string, std::vector<std::string> >		__attributes;
public:
	Location();
	~Location();
};

class Server
{
public:
	std::vector<Location>									__locations;
	std::map<std::string, std::vector<std::string> >		__attributes;

	bool													__index_default;
	bool													__listen_default;
	bool													__autoindex_default;
	bool													__client_body_max_size_default;
	Server();
	~Server();
	
};

class Web
{
private:
	typedef void (Web::*handler)(Server&, std::vector<std::string>&);
	std::map<std::string, handler>												__handlers;
	typedef std::vector<std::string>::iterator									__v_iterator;
	typedef std::map<std::string, std::vector<std::string> >::iterator			__m_iterator;
	std::vector<Server>	 														__servers;			//array of servers
	std::vector<std::string> 													__line_splited;
	std::ifstream																__file;
	bool																		__curly_server;
	bool																		__curly_location;


	void __server(Server &__server, std::vector<std::string> &__values);
	void __listen(Server &__server, std::vector<std::string> &__values);
	void __location(Server &__server, std::vector<std::string> &__values);
	void __server_name(Server &__server, std::vector<std::string> &__values);
	void __cgi(Server &__server, std::vector<std::string> &__values);
	void __root(Server &__server, std::vector<std::string> &__values);
	void __index(Server &__server, std::vector<std::string> &__values);
	void __redirect(Server &__server, std::vector<std::string> &__values);
	void __autoindex(Server &__server, std::vector<std::string> &__values);
	void __error_page(Server &__server, std::vector<std::string> &__values);
	void __upload_dir(Server &__server, std::vector<std::string> &__values);
	void __methods(Server &__server, std::vector<std::string> &__values);
	void __client_body_max_size(Server &__server, std::vector<std::string> &__values);


	
public:
	Web();
	void __parse(std::string &__config_path);
	std::vector<std::string> __parse_listen_args(std::vector<std::string> &args);

	~Web();
};

 