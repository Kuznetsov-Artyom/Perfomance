#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <intrin.h>
#include <utility>

class InstructionSet
{
	class InstructionSet_Internal;

public:
	static std::string Vendor(void) { return CPU_Rep.vendor_; }
	static std::string Brand(void) { return CPU_Rep.brand_; }

	static bool SSE3(void) { return CPU_Rep.f_1_ECX_[0]; }
	static bool PCLMULQDQ(void) { return CPU_Rep.f_1_ECX_[1]; }
	static bool MONITOR(void) { return CPU_Rep.f_1_ECX_[3]; }
	static bool SSSE3(void) { return CPU_Rep.f_1_ECX_[9]; }
	static bool FMA(void) { return CPU_Rep.f_1_ECX_[12]; }
	static bool CMPXCHG16B(void) { return CPU_Rep.f_1_ECX_[13]; }
	static bool SSE41(void) { return CPU_Rep.f_1_ECX_[19]; }
	static bool SSE42(void) { return CPU_Rep.f_1_ECX_[20]; }
	static bool MOVBE(void) { return CPU_Rep.f_1_ECX_[22]; }
	static bool POPCNT(void) { return CPU_Rep.f_1_ECX_[23]; }
	static bool AES(void) { return CPU_Rep.f_1_ECX_[25]; }
	static bool XSAVE(void) { return CPU_Rep.f_1_ECX_[26]; }
	static bool OSXSAVE(void) { return CPU_Rep.f_1_ECX_[27]; }
	static bool AVX(void) { return CPU_Rep.f_1_ECX_[28]; }
	static bool F16C(void) { return CPU_Rep.f_1_ECX_[29]; }
	static bool RDRAND(void) { return CPU_Rep.f_1_ECX_[30]; }

	static bool MSR(void) { return CPU_Rep.f_1_EDX_[5]; }
	static bool CX8(void) { return CPU_Rep.f_1_EDX_[8]; }
	static bool SEP(void) { return CPU_Rep.f_1_EDX_[11]; }
	static bool CMOV(void) { return CPU_Rep.f_1_EDX_[15]; }
	static bool CLFSH(void) { return CPU_Rep.f_1_EDX_[19]; }
	static bool MMX(void) { return CPU_Rep.f_1_EDX_[23]; }
	static bool FXSR(void) { return CPU_Rep.f_1_EDX_[24]; }
	static bool SSE(void) { return CPU_Rep.f_1_EDX_[25]; }
	static bool SSE2(void) { return CPU_Rep.f_1_EDX_[26]; }

