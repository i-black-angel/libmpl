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
#include <mpl/mapplication.h>
#include <mpl/merror.h>
#include <mpl/mlog.h>
#include <mpl/mlockfile.h>

MPL_BEGIN_NAMESPACE

std::string applicationName()
{
	return MApplication::applicationName();
}

std::string applicationDirPath()
{
	return MApplication::applicationDirPath();
}

std::string applicationFilePath()
{
	return MApplication::applicationFilePath();
}

int64_t pid()
{
	return MApplication::pid();
}

MApplication::MApplication(int argc, char *argv[])
{
}

MApplication::~MApplication()
{
}

std::string MApplication::applicationDirPath()
{
	std::string ret;

	char path[PATH_MAX] = { 0x00 };
	if (readlink("/proc/self/exe", path, sizeof(path)) == -1) {
		log_error("%s", error().c_str());
		return ret;
	}

	std::string file = path;
	size_t idx = file.find_last_of("/");
	if (idx == std::string::npos) { return std::string("."); }
	if (idx == 0) idx = 1;

    return file.substr(0, idx);
}

std::string MApplication::applicationFilePath()
{
	std::string ret;

	char path[PATH_MAX] = { 0x00 };
	if (readlink("/proc/self/exe", path, sizeof(path)) == -1) {
		log_error("%s", error().c_str());
		return ret;
	}

	return path;
}

std::string MApplication::applicationName()
{
	std::string ret;

	char path[PATH_MAX] = { 0x00 };
	if (readlink("/proc/self/exe", path, sizeof(path)) == -1) {
		log_error("%s", error().c_str());
		return ret;
	}

	std::string file = path;
	size_t idx = file.find_last_of("/");
	if (idx == std::string::npos) ret = file;
	ret = file.substr(idx + 1);

	return ret;
}

std::string MApplication::applicationVersion()
{
}

int64_t MApplication::pid()
{
    return getpid();
}

uint32_t MApplication::uptime()
{
}

void MApplication::setApplicationName(const std::string &application)
{
	_applicationName = application;
}

void MApplication::setApplicationVersion(const std::string &version)
{
	_applicationVersion = version;
}

bool MApplication::alreadyRunning(const std::string &lockfile)
{
	MLockFile l = lockfile;
	int res = l.lock();
	if (res == -1) {
		log_error("lock '%s' failed: %s", lockfile.c_str(), error().c_str());
		exit(EXIT_FAILURE);
	}
	return (res == 1);
}

MPL_END_NAMESPACE
