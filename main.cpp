/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:47:12 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/27 20:08:31 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/server.hpp"
#include "include/utils.hpp"

std::string __config_file(int ac, char **av)
{
	if (ac == 1)
		return ("config/default.conf");
	else if (ac > 2)
	{
        std::cerr << "error: bad number of arguments!." << std::endl;
        exit(1);
    }
	else
	{
		if (std::string(av[1]).find(".conf") == std::string::npos)
		{
			std::cerr << "error: bad cofig file extension!." << std::endl;
			exit(1);
		}
		return (av[1]);
	}
}

int main(int ac, char **av)
{
	// parse config file;
	try
	{
		std::string __config = __config_file(ac, av);
		
		Web servers;

		servers.__parse(__config);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
    return 0;
}
