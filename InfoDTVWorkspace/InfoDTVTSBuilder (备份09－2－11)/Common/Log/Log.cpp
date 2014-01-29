/*
 * Log.cpp
 *
 *  Created on: 2009-1-5
 *      Author: victor
 */

#include "Poco/Exception.h"
#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/SplitterChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Message.h"
#include "Poco/Logger.h"
#include "Poco/AsyncChannel.h"
#include "Log.h"

namespace InfoDTV_Common_Log
{
	using Poco::AutoPtr;
	using Poco::AsyncChannel;
	using Poco::Channel;
	using Poco::ConsoleChannel;
	using Poco::SplitterChannel;
	using Poco::FileChannel;
	using Poco::FormattingChannel;
	using Poco::Formatter;
	using Poco::PatternFormatter;
	using Poco::Logger;
	using Poco::Message;

	void InfoDTVLogger::CreateLogger(string aLoggerName)
	{
		AutoPtr<PatternFormatter> PPatternFormatter1(new PatternFormatter("%s: %p: %t"));
		AutoPtr<PatternFormatter> PPatternFormatter2(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c [%P]:%s:%q:%t"));
		AutoPtr<FormattingChannel> pFCConsole( new FormattingChannel(PPatternFormatter1));
		AutoPtr<ConsoleChannel> PConsoleChannel(new ConsoleChannel());
		pFCConsole->setChannel(PConsoleChannel);

		AutoPtr<FormattingChannel> pFCFile ( new FormattingChannel(PPatternFormatter2));
		AutoPtr<FileChannel> PFileChannel(new FileChannel(aLoggerName+".log"));
		pFCFile->setChannel(PFileChannel);

		pFCFile->setProperty("rotation", "daily");
		pFCFile->setProperty("times", "local");
		pFCFile->setProperty("purgeAge", "1 weeks");
		pFCFile->setProperty("archive", "timestamp");
		AutoPtr<SplitterChannel> splitterChannel(new SplitterChannel());
		splitterChannel->addChannel(pFCConsole);
		splitterChannel->addChannel(pFCFile);

//		AutoPtr<AsyncChannel> AsysplitterChannel(new AsyncChannel(splitterChannel));
		//				AsysplitterChannel->setChannel(splitterChannel);
		Logger::create(aLoggerName, splitterChannel, Message::PRIO_TRACE);

	}

	void InfoDTVLogger::setName(string aName)
	{
		FLoggerName=aName;
		if(!Logger::has(FLoggerName))
		{
			CreateLogger(FLoggerName);
		}
	}

	 void InfoDTVLogger::error(string aMsg)
	{
		if(!Logger::has(FLoggerName))
		{
			CreateLogger(FLoggerName);
		}
		Logger::get(FLoggerName).error(aMsg);
	}
	 void InfoDTVLogger::information(string aMsg)
	{
		if(!Logger::has(FLoggerName))
		{
			CreateLogger(FLoggerName);
		}
		Logger::get(FLoggerName).information(aMsg);
	}
	 void InfoDTVLogger::warn(string aMsg)
	{
		if(!Logger::has(FLoggerName))
		{
			CreateLogger(FLoggerName);
		}
		Logger::get(FLoggerName).warning(aMsg);
	}
	 void InfoDTVLogger::fatal(string aMsg)
	{
		if(!Logger::has(FLoggerName))
		{
			CreateLogger(FLoggerName);
		}
		Logger::get(FLoggerName).fatal(aMsg);
	}
	 void InfoDTVLogger::log(string aMsg)
	{
		information(aMsg);
	}
}
