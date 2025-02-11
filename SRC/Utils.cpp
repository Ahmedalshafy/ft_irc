/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:02:31 by mahmoud           #+#    #+#             */
/*   Updated: 2025/02/04 18:10:42 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Server.hpp"
#include "../Includes/Utils.hpp"

// Function to trim whitespace
// std::string ft_trim(std::string text)
// {
//     std::size_t first = text.find_first_not_of(" \n\r\t");
//     std::size_t last = text.find_last_not_of(" \n\r\t");

//     if (first == std::string::npos || last == std::string::npos) {
//         return "";
//     }
//     return text.substr(first, (last - first + 1));
// }

// Function to split strings by a delimiter
std::vector<std::string> ft_split(std::string str, char delimiter)
{
    std::vector<std::string> result;
    std::string word;

    for (std::size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] != delimiter)
        {
            word += str[i];
        }
        else
        {
            if (!word.empty())
            {
                result.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
    {
        result.push_back(word);
    }
    return result;
}


bool isAlphanumeric(const std::string &str)
{
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if (!std::isalnum(*it))
            return false;
    }
    return true;
}

// Function to create a user identifier string in IRC format
// std::string user_id(const std::string &nickname, const std::string &username)
// {
//     return ":" + nickname + "!" + username + "@localhost";
// }
