#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <iostream>

class Utils{
	public:
		static void debug(std::string s, std::string tag){
			std::cout << tag << " " << s << std::endl;
		}
};

#endif //_UTILS_H_
