#pragma once

#include "boost/function.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/shared_ptr.hpp"

namespace RBX
{
	enum MessageType
	{
		MESSAGE_OUTPUT = 0,
		MESSAGE_INFO = 1,
		MESSAGE_WARNING = 2,
		MESSAGE_ERROR = 3,
	};

	struct StandardOutMessage
	{
		MessageType type;
		std::string message;
		time_t time;
	};

	class StandardOut : public boost::enable_shared_from_this<RBX::StandardOut>
	{
	public:
		static boost::shared_ptr<StandardOut> singleton();

		void print(RBX::MessageType messageType, const char* format, ...); // print normally
		void print(RBX::MessageType messageType, std::exception &exception); // print exception
		static void print_exception(boost::function0<void>& f, RBX::MessageType type); // print an exception if F has an exception

	protected:
		boost::mutex sync;
	private:
		StandardOut() { };
	};
}
