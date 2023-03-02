/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:26:56 by obelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 21:56:15 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include "../include/server.hpp"
#include "../include/utils.hpp"
#include "../include/errors.hpp"
#include "../include/default.hpp"

Location::Location()
{
	/*i feel like i need to put somthing here i don't know yet XD*/
}

Location::~Location()
{
	/*probably i'll need to free some containers*/
}

Server::Server() : 
__curly_location(false),
__curly_server(false),
__index_default(true),
__listen_default(true), 
__server_name_default(true),
__methods_default(true),
__root_default(true), 
__autoindex_default(true),
__client_body_max_size_default(true)
{
	/*i feel like i need to put somthing here i don't know yet XD*/
	std::vector<std::string>	__default;

	/*LISTEN DEFAULT*/
	__default.push_back((std::string(ADDRESS).append(":")).append(PORT));
	__attributes["listen"] = __default;
	__default.clear();

	/*AUTOINDEX DEFAULT*/
	__default.push_back(std::string(AUTOINDEX));
	__attributes["autoindex"] = __default;
	__default.clear();

	/*INDEX DEFAULT*/
	__default.push_back(std::string(INDEX));
	__attributes["index"] = __default;
	__default.clear();

	/*ROOT DEFAULT*/
	__default.push_back(std::string(ROOT));
	__attributes["root"] = __default;
	__default.clear();

	/*CLIENT_BODY_MAX_SIZE DEFAULT*/
	__default.push_back(std::string(CLIENT_BODY_MAX_SIZE));
	__attributes["client_body_max_size"] = __default;
	__default.clear();

	/*SERVER NAME*/
	__default.push_back(std::string(SEVER_NAME));
	__attributes["server_name"] = __default;
	__default.clear();
	
	/*METHODS*/
	__default.push_back(std::string(METHODS));
	__attributes["methods"] = __default;
	__default.clear();
}

Server::~Server()
{
	/*probably i'll need to free some containers*/
	// __attributes.clear();
}

Web::~Web()
{
	/*probably i'll need to free some containers*/
}

Web::Web()
{
	/*i feel like i need to put somthing here i don't know yet XD*/
	__handlers["server"] = &Web::__server;
	__handlers["listen"] = &Web::__listen;
	__handlers["location"] = &Web::__location;
	__handlers["server_name"] = &Web::__server_name;
	__handlers["cgi"] = &Web::__cgi;
	__handlers["root"] = &Web::__root;
	__handlers["index"] = &Web::__index;
	__handlers["redirect"] = &Web::__redirect;
	__handlers["autoindex"] = &Web::__autoindex;
	__handlers["error_page"] = &Web::__error_page;
	__handlers["upload_dir"] = &Web::__upload_dir;
	__handlers["methods"] = &Web::__methods;
	__handlers["client_body_max_size"] = &Web::__client_body_max_size;
}

void Web::__initial_action(Server &__server)
{
	/*check syntax*/
	if (!__server.__curly_server)
		__bad_syntax();

	/* erase "atributte key word"*/
	__line_splited.erase(__line_splited.begin());	

	/* handling errors*/
	if (std::find(__line_splited.begin(), __line_splited.end(), ";") == __line_splited.end())
		__semi_colon_missing();
	if (__line_splited.size() == 1)
		__attributes_missing();
}

bool Web::__closed_bracket(Server &__server, Location &__location)
{
	if (__line_splited[0] == "}")
	{
		if (__server.__curly_location)
		{
			__server.__curly_location = false;
			__server.__locations.push_back(__location);
		}
		else if (__server.__curly_server)
		{
			__server.__curly_server = false;
			__servers.push_back(__server);
		}
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 1);
		return true;
	}
	return false;
}


std::vector<std::string> Web::__parse_args()
{
	std::vector<std::string>	__holder;
	
	while (__line_splited.front() != ";")
	{
		__holder.push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}

	/* remove ";" */
	__line_splited.erase(__line_splited.begin());
	return __holder;
}

std::vector<Server> Web::__get_servers()
{ return __servers; }


/* ---------------------------------- PARSE --------------------------------- */
/* ---------------------------------- PARSE --------------------------------- */
/* ---------------------------------- PARSE --------------------------------- */
/* ---------------------------------- PARSE --------------------------------- */
void Web::__parse(std::string &__config_path)
{
	Location								__location;
	Server									__server;
	std::string 							__line;

	__file.open(__config_path);
	__file_fail(__file);
	while (!__file.eof() || !__line_splited.empty())
	{
		if (!__line_splited.empty())
		{
			if (__closed_bracket(__server, __location))
			{
				// __server.~Server();
				// __server = Server();
				continue;
			}
			// std::cout << "[ S: " << __server.__curly_server << " ] | ";
			// std::cout << "[ L: " << __server.__curly_location << " ]" << '\n' <<'\n';
			// __vector_display(__line_splited);
			// __map_display(__server.__attributes);
			if (!__line_splited.empty())
				(this->*__handlers.at(__line_splited[0]))(__server, __location);
		}
		else
		{
			getline(__file, __line);
			__line = __extract_parameters(__line);
			__line_splited = __split_attrubites(__line, "{}; \t\r\v\f");
		}
	}
	__file.close();
}


