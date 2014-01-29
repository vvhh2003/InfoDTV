// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `ICE.ice'

#ifndef __ICE_h__
#define __ICE_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 302
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig;
bool operator==(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator!=(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator<(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator<=(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator>(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator>=(const MuxRuntimeConfig&, const MuxRuntimeConfig&);

}

}

}

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig;
bool operator==(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator!=(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator<(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator<=(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator>(const MuxRuntimeConfig&, const MuxRuntimeConfig&);
bool operator>=(const MuxRuntimeConfig&, const MuxRuntimeConfig&);

}

}

}

namespace IceInternal
{

void incRef(::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*);
void decRef(::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*);

void incRef(::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*);
void decRef(::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*);

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

typedef ::IceInternal::Handle< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig> MuxRuntimeConfigPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig> MuxRuntimeConfigPrx;

void __write(::IceInternal::BasicStream*, const MuxRuntimeConfigPrx&);
void __read(::IceInternal::BasicStream*, MuxRuntimeConfigPrx&);
void __write(::IceInternal::BasicStream*, const MuxRuntimeConfigPtr&);
void __patch__MuxRuntimeConfigPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const MuxRuntimeConfigPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const MuxRuntimeConfigPtr&);
void __decRefUnsafe(const MuxRuntimeConfigPtr&);
void __clearHandleUnsafe(MuxRuntimeConfigPtr&);

}

}

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

enum AddChannelResult
{
    ACROK,
    ACRSameName,
    ACROBError,
    ACRNoDP,
    ACRDPInitError
};

void __write(::IceInternal::BasicStream*, AddChannelResult);
void __read(::IceInternal::BasicStream*, AddChannelResult&);

struct DataProviderInfo
{
    ::std::string TypeID;
    ::std::string Name;
    ::std::string Info;

    bool operator==(const DataProviderInfo&) const;
    bool operator!=(const DataProviderInfo&) const;
    bool operator<(const DataProviderInfo&) const;
    bool operator<=(const DataProviderInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const DataProviderInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const DataProviderInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

struct ChannelInfo
{
    ::std::string ChannelName;
    ::Ice::Long OutputBitRate;
    bool IsFixOutputCounter;
    ::std::string DataProviderTypeID;
    ::std::string DataProviderConfig;

    bool operator==(const ChannelInfo&) const;
    bool operator!=(const ChannelInfo&) const;
    bool operator<(const ChannelInfo&) const;
    bool operator<=(const ChannelInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ChannelInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ChannelInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo> DataProviderInfoSeq;

class __U__DataProviderInfoSeq { };
void __write(::IceInternal::BasicStream*, const ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo*, const ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo*, __U__DataProviderInfoSeq);
void __read(::IceInternal::BasicStream*, DataProviderInfoSeq&, __U__DataProviderInfoSeq);

typedef ::std::vector< ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo> ChannelInfoSeq;

class __U__ChannelInfoSeq { };
void __write(::IceInternal::BasicStream*, const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo*, const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo*, __U__ChannelInfoSeq);
void __read(::IceInternal::BasicStream*, ChannelInfoSeq&, __U__ChannelInfoSeq);

}

}

}

namespace IceProxy
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig : virtual public ::IceProxy::Ice::Object
{
public:

    ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos()
    {
        return GetAllChannelInfos(0);
    }
    ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos(const ::Ice::Context& __ctx)
    {
        return GetAllChannelInfos(&__ctx);
    }
    
private:

    ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos(const ::Ice::Context*);
    
public:

    ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders()
    {
        return GetAllDataProviders(0);
    }
    ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders(const ::Ice::Context& __ctx)
    {
        return GetAllDataProviders(&__ctx);
    }
    
private:

    ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders(const ::Ice::Context*);
    
public:

    ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo& aChannel)
    {
        return AddChannel(aChannel, 0);
    }
    ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo& aChannel, const ::Ice::Context& __ctx)
    {
        return AddChannel(aChannel, &__ctx);
    }
    
private:

    ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo&, const ::Ice::Context*);
    
public:

    bool DelectChannel(const ::std::string& aChannelName)
    {
        return DelectChannel(aChannelName, 0);
    }
    bool DelectChannel(const ::std::string& aChannelName, const ::Ice::Context& __ctx)
    {
        return DelectChannel(aChannelName, &__ctx);
    }
    
private:

    bool DelectChannel(const ::std::string&, const ::Ice::Context*);
    
public:

    ::std::string CheckDataProviderConfig(const ::std::string& aProviderTypeID, const ::std::string& aTmpConfig)
    {
        return CheckDataProviderConfig(aProviderTypeID, aTmpConfig, 0);
    }
    ::std::string CheckDataProviderConfig(const ::std::string& aProviderTypeID, const ::std::string& aTmpConfig, const ::Ice::Context& __ctx)
    {
        return CheckDataProviderConfig(aProviderTypeID, aTmpConfig, &__ctx);
    }
    
private:

    ::std::string CheckDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    bool ModifyChanneIsFixOutputCounter(const ::std::string& aChannelName, bool aNewIsFixOutputCounter)
    {
        return ModifyChanneIsFixOutputCounter(aChannelName, aNewIsFixOutputCounter, 0);
    }
    bool ModifyChanneIsFixOutputCounter(const ::std::string& aChannelName, bool aNewIsFixOutputCounter, const ::Ice::Context& __ctx)
    {
        return ModifyChanneIsFixOutputCounter(aChannelName, aNewIsFixOutputCounter, &__ctx);
    }
    
