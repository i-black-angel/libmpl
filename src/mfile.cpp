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
#include <mpl/mfile.h>
#include <mpl/mlog.h>
#include <mpl/merror.h>
#include <mpl/mdir.h>
#include <mpl/mfileinfo.h>
#include <mpl/mstring.h>

#ifdef _MSC_VER
# pragma warning (push)
# pragma warning (disable: 4996)
#endif

MPL_BEGIN_NAMESPACE

MFile::MFile()
{
}

MFile::MFile(const char *s)
	: _fname(s)
{
}

MFile::MFile(const std::string &str)
	: _fname(str)
{
}

MFile::MFile(const MFile &other)
{
	innerCopy(other);
}
	
MFile::~MFile()
{
}

MFile &MFile::operator=(const MFile &other)
{
	innerCopy(other);
	return *this;
}

MFile &MFile::operator=(const char *s)
{
	_fname = s;
	return *this;
}

MFile &MFile::operator=(const std::string &str)
{
	_fname = str;
	return *this;
}

bool MFile::operator==(const MFile &f) const
{
	return _fname == f._fname;
}

int MFile::readbuf(char *buf, size_t bytes) const
{
	if (_fname.empty()) return -1;
	return file::readbuf(_fname, buf, bytes);
}

int MFile::writebuf(const char *buf, size_t bytes) const
{
	if (_fname.empty()) return -1;
	return file::writebuf(_fname, buf, bytes);
}


namespace file
{
	int appendLine(const std::string &file, const std::string &line)
	{
		try {
			std::fstream ofile;
			ofile.open(file.c_str(), std::ios::app);
			if (ofile.is_open())
			{
				ofile << line << std::endl;
				ofile.close();
				return line.size();
			}
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		return -1;
	}

	int readbuf(const std::string &file, char *buf, size_t bytes)
	{
#ifdef M_OS_LINUX
		int n = -1;
		int fd = open(file.c_str(), O_RDONLY);
		if (fd == -1) {
			log_error("open '%s' failed: %s", file.c_str(), error().c_str());
			return fd;
		}
		lseek(fd, 0L, SEEK_SET);
		if ((n = read(fd, buf, bytes)) < 0) {
			log_error("%s readbuf failed: %s", file.c_str(), error().c_str());
			fflush(NULL);
		}

		close(fd);
		return n;
#else
		int n = -1;
		FILE *fp = fopen(file.c_str(), "r");
		if (NULL == fp) {
			log_error("open '%s' failed: %s", file.c_str(), error().c_str());
			return -1;
		}

		n = fread(buf, 1, bytes, fp);

		fclose(fp);
		return n;
#endif
	}

	int writebuf(const std::string &file, const char *buf, size_t bytes)
	{
		MFileInfo finfo = file;
		std::string path = finfo.absolutePath();
		std::string fpath = finfo.absoluteFilePath();

		if (!MDir::exists(path) && !MDir::mkpath(path))
			return -1;

		int n = -1;
#ifndef M_OS_WIN
		int flag = O_WRONLY | O_CREAT | O_TRUNC;
		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		int fd = open(fpath.c_str(), flag, mode);
		if (fd == -1) {
			log_error("open '%s' failed: %s", fpath.c_str(), error().c_str());
			return -1;
		}

		if ((n = write(fd, buf, bytes)) < 0)
			log_error("write '%s' failed: %s", fpath.c_str(), error().c_str());

		close(fd);
#else
		FILE *fp = fopen(fpath.c_str(), "w");
		if (NULL == fp) {
			log_error("open '%s' failed: %s", fpath.c_str(), error().c_str());
			return -1;
		}

		n = fwrite(buf, 1, bytes, fp);

		fflush(fp);
		fclose(fp);
#endif	// #ifndef M_OS_WIN
		return n;
	}

	int appendbuf(const std::string &file, const char *buf, size_t bytes)
	{
		MFileInfo finfo = file;
		std::string path = finfo.absolutePath();
		std::string fpath = finfo.absoluteFilePath();

		if (!MDir::exists(path) && !MDir::mkpath(path))
			return -1;
	
		FILE *fp = fopen(fpath.c_str(), "a");
		if (NULL == fp) {
			std::string errstr = format("open '%s' failed: %s",
										fpath.c_str(), error().c_str());
			fprintf(stderr, "%s\n", errstr.c_str());
#ifdef M_OS_LINUX
			syslog(LOG_ERR, "%s", errstr.c_str());
#else
			OutputDebugString(errstr.c_str());
#endif /* M_OS_LINUX */
			return -1;
		}

		int n = fwrite(buf, 1, bytes, fp);
	
		fflush(fp);
		fclose(fp);
		return n;
	}
	
}

MPL_END_NAMESPACE

#ifdef _MSC_VER
# pragma warning (pop)
#endif
