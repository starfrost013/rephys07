#pragma once
#include "util/StandardOut.h"
#include "boost/shared_ptr.hpp"

using namespace RBX;

boost::shared_ptr<StandardOut> StandardOut::singleton()
{
	static boost::shared_ptr<StandardOut> singleton(new StandardOut());
	return singleton;
}

void StandardOut::print(RBX::MessageType type, const char* format, ...)
{
	// NOT IMPLEMENTED!
}

void StandardOut::print(RBX::MessageType type, std::exception& exp)
{
	print(type, exp.what());
}

void StandardOut::print_exception(boost::function0<void>& f, RBX::MessageType type)
{
	try
	{
		f();
	}
	catch (std::exception ex)
	{
		singleton()->print(type, ex);
	}
}