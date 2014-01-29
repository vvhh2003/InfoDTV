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

#ifndef __BroadcastController_h__
#define __BroadcastController_h__

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

namespace Broadcast
{

class BroadcastController;
bool operator==(const BroadcastController&, const BroadcastController&);
bool operator!=(const BroadcastController&, const BroadcastController&);
bool operator<(const BroadcastController&, const BroadcastController&);
bool operator<=(const BroadcastController&, const BroadcastController&);
bool operator>(const BroadcastController&, const BroadcastController&);
bool operator>=(const BroadcastController&, const BroadcastController&);

}

}

}

namespace InfoDTV
{

namespace Broadcast
{

class BroadcastController;
bool operator==(const BroadcastController&, const BroadcastController&);
bool operator!=(const BroadcastController&, const BroadcastController&);
bool operator<(const BroadcastController&, const BroadcastController&);
bool operator<=(const BroadcastController&, const BroadcastController&);
bool operator>(const BroadcastController&, const BroadcastController&);
bool operator>=(const BroadcastController&, const BroadcastController&);

}

}

namespace IceInternal
{

void incRef(::InfoDTV::Broadcast::BroadcastController*);
void decRef(::InfoDTV::Broadcast::BroadcastController*);

void incRef(::IceProxy::InfoDTV::Broadcast::BroadcastController*);
void decRef(::IceProxy::InfoDTV::Broadcast::BroadcastController*);

}

namespace InfoDTV
{

namespace Broadcast
{

typedef ::IceInternal::Handle< ::InfoDTV::Broadcast::BroadcastController> BroadcastControllerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::InfoDTV::Broadcast::BroadcastController> BroadcastControllerPrx;

void __write(::IceInternal::BasicStream*, const BroadcastControllerPrx&);
void __read(::IceInternal::BasicStream*, BroadcastControllerPrx&);
void __write(::IceInternal::BasicStream*, const BroadcastControllerPtr&);
void __patch__BroadcastControllerPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const BroadcastControllerPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const BroadcastControllerPtr&);
void __decRefUnsafe(const BroadcastControllerPtr&);
void __clearHandleUnsafe(BroadcastControllerPtr&);

}

}

namespace InfoDTV
{

namespace Broadcast
{

typedef ::std::vector< ::std::string> StringSeq;

class __U__StringSeq { };

}

}

namespace IceProxy
{

namespace InfoDTV
{

namespace Broadcast
{

class BroadcastController : virtual public ::IceProxy::Ice::Object
{
public:

    bool StartBroadcast(const ::std::string& aConfigDBName, ::Ice::Int aOutputBitRate)
    {
        return StartBroadcast(aConfigDBName, aOutputBitRate, 0);
    }
    bool StartBroadcast(const ::std::string& aConfigDBName, ::Ice::Int aOutputBitRate, const ::Ice::Context& __ctx)
    {
        return StartBroadcast(aConfigDBName, aOutputBitRate, &__ctx);
    }
    
private:

    bool StartBroadcast(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    bool StopBroadcast()
    {
        return StopBroadcast(0);
    }
    bool StopBroadcast(const ::Ice::Context& __ctx)
    {
        return StopBroadcast(&__ctx);
    }
    
private:

    bool StopBroadcast(const ::Ice::Context*);
    
public:

    bool RestartBroadcast()
    {
        return RestartBroadcast(0);
    }
    bool RestartBroadcast(const ::Ice::Context& __ctx)
    {
        return RestartBroadcast(&__ctx);
    }
    
private:

    bool RestartBroadcast(const ::Ice::Context*);
    
public:

    bool IsInBroadcasting()
    {
        return IsInBroadcasting(0);
    }
    bool IsInBroadcasting(const ::Ice::Context& __ctx)
    {
        return IsInBroadcasting(&__ctx);
    }
    
private:

    bool IsInBroadcasting(const ::Ice::Context*);
    
public:

    ::Ice::Int GetBroadcastBitRate()
    {
        return GetBroadcastBitRate(0);
    }
    ::Ice::Int GetBroadcastBitRate(const ::Ice::Context& __ctx)
    {
        return GetBroadcastBitRate(&__ctx);
    }
    
private:

    ::Ice::Int GetBroadcastBitRate(const ::Ice::Context*);
    
public:

    ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList()
    {
        return GetRuntimeConfigDatabaseNameList(0);
    }
    ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Context& __ctx)
    {
        return GetRuntimeConfigDatabaseNameList(&__ctx);
    }
    
private:

    ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Context*);
    
public:

