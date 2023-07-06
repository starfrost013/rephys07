#pragma once

#define RBXASSERT(x) if (Debugable::assertAction == Debugable::AssertAction::CrashOnAssert && x) RBX::Debugable::doCrash();

namespace RBX
{
	class Debugable
	{
	public:

		enum AssertAction
		{
			CrashOnAssert = 0,
			IgnoreAssert = 1,
		};

		static bool doCrashEnabled;

		static void doCrash();

		// REQUIRED FOR IMPLEMENTATION: RBX::DebugSettings::setAssertAction
		static AssertAction assertAction;
	};
}