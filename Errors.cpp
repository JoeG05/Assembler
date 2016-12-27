#include "stdafx.h"
#include "Errors.h"

void Errors::InitErrorReporting()
{
	m_ErrorMsgs.clear();
}

void Errors::RecordError(string &a_err)
{
	if (m_ErrorMsgs.empty() == true)
	{
		m_ErrorMsgs.push_back(a_err);
	}
}

void Errors::DisplayErrors()
{
	for (auto n = 0; n < m_ErrorMsgs.size(); n++)
	{
		cerr << m_ErrorMsgs[n] << endl;
	}
}