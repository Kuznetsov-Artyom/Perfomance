//
// Copyright (c) 2024 Kuznetsov Artyom
//
#ifndef _METRICS_HPP_
#define _METRICS_HPP_

#ifdef _WIN32

namespace metric
{
	double getLoadCPU();
	double getLoadMem();
} // namespace metric

#endif // _WIN32
#endif // _METRICS_HPP_
