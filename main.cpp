//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include <iostream>
#include <thread>
#include "instruction_set.hpp"
#include "metrics.hpp"
#include "proc_info.hpp"

static void printInstructionSet() noexcept
{
	auto& outStream = std::cout;

	auto msgLog = [&outStream](const char* isaName, bool support) {
		outStream << isaName << ": " << (support ? "supported" : "not supported") << '\n';
	};

	std::cout << "brand: " << proc::ProcInfo::brand() << '\n';
	std::cout << "model: " << proc::ProcInfo::model() << '\n';

	msgLog("ABM", proc::InstructionSet::ABM());
	msgLog("ADX", proc::InstructionSet::ADX());
	msgLog("AES", proc::InstructionSet::AES());
	msgLog("AVX", proc::InstructionSet::AVX());
	msgLog("AVX2", proc::InstructionSet::AVX2());
	msgLog("AVX512CD", proc::InstructionSet::AVX512CD());
	msgLog("AVX512ER", proc::InstructionSet::AVX512ER());
	msgLog("AVX512F", proc::InstructionSet::AVX512F());
	msgLog("AVX512PF", proc::InstructionSet::AVX512PF());
	msgLog("BMI1", proc::InstructionSet::BMI1());
	msgLog("BMI2", proc::InstructionSet::BMI2());
	msgLog("CLFSH", proc::InstructionSet::CLFSH());
	msgLog("CMOV", proc::InstructionSet::CMOV());
	msgLog("CMPXCHG16B", proc::InstructionSet::CMPXCHG16B());
	msgLog("CX8", proc::InstructionSet::CX8());
	msgLog("ERMS", proc::InstructionSet::ERMS());
	msgLog("F16C", proc::InstructionSet::F16C());
	msgLog("FMA", proc::InstructionSet::FMA());
	msgLog("FSGSBASE", proc::InstructionSet::FSGSBASE());
	msgLog("FXSR", proc::InstructionSet::FXSR());
	msgLog("HLE", proc::InstructionSet::HLE());
	msgLog("INVPCID", proc::InstructionSet::INVPCID());
	msgLog("LAHF", proc::InstructionSet::LAHF());
	msgLog("LZCNT", proc::InstructionSet::LZCNT());
	msgLog("MMX", proc::InstructionSet::MMX());
	msgLog("MMXEXT", proc::InstructionSet::MMXEXT());
	msgLog("MONITOR", proc::InstructionSet::MONITOR());
	msgLog("MOVBE", proc::InstructionSet::MOVBE());
	msgLog("MSR", proc::InstructionSet::MSR());
	msgLog("OSXSAVE", proc::InstructionSet::OSXSAVE());
	msgLog("PCLMULQDQ", proc::InstructionSet::PCLMULQDQ());
	msgLog("POPCNT", proc::InstructionSet::POPCNT());
	msgLog("PREFETCHWT1", proc::InstructionSet::PREFETCHWT1());
	msgLog("RDRAND", proc::InstructionSet::RDRAND());
	msgLog("RDSEED", proc::InstructionSet::RDSEED());
	msgLog("RDTSCP", proc::InstructionSet::RDTSCP());
	msgLog("RTM", proc::InstructionSet::RTM());
	msgLog("SHA", proc::InstructionSet::SHA());
	msgLog("SSE", proc::InstructionSet::SSE());
	msgLog("SSE2", proc::InstructionSet::SSE2());
	msgLog("SSE3", proc::InstructionSet::SSE3());
	msgLog("SSE41", proc::InstructionSet::SSE41());
	msgLog("SSE42", proc::InstructionSet::SSE42());
	msgLog("SSE4a", proc::InstructionSet::SSE4a());
	msgLog("SSSE3", proc::InstructionSet::SSSE3());
	msgLog("SYSCALL", proc::InstructionSet::SYSCALL());
	msgLog("TBM", proc::InstructionSet::TBM());
	msgLog("XOP", proc::InstructionSet::XOP());
	msgLog("XSAVE", proc::InstructionSet::XSAVE());
	msgLog("_3DNOW", proc::InstructionSet::_3DNOW());
	msgLog("_3DNOWEXT", proc::InstructionSet::_3DNOWEXT());
}

static void run()
{
	while (true)
	{
		std::cout << "brand: " << proc::ProcInfo::brand() << '\n';
		std::cout << "model: " << proc::ProcInfo::model() << '\n';

		std::cout << "isAMD: " << proc::ProcInfo::isAMD() << ' ';
		std::cout << "isIntel: " << proc::ProcInfo::isIntel() << '\n';

		std::cout << "core: " << proc::ProcInfo::countCores() << ' ';
		std::cout << "thread: " << proc::ProcInfo::countThreads() << '\n';

		std::cout << "L1: " << proc::ProcInfo::sizeCacheL1() << " KB\n";
		std::cout << "line: " << proc::ProcInfo::sizeLineCacheL1() << " B\n";
		std::cout << "L2: " << proc::ProcInfo::sizeCacheL2() << " KB\n";
		std::cout << "line: " << proc::ProcInfo::sizeLineCacheL2() << " B\n";
		std::cout << "L3: " << proc::ProcInfo::sizeCacheL3() << " KB\n";
		std::cout << "line: " << proc::ProcInfo::sizeLineCacheL3() << " B\n";


		std::cout << "cpu: " << metric::getLoadCPU() << " %\n";
		std::cout << "mem: " << metric::getLoadMem() << " %\n";

		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		system("cls");
	}
}


int main()
{
	//printInstructionSet();
	run();

	return 0;
}
