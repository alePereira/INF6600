#pragma once

#include <iostream>
#include <string>

class Utils
{
public:
	static void debug(std::string s, std::string TAG){
		std::cout << TAG << " " << s << std::endl;
	}
};