/* --------------------------------- SERVER --------------------------------- */
/* --------------------------------- SERVER --------------------------------- */
/* --------------------------------- SERVER --------------------------------- */
/* --------------------------------- SERVER --------------------------------- */
void Web::__server(Server &__server, Location &__location)
{(void)__location;
	std::string __line;

	__server.__curly_server = true;
	if (__line_splited.size() == 1)
	{
		getline(__file, __line);
		__line = __extract_parameters(__line);
		__line_splited.clear();
		__line_splited = __split_attrubites(__line, "{}; \t\r\v\f");
		__curly_right_check(__line_splited[0]);
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 1);
	}
	else if (__line_splited.size() > 1)
	{
		__curly_right_check(__line_splited[1]);
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 2);
	}
}

/* -------------------------------- LOCATION -------------------------------- */
/* -------------------------------- LOCATION -------------------------------- */
/* -------------------------------- LOCATION -------------------------------- */
/* -------------------------------- LOCATION -------------------------------- */
void Web::__location(Server &__server, Location &__location)
{(void)__location;
	std::string __line;

	if (__line_splited.size() == 2)
	{
		getline(__file, __line);
		__line = __extract_parameters(__line);
		__line_splited.clear();
		__line_splited = __split_attrubites(__line, "{}; \t\r\v\f");
		__curly_right_check(__line_splited[0]);
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 1);
	}
	else if (__line_splited.size() > 2)
	{
		__curly_right_check(__line_splited[2]);
		__line_splited.erase(__line_splited.begin(), __line_splited.begin() + 3);
	}
	__server.__curly_location = true;
}

/* --------------------------------- LISTEN --------------------------------- */
/* --------------------------------- LISTEN --------------------------------- */
/* --------------------------------- LISTEN --------------------------------- */
/* --------------------------------- LISTEN --------------------------------- */
void Web::__listen(Server &__server, Location &__location)
{(void)__location;
	__m_iterator				__listen = __server.__attributes.find("listen");
	std::vector<std::string>	__values;

	/*CHECK ZONE*/
	if (__server.__curly_location)
		__wrong_location_attribute();

	/*initial action*/
	__initial_action(__server);

	// /*remove default configuration*/
	if (__server.__listen_default)
	{
		__listen->second.clear();
		__server.__listen_default = false;
	}

	/*parse listen args*/
	__values = __parse_listen_args();
	__listen->second.insert(__listen->second.end(), __values.begin(), __values.end());
}

std::vector<std::string> Web::__parse_listen_args()
{
	std::vector<std::string>	__holder;
	
	while (__line_splited.front() != ";")
	{
		/* CHECK IP FORMT*/
		__address_prot_form(__line_splited.front());
	
		__holder.push_back(__line_splited.front());
		
		__line_splited.erase(__line_splited.begin());
	}
	/* remove ";" */
	__line_splited.erase(__line_splited.begin());

	return __holder;
}

/* ------------------------------- SERVER NAME ------------------------------ */
/* ------------------------------- SERVER NAME ------------------------------ */
/* ------------------------------- SERVER NAME ------------------------------ */
/* ------------------------------- SERVER NAME ------------------------------ */
void Web::__server_name(Server &__server, Location &__location)
{(void)__location;
	__m_iterator		__server_name = __server.__attributes.find("server_name");

	/*CHECK ZONE*/
	if (__server.__curly_location)
		__wrong_location_attribute();

	/*initial action*/
	__initial_action(__server);

	// /*remove default configuration*/
	if (__server.__server_name_default)
	{
		__server_name->second.clear();
		__server.__server_name_default = false;
	}

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		__server_name->second.push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());
}

