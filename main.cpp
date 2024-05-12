#include <iostream>
#include <thread>
#include "instruction_set.hpp"
#include "metrics.hpp"
#include "proc_info.hpp"


int main()
{
	while (true)
	{
		std::cout << bench::ProcInfo::brand() << '\n';
		std::cout << bench::ProcInfo::model() << '\n';

		std::cout << "isAMD: " << bench::ProcInfo::isAMD() << ' ';
		std::cout << "isIntel: " << bench::ProcInfo::isIntel() << '\n';

		std::cout << "core: " << bench::ProcInfo::countCores() << ' ';
		std::cout << "thread: " << bench::ProcInfo::countThreads() << '\n';

		std::cout << "L1: " << bench::ProcInfo::sizeCacheL1() << '\n';
		std::cout << "L2: " << bench::ProcInfo::sizeCacheL2() << '\n';
		std::cout << "L3: " << bench::ProcInfo::sizeCacheL3() << '\n';

		std::cout << "cpu: " << bench::getLoadCPU() << '\n';
		std::cout << "mem: " << bench::getLoadMem() << '\n';

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
	}


	return 0;
}
