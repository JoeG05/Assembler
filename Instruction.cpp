#include "stdafx.h"
#include "Instruction.h"


Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
{
	
	m_instruction = a_buff;		// store original instruction
	

	int commentpos;
	commentpos = (int)a_buff.find_first_of(';');	// finds first ;

	string line = a_buff.substr(0, commentpos);		// stores line without comment


	istringstream s(line);

	if (line.empty())
	{
		m_type = ST_Comment;
		return ST_Comment;
	}

	if (line[0] != ' ' && line[0] != '\t')
		// Line contains a label
	{
		s >> m_Label >> m_OpCode >> m_Operand;
		toUpper(m_OpCode);
		
		
		if (isAssembler(m_OpCode) == true)
		{
			m_type = ST_AssemblerInstr;
			
			return ST_AssemblerInstr;
		}
		else
		{
			m_type = ST_MachineLanguage;
			
			return ST_MachineLanguage;
		}
	}

	else
		// Line does not contain a label
	{
		s >> m_OpCode >> m_Operand;
		toUpper(m_OpCode);
		
	}

	
}

void Instruction::toUpper(string &opcode)
{
	for (int i = 0; i < (int)opcode.length(); i++)
	{
		opcode[i] = toupper(opcode[i]);
	}
}

int Instruction::LocationNextInstruction(int a_loc)
{
	if (m_OpCode == "ORG")
	{
		this->m_OperandValue = stoi(this->m_Operand);
		a_loc = this->m_OperandValue;
	}
	
	else if (m_OpCode == "DS")
	{
		this->m_OperandValue = stoi(this->m_Operand);
		a_loc = a_loc + this->m_OperandValue;
	}

	else
	{
		a_loc++;
	}

	return a_loc;
}

bool Instruction::isAssembler(string &opcode)
{
	if (opcode == "ORG" || opcode == "END" || opcode == "DC" || opcode == "DS")
	{
		return true;
	}
	else
		return false;
}