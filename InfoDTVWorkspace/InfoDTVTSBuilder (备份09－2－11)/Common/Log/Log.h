#ifndef LOG_H_
#define LOG_H_

#include <string>
using namespace std;

//typedef boost::shared_ptr<Logger> LoggerPtr;
//typedef map<string,ChannelPtr> ChannelMap;
namespace InfoDTV_Common_Log
{
	class InfoDTVLogger
	{

		private:
			std::string FLoggerName;
			void CreateLogger(string aLoggerName);
		public:
			InfoDTVLogger():FLoggerName(""){};
			virtual ~InfoDTVLogger(){};
			virtual void setName(std::string aName);
			virtual void error(std::string aMsg);
			virtual void information(std::string aMsg);
			virtual void warn(std::string aMsg);
			virtual void fatal(std::string aMsg);
			virtual void log(std::string aMsg);
	};


	static InfoDTVLogger GlobalLogger;
}

#endif /*LOG_H_*/
