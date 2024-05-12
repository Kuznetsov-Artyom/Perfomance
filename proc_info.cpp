#include "proc_info.hpp"

namespace bench
{
	ProcInfo::ProcInfoImpl::ProcInfoImpl() :
		mCores{ 0 },
		mThreads{ 0 },
		mSizeCacheL1{ 0 },
		mSizeCacheL2{ 0 },
		mSizeCacheL3{ 0 }
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
						mThreads += CountSetBits(ptr->ProcessorMask);
						break;

					case RelationCache:
						if (ptr->Cache.Level == 1)
							mSizeCacheL1 = ptr->Cache.Size;
						else if (ptr->Cache.Level == 2)
							mSizeCacheL2 = ptr->Cache.Size;
						else
							mSizeCacheL3 = ptr->Cache.Size;
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

	DWORD ProcInfo::ProcInfoImpl::CountSetBits(ULONG_PTR bitMask)
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

	DWORD ProcInfo::countCores() noexcept { return mInfo.mCores; }
	DWORD ProcInfo::countThreads() noexcept { return mInfo.mThreads; }
	DWORD ProcInfo::sizeCacheL1() noexcept { return mInfo.mSizeCacheL1; }
	DWORD ProcInfo::sizeCacheL2() noexcept { return mInfo.mSizeCacheL2; }
	DWORD ProcInfo::sizeCacheL3() noexcept { return mInfo.mSizeCacheL3; }

} // namespace bench
