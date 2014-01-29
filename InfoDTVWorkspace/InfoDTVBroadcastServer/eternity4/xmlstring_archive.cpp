#include "eternity/xmlstring_archive.hpp"

namespace eternity
{
	
	static const std::string base64_chars = 
	             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	             "abcdefghijklmnopqrstuvwxyz"
	             "0123456789+/";


	static inline bool is_base64(unsigned char c) {
	  return (isalnum(c) || (c == '+') || (c == '/'));
	}

	std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	  std::string ret;
	  int i = 0;
	  int j = 0;
	  unsigned char char_array_3[3];
	  unsigned char char_array_4[4];

	  while (in_len--) {
	    char_array_3[i++] = *(bytes_to_encode++);
	    if (i == 3) {
	      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
	      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
	      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
	      char_array_4[3] = char_array_3[2] & 0x3f;

	      for(i = 0; (i <4) ; i++)
	        ret += base64_chars[char_array_4[i]];
	      i = 0;
	    }
	  }

	  if (i)
	  {
	    for(j = i; j < 3; j++)
	      char_array_3[j] = '\0';

	    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
	    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
	    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
	    char_array_4[3] = char_array_3[2] & 0x3f;

	    for (j = 0; (j < i + 1); j++)
	      ret += base64_chars[char_array_4[j]];

	    while((i++ < 3))
	      ret += '=';

	  }

