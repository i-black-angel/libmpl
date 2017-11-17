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
#ifndef _MHTTP_H_
#define _MHTTP_H_

#include <mini/mcoredef.h>

MINI_BEGIN_NAMESPACE

class MHttp
{
public:
    explicit MHttp();
    virtual ~MHttp();
};

class MHttpServer : public MHttp
{
public:
    explicit MHttpServer();
    virtual ~MHttpServer();
};

class MHttpClient : public MHttp
{
public:
    explicit MHttpClient();
    virtual ~MHttpClient();
};

MINI_END_NAMESPACE

#endif /* _MHTTP_H_ */