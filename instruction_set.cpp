#include "instruction_set.hpp"

namespace bench 
{
	class InstructionSet::InstructionSetImpl
	{
	public:
		InstructionSetImpl();

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

	InstructionSet::InstructionSetImpl::InstructionSetImpl() :
		nIds_{ 0 },
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

	std::string InstructionSet::Brand(void) { return CPU_Rep.vendor_; }
	std::string InstructionSet::Model(void) { return CPU_Rep.brand_; }

	bool InstructionSet::isIntel() noexcept { return CPU_Rep.isIntel_; }
	bool InstructionSet::isAMD() noexcept { return CPU_Rep.isAMD_; }

	bool InstructionSet::SSE3(void) { return CPU_Rep.f_1_ECX_[0]; }
	bool InstructionSet::PCLMULQDQ(void) { return CPU_Rep.f_1_ECX_[1]; }
	bool InstructionSet::MONITOR(void) { return CPU_Rep.f_1_ECX_[3]; }
	bool InstructionSet::SSSE3(void) { return CPU_Rep.f_1_ECX_[9]; }
	bool InstructionSet::FMA(void) { return CPU_Rep.f_1_ECX_[12]; }
	bool InstructionSet::CMPXCHG16B(void) { return CPU_Rep.f_1_ECX_[13]; }
	bool InstructionSet::SSE41(void) { return CPU_Rep.f_1_ECX_[19]; }
	bool InstructionSet::SSE42(void) { return CPU_Rep.f_1_ECX_[20]; }
	bool InstructionSet::MOVBE(void) { return CPU_Rep.f_1_ECX_[22]; }
	bool InstructionSet::POPCNT(void) { return CPU_Rep.f_1_ECX_[23]; }
	bool InstructionSet::AES(void) { return CPU_Rep.f_1_ECX_[25]; }
	bool InstructionSet::XSAVE(void) { return CPU_Rep.f_1_ECX_[26]; }
	bool InstructionSet::OSXSAVE(void) { return CPU_Rep.f_1_ECX_[27]; }
	bool InstructionSet::AVX(void) { return CPU_Rep.f_1_ECX_[28]; }
	bool InstructionSet::F16C(void) { return CPU_Rep.f_1_ECX_[29]; }
	bool InstructionSet::RDRAND(void) { return CPU_Rep.f_1_ECX_[30]; }

	bool InstructionSet::MSR(void) { return CPU_Rep.f_1_EDX_[5]; }
	bool InstructionSet::CX8(void) { return CPU_Rep.f_1_EDX_[8]; }
	bool InstructionSet::SEP(void) { return CPU_Rep.f_1_EDX_[11]; }
	bool InstructionSet::CMOV(void) { return CPU_Rep.f_1_EDX_[15]; }
	bool InstructionSet::CLFSH(void) { return CPU_Rep.f_1_EDX_[19]; }
	bool InstructionSet::MMX(void) { return CPU_Rep.f_1_EDX_[23]; }
	bool InstructionSet::FXSR(void) { return CPU_Rep.f_1_EDX_[24]; }
	bool InstructionSet::SSE(void) { return CPU_Rep.f_1_EDX_[25]; }
	bool InstructionSet::SSE2(void) { return CPU_Rep.f_1_EDX_[26]; }

	bool InstructionSet::FSGSBASE(void) { return CPU_Rep.f_7_EBX_[0]; }
	bool InstructionSet::BMI1(void) { return CPU_Rep.f_7_EBX_[3]; }
	bool InstructionSet::HLE(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
	bool InstructionSet::AVX2(void) { return CPU_Rep.f_7_EBX_[5]; }
	bool InstructionSet::BMI2(void) { return CPU_Rep.f_7_EBX_[8]; }
	bool InstructionSet::ERMS(void) { return CPU_Rep.f_7_EBX_[9]; }
	bool InstructionSet::INVPCID(void) { return CPU_Rep.f_7_EBX_[10]; }
	bool InstructionSet::RTM(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
	bool InstructionSet::AVX512F(void) { return CPU_Rep.f_7_EBX_[16]; }
	bool InstructionSet::RDSEED(void) { return CPU_Rep.f_7_EBX_[18]; }
	bool InstructionSet::ADX(void) { return CPU_Rep.f_7_EBX_[19]; }
	bool InstructionSet::AVX512PF(void) { return CPU_Rep.f_7_EBX_[26]; }
	bool InstructionSet::AVX512ER(void) { return CPU_Rep.f_7_EBX_[27]; }
	bool InstructionSet::AVX512CD(void) { return CPU_Rep.f_7_EBX_[28]; }
	bool InstructionSet::SHA(void) { return CPU_Rep.f_7_EBX_[29]; }

	bool InstructionSet::PREFETCHWT1(void) { return CPU_Rep.f_7_ECX_[0]; }

	bool InstructionSet::LAHF(void) { return CPU_Rep.f_81_ECX_[0]; }
	bool InstructionSet::LZCNT(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
	bool InstructionSet::ABM(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
	bool InstructionSet::SSE4a(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
	bool InstructionSet::XOP(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
	bool InstructionSet::TBM(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }

	bool InstructionSet::SYSCALL(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
	bool InstructionSet::MMXEXT(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
	bool InstructionSet::RDTSCP(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
	bool InstructionSet::_3DNOWEXT(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
	bool InstructionSet::_3DNOW(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

	const InstructionSet::InstructionSetImpl InstructionSet::CPU_Rep;
}
