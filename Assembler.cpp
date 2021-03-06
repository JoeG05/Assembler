//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler( )
{
}
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( line );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
	  }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {

            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
		//cout << loc << "   " << line << endl;
    }
}

void Assembler::PassII()
{
	m_facc.rewind();
	int loc = 0;
	

	cout << "Translation:" << endl;
	cout << "Location    Contents    Original" << endl;

	bool end = false;

	for (;;)
	{
		string line;
		if (!m_facc.GetNextLine(line))
		{
			if (end == false)
			{
				string error = "No end statement";
				Errors::RecordError(error);
			}
			return;
		}

		Instruction::InstructionType st = m_inst.ParseInstruction(line);

		if (st == Instruction::ST_Comment)
		{
			cout << "		" << m_inst.GetOriginalInstruction();
			continue;
		}

		else if (st == Instruction::ST_End)
		{
			end = true;
			if (!m_facc.GetNextLine(line))
			{
				cout << "     " << m_inst.GetOriginalInstruction();
				continue;
			}
			else
			{
				cout << "     " << m_inst.GetOriginalInstruction();
				return;
			}
		}
	}
}