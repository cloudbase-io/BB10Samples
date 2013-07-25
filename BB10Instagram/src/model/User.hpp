/* Copyright (c) 2013 Cloudbase.io Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