    ::std::string GetBroadcastConfigDBName()
    {
        return GetBroadcastConfigDBName(0);
    }
    ::std::string GetBroadcastConfigDBName(const ::Ice::Context& __ctx)
    {
        return GetBroadcastConfigDBName(&__ctx);
    }
    
private:

    ::std::string GetBroadcastConfigDBName(const ::Ice::Context*);
    
public:

    ::Ice::Int DeleteRuntimeConfigDB(const ::std::string& RuntimeConfigDB)
    {
        return DeleteRuntimeConfigDB(RuntimeConfigDB, 0);
    }
    ::Ice::Int DeleteRuntimeConfigDB(const ::std::string& RuntimeConfigDB, const ::Ice::Context& __ctx)
    {
        return DeleteRuntimeConfigDB(RuntimeConfigDB, &__ctx);
    }
    
private:

    ::Ice::Int DeleteRuntimeConfigDB(const ::std::string&, const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

}

namespace IceDelegate
{

namespace InfoDTV
{

namespace Broadcast
{

class BroadcastController : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool StartBroadcast(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual bool StopBroadcast(const ::Ice::Context*) = 0;

    virtual bool RestartBroadcast(const ::Ice::Context*) = 0;

    virtual bool IsInBroadcasting(const ::Ice::Context*) = 0;

    virtual ::Ice::Int GetBroadcastBitRate(const ::Ice::Context*) = 0;

    virtual ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Context*) = 0;

    virtual ::std::string GetBroadcastConfigDBName(const ::Ice::Context*) = 0;

    virtual ::Ice::Int DeleteRuntimeConfigDB(const ::std::string&, const ::Ice::Context*) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace InfoDTV
{

namespace Broadcast
{

class BroadcastController : virtual public ::IceDelegate::InfoDTV::Broadcast::BroadcastController,
                            virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool StartBroadcast(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual bool StopBroadcast(const ::Ice::Context*);

    virtual bool RestartBroadcast(const ::Ice::Context*);

    virtual bool IsInBroadcasting(const ::Ice::Context*);

    virtual ::Ice::Int GetBroadcastBitRate(const ::Ice::Context*);

    virtual ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Context*);

    virtual ::std::string GetBroadcastConfigDBName(const ::Ice::Context*);

    virtual ::Ice::Int DeleteRuntimeConfigDB(const ::std::string&, const ::Ice::Context*);
};

}

}

}

namespace IceDelegateD
{

namespace InfoDTV
{

namespace Broadcast
{

class BroadcastController : virtual public ::IceDelegate::InfoDTV::Broadcast::BroadcastController,
                            virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool StartBroadcast(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual bool StopBroadcast(const ::Ice::Context*);

    virtual bool RestartBroadcast(const ::Ice::Context*);

    virtual bool IsInBroadcasting(const ::Ice::Context*);

    virtual ::Ice::Int GetBroadcastBitRate(const ::Ice::Context*);

    virtual ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Context*);

    virtual ::std::string GetBroadcastConfigDBName(const ::Ice::Context*);

    virtual ::Ice::Int DeleteRuntimeConfigDB(const ::std::string&, const ::Ice::Context*);
};

}

}

}

namespace InfoDTV
{

namespace Broadcast
{

class BroadcastController : virtual public ::Ice::Object
{
public:

    typedef BroadcastControllerPrx ProxyType;
    typedef BroadcastControllerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool StartBroadcast(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___StartBroadcast(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool StopBroadcast(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___StopBroadcast(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RestartBroadcast(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RestartBroadcast(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsInBroadcasting(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsInBroadcasting(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetBroadcastBitRate(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetBroadcastBitRate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::InfoDTV::Broadcast::StringSeq GetRuntimeConfigDatabaseNameList(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetRuntimeConfigDatabaseNameList(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetBroadcastConfigDBName(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetBroadcastConfigDBName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int DeleteRuntimeConfigDB(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteRuntimeConfigDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__BroadcastControllerPtr(void*, ::Ice::ObjectPtr&);

}

}

#endif
