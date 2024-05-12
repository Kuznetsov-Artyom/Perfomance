//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include <iostream>
#include <thread>
#include "instruction_set.hpp"
#include "metrics.hpp"
#include "proc_info.hpp"


int main()
{
	while (true)
	{
		std::cout << proc::ProcInfo::brand() << '\n';
		std::cout << proc::ProcInfo::model() << '\n';

		std::cout << "isAMD: " << proc::ProcInfo::isAMD() << ' ';
		std::cout << "isIntel: " << proc::ProcInfo::isIntel() << '\n';

		std::cout << "core: " << proc::ProcInfo::countCores() << ' ';
		std::cout << "thread: " << proc::ProcInfo::countThreads() << '\n';

		std::cout << "L1: " << proc::ProcInfo::sizeCacheL1() << '\n';
		std::cout << "L2: " << proc::ProcInfo::sizeCacheL2() << '\n';
		std::cout << "L3: " << proc::ProcInfo::sizeCacheL3() << '\n';

		std::cout << "cpu: " << metric::getLoadCPU() << '\n';
		std::cout << "mem: " << metric::getLoadMem() << '\n';

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
	}


	return 0;
}