	  return ret;

	}

	std::string base64_decode(std::string const& encoded_string) {
	  int in_len = encoded_string.size();
	  int i = 0;
	  int j = 0;
	  int in_ = 0;
	  unsigned char char_array_4[4], char_array_3[3];
	  std::string ret;

	  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
	    char_array_4[i++] = encoded_string[in_]; in_++;
	    if (i ==4) {
	      for (i = 0; i <4; i++)
	        char_array_4[i] = base64_chars.find(char_array_4[i]);

	      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
	      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

	      for (i = 0; (i < 3); i++)
	        ret += char_array_3[i];
	      i = 0;
	    }
	  }

	  if (i) {
	    for (j = i; j <4; j++)
	      char_array_4[j] = 0;

	    for (j = 0; j <4; j++)
	      char_array_4[j] = base64_chars.find(char_array_4[j]);

	    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
	    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

	    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	  }

	  return ret;
	}
	
	string xmlstring_archive::Result()
	{
		//close();
		return m_XMLString;
	}
	
	
	/** initialize and XML archive using the file
	 named file_name. If mode is load create
	 the file. Anyway init update archive to
	 begin persistence operations.
	 */
	
	
	void xmlstring_archive::open(std::string XML_Content, opening_mode mode)
	{
		init(XML_Content, mode==load);
		//cout<<"DEBUG:"<<m_oOut.str()<<endl;
	}
	
	
	/** initialize and XML archive using the file
	 named file_name. If loading is true create
	 the file. Anyway init update archive to
	 begin persistence operations.
	 Deprecated: use open instead
	 */
	void xmlstring_archive::init(std::string XML_Content, bool loading)
	{
		done();
		if (loading)
		{
			//throw eternity::exception("opening XML archive " + file_name + " error");;
			m_pCurElement= m_oParser.scan_file(XML_Content);
			
			if (m_pCurElement==NULL)
				throw eternity::exception("opening XML archive " + XML_Content + " error");
			
			m_pCurElement = m_pCurElement->foundChild("archive", 0);
			
			if (m_pCurElement==NULL)
				throw eternity::exception("file " + XML_Content + " is not a valid eternity XML archive");
			
		}
		else
		{
		//	m_oOut.open(file_name.c_str());
			
//			m_oOut << "<?xml version=\"1.0\"?>" << endl;
//			m_oOut << "<!-- eternity persistence framework   -->" << endl;
//			m_oOut << "<!-- Nicola Santi - www.winghands.it  -->" << endl;
		//	cout<<"DEBUG:  "<<m_oOut.str()<<endl;
			m_oOut << "<archive version=\"4.0\" sub=\"VV\">" << endl;
		}
		
		set_loading(loading);
	}
	
	void xmlstring_archive::formatting()
	{
		for (size_t i=0; i< m_nTab; ++i)
			m_oOut << "\t";
	}
	
	
	/// read (and return) a string with label key at position pos
	std::string xmlstring_archive::read(std::string key, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		if (m_pCurElement)
		{
			//const SimpleXMLParser::Element& e = (*m_pCurElement)(key.c_str(), pos);
			//string tmp(e.GetValue());
			//return tmp;

			if (m_pCurElement->foundChild(key, pos) == NULL)
				throw eternity::exception("archive not compatible with class to load.");
			
			return m_pCurElement->foundChild(key, pos)->value;
			//return  std::string((*m_pCurElement)(key.c_str(), pos).GetValue());
		}
		else
			return "";
	}
	
	
	/// read (and put in value) a string with label key at position pos
	void xmlstring_archive::read(std::string key, std::string &value, int pos)
	{
		value = read(key, pos);
		//Decode XML Encode;
	}
	
	/// read (and put in value) a int with label key at position pos
	void xmlstring_archive::read(std::string key, long long &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		value=atoi(read(key, pos).c_str());
	}
	
	
	/// read (and put in value) a int with label key at position pos
	void xmlstring_archive::read(std::string key, long &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		value=atoi(read(key, pos).c_str());
	}
	

	
	/// read (and put in value) a int with label key at position pos
	void xmlstring_archive::read(std::string key, bool &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
//		std::string TmpStr=read(key, pos);
//		if(TmpStr=="true")
//			value=true;
//		else
//			value=false;
		value=atoi(read(key, pos).c_str());
	}
	
	/// read (and put in value) a int with label key at position pos
	void xmlstring_archive::read(std::string key, int &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		value=atoi(read(key, pos).c_str());
	}
	
	
	/// read (and put in value) a int with label key at position pos
	void xmlstring_archive::read(std::string key, unsigned int &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		value=atoi(read(key, pos).c_str());
	}
	
	/// read (and put in value) a float with label key at position pos
	void xmlstring_archive::read(std::string key, float &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		value= (float) atof(read(key, pos).c_str());
	}
	
	

	/// read (and put in value) a double with label key at position pos
	void xmlstring_archive::read(std::string key, double &value, int pos)
	{
		if (!is_loading())
			throw eternity::exception("read attempt on an archive open for storing.");
		value=atof(read(key, pos).c_str());
	}
	
	
	/// Create a node (e.g. <name attributes>) and set it as current one (enter branch)
	void xmlstring_archive::make_branch(std::string name, std::map<std::string,std::string> attributes)
	{
		if (is_loading() )
			throw new eternity::exception("called make_branch on a loading archive");
		
		formatting();
		m_oOut << "<" << name;
		
		std::map<std::string,std::string>::iterator i = attributes.begin();
		
		for (; i!=attributes.end(); ++i)
			m_oOut << " " << (*i).first << "=\"" << (*i).second << "\"";
		
		m_oOut << ">" << endl;
		
		m_nTab++;
		
		m_dBranches.push_front(new node(name));
		
	}
	
	
	/// Enter in the node with tag equals to name and return its attributes
	std::map<std::string,std::string> xmlstring_archive::enter_branch(std::string name, size_t pos)
	{
		if (is_storing() )
			throw new eternity::exception("called enter_branch on a storing archive");
		
		node* m_pPrevElement = m_pCurElement;
		
		
		//Save current XML element before move to the next one
		m_pCurElement= m_pCurElement->foundChild(name, pos);
		
		m_dBranches.push_front(m_pPrevElement);
		
		return m_pCurElement->attributes;
	}
	
	
	/// Leaves current node and returns to its parent
	void xmlstring_archive::leave_current_branch()
	{
		
		if (is_storing() )
		{
			if (m_dBranches.size()==0)
				throw new eternity::exception("make_branch()/leave_current_branch() mismatch");
			m_nTab--;
			formatting();
			m_oOut << "</" << m_dBranches[0]->name << ">" << endl;
			delete m_dBranches[0];
			m_dBranches.pop_front();
		}
		else
		{
			if (m_dBranches.size()==0)
				throw new eternity::exception("enter_branch()/leave_current_branch() mismatch");
			m_pCurElement=m_dBranches[0];
			m_dBranches.pop_front();
		}
	}
}

