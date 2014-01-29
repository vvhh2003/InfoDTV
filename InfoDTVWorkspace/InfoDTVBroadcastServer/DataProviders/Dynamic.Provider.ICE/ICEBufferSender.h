// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `ICEBufferSender.ice'

#ifndef __ICEBufferSender_h__
#define __ICEBufferSender_h__

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

namespace Dynamic
{

namespace Provider
{

class BufferTransfer;
bool operator==(const BufferTransfer&, const BufferTransfer&);
bool operator!=(const BufferTransfer&, const BufferTransfer&);
bool operator<(const BufferTransfer&, const BufferTransfer&);
bool operator<=(const BufferTransfer&, const BufferTransfer&);
bool operator>(const BufferTransfer&, const BufferTransfer&);
bool operator>=(const BufferTransfer&, const BufferTransfer&);

}

}

}

}

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace Dynamic
{

namespace Provider
{

class BufferTransfer;
bool operator==(const BufferTransfer&, const BufferTransfer&);
bool operator!=(const BufferTransfer&, const BufferTransfer&);
bool operator<(const BufferTransfer&, const BufferTransfer&);
bool operator<=(const BufferTransfer&, const BufferTransfer&);
bool operator>(const BufferTransfer&, const BufferTransfer&);
bool operator>=(const BufferTransfer&, const BufferTransfer&);

}

}

}

}

namespace IceInternal
{

void incRef(::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer*);
void decRef(::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer*);

void incRef(::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer*);
void decRef(::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer*);

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace Dynamic
{

namespace Provider
{

typedef ::IceInternal::Handle< ::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer> BufferTransferPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer> BufferTransferPrx;

void __write(::IceInternal::BasicStream*, const BufferTransferPrx&);
void __read(::IceInternal::BasicStream*, BufferTransferPrx&);
void __write(::IceInternal::BasicStream*, const BufferTransferPtr&);
void __patch__BufferTransferPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const BufferTransferPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const BufferTransferPtr&);
void __decRefUnsafe(const BufferTransferPtr&);
void __clearHandleUnsafe(BufferTransferPtr&);

}

}

}

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace Dynamic
{

namespace Provider
{

typedef ::std::vector< ::Ice::Byte> ByteSeq;

class __U__ByteSeq { };

}

}

}

}

namespace IceProxy
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace Dynamic
{

namespace Provider
{

class BufferTransfer : virtual public ::IceProxy::Ice::Object
{
public:

    void Login()
    {
        Login(0);
    }
    void Login(const ::Ice::Context& __ctx)
    {
        Login(&__ctx);
    }
    
private:

    void Login(const ::Ice::Context*);
    
public:

    void SendBuffer(const ::std::string& aServiceName, ::Ice::Int aBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq)
    {
        SendBuffer(aServiceName, aBufferLength, aSeq, 0);
    }
    void SendBuffer(const ::std::string& aServiceName, ::Ice::Int aBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq, const ::Ice::Context& __ctx)
    {
        SendBuffer(aServiceName, aBufferLength, aSeq, &__ctx);
    }
    
private:

    void SendBuffer(const ::std::string&, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*);
    
public:

    void SendBuffer2(const ::std::string& aServiceName, const ::std::string& aBufferGuid, ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq)
    {
        SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, 0);
    }
    void SendBuffer2(const ::std::string& aServiceName, const ::std::string& aBufferGuid, ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq, const ::Ice::Context& __ctx)
    {
        SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, &__ctx);
    }
    
private:

    void SendBuffer2(const ::std::string&, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*);
    
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

}

namespace IceDelegate
{

namespace InfoDTV
{

namespace Multiplexer
{

namespace Dynamic
{

namespace Provider
{

class BufferTransfer : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void Login(const ::Ice::Context*) = 0;

    virtual void SendBuffer(const ::std::string&, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*) = 0;

    virtual void SendBuffer2(const ::std::string&, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*) = 0;
};

}

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

namespace Dynamic
{

namespace Provider
{

class BufferTransfer : virtual public ::IceDelegate::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer,
                       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void Login(const ::Ice::Context*);

    virtual void SendBuffer(const ::std::string&, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*);

    virtual void SendBuffer2(const ::std::string&, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*);
};

}

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

namespace Dynamic
{

namespace Provider
{

class BufferTransfer : virtual public ::IceDelegate::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer,
                       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void Login(const ::Ice::Context*);

    virtual void SendBuffer(const ::std::string&, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*);

    virtual void SendBuffer2(const ::std::string&, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Context*);
};

}

}

}

}

}

namespace InfoDTV
{

namespace Multiplexer
{

namespace Dynamic
{

namespace Provider
{

class BufferTransfer : virtual public ::Ice::Object
{
public:

    typedef BufferTransferPrx ProxyType;
    typedef BufferTransferPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void Login(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Login(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void SendBuffer(const ::std::string&, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SendBuffer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void SendBuffer2(const ::std::string&, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SendBuffer2(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__BufferTransferPtr(void*, ::Ice::ObjectPtr&);

}

}

}

}

#endif
