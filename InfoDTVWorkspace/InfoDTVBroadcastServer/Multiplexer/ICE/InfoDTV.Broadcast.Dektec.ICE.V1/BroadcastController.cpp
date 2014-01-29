// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `BroadcastController.ice'

#include "BroadcastController.h"
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

static const ::std::string __InfoDTV__Broadcast__BroadcastController__StartBroadcast_name = "StartBroadcast";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__StopBroadcast_name = "StopBroadcast";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__RestartBroadcast_name = "RestartBroadcast";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__IsInBroadcasting_name = "IsInBroadcasting";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__GetBroadcastBitRate_name = "GetBroadcastBitRate";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__GetRuntimeConfigDatabaseNameList_name = "GetRuntimeConfigDatabaseNameList";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__GetBroadcastConfigDBName_name = "GetBroadcastConfigDBName";

static const ::std::string __InfoDTV__Broadcast__BroadcastController__DeleteRuntimeConfigDB_name = "DeleteRuntimeConfigDB";

void
IceInternal::incRef(::InfoDTV::Broadcast::BroadcastController* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::InfoDTV::Broadcast::BroadcastController* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::InfoDTV::Broadcast::BroadcastController* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::InfoDTV::Broadcast::BroadcastController* p)
{
    p->__decRef();
}

void
InfoDTV::Broadcast::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Broadcast::BroadcastControllerPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
InfoDTV::Broadcast::__read(::IceInternal::BasicStream* __is, ::InfoDTV::Broadcast::BroadcastControllerPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::InfoDTV::Broadcast::BroadcastController;
        v->__copyFrom(proxy);
    }
}

