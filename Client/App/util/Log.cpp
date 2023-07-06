#pragma once
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
		sprintf_s(&buffer[4], 64, format, displayBytes);
	}
	else if (bytes < 1000000)
	{
		format = "%dKB";
		sprintf_s(&buffer[4], 64, format, displayBytes / 1000);
	}
	else if (bytes < 1000000000)
	{
		format = "%dMB";
		sprintf_s(&buffer[4], 64, format, displayBytes / 1000000);
	}
	else
	{
		format = "%dGB";
		sprintf_s(&buffer[4], 64, format, displayBytes / 1000000000);
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
		sprintf_s(&buffer[4], 64, format);
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

	sprintf_s(&buffer[4], 64, format, displayTime);
}