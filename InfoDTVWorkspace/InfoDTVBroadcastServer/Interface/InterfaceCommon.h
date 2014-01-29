#ifndef INTERFACECOMMON_H_
#define INTERFACECOMMON_H_


#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
using namespace std;
namespace MultiplexerCore
{
typedef	std::vector <int> IntList; 
typedef  boost::shared_ptr< IntList > IntListPtr;
typedef std::vector <std::string> StringList;
typedef  boost::shared_ptr< StringList > StringListPtr;

};


#endif /*INTERFACECOMMON_H_*/
