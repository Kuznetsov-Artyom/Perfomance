#include "instruction_set.hpp"

namespace bench 
{
	InstructionSet::InstructionSetImpl::InstructionSetImpl() :
		mCountIds{ 0 },
		mCountExIds{ 0 },
		mIsIntel{ false },
		mIsAMD{ false },
		mBrand{},
		mModel{},
		f_1_ECX_{ 0 },
		f_1_EDX_{ 0 },
		f_7_EBX_{ 0 },
		f_7_ECX_{ 0 },
		f_81_ECX_{ 0 },
		f_81_EDX_{ 0 },
		mData{},
		mExtData{}
	{
		std::array<int, 4> cpui{};

		__cpuid(cpui.data(), 0);
		mCountIds = cpui[0];

		mData.reserve(mCountIds);

		for (int i = 0; i <= mCountIds; ++i)
		{
			__cpuidex(cpui.data(), i, 0);
			mData.push_back(cpui);
		}

		char brand_[0x20];
		std::memset(brand_, 0, sizeof(brand_));
		*reinterpret_cast<int*>(brand_) = mData[0][1];
		*reinterpret_cast<int*>(brand_ + 4) = mData[0][3];
		*reinterpret_cast<int*>(brand_ + 8) = mData[0][2];
		mBrand = brand_;

		if (mBrand == "GenuineIntel")
			mIsIntel = true;
		else if (mBrand == "AuthenticAMD")
			mIsAMD = true;

		if (mCountIds >= 1)
		{
			f_1_ECX_ = mData[1][2];
			f_1_EDX_ = mData[1][3];
		}

		if (mCountIds >= 7)
		{
			f_7_EBX_ = mData[7][1];
			f_7_ECX_ = mData[7][2];
		}

		__cpuid(cpui.data(), 0x80000000);
		mCountExIds = cpui[0];

		char brand[0x40];
		memset(brand, 0, sizeof(brand));

		for (int i = 0x80000000; i <= mCountExIds; ++i)
		{
			__cpuidex(cpui.data(), i, 0);
			mExtData.push_back(cpui);
		}

		if (mCountExIds >= 0x80000001)
		{
			f_81_ECX_ = mExtData[1][2];
			f_81_EDX_ = mExtData[1][3];
		}

		if (mCountExIds >= 0x80000004)
		{
			memcpy(brand, mExtData[2].data(), sizeof(cpui));
			memcpy(brand + 16, mExtData[3].data(), sizeof(cpui));
			memcpy(brand + 32, mExtData[4].data(), sizeof(cpui));
			mModel = brand;
		}
	};

	std::string InstructionSet::brand() { return mInstrInfo.mBrand; }
	std::string InstructionSet::model() { return mInstrInfo.mModel; }

	bool InstructionSet::isIntel() noexcept { return mInstrInfo.mIsIntel; }
	bool InstructionSet::isAMD() noexcept { return mInstrInfo.mIsAMD; }

	bool InstructionSet::SSE3() noexcept { return mInstrInfo.f_1_ECX_[0]; }
	bool InstructionSet::PCLMULQDQ() noexcept { return mInstrInfo.f_1_ECX_[1]; }
	bool InstructionSet::MONITOR() noexcept { return mInstrInfo.f_1_ECX_[3]; }
	bool InstructionSet::SSSE3() noexcept { return mInstrInfo.f_1_ECX_[9]; }
	bool InstructionSet::FMA() noexcept { return mInstrInfo.f_1_ECX_[12]; }
	bool InstructionSet::CMPXCHG16B() noexcept { return mInstrInfo.f_1_ECX_[13]; }
	bool InstructionSet::SSE41() noexcept { return mInstrInfo.f_1_ECX_[19]; }
	bool InstructionSet::SSE42() noexcept { return mInstrInfo.f_1_ECX_[20]; }
	bool InstructionSet::MOVBE() noexcept { return mInstrInfo.f_1_ECX_[22]; }
	bool InstructionSet::POPCNT() noexcept { return mInstrInfo.f_1_ECX_[23]; }
	bool InstructionSet::AES() noexcept { return mInstrInfo.f_1_ECX_[25]; }
	bool InstructionSet::XSAVE() noexcept { return mInstrInfo.f_1_ECX_[26]; }
	bool InstructionSet::OSXSAVE() noexcept { return mInstrInfo.f_1_ECX_[27]; }
	bool InstructionSet::AVX() noexcept { return mInstrInfo.f_1_ECX_[28]; }
	bool InstructionSet::F16C() noexcept { return mInstrInfo.f_1_ECX_[29]; }
	bool InstructionSet::RDRAND() noexcept { return mInstrInfo.f_1_ECX_[30]; }

