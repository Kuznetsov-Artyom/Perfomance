#include "metrics.hpp"

namespace bench
{
	double getLoadCPU()
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

	double getLoadMem()
	{
		MEMORYSTATUSEX stat{};
		stat.dwLength = sizeof(stat);

		GlobalMemoryStatusEx(&stat);
		return (static_cast<double>(stat.ullTotalPhys - stat.ullAvailPhys) / stat.ullTotalPhys) * 100;
	}
} // namespace bench
