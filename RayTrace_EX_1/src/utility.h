#pragma once
#ifndef DRAGON_CORE_UTILITY
#define DRAGON_CORE_UTILITY
#include<iostream>
#include<string>
namespace dragon {
	void Warning(const ::std::string&w) {
		::std::cout << w << ::std::endl;
		abort();
	}
}
#endif