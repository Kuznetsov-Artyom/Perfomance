//
// Copyright (c) 2024 Kuznetsov Artyom
//
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
			struct CacheInfo
			{
				DWORD mSizeCache;
				DWORD mSizeLine;
			};

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
			CacheInfo mCacheL1;
			CacheInfo mCacheL2;
			CacheInfo mCacheL3;
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

		static DWORD sizeLineCacheL1() noexcept;
		static DWORD sizeLineCacheL2() noexcept;
		static DWORD sizeLineCacheL3() noexcept;
	};
	
} // namespace proc

#endif // _WIN32
#endif // _PROC_INFO_HPP_
