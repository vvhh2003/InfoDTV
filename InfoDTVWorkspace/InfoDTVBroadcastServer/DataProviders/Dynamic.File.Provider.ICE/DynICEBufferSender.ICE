#ifndef INFODTV_ICE
#define INFODTV_ICE

module InfoDTV
{


module Multiplexer
{

module Dynamic
{

module Provider

{


sequence<byte> ByteSeq;

interface DynamicBufferTransfer
{
    void SendBuffer(string aServiceName,string aBufferGuid,int aSendIndex,int aTotalBufferLength,int aCurrentBufferLength,ByteSeq aSeq);
};

};

};

};

};
#endif