	static bool FSGSBASE(void) { return CPU_Rep.f_7_EBX_[0]; }
	static bool BMI1(void) { return CPU_Rep.f_7_EBX_[3]; }
	static bool HLE(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
	static bool AVX2(void) { return CPU_Rep.f_7_EBX_[5]; }
	static bool BMI2(void) { return CPU_Rep.f_7_EBX_[8]; }
	static bool ERMS(void) { return CPU_Rep.f_7_EBX_[9]; }
	static bool INVPCID(void) { return CPU_Rep.f_7_EBX_[10]; }
	static bool RTM(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
	static bool AVX512F(void) { return CPU_Rep.f_7_EBX_[16]; }
	static bool RDSEED(void) { return CPU_Rep.f_7_EBX_[18]; }
	static bool ADX(void) { return CPU_Rep.f_7_EBX_[19]; }
	static bool AVX512PF(void) { return CPU_Rep.f_7_EBX_[26]; }
	static bool AVX512ER(void) { return CPU_Rep.f_7_EBX_[27]; }
	static bool AVX512CD(void) { return CPU_Rep.f_7_EBX_[28]; }
	static bool SHA(void) { return CPU_Rep.f_7_EBX_[29]; }

	static bool PREFETCHWT1(void) { return CPU_Rep.f_7_ECX_[0]; }

	static bool LAHF(void) { return CPU_Rep.f_81_ECX_[0]; }
	static bool LZCNT(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
	static bool ABM(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
	static bool SSE4a(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
	static bool XOP(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
	static bool TBM(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }

	static bool SYSCALL(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
	static bool MMXEXT(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
	static bool RDTSCP(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
	static bool _3DNOWEXT(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
	static bool _3DNOW(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

private:
	static const InstructionSet_Internal CPU_Rep;

	class InstructionSet_Internal
	{
	public:
		InstructionSet_Internal()
			: nIds_{ 0 },
			nExIds_{ 0 },
			isIntel_{ false },
			isAMD_{ false },
			f_1_ECX_{ 0 },
			f_1_EDX_{ 0 },
			f_7_EBX_{ 0 },
			f_7_ECX_{ 0 },
			f_81_ECX_{ 0 },
			f_81_EDX_{ 0 },
			data_{},
			extdata_{}
		{
			std::array<int, 4> cpui;

			__cpuid(cpui.data(), 0);
			nIds_ = cpui[0];

			for (int i = 0; i <= nIds_; ++i)
			{
				__cpuidex(cpui.data(), i, 0);
				data_.push_back(cpui);
			}

			char vendor[0x20];
			memset(vendor, 0, sizeof(vendor));
			*reinterpret_cast<int*>(vendor) = data_[0][1];
			*reinterpret_cast<int*>(vendor + 4) = data_[0][3];
			*reinterpret_cast<int*>(vendor + 8) = data_[0][2];
			vendor_ = vendor;
			if (vendor_ == "GenuineIntel")
			{
				isIntel_ = true;
			}
			else if (vendor_ == "AuthenticAMD")
			{
				isAMD_ = true;
			}

			if (nIds_ >= 1)
			{
				f_1_ECX_ = data_[1][2];
				f_1_EDX_ = data_[1][3];
			}

			if (nIds_ >= 7)
			{
				f_7_EBX_ = data_[7][1];
				f_7_ECX_ = data_[7][2];
			}

			__cpuid(cpui.data(), 0x80000000);
			nExIds_ = cpui[0];

			char brand[0x40];
			memset(brand, 0, sizeof(brand));

			for (int i = 0x80000000; i <= nExIds_; ++i)
			{
				__cpuidex(cpui.data(), i, 0);
				extdata_.push_back(cpui);
			}

			if (nExIds_ >= 0x80000001)
			{
				f_81_ECX_ = extdata_[1][2];
				f_81_EDX_ = extdata_[1][3];
			}

			if (nExIds_ >= 0x80000004)
			{
				memcpy(brand, extdata_[2].data(), sizeof(cpui));
				memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
				memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
				brand_ = brand;
			}
		};

		int nIds_;
		int nExIds_;
		std::string vendor_;
		std::string brand_;
		bool isIntel_;
		bool isAMD_;
		std::bitset<32> f_1_ECX_;
		std::bitset<32> f_1_EDX_;
		std::bitset<32> f_7_EBX_;
		std::bitset<32> f_7_ECX_;
		std::bitset<32> f_81_ECX_;
		std::bitset<32> f_81_EDX_;
		std::vector<std::array<int, 4>> data_;
		std::vector<std::array<int, 4>> extdata_;
	};
};

const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;

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
					if (ptr->Relationship == RelationProcessorCore)
					{
						++countCore;
						countThread += CountSetBits(ptr->ProcessorMask);
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

int main()
{
	while (true)
	{
		std::cout << InstructionSet::Vendor() << std::endl;
		std::cout << InstructionSet::Brand() << std::endl;

		auto infoProc = GetCountCoresCPU();
		std::cout << "core: " << infoProc.first << ' ' << "thread: " << infoProc.second << '\n';

		std::cout << "cpu: " << GetLoadCPU() << '\n';
		std::cout << "mem: " << GetLoadMem() << '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
	}

	return 0;
}
