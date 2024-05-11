#include <iostream>
#include <Windows.h>
#include <thread>
#include <utility>
#include "instruction_set.hpp"

namespace bench
{
	double GetLoadCPU()
	{
		FILETIME idleTime, kernelTime, userTime;
		ULONGLONG idleTime64, kernelTime64, userTime64;
		static ULONGLONG prevIdleTime = 0, prevKernelTime = 0, prevUserTime = 0;

		GetSystemTimes(&idleTime, &kernelTime, &userTime);

		idleTime64 = (static_cast<ULONGLONG>(idleTime.dwHighDateTime) << 32) | idleTime.dwLowDateTime;
		kernelTime64 = (static_cast<ULONGLONG>(kernelTime.dwHighDateTime) << 32) | kernelTime.dwLowDateTime;
		userTime64 = (static_cast<ULONGLONG>(userTime.dwHighDateTime) << 32) | userTime.dwLowDateTime;

		ULONGLONG totalTime = (kernelTime64 + userTime64) - (prevKernelTime + prevUserTime);
		ULONGLONG totalIdleTime = idleTime64 - prevIdleTime;
		double cpuLoad = 100.0 - (totalIdleTime * 100.0) / totalTime;

		prevIdleTime = idleTime64;
		prevKernelTime = kernelTime64;
		prevUserTime = userTime64;

		return cpuLoad;
	}

	double GetLoadMem()
	{
		MEMORYSTATUSEX stat{};
		stat.dwLength = sizeof(stat);

		GlobalMemoryStatusEx(&stat);
		return (static_cast<double>(stat.ullTotalPhys - stat.ullAvailPhys) / stat.ullTotalPhys) * 100;
	}

	DWORD CountSetBits(ULONG_PTR bitMask)
	{
		DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
		DWORD bitSetCount = 0;
		ULONG_PTR bitTest = static_cast<ULONG_PTR>(1) << LSHIFT;

		for (DWORD i = 0; i <= LSHIFT; ++i)
		{
			bitSetCount += ((bitMask & bitTest) ? 1 : 0);
			bitTest /= 2;
		}

		return bitSetCount;
	}

	using COUNT_PROC_CORES = std::pair<int, int>;

	COUNT_PROC_CORES GetCountCoresCPU()
	{
		COUNT_PROC_CORES procInfo(-1, -1);
		DWORD size = 0;
		GetLogicalProcessorInformation(nullptr, &size);

		if (GetLastError())
		{
			PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buf =
				(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)std::malloc(size);

			if (buf)
			{
				if (GetLogicalProcessorInformation(buf, &size))
				{
					DWORD countCore = 0;
					DWORD countThread = 0;
					DWORD offset = 0;
					PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = buf;

					while (offset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= size)
					{
						switch (ptr->Relationship)
						{
						case RelationProcessorCore:
							++countCore;
							countThread += CountSetBits(ptr->ProcessorMask);
							break;
							/*case RelationCache:
								std::cout << "lvl: " << static_cast<int>(ptr->Cache.Level) << '\n';
								std::cout << "size: " << static_cast<int>(ptr->Cache.Size) << '\n';
								break;*/
						default:
							break;
						}

						offset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
						++ptr;
					}

					procInfo.first = countCore;
					procInfo.second = countThread;
				}
				std::free(buf);
			}
		}

		return procInfo;
	}
}

int main()
{
	while (true)
	{
		std::cout << bench::InstructionSet::Brand() << '\n';
		std::cout << bench::InstructionSet::Model() << '\n';

		auto infoProc = bench::GetCountCoresCPU();
		std::cout << "core: " << infoProc.first << ' ' << "thread: " << infoProc.second << '\n';

		std::cout << "cpu: " << bench::GetLoadCPU() << '\n';
		std::cout << "mem: " << bench::GetLoadMem() << '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
	}

	return 0;
}
