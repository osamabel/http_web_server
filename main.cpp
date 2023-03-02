/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:47:12 by obelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 18:35:24 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/server.hpp"
#include "include/utils.hpp"
#include "include/errors.hpp"

int main(int ac, char **av)
{
	// parse config file;
	Web servers;
	try
	{
		std::string __config = __config_file(ac, av);

		servers.__parse(__config);
		
		__map_display(servers.__servers[1].__attributes);
		std::cout << "\033[1;34m" << servers.__get_servers().size() << "\033[0m" << '\n';
		// std::cout << "\033[1;34m" << servers.__get_servers().size() << "\033[0m" << '\n';
	}
	catch(const std::exception& e)
	{
		// std::cout << "\033[1;34m" << servers.__get_servers().size() << "\033[0m" << '\n';
		std::cerr << "\033[1;31m" << "error: bad synatx" << "\033[0m" << '\n';
	}

	
	
    return 0;
}
