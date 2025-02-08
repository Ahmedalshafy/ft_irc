/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:20:06 by alsaeed           #+#    #+#             */
/*   Updated: 2025/02/08 13:36:36 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PARSEMESG_HPP
#define PARSEMESG_HPP

#include <string>
#include <vector>
class ParseMessage {

	private:

		int 						_msgLen;
		std::string					_msg;
		std::string					_cmd;
		std::vector<std::string>	_params;
		std::string					_trailing;
		bool						_notValidParam;
		std::string					_errorMsg;

	public:

		ParseMessage( const std::string &message );

		void 						displayCommand(  const ParseMessage &parsedMessage ) const;
		bool						isValid( const std::string &param ) const;
		// std::string					ft_trim( const std::string &str ) const;

		int							getMsgLen( void ) const { return _msgLen; }
		std::string					getMsg( void ) const { return _msg; }
		std::string					getCmd( void ) const { return _cmd; }
		std::vector<std::string>	getParams( void ) const { return _params; }
		std::string					getTrailing( void ) const { return _trailing; }
		std::string					getErrorMsg( void ) const { return _errorMsg; }
};

#endif /* PARSEMSG_HPP */