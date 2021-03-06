/**
 * Copyright 2017 Shusheng Shao <iblackangel@163.com>
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
#ifndef _MAPPLICATION_H_
#define _MAPPLICATION_H_

#include <mpl/mcoredef.h>

MPL_BEGIN_NAMESPACE

std::string applicationName();
std::string applicationDirPath();
std::string applicationFilePath();

class MApplication
{
public:
    explicit MApplication(int argc, char *argv[]);
    virtual ~MApplication();

	static std::string applicationDirPath();
	static std::string applicationFilePath();
	static std::string applicationName();
	static std::string applicationVersion();
	static uint32_t uptime();

	void setApplicationName(const std::string &application);
	void setApplicationVersion(const std::string &version);

private:
	std::string _applicationName;
	std::string _applicationVersion;
};

MPL_END_NAMESPACE

#endif /* _MAPPLICATION_H_ */
