/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:16:26 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/28 16:49:37 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/errors.hpp"

void __curly_right_check(std::string __curly)
{
	if (__curly != "{")
	{
		std::cerr << "error: Curly Bracket missing!." << std::endl;
		exit(1);
	}
}

void __file_fail(std::ifstream	&__file)
{
	if (__file.fail())
	{
		std::cerr << "error: Fail to opean configuration file!." << std::endl;
		exit(1);
	}
}

void __bad_number_arguments()
{
    std::cerr << "error: bad number of arguments!." << std::endl;
    exit(1);
}

void __extention_is_good(std::string str)
{
	if (str.find(".conf") == std::string::npos)
	{
		std::cerr << "error: bad config file extension!." << std::endl;
		exit(1);
	}
}

void __semi_colon_missing()
{
	std::cerr << "error: semi colon missing!." << std::endl;
	exit(1);
}

void __attributes_missing()
{
	std::cerr << "error: attributes missing!." << std::endl;
	exit(1);
}