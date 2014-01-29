// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `DynICEBufferSender.ice'

#include "DynICEBufferSender.h"
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

static const ::std::string __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer__SendBuffer_name = "SendBuffer";

void
IceInternal::incRef(::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer* p)
{
    p->__decRef();
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__read(::IceInternal::BasicStream* __is, ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer;
        v->__copyFrom(proxy);
    }
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__write(::IceInternal::BasicStream* __os, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__addObject(const DynamicBufferTransferPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::__usesClasses(const DynamicBufferTransferPtr& p)
{
    return p->__usesClasses();
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__decRefUnsafe(const DynamicBufferTransferPtr& p)
{
    p->__decRefUnsafe();
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__clearHandleUnsafe(DynamicBufferTransferPtr& p)
{
    p.__clearHandleUnsafe();
}

void
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::SendBuffer(const ::std::string& aServiceName, const ::std::string& aBufferGuid, ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate();
            ::IceDelegate::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer* __del = dynamic_cast< ::IceDelegate::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer*>(__delBase.get());
            __del->SendBuffer(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, __ctx);
            return;
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
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_staticId()
{
    return ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer);
}

bool
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::operator==(const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::operator!=(const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::operator<(const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::operator<=(const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return l < r || l == r;
}

bool
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::operator>(const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::operator>=(const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::IceProxy::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return !(l < r);
}

void
IceDelegateM::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::SendBuffer(const ::std::string& aServiceName, const ::std::string& aBufferGuid, ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer__SendBuffer_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(aServiceName);
        __os->write(aBufferGuid);
        __os->write(aSendIndex);
        __os->write(aTotalBufferLength);
        __os->write(aCurrentBufferLength);
        if(aSeq.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            __os->write(&aSeq[0], &aSeq[0] + aSeq.size());
        }
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
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateD::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::SendBuffer(const ::std::string& aServiceName, const ::std::string& aBufferGuid, ::Ice::Int aSendIndex, ::Ice::Int aTotalBufferLength, ::Ice::Int aCurrentBufferLength, const ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq& aSeq, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer__SendBuffer_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer* __servant = dynamic_cast< ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer*>(__direct.servant().get());
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
                __servant->SendBuffer(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, __current);
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
        return;
    }
}

::Ice::ObjectPtr
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids[2] =
{
    "::Ice::Object",
    "::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer"
};

bool
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids, __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids + 2, _s);
}

::std::vector< ::std::string>
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids[0], &__InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids[2]);
}

const ::std::string&
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_id(const ::Ice::Current&) const
{
    return __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids[1];
}

const ::std::string&
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_staticId()
{
    return __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_ids[1];
}

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::___SendBuffer(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string aServiceName;
    ::std::string aBufferGuid;
    ::Ice::Int aSendIndex;
    ::Ice::Int aTotalBufferLength;
    ::Ice::Int aCurrentBufferLength;
    ::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq aSeq;
    __is->read(aServiceName);
    __is->read(aBufferGuid);
    __is->read(aSendIndex);
    __is->read(aTotalBufferLength);
    __is->read(aCurrentBufferLength);
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___aSeq;
    __is->read(___aSeq);
    ::std::vector< ::Ice::Byte>(___aSeq.first, ___aSeq.second).swap(aSeq);
    SendBuffer(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, __current);
    return ::IceInternal::DispatchOK;
}

static ::std::string __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_all[] =
{
    "SendBuffer",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::IceInternal::DispatchStatus
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_all, __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_all + 5, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __InfoDTV__Multiplexer__Dynamic__Provider__DynamicBufferTransfer_all)
    {
        case 0:
        {
            return ___SendBuffer(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__write(::IceInternal::BasicStream* __os) const
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
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__read(::IceInternal::BasicStream* __is, bool __rid)
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
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer was not generated with stream support";
    throw ex;
}

void
InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer was not generated with stream support";
    throw ex;
}

void
InfoDTV::Multiplexer::Dynamic::Provider::__patch__DynamicBufferTransferPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPtr* p = static_cast< ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPtr*>(__addr);
    assert(p);
    *p = ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransferPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer::ice_staticId();
        throw e;
    }
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::operator==(const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::operator!=(const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::operator<(const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::operator<=(const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return l < r || l == r;
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::operator>(const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return !(l < r) && !(l == r);
}

bool
InfoDTV::Multiplexer::Dynamic::Provider::operator>=(const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& l, const ::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer& r)
{
    return !(l < r);
}

static const char* __sliceChecksums[] =
{
    "::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq", "eae189e6d7b57b6f9628e78293d6d7",
    "::InfoDTV::Multiplexer::Dynamic::Provider::DynamicBufferTransfer", "2acc375f3bb8ef568c79601d8e6b8663",
    0
};
static IceInternal::SliceChecksumInit __sliceChecksumInit(__sliceChecksums);
