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
#include <mpl.h>

class DataHandler : public mpl::MDataHandler<std::string>
{
protected:
	virtual void handle(std::string &t) {
		// std::cout << t << std::endl;
		printf ("threadID: %ld, string: %s\n", id(), t.c_str());
	}
};

DataHandler d;
void insert(const std::string &val)
{
	d.push(val);
}

int main(int argc, char *argv[])
{
	d.start();
	sleep(1);
	for (int i = 0; i < 10; ++i) {
		std::string index = mpl::format("index-%d", i);
		insert(index);
		// d.push(index);
		sleep(1);
		// usleep(1000);
	}

	d.stop();
	getchar();
	// while (1) {
	// 	sleep(1);
	// }
    return 0;
}
