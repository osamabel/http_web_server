/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:26:56 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/26 19:27:38 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

Web::~Web()
{}

Web::Web(std::string &__config) : __config_path(__config)
{}

std::string Web::__extract_parameters(std::string &old)
{
	int pos = old.find('#');
	old = old.substr(0, pos);



	return old;
}

void Web::__parse()
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
		std::getline(__file, line);
		line = __extract_parameters(line);
		std::cout << line << std::endl;
	}

	__file.close();
}