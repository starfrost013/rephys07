#pragma once
#include <fstream>
#include <windows.h>

#include <util\Debug.h>
#include <util\Log.h>

using namespace RBX;

void Log::setLogProvider(ILogProvider* provider)
{
	Log::provider = provider;
}

std::string Log::formatMem(unsigned int bytes) // should take long in future revs
{
	int displayBytes = bytes;
	char buffer[64]{};
	const char* format = "%dB";

	// can't match - sprintf deprecated
	if (bytes < 1000)
	{
		sprintf_s(buffer, 64, format, displayBytes);
	}
	else if (bytes < 1000000)
	{
		format = "%dKB";
		sprintf_s(buffer, 64, format, displayBytes / 1000);
	}
	else if (bytes < 1000000000)
	{
		format = "%dMB";
		sprintf_s(buffer, 64, format, displayBytes / 1000000);
	}
	else
	{
		format = "%dGB";
		sprintf_s(buffer, 64, format, displayBytes / 1000000000);
	}

	return buffer;
}

std::string Log::formatTime(double time)
{
	// todo: rbx::debugable
	int displayTime = time;
	char buffer[64]{};
	const char* format = "0s";

	if (time == 0.0)
	{
		sprintf_s(buffer, 64, format);
	}
	else if (displayTime <= 0.1)
	{
		displayTime *= 1000.0;
		format = "%.3gms";
	}
	else
	{
		format = "%.3gs";
	}

	sprintf_s(buffer, 64, format, displayTime);
}

void Log::writeEntry(Log::Severity severity, const char* message)
{
	_SYSTEMTIME systemTime;
	char buffer[256]{};

	const char* error = " Error:   ";
	const char* warning = " Warning: ";
	const char* information = "          ";

	RBXASSERT(!Log::provider->provideLog());

	GetLocalTime(&systemTime);

	sprintf_s(buffer, 256, "%02u:%02u.%03u ", systemTime.wHour, systemTime.wMinute, systemTime.wMilliseconds);

	stream.flush();

	switch (severity)
	{
		case Log::Severity::Information:
			RBXASSERT(!Log::provider->provideLog());
			stream << error;
			break;
		case Log::Severity::Warning:
			RBXASSERT(!Log::provider->provideLog());
			stream << warning;
			break;
		case Log::Severity::Error:
			RBXASSERT(!Log::provider->provideLog());
			stream << information;
			break;
	}

	stream << message;
	stream << "\n";
}

void Log::timeStamp(bool includeDate)
{
	_SYSTEMTIME systemTime;
	char s[256];

	// get local time
	GetLocalTime((LPSYSTEMTIME)&systemTime);

	if (includeDate)
	{
		sprintf_s(s, 256, "%02u.%02u.%u ", systemTime.wYear, systemTime.wMonth, systemTime.wDay);
		stream << s;
	}

	sprintf_s(s, 256, "%02u:%02u.%03u ", systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	stream << s;

	stream.flush();
}