void
InfoDTV::Broadcast::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Broadcast::BroadcastControllerPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
InfoDTV::Broadcast::__addObject(const BroadcastControllerPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
InfoDTV::Broadcast::__usesClasses(const BroadcastControllerPtr& p)
{
    return p->__usesClasses();
}

void
InfoDTV::Broadcast::__decRefUnsafe(const BroadcastControllerPtr& p)
{
    p->__decRefUnsafe();
}

void
InfoDTV::Broadcast::__clearHandleUnsafe(BroadcastControllerPtr& p)
{
    p.__clearHandleUnsafe();
}

bool
IceProxy::InfoDTV::Broadcast::BroadcastController::StartBroadcast(const ::std::string& aConfigDBName, ::Ice::Int aOutputBitRate, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__StartBroadcast_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->StartBroadcast(aConfigDBName, aOutputBitRate, __ctx);
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
IceProxy::InfoDTV::Broadcast::BroadcastController::StopBroadcast(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__StopBroadcast_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->StopBroadcast(__ctx);
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
IceProxy::InfoDTV::Broadcast::BroadcastController::RestartBroadcast(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__RestartBroadcast_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->RestartBroadcast(__ctx);
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
IceProxy::InfoDTV::Broadcast::BroadcastController::IsInBroadcasting(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__IsInBroadcasting_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->IsInBroadcasting(__ctx);
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

::Ice::Int
IceProxy::InfoDTV::Broadcast::BroadcastController::GetBroadcastBitRate(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__GetBroadcastBitRate_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->GetBroadcastBitRate(__ctx);
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

::InfoDTV::Broadcast::StringSeq
IceProxy::InfoDTV::Broadcast::BroadcastController::GetRuntimeConfigDatabaseNameList(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__GetRuntimeConfigDatabaseNameList_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->GetRuntimeConfigDatabaseNameList(__ctx);
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
IceProxy::InfoDTV::Broadcast::BroadcastController::GetBroadcastConfigDBName(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__GetBroadcastConfigDBName_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->GetBroadcastConfigDBName(__ctx);
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

::Ice::Int
IceProxy::InfoDTV::Broadcast::BroadcastController::DeleteRuntimeConfigDB(const ::std::string& RuntimeConfigDB, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__InfoDTV__Broadcast__BroadcastController__DeleteRuntimeConfigDB_name);
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Broadcast::BroadcastController* __del = dynamic_cast< ::IceDelegate::InfoDTV::Broadcast::BroadcastController*>(__delBase.get());
            return __del->DeleteRuntimeConfigDB(RuntimeConfigDB, __ctx);
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
IceProxy::InfoDTV::Broadcast::BroadcastController::ice_staticId()
{
    return ::InfoDTV::Broadcast::BroadcastController::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::InfoDTV::Broadcast::BroadcastController::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::InfoDTV::Broadcast::BroadcastController);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::InfoDTV::Broadcast::BroadcastController::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::InfoDTV::Broadcast::BroadcastController);
}

bool
IceProxy::InfoDTV::Broadcast::operator==(const ::IceProxy::InfoDTV::Broadcast::BroadcastController& l, const ::IceProxy::InfoDTV::Broadcast::BroadcastController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Broadcast::operator!=(const ::IceProxy::InfoDTV::Broadcast::BroadcastController& l, const ::IceProxy::InfoDTV::Broadcast::BroadcastController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Broadcast::operator<(const ::IceProxy::InfoDTV::Broadcast::BroadcastController& l, const ::IceProxy::InfoDTV::Broadcast::BroadcastController& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Broadcast::operator<=(const ::IceProxy::InfoDTV::Broadcast::BroadcastController& l, const ::IceProxy::InfoDTV::Broadcast::BroadcastController& r)
{
    return l < r || l == r;
}

bool
IceProxy::InfoDTV::Broadcast::operator>(const ::IceProxy::InfoDTV::Broadcast::BroadcastController& l, const ::IceProxy::InfoDTV::Broadcast::BroadcastController& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::InfoDTV::Broadcast::operator>=(const ::IceProxy::InfoDTV::Broadcast::BroadcastController& l, const ::IceProxy::InfoDTV::Broadcast::BroadcastController& r)
{
    return !(l < r);
}

bool
IceDelegateM::InfoDTV::Broadcast::BroadcastController::StartBroadcast(const ::std::string& aConfigDBName, ::Ice::Int aOutputBitRate, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__StartBroadcast_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aConfigDBName);
        __os->write(aOutputBitRate);
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
IceDelegateM::InfoDTV::Broadcast::BroadcastController::StopBroadcast(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__StopBroadcast_name, ::Ice::Normal, __context, __compress);
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
IceDelegateM::InfoDTV::Broadcast::BroadcastController::RestartBroadcast(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__RestartBroadcast_name, ::Ice::Normal, __context, __compress);
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
IceDelegateM::InfoDTV::Broadcast::BroadcastController::IsInBroadcasting(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__IsInBroadcasting_name, ::Ice::Normal, __context, __compress);
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

::Ice::Int
IceDelegateM::InfoDTV::Broadcast::BroadcastController::GetBroadcastBitRate(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__GetBroadcastBitRate_name, ::Ice::Normal, __context, __compress);
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
        ::Ice::Int __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::InfoDTV::Broadcast::StringSeq
IceDelegateM::InfoDTV::Broadcast::BroadcastController::GetRuntimeConfigDatabaseNameList(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__GetRuntimeConfigDatabaseNameList_name, ::Ice::Normal, __context, __compress);
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
        ::InfoDTV::Broadcast::StringSeq __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::std::string
IceDelegateM::InfoDTV::Broadcast::BroadcastController::GetBroadcastConfigDBName(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__GetBroadcastConfigDBName_name, ::Ice::Normal, __context, __compress);
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

::Ice::Int
IceDelegateM::InfoDTV::Broadcast::BroadcastController::DeleteRuntimeConfigDB(const ::std::string& RuntimeConfigDB, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Broadcast__BroadcastController__DeleteRuntimeConfigDB_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(RuntimeConfigDB);
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
        ::Ice::Int __ret;
        __is->read(__ret);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateD::InfoDTV::Broadcast::BroadcastController::StartBroadcast(const ::std::string& aConfigDBName, ::Ice::Int aOutputBitRate, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__StartBroadcast_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->StartBroadcast(aConfigDBName, aOutputBitRate, __current);
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
IceDelegateD::InfoDTV::Broadcast::BroadcastController::StopBroadcast(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__StopBroadcast_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->StopBroadcast(__current);
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
IceDelegateD::InfoDTV::Broadcast::BroadcastController::RestartBroadcast(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__RestartBroadcast_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->RestartBroadcast(__current);
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
IceDelegateD::InfoDTV::Broadcast::BroadcastController::IsInBroadcasting(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__IsInBroadcasting_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        bool __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->IsInBroadcasting(__current);
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

::Ice::Int
IceDelegateD::InfoDTV::Broadcast::BroadcastController::GetBroadcastBitRate(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__GetBroadcastBitRate_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::Ice::Int __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->GetBroadcastBitRate(__current);
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

::InfoDTV::Broadcast::StringSeq
IceDelegateD::InfoDTV::Broadcast::BroadcastController::GetRuntimeConfigDatabaseNameList(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__GetRuntimeConfigDatabaseNameList_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::InfoDTV::Broadcast::StringSeq __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->GetRuntimeConfigDatabaseNameList(__current);
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
IceDelegateD::InfoDTV::Broadcast::BroadcastController::GetBroadcastConfigDBName(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__GetBroadcastConfigDBName_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::std::string __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->GetBroadcastConfigDBName(__current);
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

::Ice::Int
IceDelegateD::InfoDTV::Broadcast::BroadcastController::DeleteRuntimeConfigDB(const ::std::string& RuntimeConfigDB, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Broadcast__BroadcastController__DeleteRuntimeConfigDB_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::Ice::Int __ret;
        try
        {
            ::InfoDTV::Broadcast::BroadcastController* __servant = dynamic_cast< ::InfoDTV::Broadcast::BroadcastController*>(__direct.servant().get());
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
                __ret = __servant->DeleteRuntimeConfigDB(RuntimeConfigDB, __current);
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
InfoDTV::Broadcast::BroadcastController::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __InfoDTV__Broadcast__BroadcastController_ids[2] =
{
    "::Ice::Object",
    "::InfoDTV::Broadcast::BroadcastController"
};

bool
InfoDTV::Broadcast::BroadcastController::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__InfoDTV__Broadcast__BroadcastController_ids, __InfoDTV__Broadcast__BroadcastController_ids + 2, _s);
}

::std::vector< ::std::string>
InfoDTV::Broadcast::BroadcastController::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__InfoDTV__Broadcast__BroadcastController_ids[0], &__InfoDTV__Broadcast__BroadcastController_ids[2]);
}

const ::std::string&
InfoDTV::Broadcast::BroadcastController::ice_id(const ::Ice::Current&) const
{
    return __InfoDTV__Broadcast__BroadcastController_ids[1];
}

const ::std::string&
InfoDTV::Broadcast::BroadcastController::ice_staticId()
{
    return __InfoDTV__Broadcast__BroadcastController_ids[1];
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___StartBroadcast(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string aConfigDBName;
    ::Ice::Int aOutputBitRate;
    __is->read(aConfigDBName);
    __is->read(aOutputBitRate);
    bool __ret = StartBroadcast(aConfigDBName, aOutputBitRate, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___StopBroadcast(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = StopBroadcast(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___RestartBroadcast(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = RestartBroadcast(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___IsInBroadcasting(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    bool __ret = IsInBroadcasting(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___GetBroadcastBitRate(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::Int __ret = GetBroadcastBitRate(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___GetRuntimeConfigDatabaseNameList(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::InfoDTV::Broadcast::StringSeq __ret = GetRuntimeConfigDatabaseNameList(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&__ret[0], &__ret[0] + __ret.size());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___GetBroadcastConfigDBName(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = GetBroadcastConfigDBName(__current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::___DeleteRuntimeConfigDB(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string RuntimeConfigDB;
    __is->read(RuntimeConfigDB);
    ::Ice::Int __ret = DeleteRuntimeConfigDB(RuntimeConfigDB, __current);
    __os->write(__ret);
    return ::IceInternal::DispatchOK;
}

static ::std::string __InfoDTV__Broadcast__BroadcastController_all[] =
{
    "DeleteRuntimeConfigDB",
    "GetBroadcastBitRate",
    "GetBroadcastConfigDBName",
    "GetRuntimeConfigDatabaseNameList",
    "IsInBroadcasting",
    "RestartBroadcast",
    "StartBroadcast",
    "StopBroadcast",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
InfoDTV::Broadcast::BroadcastController::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__InfoDTV__Broadcast__BroadcastController_all, __InfoDTV__Broadcast__BroadcastController_all + 12, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __InfoDTV__Broadcast__BroadcastController_all)
    {
        case 0:
        {
            return ___DeleteRuntimeConfigDB(in, current);
        }
        case 1:
        {
            return ___GetBroadcastBitRate(in, current);
        }
        case 2:
        {
            return ___GetBroadcastConfigDBName(in, current);
        }
        case 3:
        {
            return ___GetRuntimeConfigDatabaseNameList(in, current);
        }
        case 4:
        {
            return ___IsInBroadcasting(in, current);
        }
        case 5:
        {
            return ___RestartBroadcast(in, current);
        }
        case 6:
        {
            return ___StartBroadcast(in, current);
        }
        case 7:
        {
            return ___StopBroadcast(in, current);
        }
        case 8:
        {
            return ___ice_id(in, current);
        }
        case 9:
        {
            return ___ice_ids(in, current);
        }
        case 10:
        {
            return ___ice_isA(in, current);
        }
        case 11:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
InfoDTV::Broadcast::BroadcastController::__write(::IceInternal::BasicStream* __os) const
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
InfoDTV::Broadcast::BroadcastController::__read(::IceInternal::BasicStream* __is, bool __rid)
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
InfoDTV::Broadcast::BroadcastController::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type InfoDTV::Broadcast::BroadcastController was not generated with stream support";
    throw ex;
}

void
InfoDTV::Broadcast::BroadcastController::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type InfoDTV::Broadcast::BroadcastController was not generated with stream support";
    throw ex;
}

void 
InfoDTV::Broadcast::__patch__BroadcastControllerPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::InfoDTV::Broadcast::BroadcastControllerPtr* p = static_cast< ::InfoDTV::Broadcast::BroadcastControllerPtr*>(__addr);
    assert(p);
    *p = ::InfoDTV::Broadcast::BroadcastControllerPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::InfoDTV::Broadcast::BroadcastController::ice_staticId();
        throw e;
    }
}

bool
InfoDTV::Broadcast::operator==(const ::InfoDTV::Broadcast::BroadcastController& l, const ::InfoDTV::Broadcast::BroadcastController& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Broadcast::operator!=(const ::InfoDTV::Broadcast::BroadcastController& l, const ::InfoDTV::Broadcast::BroadcastController& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Broadcast::operator<(const ::InfoDTV::Broadcast::BroadcastController& l, const ::InfoDTV::Broadcast::BroadcastController& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Broadcast::operator<=(const ::InfoDTV::Broadcast::BroadcastController& l, const ::InfoDTV::Broadcast::BroadcastController& r)
{
    return l < r || l == r;
}

bool
InfoDTV::Broadcast::operator>(const ::InfoDTV::Broadcast::BroadcastController& l, const ::InfoDTV::Broadcast::BroadcastController& r)
{
    return !(l < r) && !(l == r);
}

bool
InfoDTV::Broadcast::operator>=(const ::InfoDTV::Broadcast::BroadcastController& l, const ::InfoDTV::Broadcast::BroadcastController& r)
{
    return !(l < r);
}

static const char* __sliceChecksums[] =
{
    "::InfoDTV::Broadcast::BroadcastController", "e9ad99caf966b2584efe91e88ea04b18",
    "::InfoDTV::Broadcast::StringSeq", "7986f19514e3b04fbe4af53c7446e563",
    0
};
static IceInternal::SliceChecksumInit __sliceChecksumInit(__sliceChecksums);
