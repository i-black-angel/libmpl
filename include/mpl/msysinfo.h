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
#ifndef _MSYSINFO_H_
#define _MSYSINFO_H_

#include <mpl/mcoredef.h>

MPL_BEGIN_NAMESPACE

std::string hostname();

class MCpuInfo
{
public:
	std::string vendor() const;
	std::string model() const;
	std::string flags() const;
};

std::string cpuArchitecture();
int numberOfCores();

std::string kernelType();
std::string kernelVersion();
std::string productType();
std::string productVersion();
std::string prettyProductName();

uint64_t memoryAvailSize();
uint64_t memoryTotalSize();
uint64_t memoryUsedSize();
double memoryPercent();

double cpuPercent();

uint32_t uptimelong();
std::string uptime(); // how long the system has been running
std::string since();	// System up since, yyyy-mm-dd HH:MM:SS

MPL_END_NAMESPACE

#endif /* _MSYSINFO_H_ */
