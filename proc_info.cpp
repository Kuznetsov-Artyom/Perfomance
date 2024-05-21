//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include <intrin.h>
#include <vector>
#include <array>
#include <cstring>
#include <cstdlib>
#include "proc_info.hpp"

namespace proc
{
	DWORD ProcInfo::ProcInfoImpl::countSetBits(ULONG_PTR bitMask)
	{
		DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
		DWORD bitSetCount = 0;
		ULONG_PTR bitTest = static_cast<ULONG_PTR>(1) << LSHIFT;

		for (DWORD i = 0; i <= LSHIFT; ++i)
		{
			bitSetCount += ((bitMask & bitTest) ? 1 : 0);
			bitTest = (bitTest >> 1);
		}

		return bitSetCount;
	}

	void ProcInfo::ProcInfoImpl::getProdSpecification()
	{
		std::vector<std::array<int, 4>> data;
		std::array<int, 4> cpui{};

		__cpuid(cpui.data(), 0);
		int countIds = cpui[0];

		for (int i = 0; i <= countIds; ++i)
		{
			__cpuidex(cpui.data(), i, 0);
			data.push_back(cpui);
		}

		char brandProc[0x20]{};
		*reinterpret_cast<int*>(brandProc) = data[0][1];
		*reinterpret_cast<int*>(brandProc + 4) = data[0][3];
		*reinterpret_cast<int*>(brandProc + 8) = data[0][2];

		if (std::strcmp(brandProc, "GenuineIntel") == 0)
		{
			mBrand = "Intel";
			mIsIntel = true;
		}
		else if (std::strcmp(brandProc, "AuthenticAMD") == 0)
		{
			mBrand = "AMD";
			mIsAMD = true;
		}

		data.clear();
		__cpuid(cpui.data(), 0x80000000);
		countIds = cpui[0];
		
		for (int i = 0x80000000; i <= countIds; ++i)
		{
			__cpuidex(cpui.data(), i, 0);
			data.push_back(cpui);
		}

		if (countIds >= 0x80000004)
		{
			char modelProc[0x40]{};
			std::memcpy(modelProc, data[2].data(), sizeof(cpui));
			std::memcpy(modelProc + 16, data[3].data(), sizeof(cpui));
			std::memcpy(modelProc + 32, data[4].data(), sizeof(cpui));
			mModel = modelProc;
		}
	}

	void ProcInfo::ProcInfoImpl::getTechSpecification()
	{
		DWORD size = 0;
		GetLogicalProcessorInformation(nullptr, &size);

		if (GetLastError())
		{
			PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buf =
				(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)std::malloc(size);

			if (buf && (GetLogicalProcessorInformation(buf, &size)))
			{
				DWORD offset = 0;
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = buf;

				while (offset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= size)
				{
					switch (ptr->Relationship)
					{
					case RelationProcessorCore:
						++mCores;
						mThreads += countSetBits(ptr->ProcessorMask);
						break;

					case RelationCache:
						if (ptr->Cache.Level == 1)
							mSizeCacheL1 = ptr->Cache.Size / 1024;
						else if (ptr->Cache.Level == 2)
							mSizeCacheL2 = ptr->Cache.Size / 1024;
						else
							mSizeCacheL3 = ptr->Cache.Size / 1024;
						break;

					default:
						break;
					}

					offset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
					++ptr;
				}
				std::free(buf);
			}
			else std::exit(GetLastError());
		}
	}

	ProcInfo::ProcInfoImpl::ProcInfoImpl() :
		mIsIntel{},
		mIsAMD{},
		mBrand{},
		mModel{},
		mCores{},
		mThreads{},
		mSizeCacheL1{},
		mSizeCacheL2{},
		mSizeCacheL3{}
	{
		getProdSpecification();
		getTechSpecification();
	}

	bool ProcInfo::isIntel() noexcept { return mInfo.mIsIntel; }
	bool ProcInfo::isAMD() noexcept { return mInfo.mIsAMD; }

	std::string ProcInfo::brand() noexcept { return mInfo.mBrand; }
	std::string ProcInfo::model() noexcept { return mInfo.mModel; }

	DWORD ProcInfo::countCores() noexcept { return mInfo.mCores; }
	DWORD ProcInfo::countThreads() noexcept { return mInfo.mThreads; }
	DWORD ProcInfo::sizeCacheL1() noexcept { return mInfo.mSizeCacheL1; }
	DWORD ProcInfo::sizeCacheL2() noexcept { return mInfo.mSizeCacheL2; }
	DWORD ProcInfo::sizeCacheL3() noexcept { return mInfo.mSizeCacheL3; }

} // namespace proc
