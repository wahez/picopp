#pragma once
#include <map>
#include <string>
#include <vector>
#include <cassert>


namespace PicoPP::PIOPP
{


	enum class Code: std::uint8_t
	{
		JMP  = 0b000,
		WAIT = 0b001,
		IN   = 0b010,
		OUT  = 0b011,
		PUSH = 0b100,
		PULL = 0b100,
		MOV  = 0b101,
		IRQ  = 0b110,
		SET  = 0b111,
	};

	enum class Location : std::uint8_t
	{
		PINS = 0b000,
		X = 0b001,
		Y = 0b010,
		NLL = 0b011,
		PINDIRS = 0b100,
		PC = 0b101,
		ISR = 0b110,
		EXEC = 0b111,
	};

	enum class Destination: std::uint8_t
	{
		PINS = 0b000,
		X = 0b001,
		Y = 0b010,
		EXEC = 0b100,
		PC = 0b101,
		ISR = 0b110,
		OSR = 0b111,
	};

	enum class Operation: std::uint8_t
	{
		None = 0b00,
		Invert = 0b01,
		BitReverse = 0b10,
	};

	enum class Source: std::uint8_t
	{
		PINS = 0b000,
		X = 0b001,
		Y = 0b010,
		NLL = 0b011,
		STATUS = 0b101,
		ISR = 0b110,
		OSR = 0b111,
	};

	enum class Condition: std::uint8_t
	{
		Always = 0b000,
		notX = 0b001,
		X__ = 0b010,
		notY = 0b011,
		Y__ = 0b100,
		XneY= 0b101,
		PIN = 0b110,
		nOSRE = 0b111,
	};

	enum class WaitSource : std::uint8_t
	{
		GPIO = 0b00,
		PIN = 0b01,
		IRQ = 0b10,
	};

	enum class IRQ : std::uint8_t
	{
		SET = 0b00,
		SETWAIT = 0b01,
		CLEAR = 0b10,
	};

	template<int NBits, typename T=uint>
	struct Bits
	{
		constexpr Bits(T b=T{}) : bits(static_cast<uint>(b)) { assert(b >> NBits == 0); }
		uint bits;

		template<int NB, typename OT>
		constexpr Bits<NB+NBits> operator<<(const Bits<NB, OT>& rhs) const { return Bits<NB+NBits, uint>{(bits << NB) | rhs.bits }; }
	};

	struct Instruction
	{
		Bits<3, Code> code;
		Bits<8> arguments;
		char const* label{nullptr};
		Bits<5> delay{0};
		Bits<5> _side{0};

		constexpr Instruction side(Bits<5> s) const { auto i = *this; i._side = s; return i; }
		constexpr Instruction operator[](Bits<5> d) const { auto i = *this; i.delay = d; return i; }
	};

	inline constexpr Instruction jmp(Bits<3, Condition> condition, char const* address)
	{ return Instruction{Code::JMP, condition << Bits<5>{}, address}; }

	inline constexpr Instruction jmp(char const* address)
	{ return jmp(Condition::Always, address); }

	inline constexpr Instruction wait(Bits<1> pol, Bits<2, WaitSource> source, Bits<5> index)
	{ return Instruction{Code::WAIT, pol << source << index}; }

	inline constexpr Instruction wait_irq_rel(Bits<1> pol, Bits<4> index)
	{ return wait(pol, WaitSource::IRQ, Bits<1>{1} << index); }

	inline constexpr Instruction in(Bits<3, Source> source, Bits<5> bit_count)
	{ return Instruction{Code::IN, source << bit_count}; }

	inline constexpr Instruction out(Bits<3, Location> destination, Bits<5> bit_count)
	{ return Instruction{Code::OUT, destination << bit_count}; }

	inline constexpr Instruction push(Bits<1> ifFull=Bits<1>{0}, Bits<1> blocking=Bits<1>{1})
	{ return Instruction{Code::PUSH, Bits<1>{0} << ifFull << blocking << Bits<5>{}}; }

	inline constexpr Instruction pull(Bits<1> ifEmpty=Bits<1>{0}, Bits<1> blocking=Bits<1>{1})
	{ return Instruction{Code::PULL, Bits<1>{1} << ifEmpty << blocking << Bits<5>{}}; }

	inline constexpr Instruction mov(Bits<3, Destination> destination, Bits<2, Operation> op, Bits<3, Source> source)
	{ return Instruction{Code::MOV, destination << op << source}; }

	inline constexpr Instruction irq(Bits<2, IRQ> instr, Bits<4> irq_num, Bits<1> rel)
	{ return Instruction{Code::IRQ, Bits<1>{0} << instr << rel << irq_num}; }

	inline constexpr Instruction set(Bits<3, Destination> destination, Bits<5> data)
	{ return Instruction{Code::SET, destination << data}; }

	inline constexpr Instruction nop = mov(Destination::Y, Operation::None, Source::Y);


	struct ProgramBuilder
	{
		template<typename... Instructions>
		static std::vector<std::uint16_t> Build(uint side_set_bits, Instructions&&... instructions)
		{
			auto builder = ProgramBuilder{};
			builder.side_set_bits = side_set_bits;
			(builder.add_line(std::forward<Instructions>(instructions)), ...); // add all lines in order
			return builder.instructions_to_code();
		}
	private:
		void add_line(Instruction instruction)
		{
			instructions.emplace_back(std::move(instruction));
		}
		void add_line(std::string label)
		{
			labels.emplace(std::move(label), instructions.size());
		}

		Bits<16> finalize(const Instruction& instr) const;
		std::vector<std::uint16_t> instructions_to_code() const;

		uint side_set_bits;
		std::map<std::string, uint> labels;
		std::vector<Instruction> instructions;

	};


}
