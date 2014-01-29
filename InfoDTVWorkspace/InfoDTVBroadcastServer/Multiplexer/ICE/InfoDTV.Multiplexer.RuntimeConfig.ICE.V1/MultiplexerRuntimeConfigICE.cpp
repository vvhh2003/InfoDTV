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

#include "MultiplexerRuntimeConfigICE.h"
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <Ice/SliceChecksums.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/ScopedArray.h>

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

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllChannelInfos_name = "GetAllChannelInfos";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllDataProviders_name = "GetAllDataProviders";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__AddChannel_name = "AddChannel";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__DelectChannel_name = "DelectChannel";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__CheckDataProviderConfig_name = "CheckDataProviderConfig";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChanneIsFixOutputCounter_name = "ModifyChanneIsFixOutputCounter";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelOutputBitRate_name = "ModifyChannelOutputBitRate";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelName_name = "ModifyChannelName";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProvider_name = "ModifyChannelDataProvider";

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProviderConfig_name = "ModifyChannelDataProviderConfig";

void
IceInternal::incRef(::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* p)
{
    p->__decRef();
}

void
InfoDTV::Multiplexer::RuntimeConfig::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
InfoDTV::Multiplexer::RuntimeConfig::__read(::IceInternal::BasicStream* __is, ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig;
        v->__copyFrom(proxy);
    }
}

void
InfoDTV::Multiplexer::RuntimeConfig::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
InfoDTV::Multiplexer::RuntimeConfig::__write(::IceInternal::BasicStream* __os, ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult v)
{
    __os->write(static_cast< ::Ice::Byte>(v));
}

void
InfoDTV::Multiplexer::RuntimeConfig::__read(::IceInternal::BasicStream* __is, ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult& v)
{
    ::Ice::Byte val;
    __is->read(val);
    v = static_cast< ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult>(val);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo::operator==(const DataProviderInfo& __rhs) const
{
    return !operator!=(__rhs);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo::operator!=(const DataProviderInfo& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(TypeID != __rhs.TypeID)
    {
        return true;
    }
    if(Name != __rhs.Name)
    {
        return true;
    }
    if(Info != __rhs.Info)
    {
        return true;
    }
    return false;
}

bool
InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo::operator<(const DataProviderInfo& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(TypeID < __rhs.TypeID)
    {
        return true;
    }
    else if(__rhs.TypeID < TypeID)
    {
        return false;
    }
    if(Name < __rhs.Name)
    {
        return true;
    }
    else if(__rhs.Name < Name)
    {
        return false;
    }
    if(Info < __rhs.Info)
    {
        return true;
    }
    else if(__rhs.Info < Info)
    {
        return false;
    }
    return false;
}

void
InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(TypeID);
    __os->write(Name);
    __os->write(Info);
}

void
InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo::__read(::IceInternal::BasicStream* __is)
{
    __is->read(TypeID);
    __is->read(Name);
    __is->read(Info);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo::operator==(const ChannelInfo& __rhs) const
{
    return !operator!=(__rhs);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo::operator!=(const ChannelInfo& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(ChannelName != __rhs.ChannelName)
    {
        return true;
    }
    if(OutputBitRate != __rhs.OutputBitRate)
    {
        return true;
    }
    if(IsFixOutputCounter != __rhs.IsFixOutputCounter)
    {
        return true;
    }
    if(DataProviderTypeID != __rhs.DataProviderTypeID)
    {
        return true;
    }
    if(DataProviderConfig != __rhs.DataProviderConfig)
    {
        return true;
    }
    return false;
}

bool
InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo::operator<(const ChannelInfo& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(ChannelName < __rhs.ChannelName)
    {
        return true;
    }
    else if(__rhs.ChannelName < ChannelName)
    {
        return false;
    }
    if(OutputBitRate < __rhs.OutputBitRate)
    {
        return true;
    }
    else if(__rhs.OutputBitRate < OutputBitRate)
    {
        return false;
    }
    if(IsFixOutputCounter < __rhs.IsFixOutputCounter)
    {
        return true;
    }
    else if(__rhs.IsFixOutputCounter < IsFixOutputCounter)
    {
        return false;
    }
    if(DataProviderTypeID < __rhs.DataProviderTypeID)
    {
        return true;
    }
    else if(__rhs.DataProviderTypeID < DataProviderTypeID)
    {
        return false;
    }
    if(DataProviderConfig < __rhs.DataProviderConfig)
    {
        return true;
    }
    else if(__rhs.DataProviderConfig < DataProviderConfig)
    {
        return false;
    }
    return false;
}

void
InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(ChannelName);
    __os->write(OutputBitRate);
    __os->write(IsFixOutputCounter);
    __os->write(DataProviderTypeID);
    __os->write(DataProviderConfig);
}

void
InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo::__read(::IceInternal::BasicStream* __is)
{
    __is->read(ChannelName);
    __is->read(OutputBitRate);
    __is->read(IsFixOutputCounter);
    __is->read(DataProviderTypeID);
    __is->read(DataProviderConfig);
}

void
InfoDTV::Multiplexer::RuntimeConfig::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo* begin, const ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo* end, ::InfoDTV::Multiplexer::RuntimeConfig::__U__DataProviderInfoSeq)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
InfoDTV::Multiplexer::RuntimeConfig::__read(::IceInternal::BasicStream* __is, ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq& v, ::InfoDTV::Multiplexer::RuntimeConfig::__U__DataProviderInfoSeq)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 3);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

