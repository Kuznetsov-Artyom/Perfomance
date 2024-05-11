#ifndef _METRICS_HPP_
#define _METRICS_HPP_

#ifdef _WIN32

#include <Windows.h>

namespace bench
{
	double getLoadCPU();
	double getLoadMem();
} // namespace bench

#endif // _WIN32
#endif // _METRICS_HPP_
