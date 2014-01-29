// Eternity persistence system
//////////////////////////////////////////////////////////////////////
//
// 1999-2003 Nicola Santi.
//
// This software is released under the terms of Eternity Artistic
// License. Please read the file eternity-licence to learn details.
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Except as contained in this notice, the name of Nicola Santi
// shall not be used in advertising or otherwise to promote the sale,
// use or other dealings in this Software without prior written
// authorization from Nicola Santi.
//////////////////////////////////////////////////////////////////////

#ifndef XMLSTRINGSCANNER_HPP
#define XMLSTRINGSCANNER_HPP

#include <math.h>
#include <stdlib.h>

#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>  
#include "xmlscanner.hpp"

namespace eternity {



	
class xmlstring_scanner
{
private:
	std::stringstream stream;
	node  rootnode;
	node* currnode;

	std::string currAttribute;

	enum context_mode { value, tagname, comment, doctype, attr, attrvalue, closebracket, closetag, endfile } context;

public:
	xmlstring_scanner(void);
	~xmlstring_scanner(void) ;

	void close();
	node* scan_file(std::string XML_Content);
	
protected:
	char read_next_char(void);
	char read_next_non_space_char(void);
	std::string read_literal(void);
	std::string read_word(void);
	void read_value(void);
	void read_tag_name(void);
	void read_close_tag(void);
	void read_attributes(void);
	void read_attribute_value(void);
	void close_bracket(void);
	void read_comment(void);
	void read_doc_type(void);
	
};

};

#endif //XMLSCANNER_HPP
