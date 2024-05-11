#ifndef _PROC_INFO_HPP_
#define _PROC_INFO_HPP_

#ifdef _WIN32

#include <Windows.h>
#include <cstdlib>

namespace bench
{
	class ProcInfo
	{
		class ProcInfoImpl;

	public:
		static DWORD countCores() noexcept;
		static DWORD countThreads() noexcept;
		static DWORD sizeCacheL1() noexcept;
		static DWORD sizeCacheL2() noexcept;
		static DWORD sizeCacheL3() noexcept;

	private:
		static const ProcInfoImpl mInfo;
	};

	class ProcInfo::ProcInfoImpl
	{
	public:
		ProcInfoImpl();

		DWORD mCores;
		DWORD mThreads;
		DWORD mSizeCacheL1;
		DWORD mSizeCacheL2;
		DWORD mSizeCacheL3;

	private:
		DWORD CountSetBits(ULONG_PTR bitMask);
	};
} // namespace bench

#endif // _WIN32
#endif // _PROC_INFO_HPP_
