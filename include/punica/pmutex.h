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
#ifndef _PMUTEX_H_
#define _PMUTEX_H_

#include <punica/pcoredef.h>

PUNICA_BEGIN_NAMESPACE

class PMutex
{
public:
    explicit PMutex();
    virtual ~PMutex();

	void lock();
	bool unlock();
	bool trylock();
private:
	P_DISABLE_COPY(PMutex)

	pthread_mutex_t _mutex;
};

class PMutexLocker
{
public:
    explicit PMutexLocker(PMutex &mutex)
		: _mutex(mutex) {
		_mutex.lock();
	}
    ~PMutexLocker() {
		_mutex.unlock();
	}
private:
	P_DISABLE_COPY(PMutexLocker)
	
	PMutex &_mutex;
};

PUNICA_END_NAMESPACE

#endif /* _PMUTEX_H_ */
