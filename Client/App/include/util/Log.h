#pragma once
#include <string>
#include "util/Declarations.h"

namespace RBX
{
	class Log;

	class RBXInterface ILogProvider
	{
	public:
		virtual Log* provideLog() = 0;
	};

	class Log
	{
	public:
		static void setLogProvider(ILogProvider* provider);
		static std::string formatMem(unsigned int bytes);
		static std::string formatTime(double time);
		void timeStamp(bool includeDate);

		enum Severity
		{
			Information = 0,
			Warning = 1,
			Error = 2,

		};
		void writeEntry(Severity severity, const char* message);
	private:
		static ILogProvider* provider;

		Severity worstSeverity;

		std::string logFile;
		std::ofstream stream;
	};
};