void
InfoDTV::Multiplexer::RuntimeConfig::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo* begin, const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo* end, ::InfoDTV::Multiplexer::RuntimeConfig::__U__ChannelInfoSeq)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
InfoDTV::Multiplexer::RuntimeConfig::__read(::IceInternal::BasicStream* __is, ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq& v, ::InfoDTV::Multiplexer::RuntimeConfig::__U__ChannelInfoSeq)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 12);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

void
InfoDTV::Multiplexer::RuntimeConfig::__addObject(const MuxRuntimeConfigPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::__usesClasses(const MuxRuntimeConfigPtr& p)
{
    return p->__usesClasses();
}

void
InfoDTV::Multiplexer::RuntimeConfig::__decRefUnsafe(const MuxRuntimeConfigPtr& p)
{
    p->__decRefUnsafe();
}

void
InfoDTV::Multiplexer::RuntimeConfig::__clearHandleUnsafe(MuxRuntimeConfigPtr& p)
{
    p.__clearHandleUnsafe();
}

::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::GetAllChannelInfos(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllChannelInfos_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->GetAllChannelInfos(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapperRelaxed(__delBase, __ex, __cnt);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::GetAllDataProviders(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllDataProviders_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->GetAllDataProviders(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapperRelaxed(__delBase, __ex, __cnt);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo& aChannel, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__AddChannel_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->AddChannel(aChannel, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::DelectChannel(const ::std::string& aChannelName, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__DelectChannel_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->DelectChannel(aChannelName, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::std::string
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::CheckDataProviderConfig(const ::std::string& aProviderTypeID, const ::std::string& aTmpConfig, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__CheckDataProviderConfig_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->CheckDataProviderConfig(aProviderTypeID, aTmpConfig, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChanneIsFixOutputCounter(const ::std::string& aChannelName, bool aNewIsFixOutputCounter, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChanneIsFixOutputCounter_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->ModifyChanneIsFixOutputCounter(aChannelName, aNewIsFixOutputCounter, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelOutputBitRate(const ::std::string& aChannelName, ::Ice::Long aNewOutputBitRate, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelOutputBitRate_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->ModifyChannelOutputBitRate(aChannelName, aNewOutputBitRate, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelName(const ::std::string& aChannelName, const ::std::string& aNewChannelName, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelName_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->ModifyChannelName(aChannelName, aNewChannelName, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelDataProvider(const ::std::string& aChannelName, const ::std::string& aNewDataProviderTypeID, const ::std::string& aNewDataProviderConfig, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProvider_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->ModifyChannelDataProvider(aChannelName, aNewDataProviderTypeID, aNewDataProviderConfig, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelDataProviderConfig(const ::std::string& aChannelName, const ::std::string& aNewDataProviderConfig, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProviderConfig_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__delBase.get());
            return __del->ModifyChannelDataProviderConfig(aChannelName, aNewDataProviderConfig, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

const ::std::string&
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_staticId()
{
    return ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig);
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::operator==(const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::operator!=(const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::operator<(const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::operator<=(const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return l < r || l == r;
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::operator>(const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::InfoDTV::Multiplexer::RuntimeConfig::operator>=(const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::IceProxy::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return !(l < r);
}

::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::GetAllChannelInfos(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllChannelInfos_name, ::Ice::Idempotent, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq __ret;
        ::InfoDTV::Multiplexer::RuntimeConfig::__read(__is, __ret, ::InfoDTV::Multiplexer::RuntimeConfig::__U__ChannelInfoSeq());
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::GetAllDataProviders(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllDataProviders_name, ::Ice::Idempotent, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq __ret;
        ::InfoDTV::Multiplexer::RuntimeConfig::__read(__is, __ret, ::InfoDTV::Multiplexer::RuntimeConfig::__U__DataProviderInfoSeq());
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo& aChannel, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__AddChannel_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        aChannel.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult __ret;
        ::InfoDTV::Multiplexer::RuntimeConfig::__read(__is, __ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::DelectChannel(const ::std::string& aChannelName, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__DelectChannel_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aChannelName);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::std::string
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::CheckDataProviderConfig(const ::std::string& aProviderTypeID, const ::std::string& aTmpConfig, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__CheckDataProviderConfig_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aProviderTypeID);
        __os->write(aTmpConfig);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::std::string __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChanneIsFixOutputCounter(const ::std::string& aChannelName, bool aNewIsFixOutputCounter, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChanneIsFixOutputCounter_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aChannelName);
        __os->write(aNewIsFixOutputCounter);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelOutputBitRate(const ::std::string& aChannelName, ::Ice::Long aNewOutputBitRate, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelOutputBitRate_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aChannelName);
        __os->write(aNewOutputBitRate);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelName(const ::std::string& aChannelName, const ::std::string& aNewChannelName, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelName_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aChannelName);
        __os->write(aNewChannelName);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelDataProvider(const ::std::string& aChannelName, const ::std::string& aNewDataProviderTypeID, const ::std::string& aNewDataProviderConfig, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProvider_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aChannelName);
        __os->write(aNewDataProviderTypeID);
        __os->write(aNewDataProviderConfig);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelDataProviderConfig(const ::std::string& aChannelName, const ::std::string& aNewDataProviderConfig, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProviderConfig_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aChannelName);
        __os->write(aNewDataProviderConfig);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        bool __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::GetAllChannelInfos(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllChannelInfos_name, ::Ice::Idempotent, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->GetAllChannelInfos(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::GetAllDataProviders(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__GetAllDataProviders_name, ::Ice::Idempotent, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->GetAllDataProviders(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::AddChannel(const ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo& aChannel, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__AddChannel_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->AddChannel(aChannel, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

bool
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::DelectChannel(const ::std::string& aChannelName, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__DelectChannel_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->DelectChannel(aChannelName, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::std::string
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::CheckDataProviderConfig(const ::std::string& aProviderTypeID, const ::std::string& aTmpConfig, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__CheckDataProviderConfig_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::std::string __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->CheckDataProviderConfig(aProviderTypeID, aTmpConfig, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

bool
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChanneIsFixOutputCounter(const ::std::string& aChannelName, bool aNewIsFixOutputCounter, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChanneIsFixOutputCounter_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->ModifyChanneIsFixOutputCounter(aChannelName, aNewIsFixOutputCounter, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

bool
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelOutputBitRate(const ::std::string& aChannelName, ::Ice::Long aNewOutputBitRate, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelOutputBitRate_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->ModifyChannelOutputBitRate(aChannelName, aNewOutputBitRate, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

bool
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelName(const ::std::string& aChannelName, const ::std::string& aNewChannelName, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelName_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->ModifyChannelName(aChannelName, aNewChannelName, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

bool
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelDataProvider(const ::std::string& aChannelName, const ::std::string& aNewDataProviderTypeID, const ::std::string& aNewDataProviderConfig, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProvider_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->ModifyChannelDataProvider(aChannelName, aNewDataProviderTypeID, aNewDataProviderConfig, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

bool
IceDelegateD::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ModifyChannelDataProviderConfig(const ::std::string& aChannelName, const ::std::string& aNewDataProviderConfig, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig__ModifyChannelDataProviderConfig_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig* __servant = dynamic_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->ModifyChannelDataProviderConfig(aChannelName, aNewDataProviderConfig, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::Ice::ObjectPtr
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids[2] =
{
    "::Ice::Object",
    "::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig"
};

bool
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids + 2, _s);
}

::std::vector< ::std::string>
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids[0], &__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids[2]);
}

const ::std::string&
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_id(const ::Ice::Current&) const
{
    return __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids[1];
}

const ::std::string&
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_staticId()
{
    return __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_ids[1];
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___GetAllChannelInfos(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq __ret = GetAllChannelInfos(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::InfoDTV::Multiplexer::RuntimeConfig::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::InfoDTV::Multiplexer::RuntimeConfig::__U__ChannelInfoSeq());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___GetAllDataProviders(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq __ret = GetAllDataProviders(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::InfoDTV::Multiplexer::RuntimeConfig::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::InfoDTV::Multiplexer::RuntimeConfig::__U__DataProviderInfoSeq());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___AddChannel(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo aChannel;
    aChannel.__read(__is);
    ::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult __ret = AddChannel(aChannel, __current);
    ::InfoDTV::Multiplexer::RuntimeConfig::__write(__os, __ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___DelectChannel(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aChannelName;
    __is->read(aChannelName);
    bool __ret = DelectChannel(aChannelName, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___CheckDataProviderConfig(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aProviderTypeID;
    ::std::string aTmpConfig;
    __is->read(aProviderTypeID);
    __is->read(aTmpConfig);
    ::std::string __ret = CheckDataProviderConfig(aProviderTypeID, aTmpConfig, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___ModifyChanneIsFixOutputCounter(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aChannelName;
    bool aNewIsFixOutputCounter;
    __is->read(aChannelName);
    __is->read(aNewIsFixOutputCounter);
    bool __ret = ModifyChanneIsFixOutputCounter(aChannelName, aNewIsFixOutputCounter, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___ModifyChannelOutputBitRate(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aChannelName;
    ::Ice::Long aNewOutputBitRate;
    __is->read(aChannelName);
    __is->read(aNewOutputBitRate);
    bool __ret = ModifyChannelOutputBitRate(aChannelName, aNewOutputBitRate, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___ModifyChannelName(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aChannelName;
    ::std::string aNewChannelName;
    __is->read(aChannelName);
    __is->read(aNewChannelName);
    bool __ret = ModifyChannelName(aChannelName, aNewChannelName, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___ModifyChannelDataProvider(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aChannelName;
    ::std::string aNewDataProviderTypeID;
    ::std::string aNewDataProviderConfig;
    __is->read(aChannelName);
    __is->read(aNewDataProviderTypeID);
    __is->read(aNewDataProviderConfig);
    bool __ret = ModifyChannelDataProvider(aChannelName, aNewDataProviderTypeID, aNewDataProviderConfig, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::___ModifyChannelDataProviderConfig(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aChannelName;
    ::std::string aNewDataProviderConfig;
    __is->read(aChannelName);
    __is->read(aNewDataProviderConfig);
    bool __ret = ModifyChannelDataProviderConfig(aChannelName, aNewDataProviderConfig, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

static ::std::string __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_all[] =
{
    "AddChannel",
    "CheckDataProviderConfig",
    "DelectChannel",
    "GetAllChannelInfos",
    "GetAllDataProviders",
    "ModifyChanneIsFixOutputCounter",
    "ModifyChannelDataProvider",
    "ModifyChannelDataProviderConfig",
    "ModifyChannelName",
    "ModifyChannelOutputBitRate",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_all, __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_all + 14, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __InfoDTV__Multiplexer__RuntimeConfig__MuxRuntimeConfig_all)
    {
        case 0:
        {
            return ___AddChannel(in, current);
        }
        case 1:
        {
            return ___CheckDataProviderConfig(in, current);
        }
        case 2:
        {
            return ___DelectChannel(in, current);
        }
        case 3:
        {
            return ___GetAllChannelInfos(in, current);
        }
        case 4:
        {
            return ___GetAllDataProviders(in, current);
        }
        case 5:
        {
            return ___ModifyChanneIsFixOutputCounter(in, current);
        }
        case 6:
        {
            return ___ModifyChannelDataProvider(in, current);
        }
        case 7:
        {
            return ___ModifyChannelDataProviderConfig(in, current);
        }
        case 8:
        {
            return ___ModifyChannelName(in, current);
        }
        case 9:
        {
            return ___ModifyChannelOutputBitRate(in, current);
        }
        case 10:
        {
            return ___ice_id(in, current);
        }
        case 11:
        {
            return ___ice_ids(in, current);
        }
        case 12:
        {
            return ___ice_isA(in, current);
        }
        case 13:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig was not generated with stream support";
    throw ex;
}

void
InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig was not generated with stream support";
    throw ex;
}

void 
InfoDTV::Multiplexer::RuntimeConfig::__patch__MuxRuntimeConfigPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigPtr* p = static_cast< ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigPtr*>(__addr);
    assert(p);
    *p = ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfigPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig::ice_staticId();
        throw e;
    }
}

bool
InfoDTV::Multiplexer::RuntimeConfig::operator==(const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::operator!=(const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::operator<(const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::operator<=(const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return l < r || l == r;
}

bool
InfoDTV::Multiplexer::RuntimeConfig::operator>(const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return !(l < r) && !(l == r);
}

bool
InfoDTV::Multiplexer::RuntimeConfig::operator>=(const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& l, const ::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig& r)
{
    return !(l < r);
}

static const char* __sliceChecksums[] =
{
    "::InfoDTV::Multiplexer::RuntimeConfig::AddChannelResult", "2a179cece94f578788cf4f18ac4c847d",
    "::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfo", "761733ae7dfa24d2e23a5b158047ce",
    "::InfoDTV::Multiplexer::RuntimeConfig::ChannelInfoSeq", "b236837a8c23dafe75f1307441305480",
    "::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfo", "f23efbeef2ad44ac4ed75fa8c171c",
    "::InfoDTV::Multiplexer::RuntimeConfig::DataProviderInfoSeq", "775d58bc2ae7e2fd2c92f230a3d552",
    "::InfoDTV::Multiplexer::RuntimeConfig::MuxRuntimeConfig", "39abad73f8c1f91cf9faa5b0af1678db",
    0
};
static IceInternal::SliceChecksumInit __sliceChecksumInit(__sliceChecksums);
