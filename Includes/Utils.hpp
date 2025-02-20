/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:06:48 by mahmoud           #+#    #+#             */
/*   Updated: 2025/02/04 18:08:39 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Server.hpp"

// Function to trim whitespace from the start and end of a string
// std::string ft_trim(std::string &str);

// Function to split a string by a given delimiter
std::vector<std::string> ft_split(std::string str, char delimiter);

// Function to create a user identifier string in IRC format
// std::string user_id(const std::string &nickname, const std::string &username);

bool isAlphanumeric(const std::string &str);

#endif // UTILS_HPP