private:

    bool ModifyChanneIsFixOutputCounter(const ::std::string&, bool, const ::Ice::Context*);
    
public:

    bool ModifyChannelOutputBitRate(const ::std::string& aChannelName, ::Ice::Long aNewOutputBitRate)
    {
        return ModifyChannelOutputBitRate(aChannelName, aNewOutputBitRate, 0);
    }
    bool ModifyChannelOutputBitRate(const ::std::string& aChannelName, ::Ice::Long aNewOutputBitRate, const ::Ice::Context& __ctx)
    {
        return ModifyChannelOutputBitRate(aChannelName, aNewOutputBitRate, &__ctx);
    }
    
private:

    bool ModifyChannelOutputBitRate(const ::std::string&, ::Ice::Long, const ::Ice::Context*);
    
public:

    bool ModifyChannelName(const ::std::string& aChannelName, const ::std::string& aNewChannelName)
    {
        return ModifyChannelName(aChannelName, aNewChannelName, 0);
    }
    bool ModifyChannelName(const ::std::string& aChannelName, const ::std::string& aNewChannelName, const ::Ice::Context& __ctx)
    {
        return ModifyChannelName(aChannelName, aNewChannelName, &__ctx);
    }
    
private:

    bool ModifyChannelName(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    bool ModifyChannelDataProvider(const ::std::string& aChannelName, const ::std::string& aNewDataProviderTypeID, const ::std::string& aNewDataProviderConfig)
    {
        return ModifyChannelDataProvider(aChannelName, aNewDataProviderTypeID, aNewDataProviderConfig, 0);
    }
    bool ModifyChannelDataProvider(const ::std::string& aChannelName, const ::std::string& aNewDataProviderTypeID, const ::std::string& aNewDataProviderConfig, const ::Ice::Context& __ctx)
    {
        return ModifyChannelDataProvider(aChannelName, aNewDataProviderTypeID, aNewDataProviderConfig, &__ctx);
    }
    
private:

    bool ModifyChannelDataProvider(const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    bool ModifyChannelDataProviderConfig(const ::std::string& aChannelName, const ::std::string& aNewDataProviderConfig)
    {
        return ModifyChannelDataProviderConfig(aChannelName, aNewDataProviderConfig, 0);
    }
    bool ModifyChannelDataProviderConfig(const ::std::string& aChannelName, const ::std::string& aNewDataProviderConfig, const ::Ice::Context& __ctx)
    {
        return ModifyChannelDataProviderConfig(aChannelName, aNewDataProviderConfig, &__ctx);
    }
    
private:

    bool ModifyChannelDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

}

}

namespace IceDelegate
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos(const ::Ice::Context*) = 0;

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders(const ::Ice::Context*) = 0;

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo&, const ::Ice::Context*) = 0;

    virtual bool DelectChannel(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::std::string CheckDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual bool ModifyChanneIsFixOutputCounter(const ::std::string&, bool, const ::Ice::Context*) = 0;

    virtual bool ModifyChannelOutputBitRate(const ::std::string&, ::Ice::Long, const ::Ice::Context*) = 0;

    virtual bool ModifyChannelName(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual bool ModifyChannelDataProvider(const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual bool ModifyChannelDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;
};

}

}

}

}

namespace IceDelegateM
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig : virtual public ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig,
                         virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos(const ::Ice::Context*);

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders(const ::Ice::Context*);

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo&, const ::Ice::Context*);

    virtual bool DelectChannel(const ::std::string&, const ::Ice::Context*);

    virtual ::std::string CheckDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual bool ModifyChanneIsFixOutputCounter(const ::std::string&, bool, const ::Ice::Context*);

    virtual bool ModifyChannelOutputBitRate(const ::std::string&, ::Ice::Long, const ::Ice::Context*);

    virtual bool ModifyChannelName(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual bool ModifyChannelDataProvider(const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual bool ModifyChannelDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*);
};

}

}

}

}

namespace IceDelegateD
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig : virtual public ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig,
                         virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos(const ::Ice::Context*);

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders(const ::Ice::Context*);

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo&, const ::Ice::Context*);

    virtual bool DelectChannel(const ::std::string&, const ::Ice::Context*);

    virtual ::std::string CheckDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual bool ModifyChanneIsFixOutputCounter(const ::std::string&, bool, const ::Ice::Context*);

    virtual bool ModifyChannelOutputBitRate(const ::std::string&, ::Ice::Long, const ::Ice::Context*);

    virtual bool ModifyChannelName(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual bool ModifyChannelDataProvider(const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual bool ModifyChannelDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Context*);
};

}

}

}

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace RuntimeConfig
{

class MuxRuntimeConfig : virtual public ::Ice::Object
{
public:

    typedef MuxRuntimeConfigPrx ProxyType;
    typedef MuxRuntimeConfigPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq GetAllChannelInfos(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetAllChannelInfos(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq GetAllDataProviders(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetAllDataProviders(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddChannel(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DelectChannel(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DelectChannel(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string CheckDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckDataProviderConfig(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ModifyChanneIsFixOutputCounter(const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ModifyChanneIsFixOutputCounter(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ModifyChannelOutputBitRate(const ::std::string&, ::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ModifyChannelOutputBitRate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ModifyChannelName(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ModifyChannelName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ModifyChannelDataProvider(const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ModifyChannelDataProvider(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ModifyChannelDataProviderConfig(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ModifyChannelDataProviderConfig(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__MuxRuntimeConfigPtr(void*, ::Ice::ObjectPtr&);

}

}

}

#endif
