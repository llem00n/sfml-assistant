#pragma once
#ifndef SEARCH_MODULE_HPP
#define SEARCH_MODULE_HPP

#include <vector>
#include <string>

#include "module.hpp"


class SearchModule : public Module {
public:
	SearchModule(AI& ai) : Module(ai) {};

	virtual bool		call();
	static bool			isSuitable(const std::vector<std::string>& lastMessage);

private:
	static std::string to_url(const std::string& str);
};

#endif // !SEARCH_MODULE_HPP
