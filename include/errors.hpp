/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:16:56 by obelkhad          #+#    #+#             */
/*   Updated: 2023/02/28 16:49:00 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <iostream>
#include <fstream>

void __curly_right_check(std::string __curly);
void __file_fail(std::ifstream	&__file);
void __extention_is_good(std::string str);
void __bad_number_arguments();
void __semi_colon_missing();
void __attributes_missing();