/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:26:56 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/27 20:30:37 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/utils.hpp"

Server::Server()
{
	/*i feel like i need to put somthing here i don't know yet XD*/
}

Server::~Server()
{
	/*probably i'll need to free some containers*/
}

Web::~Web()
{
	/*probably i'll need to free some containers*/
}

Web::Web() : __curly_server(false), __curly_location(false)
{
	/*i feel like i need to put somthing here i don't know yet XD*/
	__handlers["server"] = &Web::__server;
	__handlers["listen"] = &Web::__listen;
	__handlers["location"] = &Web::__location;
	__handlers["server_name"] = &Web::__server_name;
	__handlers["root"] = &Web::__root;
	__handlers["index"] = &Web::__index;
	__handlers["redirect"] = &Web::__redirect;
	__handlers["autoindex"] = &Web::__autoindex;
	__handlers["error_page"] = &Web::__error_page;
	__handlers["upload_dir"] = &Web::__upload_dir;
	__handlers["methods"] = &Web::__methods;
	__handlers["client_body_max_size"] = &Web::__client_body_max_size;
}

void Web::__parse(std::string &__config_path)
{
	std::string line;

	__file.open(__config_path);
	if (__file.fail())
	{
		std::cerr << "error: Fail to opean configuration file!." << std::endl;
		exit(1);
	}
	while (!__file.eof())
	{
		if (!__line_splited.empty())
		{
			(this->*__handlers.at(__line_splited[0]))();
			continue;
		}
		else
		{
			getline(__file, line);
			line = __extract_parameters(line);
			__line_splited = __split_attrubites(line, "{}; \t\r\v\f");
		}
	}
	__file.close();
}

void Web::__server()
{
	std::string line;

	__vector_display(__line_splited);
	if (__line_splited.size() == 1)
	{
		getline(__file, line);
		line = __extract_parameters(line);
		__line_splited.clear();
		__line_splited = __split_attrubites(line, "{}; \t\r\v\f");
		//TODO: handline "{, }"
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 1);
	}
	else if (__line_splited.size() > 1)
	{
		if (__line_splited[1] != "{")
		{
			std::cerr << "error: Curly Bracket missing!." << std::endl;
			exit(1);
		}
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 2);
		__curly_server = true;
	}
}

void Web::__listen()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}

void Web::__location()
{
	std::string line;

	__location_zone = true;
	__vector_display(__line_splited);
	if (__line_splited.size() > 3)
	{
		std::cerr << "error: location syntax!." << std::endl;
		exit(1);
	}
	else
	{
		//TODO:save __line_splited[1] (path of location)
		if (__line_splited.size() == 3)
		{
			if (__line_splited[2] != "{")
			{
				std::cerr << "error: Curly Bracket missing!." << std::endl;
				exit(1);
			}
			__curly_location = true;
		}
		__line_splited.clear();
	}
}

void Web::__server_name()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__cgi()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__root()
{
		__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__index()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__redirect()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__autoindex()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__error_page()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__upload_dir()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__methods()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}
void Web::__client_body_max_size()
{
	__vector_display(__line_splited);
	__line_splited.clear();
}