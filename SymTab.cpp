//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/

void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

void SymbolTable::DisplaySymbolTable()
{
	cout << "		Symbol Table" << endl;
	cout << "#		Symbol		Loc" << endl;
	int symnum = 0;
	for (auto i = m_symbolTable.begin(); i != m_symbolTable.end(); i++)
	{
		cout << symnum << "		" << i->first << "		" << i->second << endl;
		symnum++;
	}
}

bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
{
	if (m_symbolTable.find(a_symbol) != m_symbolTable.end())
	{
		a_loc = m_symbolTable[a_symbol];
		return true;
	}
	else
		return false;
}