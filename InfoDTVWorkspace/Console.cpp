//////////////////////////////////////////////////////////////////////////
// Copyright (c) 2004 Facundo M. Carreiro
// fcarreiro <at> fibertel <dot> com <dot> ar
// v0rtex <at> fibertel <dot> com <dot> ar
// v0rtex__ <at> hotmail <dot> com
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// console default construtor & destructor
//////////////////////////////////////////////////////////////////////////
#include "Console.h"

console::console() : m_lineIndex(0),
defaultCommand(NULL), m_commandBufferSize(20),
m_textBufferSize(50)
{
	// initialize variables to default
}

console::~console()
{
	// all the containers are automatically cleared
}

//////////////////////////////////////////////////////////////////////////
// print() : Prints text in the console (adds to the list)
//////////////////////////////////////////////////////////////////////////

void console::print(const std::string & strTxt)
{
	// push it
	m_textBuffer.push_back(strTemp);

	// if we are out of bounds
	if(m_textBuffer.size() > m_textBufferSize)
	m_textBuffer.pop_front();
}

//////////////////////////////////////////////////////////////////////////
// parseCommandLine() : Executes commandline
//////////////////////////////////////////////////////////////////////////

void console::parseCommandLine()
{
	std::ostringstream out;
	std::string::size_type index = 0;
	std::vector<std::string> arguments;
	ITEM_DB::const_iterator iter;

	std::ostringstream out; // more info here
	std::string::size_type index = 0;
	std::vector<std::string> arguments;
	std::list<console_item_t>::const_iterator iter;

	// add to text buffer
	if(m_commandEcho)
	{
		print(m_commandLine);
	}

	// add to commandline buffer
	m_commandBuffer.push_back(m_commandLine);
	if(m_commandBuffer.size() > m_commandBufferSize) m_commandBuffer.erase(m_commandBuffer.begin());

	// tokenize
	while(index != std::string::npos)
	{
		// push word
		std::string::size_type next_space = m_commandLine.find(' ');
		arguments.push_back(m_commandLine.substr(index, next_space));

		// increment index
		if(next_space != std::string::npos) index = next_space + 1;
		else break;
	}

	// execute
	for(iter = m_itemList.begin(); iter != m_itemList.end(); ++iter)
	{
		if(iter->name == arguments[0])
		{
			switch(iter->type)
			{
			case CTYPE_UCHAR:
				if(arguments.size() > 2)
				{
					return true;
				}
				else if(arguments.size() == 1)
				{
					out.str("");
					out << (*iter).name << " = " << *((unsigned char *)(*iter).var);
					print(out.str());
					return true;
				}
				else if(arguments.size() == 2)
				{
					*((unsigned char *)(*iter).var) = (unsigned char) atoi(arguments[1].c_str());
					return true;
				}
				break;

			case CTYPE_CHAR:
				if(arguments.size() > 2)
				{
					return true;
				}
				else if(arguments.size() == 1)
				{
					out.str("");
					out << (*iter).name << " = " << *((char *)(*iter).var);
					print(out.str());
					return true;
				}
				else if(arguments.size() == 2)
				{
					*((char *)(*iter).var) = (char) atoi(arguments[1].c_str());
					return true;
				}
				break;

			case CTYPE_UINT:
				if(arguments.size() > 2)
				{
					return true;
				}
				else if(arguments.size() == 1)
				{
					out.str("");
					out << (*iter).name << " = " << *((unsigned int *)(*iter).var);
					print(out.str());
					return true;
				}
				if(arguments.size() == 2)
				{
					*((unsigned int *)(*iter).var) = (unsigned int) atoi(arguments[1].c_str());
					return true;
				}
				break;

			case CTYPE_INT:
				if(arguments.size() > 2)
				{
					return true;
				}
				else if(arguments.size() == 1)
				{
					out.str("");
					out << (*iter).name << " = " << *((int *)(*iter).var);
					print(out.str());
					return true;
				}
				if(arguments.size() == 2)
				{
					*((int *)(*iter).var) = (int) atoi(arguments[1].c_str());
					return true;
				}
				break;

			case CTYPE_FLOAT:
				if(arguments.size() > 2)
				{
					return true;
				}
				else if(arguments.size() == 1)
				{
					out.str("");
					out << (*iter).name << " = " << *((float *)(*iter).var);
					print(out.str());
					return true;
				}
				if(arguments.size() == 2)
				{
					*((float *)(*iter).var) = (float)atof(arguments[1].c_str());
					return true;
				}
				break;

			case CTYPE_STRING:
				if(arguments.size() == 1)
				{
					out.str("");
					out << (*iter).name << " = " << (std::string *)(*iter).var;
					Print(out.str());
					return false;
				}
				else if(arguments.size() > 1)
				{
					// reset variable
					*((std::string *)(*iter).var) = "";

					// add new string
					for(int i = 0; i < arguments.size(); ++i)
					{
						*((std::string *)(*iter).var) += arguments[i];
					}
					return true;
				}
				break;

			case CTYPE_FUNCTION:
				(*iter).function(arguments);
				return true;
				break;

			default:
				m_defaultCommand(arguments);
				return false;
				break;
			}
		}
	}

	// end
	return true;
}

