
#ifndef ITSCHANNELSTREAM_H
#define ITSCHANNELSTREAM_H
#include "InterfaceCommon.h" 
#include "../Common/TSPacketStruct.h"
#include "ITSDataProvider.h"

/**
  * class ITSChannelStream
  */
using namespace std;
namespace MultiplexerCore
{




class ITSChannelStream
{
public:


	virtual ~ITSChannelStream(){};
  /**
   * @param  aAverageBitRate
   */
  virtual void DecOutputPrority (long aAverageBitRate )  =0;


  /**
   * @return list <int>
   */
  virtual IntListPtr GetOutputPIDs ( )  =0;


  /**
   * @return TSPacketStructTSPacketStruct
   */
  virtual  TSPacketStructPtr GetTSPacket ( )  =0;


  /**
   */
  virtual void ResetCounter ( ) =0;


  /**
   */
  virtual void InitOutputPrority ( ) =0;


  /**
   * @return bool
   */
  virtual bool IsNullTS ( ) =0;


  /**
   */
  virtual void Reset ( ) =0;


  /**
   */
  virtual void ResetOutputPrority ( ) =0;


  /**
   * @param  aTSDataProvider
   */
  virtual void SwitchProvider (ITSDataProviderPtr aTSDataProvider ) =0;


  /**
   * @return ITSDataProvider *
   */
  virtual ITSDataProviderPtr getDataProvider ( ) =0;


  /**
   * @return bool
   */
  virtual bool getIsFixOutputCounter ( ) =0;


  /**
   * @param  aIsFix
   */
  virtual void setIsFixOutputCounter (bool aIsFix ) =0;


  /**
   * @return long
   */
  virtual long getOutputPrority ( ) =0;


  /**
   * @return long
   */
  virtual long getOutputBitRate ( ) =0;


  /**
   * @param  aNewBitRate
   */
  virtual void setOutputBitRate (long aNewBitRate ) =0;


  /**
   * @return string
   */
  virtual string getStreamName ( ) =0;


  /**
   * @param  aStreamName
   */
  virtual void setStreamName (string aStreamName ) =0;


};


typedef  boost::shared_ptr<ITSChannelStream> ITSChannelStreamPtr;
};

#endif // ITSCHANNELSTREAM_H
