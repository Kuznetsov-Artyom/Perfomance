#ifndef _INSTRUCTION_SET_HPP_
#define _INSTRUCTION_SET_HPP_

#ifdef _WIN32

#include <array>
#include <bitset>
#include <vector>

namespace bench
{
	class InstructionSet
	{
		class InstructionSetImpl
		{
		public:
			InstructionSetImpl();

			bool mIsIntel;
			bool mIsAMD;

			std::bitset<32> f_1_ECX_;
			std::bitset<32> f_1_EDX_;
			std::bitset<32> f_7_EBX_;
			std::bitset<32> f_7_ECX_;
			std::bitset<32> f_81_ECX_;
			std::bitset<32> f_81_EDX_;

			std::vector<std::array<int, 4>> mData;
			std::vector<std::array<int, 4>> mExtData;
		};

	private:
		inline static const InstructionSetImpl mInstrInfo;

	public:
		static bool SSE3() noexcept;
		static bool PCLMULQDQ() noexcept;
		static bool MONITOR() noexcept;
		static bool SSSE3() noexcept;
		static bool FMA() noexcept;
		static bool CMPXCHG16B() noexcept;
		static bool SSE41() noexcept;
		static bool SSE42() noexcept;
		static bool MOVBE() noexcept;
		static bool POPCNT() noexcept;
		static bool AES() noexcept;
		static bool XSAVE() noexcept;
		static bool OSXSAVE() noexcept;
		static bool AVX() noexcept;
		static bool F16C() noexcept;
		static bool RDRAND() noexcept;

		static bool MSR() noexcept;
		static bool CX8() noexcept;
		static bool SEP() noexcept;
		static bool CMOV() noexcept;
		static bool CLFSH() noexcept;
		static bool MMX() noexcept;
		static bool FXSR() noexcept;
		static bool SSE() noexcept;
		static bool SSE2() noexcept;

		static bool FSGSBASE() noexcept;
		static bool BMI1() noexcept;
		static bool HLE() noexcept;
		static bool AVX2() noexcept;
		static bool BMI2() noexcept;
		static bool ERMS() noexcept;
		static bool INVPCID() noexcept;
		static bool RTM() noexcept;
		static bool AVX512F() noexcept;
		static bool RDSEED() noexcept;
		static bool ADX() noexcept;
		static bool AVX512PF() noexcept;
		static bool AVX512ER() noexcept;
		static bool AVX512CD() noexcept;
		static bool SHA() noexcept;

		static bool PREFETCHWT1() noexcept;

		static bool LAHF() noexcept;
		static bool LZCNT() noexcept;
		static bool ABM() noexcept;
		static bool SSE4a() noexcept;
		static bool XOP() noexcept;
		static bool TBM() noexcept;

		static bool SYSCALL() noexcept;
		static bool MMXEXT() noexcept;
		static bool RDTSCP() noexcept;
		static bool _3DNOWEXT() noexcept;
		static bool _3DNOW() noexcept;
	};	
} // namespace bench

#endif // _WIN32
#endif // _INSTRUCTION_SET_HPP_
