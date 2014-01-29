#ifndef ITSMUXCHANNELSTREAMS_H_INCLUDED
#define ITSMUXCHANNELSTREAMS_H_INCLUDED


#include "InterfaceCommon.h"
#include "ITSMuxChannelStreams.h"
#include "ITSChannelStream.h"
#include "../Common/TSPacketStruct.h"

/**
  * class ITSMuxChannelStreams
  */
using namespace std;
namespace MultiplexerCore
{

	const string NULLSTREAM_NAME = "NULLSTREAM000";

class ITSMuxChannelStreams
{
public:

	virtual ~ITSMuxChannelStreams(){};
  /**
   * @return ITSChannelStream &
   * @param  AFStreamName
   * @param  AFOutputBitRate
   * @param  AFTSDataProvider
   * @param  AIsFixOutputCounter
   */
  virtual ITSChannelStreamPtr AddChannelStream (string AFStreamName, long AFOutputBitRate, ITSDataProviderPtr AFTSDataProvider, bool AIsFixOutputCounter ) =0;


  /**
   * @return long
   */
  virtual long GetCurrentTotalTSChannelBitRate ( )   =0;

  virtual void ConfigChanged (string aStreamName,string aNewConfig )=0;

  /**
   * @return ITSChannelStream &
   * @param  aStreamName
   * @param  aStream
   */
  virtual ITSChannelStreamPtr AddChannelStream (string aStreamName, ITSChannelStreamPtr aStream )   =0;


  /**
   * @param  aStreamName
   */
  virtual void DeleteChannelStream (string aStreamName )  =0;


  /**
   * @return list <int>
   */
  virtual IntListPtr GetOutputPIDs ( )  =0;


  /**
   * @return long
   * @param  aStreamName
   */
  virtual long GetOutputBitRateByName (string aStreamName ) =0;


  /**
   * @return list <string>
   */
  virtual StringListPtr GetOutputStreamNames ( ) =0;


  /**
   * @return ITSChannelStream *
   * @param  aChannelName
   */
  virtual ITSChannelStreamPtr GetTSChannelByName (string aChannelName ) =0;


  /**
   * @return TSPacketStruct
   */
  virtual TSPacketStructPtr OutputPacket ( ) =0;


  /**
   */
  virtual void ReCalculateMuxStreamsBitRate ( ) =0;


  /**
   */
  virtual void ClearAllStream ( ) =0;


  /**
   */
  virtual void ResetStreams ( ) =0;


};

typedef  boost::shared_ptr<ITSMuxChannelStreams> ITSMuxChannelStreamsPtr;
};


#endif // ITSMUXCHANNELSTREAMS_H_INCLUDED
