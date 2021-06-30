#include "pioasm.h"
#include <cassert>


namespace PicoPP::PIOPP
{


	Bits<16> ProgramBuilder::finalize(const Instruction& instr) const
	{
		auto delay = instr.delay;
		if (!side_set_bits)
		{
			assert(instr._side == 0);
		}
		else if (instr._side.bits)
			delay.bits |= instr._side.bits << (5-side_set_bits);

		auto arguments = instr.arguments;
		if (instr.code.bits == static_cast<uint>(Code::JMP))
		{
			assert(!instr.label.empty());
			arguments.bits |= labels.at(instr.label);
		}
		else
		{
			assert(instr.label.empty());
		}
		return instr.code << delay << arguments;
	}


	std::vector<std::uint16_t> ProgramBuilder::instructions_to_code() const
	{
		std::vector<std::uint16_t> codes;
		codes.reserve(instructions.size());
		for (const auto& instruction: instructions)
			codes.push_back(finalize(instruction).bits);
		return codes;
	}


}