	bool InstructionSet::MSR() noexcept { return mInstrInfo.f_1_EDX_[5]; }
	bool InstructionSet::CX8() noexcept { return mInstrInfo.f_1_EDX_[8]; }
	bool InstructionSet::SEP() noexcept { return mInstrInfo.f_1_EDX_[11]; }
	bool InstructionSet::CMOV() noexcept { return mInstrInfo.f_1_EDX_[15]; }
	bool InstructionSet::CLFSH() noexcept { return mInstrInfo.f_1_EDX_[19]; }
	bool InstructionSet::MMX() noexcept { return mInstrInfo.f_1_EDX_[23]; }
	bool InstructionSet::FXSR() noexcept { return mInstrInfo.f_1_EDX_[24]; }
	bool InstructionSet::SSE() noexcept { return mInstrInfo.f_1_EDX_[25]; }
	bool InstructionSet::SSE2() noexcept { return mInstrInfo.f_1_EDX_[26]; }

	bool InstructionSet::FSGSBASE() noexcept { return mInstrInfo.f_7_EBX_[0]; }
	bool InstructionSet::BMI1() noexcept { return mInstrInfo.f_7_EBX_[3]; }
	bool InstructionSet::HLE() noexcept { return mInstrInfo.mIsIntel && mInstrInfo.f_7_EBX_[4]; }
	bool InstructionSet::AVX2() noexcept { return mInstrInfo.f_7_EBX_[5]; }
	bool InstructionSet::BMI2() noexcept { return mInstrInfo.f_7_EBX_[8]; }
	bool InstructionSet::ERMS() noexcept { return mInstrInfo.f_7_EBX_[9]; }
	bool InstructionSet::INVPCID() noexcept { return mInstrInfo.f_7_EBX_[10]; }
	bool InstructionSet::RTM() noexcept { return mInstrInfo.mIsIntel && mInstrInfo.f_7_EBX_[11]; }
	bool InstructionSet::AVX512F() noexcept { return mInstrInfo.f_7_EBX_[16]; }
	bool InstructionSet::RDSEED() noexcept { return mInstrInfo.f_7_EBX_[18]; }
	bool InstructionSet::ADX() noexcept { return mInstrInfo.f_7_EBX_[19]; }
	bool InstructionSet::AVX512PF() noexcept { return mInstrInfo.f_7_EBX_[26]; }
	bool InstructionSet::AVX512ER() noexcept { return mInstrInfo.f_7_EBX_[27]; }
	bool InstructionSet::AVX512CD() noexcept { return mInstrInfo.f_7_EBX_[28]; }
	bool InstructionSet::SHA() noexcept { return mInstrInfo.f_7_EBX_[29]; }

	bool InstructionSet::PREFETCHWT1() noexcept { return mInstrInfo.f_7_ECX_[0]; }

	bool InstructionSet::LAHF() noexcept { return mInstrInfo.f_81_ECX_[0]; }
	bool InstructionSet::LZCNT() noexcept { return mInstrInfo.mIsIntel && mInstrInfo.f_81_ECX_[5]; }
	bool InstructionSet::ABM() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_ECX_[5]; }
	bool InstructionSet::SSE4a() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_ECX_[6]; }
	bool InstructionSet::XOP() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_ECX_[11]; }
	bool InstructionSet::TBM() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_ECX_[21]; }

	bool InstructionSet::SYSCALL() noexcept { return mInstrInfo.mIsIntel && mInstrInfo.f_81_EDX_[11]; }
	bool InstructionSet::MMXEXT() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_EDX_[22]; }
	bool InstructionSet::RDTSCP() noexcept { return mInstrInfo.mIsIntel && mInstrInfo.f_81_EDX_[27]; }
	bool InstructionSet::_3DNOWEXT() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_EDX_[30]; }
	bool InstructionSet::_3DNOW() noexcept { return mInstrInfo.mIsAMD && mInstrInfo.f_81_EDX_[31]; }

	const InstructionSet::InstructionSetImpl InstructionSet::mInstrInfo;
} // namespace bench