/* --------------------------------- METHODS -------------------------------- */
/* --------------------------------- METHODS -------------------------------- */
/* --------------------------------- METHODS -------------------------------- */
/* --------------------------------- METHODS -------------------------------- */
void Web::__methods(Server &__server, Location &__location)
{
	__m_iterator				__methods;
	std::vector<std::string>	__values;

	/*initial action*/
	__initial_action(__server);
	
	/*extract values*/
	__values = __parse_args();

	/*CHECK LOCATION*/
	if (__server.__curly_location)
		__location.__attributes["methods"].insert(\
		__location.__attributes["methods"].end(), __values.begin(), __values.end());
	else
	{
		__methods = __server.__attributes.find("methods");

		/*remove default configuration*/
		if (__server.__methods_default)
		{
			__methods->second.clear();
			__server.__methods_default = false;
		}

		/*add valuses*/
		__methods->second.insert(__methods->second.end(), __values.begin(), __values.end());
	}
}
/* ----------------------------------- CGI ---------------------------------- */
/* ----------------------------------- CGI ---------------------------------- */
/* ----------------------------------- CGI ---------------------------------- */
/* ----------------------------------- CGI ---------------------------------- */
void Web::__cgi(Server &__server, Location &__location)
{(void)__location;
	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["cgi"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());
}

/* ---------------------------------- ROOT ---------------------------------- */
/* ---------------------------------- ROOT ---------------------------------- */
/* ---------------------------------- ROOT ---------------------------------- */
/* ---------------------------------- ROOT ---------------------------------- */
void Web::__root(Server &__server, Location &__location)
{(void)__location;
	__m_iterator		__root = __server.__attributes.find("root");


	/*remove default configuration*/
	if (__server.__root_default)
	{
		__root->second.clear();
		__server.__root_default = false;
	}

	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["root"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());

	/*check number of args*/
	// if (__server.__attributes["root"].size() != 1)
	// 	__bad_number_arguments();
}

/* ---------------------------------- INDEX --------------------------------- */
/* ---------------------------------- INDEX --------------------------------- */
/* ---------------------------------- INDEX --------------------------------- */
/* ---------------------------------- INDEX --------------------------------- */
void Web::__index(Server &__server, Location &__location)
{(void)__location;
	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["index"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());
}

/* ------------------------------- REDIRECTION ------------------------------ */
/* ------------------------------- REDIRECTION ------------------------------ */
/* ------------------------------- REDIRECTION ------------------------------ */
/* ------------------------------- REDIRECTION ------------------------------ */
void Web::__redirect(Server &__server, Location &__location)
{(void)__location;
	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["redirect"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());
}

/* -------------------------------- AUTOINDEX ------------------------------- */
/* -------------------------------- AUTOINDEX ------------------------------- */
/* -------------------------------- AUTOINDEX ------------------------------- */
/* -------------------------------- AUTOINDEX ------------------------------- */
void Web::__autoindex(Server &__server, Location &__location)
{(void)__location;
	__m_iterator				__autoindex = __server.__attributes.find("autoindex");

	/*remove default configuration*/
	if (__server.__autoindex_default)
	{
		__autoindex->second.clear();
		__server.__autoindex_default = false;
	}

	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["autoindex"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());

	/*check number of args*/
	// if (__server.__attributes["autoindex"].size() != 1)
	// 	__bad_number_arguments();
}

/* ------------------------------- ERROR PAGES ------------------------------ */
/* ------------------------------- ERROR PAGES ------------------------------ */
/* ------------------------------- ERROR PAGES ------------------------------ */
/* ------------------------------- ERROR PAGES ------------------------------ */
void Web::__error_page(Server &__server, Location &__location)
{(void)__location;
	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["error_page"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());
}

/* ------------------------------- UPLOAD DIR ------------------------------- */
/* ------------------------------- UPLOAD DIR ------------------------------- */
/* ------------------------------- UPLOAD DIR ------------------------------- */
/* ------------------------------- UPLOAD DIR ------------------------------- */
void Web::__upload_dir(Server &__server, Location &__location)
{(void)__location;
	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["upload_dir"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());

	/*check number of args*/
	// if (__server.__attributes["upload_dir"].size() != 1)
	// 	__bad_number_arguments();
}


/* ----------------------------- CLIENT MAX SIZE ---------------------------- */
/* ----------------------------- CLIENT MAX SIZE ---------------------------- */
/* ----------------------------- CLIENT MAX SIZE ---------------------------- */
/* ----------------------------- CLIENT MAX SIZE ---------------------------- */
void Web::__client_body_max_size(Server &__server, Location &__location)
{(void)__location;
	__m_iterator				__client_body_max_size = __server.__attributes.find("client_body_max_size");

	/*remove default configuration*/
	if (__server.__client_body_max_size_default)
	{
		__client_body_max_size->second.clear();
		__server.__client_body_max_size_default = false;
	}
	
	/*initial action*/
	__initial_action(__server);

	/*add valuses*/
	while (__line_splited.front() != ";")	
	{
		(__server.__attributes["client_body_max_size"]).push_back(__line_splited.front());
		__line_splited.erase(__line_splited.begin());
	}
	__line_splited.erase(__line_splited.begin());

	/*check number of args*/
	// if (__server.__attributes["client_body_max_size"].size() != 1)
	// 	__bad_number_arguments();
}