#ifndef _PROC_INFO_HPP_
#define _PROC_INFO_HPP_

#ifdef _WIN32

#include <Windows.h>
#include <string>

namespace proc
{
	class ProcInfo
	{
		class ProcInfoImpl
		{
		private:
			DWORD countSetBits(ULONG_PTR bitMask);

			void getProdSpecification();
			void getTechSpecification();

		public:
			ProcInfoImpl();

			bool mIsIntel;
			bool mIsAMD;

			std::string mBrand;
			std::string mModel;

			DWORD mCores;
			DWORD mThreads;
			DWORD mSizeCacheL1;
			DWORD mSizeCacheL2;
			DWORD mSizeCacheL3;
		};

	private:
		inline static const ProcInfoImpl mInfo;

	public:
		static bool isIntel() noexcept;
		static bool isAMD() noexcept;

		static std::string brand() noexcept;
		static std::string model() noexcept;

		static DWORD countCores() noexcept;
		static DWORD countThreads() noexcept;
		static DWORD sizeCacheL1() noexcept;
		static DWORD sizeCacheL2() noexcept;
		static DWORD sizeCacheL3() noexcept;
	};
	
} // namespace proc

#endif // _WIN32
#endif // _PROC_INFO_HPP_
