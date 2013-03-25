/*
 * User.hpp
 *
 *  Created on: Mar 24, 2013
 *      Author: stef
 */

#ifndef USER_HPP_
#define USER_HPP_

#include "CBSerializable.h"

class User : public Cloudbase::CBSerializable {
public:
	User(QString uname) : username_(uname) {};

	std::string serialize() {
		std::string out = "[ { ";
		out += "\"username\" : \"" + username_.toStdString() + "\" } ]";

		return out;
	}

	QString getUsername() { return username_; };
private:
	QString username_;
};


#endif /* USER_HPP_ */