//////////////////////////////////////////////////////////////////////////
// addItem() : Adds a variable or function to the console
//////////////////////////////////////////////////////////////////////////

void console::addItem(const std::string & strName, void *pointer, console_item_type_t type);
{
	console_item_t it;

	// fill item properties
	it.name = strName;
	it.type = type;

	// address
	if(type != CTYPE_FUNCTION)
	{
		it.variable_pointer = pointer;
	}
	else
	{
		it.functione = (console_function) pointer;
	}

	// add item
	m_itemList.push_back(it);
}

//////////////////////////////////////////////////////////////////////////
// deleteItem() : Deletes a variable or function from the console
//////////////////////////////////////////////////////////////////////////

void console::deleteItem(const std::string & strName)
{
	ITEM_DB::iterator iter;
	
	// find item
	for (iter = m_itemList.begin(); iter != m_itemList.end(); ++iter)
	{
		if (iter->name == strName)
		{
			m_itemList.erase(iter);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// passKey() : Processes console keypress
//////////////////////////////////////////////////////////////////////////

void console::passKey(char key)
{
	// if we can print the char
	if(c > 31) m_commandLine += key;
}

//////////////////////////////////////////////////////////////////////////
// passBackspace() : Removes last character
//////////////////////////////////////////////////////////////////////////

void console::passBackspace()
{
	if(m_commandLine.length() > 0)
	{
		m_commandLine.pop_back();
	}
}

//////////////////////////////////////////////////////////////////////////
// passIntro() : Executes Commandline
//////////////////////////////////////////////////////////////////////////

void console::passIntro()
{
	if(m_commandLine.length() > 0)
	{
		parseCommandLine();
	}
}

//////////////////////////////////////////////////////////////////////////
// setTextBufferSize() : Sets and checks text buffer size
//////////////////////////////////////////////////////////////////////////

void console::setTextBufferSize(int size)
{
	m_textBufferSize = size;

	// remove any extra line
	if(m_textBuffer.size() > m_textBufferSize)
	{
		std::list<std::string>::iterator it;
		it = m_textBuffer.end() - m_textBufferSize;
		m_textBuffer.erase(m_textBuffer.begin(), it);
	}
}

//////////////////////////////////////////////////////////////////////////
// setCommandBufferSize() : Sets and checks line buffer size
//////////////////////////////////////////////////////////////////////////

void console::setCommandBufferSize(int size)
{
	m_lineBufferSize = size;

	// remove any extra line
	if(m_lineBuffer.size() > m_lineBufferSize)
	{
		std::vector<std::string>::iterator it;
		it = m_commandBuffer.end() - m_commandBufferSize;
		m_textBuffer.erase(m_commandBuffer.begin(), it);
	}
}

//////////////////////////////////////////////////////////////////////////
// historyGo() : Changes actual commandline into some past command
//////////////////////////////////////////////////////////////////////////

void console::historyGo(int where)
{
	// increment line index
	m_lineIndex += i;

	// error correct line index
	if(m_lineIndex < 0)
	{
		m_lineIndex = 0;
	}
	else if(m_iLineIndex >= m_lineBuffer.size())
	{
		m_lineIndex = m_lineBuffer.size() - 1;
	}

	// set command line
	if(!m_commandBuffer.empty())
	{
		m_commandLine = m_commandBuffer[m_lineIndex];
	}
}

//////////////////////////////////////////////////////////////////////////
// End
//////////////////////////////////////////////////////////////////////////
