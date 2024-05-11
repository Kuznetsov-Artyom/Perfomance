#ifndef _INSTRUCTION_SET_HPP_
#define _INSTRUCTION_SET_HPP_

#ifdef _WIN32

#include <string>
#include <array>
#include <vector>
#include <bitset>
#include <intrin.h>

namespace bench
{
	class InstructionSet
	{
		class InstructionSetImpl;

	public:
		static std::string Brand();
		static std::string Model();

		static bool isIntel() noexcept;
		static bool isAMD() noexcept;

		static bool SSE3();
		static bool PCLMULQDQ();
		static bool MONITOR();
		static bool SSSE3();
		static bool FMA();
		static bool CMPXCHG16B();
		static bool SSE41();
		static bool SSE42();
		static bool MOVBE();
		static bool POPCNT();
		static bool AES();
		static bool XSAVE();
		static bool OSXSAVE();
		static bool AVX();
		static bool F16C();
		static bool RDRAND();

		static bool MSR();
		static bool CX8();
		static bool SEP();
		static bool CMOV();
		static bool CLFSH();
		static bool MMX();
		static bool FXSR();
		static bool SSE();
		static bool SSE2();

		static bool FSGSBASE();
		static bool BMI1();
		static bool HLE();
		static bool AVX2();
		static bool BMI2();
		static bool ERMS();
		static bool INVPCID();
		static bool RTM();
		static bool AVX512F();
		static bool RDSEED();
		static bool ADX();
		static bool AVX512PF();
		static bool AVX512ER();
		static bool AVX512CD();
		static bool SHA();

		static bool PREFETCHWT1();

		static bool LAHF();
		static bool LZCNT();
		static bool ABM();
		static bool SSE4a();
		static bool XOP();
		static bool TBM();

		static bool SYSCALL();
		static bool MMXEXT();
		static bool RDTSCP();
		static bool _3DNOWEXT();
		static bool _3DNOW();

	private:
		static const InstructionSetImpl CPU_Rep;
	};
}

#endif // _WIN32
#endif // _INSTRUCTION_SET_HPP_
