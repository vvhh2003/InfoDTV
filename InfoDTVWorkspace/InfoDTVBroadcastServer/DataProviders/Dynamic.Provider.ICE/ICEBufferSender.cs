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

using _System = System;
using _Microsoft = Microsoft;

namespace InfoDTV
{
    namespace Multiplexer
    {
        namespace Dynamic
        {
            namespace Provider
            {
                public interface BufferTransfer : Ice.Object, BufferTransferOperations_, BufferTransferOperationsNC_
                {
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
                public interface BufferTransferPrx : Ice.ObjectPrx
                {
                    void Login();
                    void Login(Ice.Context context__);

                    void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq);
                    void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Context context__);

                    void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq);
                    void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Context context__);
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
                public interface BufferTransferOperations_
                {
                    void Login(Ice.Current current__);

                    void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Current current__);

                    void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Current current__);
                }

                public interface BufferTransferOperationsNC_
                {
                    void Login();

                    void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq);

                    void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq);
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
                public sealed class ByteSeqHelper
                {
                    public static void write(IceInternal.BasicStream os__, byte[] v__)
                    {
                        os__.writeByteSeq(v__);
                    }

                    public static byte[] read(IceInternal.BasicStream is__)
                    {
                        byte[] v__;
                        v__ = is__.readByteSeq();
                        return v__;
                    }
                }

                public sealed class BufferTransferPrxHelper : Ice.ObjectPrxHelperBase, BufferTransferPrx
                {
                    #region Synchronous operations

                    public void Login()
                    {
                        Login(null, false);
                    }

                    public void Login(Ice.Context context__)
                    {
                        Login(context__, true);
                    }

                    private void Login(Ice.Context context__, bool explicitContext__)
                    {
                        if(explicitContext__ && context__ == null)
                        {
                            context__ = emptyContext_;
                        }
                        int cnt__ = 0;
                        while(true)
                        {
                            Ice.ObjectDel_ delBase__ = null;
                            try
                            {
                                delBase__ = getDelegate__();
                                BufferTransferDel_ del__ = (BufferTransferDel_)delBase__;
                                del__.Login(context__);
                                return;
                            }
                            catch(IceInternal.LocalExceptionWrapper ex__)
                            {
                                handleExceptionWrapper__(delBase__, ex__);
                            }
                            catch(Ice.LocalException ex__)
                            {
                                cnt__ = handleException__(delBase__, ex__, cnt__);
                            }
                        }
                    }

                    public void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq)
                    {
                        SendBuffer(aServiceName, aBufferLength, aSeq, null, false);
                    }

                    public void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Context context__)
                    {
                        SendBuffer(aServiceName, aBufferLength, aSeq, context__, true);
                    }

                    private void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Context context__, bool explicitContext__)
                    {
                        if(explicitContext__ && context__ == null)
                        {
                            context__ = emptyContext_;
                        }
                        int cnt__ = 0;
                        while(true)
                        {
                            Ice.ObjectDel_ delBase__ = null;
                            try
                            {
                                delBase__ = getDelegate__();
                                BufferTransferDel_ del__ = (BufferTransferDel_)delBase__;
                                del__.SendBuffer(aServiceName, aBufferLength, aSeq, context__);
                                return;
                            }
                            catch(IceInternal.LocalExceptionWrapper ex__)
                            {
                                handleExceptionWrapper__(delBase__, ex__);
                            }
                            catch(Ice.LocalException ex__)
                            {
                                cnt__ = handleException__(delBase__, ex__, cnt__);
                            }
                        }
                    }

                    public void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq)
                    {
                        SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, null, false);
                    }

                    public void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Context context__)
                    {
                        SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, context__, true);
                    }

                    private void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Context context__, bool explicitContext__)
                    {
                        if(explicitContext__ && context__ == null)
                        {
                            context__ = emptyContext_;
                        }
                        int cnt__ = 0;
                        while(true)
                        {
                            Ice.ObjectDel_ delBase__ = null;
                            try
                            {
                                delBase__ = getDelegate__();
                                BufferTransferDel_ del__ = (BufferTransferDel_)delBase__;
                                del__.SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, context__);
                                return;
                            }
                            catch(IceInternal.LocalExceptionWrapper ex__)
                            {
                                handleExceptionWrapper__(delBase__, ex__);
                            }
                            catch(Ice.LocalException ex__)
                            {
                                cnt__ = handleException__(delBase__, ex__, cnt__);
                            }
                        }
                    }

                    #endregion

                    #region Checked and unchecked cast operations

                    public static BufferTransferPrx checkedCast(Ice.ObjectPrx b)
                    {
                        if(b == null)
                        {
                            return null;
                        }
                        if(b is BufferTransferPrx)
                        {
                            return (BufferTransferPrx)b;
                        }
                        if(b.ice_isA("::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer"))
                        {
                            BufferTransferPrxHelper h = new BufferTransferPrxHelper();
                            h.copyFrom__(b);
                            return h;
                        }
                        return null;
                    }

                    public static BufferTransferPrx checkedCast(Ice.ObjectPrx b, Ice.Context ctx)
                    {
                        if(b == null)
                        {
                            return null;
                        }
                        if(b is BufferTransferPrx)
                        {
                            return (BufferTransferPrx)b;
                        }
                        if(b.ice_isA("::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer", ctx))
                        {
                            BufferTransferPrxHelper h = new BufferTransferPrxHelper();
                            h.copyFrom__(b);
                            return h;
                        }
                        return null;
                    }

                    public static BufferTransferPrx checkedCast(Ice.ObjectPrx b, string f)
                    {
                        if(b == null)
                        {
                            return null;
                        }
                        Ice.ObjectPrx bb = b.ice_facet(f);
                        try
                        {
                            if(bb.ice_isA("::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer"))
                            {
                                BufferTransferPrxHelper h = new BufferTransferPrxHelper();
                                h.copyFrom__(bb);
                                return h;
                            }
                        }
                        catch(Ice.FacetNotExistException)
                        {
                        }
                        return null;
                    }

                    public static BufferTransferPrx checkedCast(Ice.ObjectPrx b, string f, Ice.Context ctx)
                    {
                        if(b == null)
                        {
                            return null;
                        }
                        Ice.ObjectPrx bb = b.ice_facet(f);
                        try
                        {
                            if(bb.ice_isA("::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer", ctx))
                            {
                                BufferTransferPrxHelper h = new BufferTransferPrxHelper();
                                h.copyFrom__(bb);
                                return h;
                            }
                        }
                        catch(Ice.FacetNotExistException)
                        {
                        }
                        return null;
                    }

                    public static BufferTransferPrx uncheckedCast(Ice.ObjectPrx b)
                    {
                        if(b == null)
                        {
                            return null;
                        }
                        BufferTransferPrxHelper h = new BufferTransferPrxHelper();
                        h.copyFrom__(b);
                        return h;
                    }

                    public static BufferTransferPrx uncheckedCast(Ice.ObjectPrx b, string f)
                    {
                        if(b == null)
                        {
                            return null;
                        }
                        Ice.ObjectPrx bb = b.ice_facet(f);
                        BufferTransferPrxHelper h = new BufferTransferPrxHelper();
                        h.copyFrom__(bb);
                        return h;
                    }

                    #endregion

                    #region Marshaling support

                    protected override Ice.ObjectDelM_ createDelegateM__()
                    {
                        return new BufferTransferDelM_();
                    }

                    protected override Ice.ObjectDelD_ createDelegateD__()
                    {
                        return new BufferTransferDelD_();
                    }

                    public static void write__(IceInternal.BasicStream os__, BufferTransferPrx v__)
                    {
                        os__.writeProxy(v__);
                    }

                    public static BufferTransferPrx read__(IceInternal.BasicStream is__)
                    {
                        Ice.ObjectPrx proxy = is__.readProxy();
                        if(proxy != null)
                        {
                            BufferTransferPrxHelper result = new BufferTransferPrxHelper();
                            result.copyFrom__(proxy);
                            return result;
                        }
                        return null;
                    }

                    #endregion
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
                public interface BufferTransferDel_ : Ice.ObjectDel_
                {
                    void Login(Ice.Context context__);

                    void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Context context__);

                    void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Context context__);
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
                public sealed class BufferTransferDelM_ : Ice.ObjectDelM_, BufferTransferDel_
                {
                    public void Login(Ice.Context context__)
                    {
                        IceInternal.Outgoing og__ = getOutgoing("Login", Ice.OperationMode.Normal, context__);
                        try
                        {
                            bool ok__ = og__.invoke();
                            try
                            {
                                IceInternal.BasicStream is__ = og__.istr();
                                if(!ok__)
                                {
                                    try
                                    {
                                        is__.throwException();
                                    }
                                    catch(Ice.UserException ex)
                                    {
                                        throw new Ice.UnknownUserException(ex);
                                    }
                                }
                            }
                            catch(Ice.LocalException ex__)
                            {
                                throw new IceInternal.LocalExceptionWrapper(ex__, false);
                            }
                        }
                        finally
                        {
                            reclaimOutgoing(og__);
                        }
                    }

                    public void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Context context__)
                    {
                        IceInternal.Outgoing og__ = getOutgoing("SendBuffer", Ice.OperationMode.Normal, context__);
                        try
                        {
                            try
                            {
                                IceInternal.BasicStream os__ = og__.ostr();
                                os__.writeString(aServiceName);
                                os__.writeInt(aBufferLength);
                                os__.writeByteSeq(aSeq);
                            }
                            catch(Ice.LocalException ex__)
                            {
                                og__.abort(ex__);
                            }
                            bool ok__ = og__.invoke();
                            try
                            {
                                IceInternal.BasicStream is__ = og__.istr();
                                if(!ok__)
                                {
                                    try
                                    {
                                        is__.throwException();
                                    }
                                    catch(Ice.UserException ex)
                                    {
                                        throw new Ice.UnknownUserException(ex);
                                    }
                                }
                            }
                            catch(Ice.LocalException ex__)
                            {
                                throw new IceInternal.LocalExceptionWrapper(ex__, false);
                            }
                        }
                        finally
                        {
                            reclaimOutgoing(og__);
                        }
                    }

                    public void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Context context__)
                    {
                        IceInternal.Outgoing og__ = getOutgoing("SendBuffer2", Ice.OperationMode.Normal, context__);
                        try
                        {
                            try
                            {
                                IceInternal.BasicStream os__ = og__.ostr();
                                os__.writeString(aServiceName);
                                os__.writeString(aBufferGuid);
                                os__.writeInt(aSendIndex);
                                os__.writeInt(aTotalBufferLength);
                                os__.writeInt(aCurrentBufferLength);
                                os__.writeByteSeq(aSeq);
                            }
                            catch(Ice.LocalException ex__)
                            {
                                og__.abort(ex__);
                            }
                            bool ok__ = og__.invoke();
                            try
                            {
                                IceInternal.BasicStream is__ = og__.istr();
                                if(!ok__)
                                {
                                    try
                                    {
                                        is__.throwException();
                                    }
                                    catch(Ice.UserException ex)
                                    {
                                        throw new Ice.UnknownUserException(ex);
                                    }
                                }
                            }
                            catch(Ice.LocalException ex__)
                            {
                                throw new IceInternal.LocalExceptionWrapper(ex__, false);
                            }
                        }
                        finally
                        {
                            reclaimOutgoing(og__);
                        }
                    }
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
                public sealed class BufferTransferDelD_ : Ice.ObjectDelD_, BufferTransferDel_
                {
                    public void Login(Ice.Context context__)
                    {
                        Ice.Current current__ = new Ice.Current();
                        initCurrent__(ref current__, "Login", Ice.OperationMode.Normal, context__);
                        while(true)
                        {
                            IceInternal.Direct direct__ = new IceInternal.Direct(current__);
                            object servant__ = direct__.servant();
                            if(servant__ is BufferTransfer)
                            {
                                try
                                {
                                    ((InfoDTV.Multiplexer.Dynamic.Provider.BufferTransfer)servant__).Login(current__);
                                    return;
                                }
                                catch(Ice.LocalException ex__)
                                {
                                    throw new IceInternal.LocalExceptionWrapper(ex__, false);
                                }
                                finally
                                {
                                    direct__.destroy();
                                }
                            }
                            else
                            {
                                direct__.destroy();
                                Ice.OperationNotExistException opEx__ = new Ice.OperationNotExistException();
                                opEx__.id = current__.id;
                                opEx__.facet = current__.facet;
                                opEx__.operation = current__.operation;
                                throw opEx__;
                            }
                        }
                    }

                    public void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Context context__)
                    {
                        Ice.Current current__ = new Ice.Current();
                        initCurrent__(ref current__, "SendBuffer", Ice.OperationMode.Normal, context__);
                        while(true)
                        {
                            IceInternal.Direct direct__ = new IceInternal.Direct(current__);
                            object servant__ = direct__.servant();
                            if(servant__ is BufferTransfer)
                            {
                                try
                                {
                                    ((InfoDTV.Multiplexer.Dynamic.Provider.BufferTransfer)servant__).SendBuffer(aServiceName, aBufferLength, aSeq, current__);
                                    return;
                                }
                                catch(Ice.LocalException ex__)
                                {
                                    throw new IceInternal.LocalExceptionWrapper(ex__, false);
                                }
                                finally
                                {
                                    direct__.destroy();
                                }
                            }
                            else
                            {
                                direct__.destroy();
                                Ice.OperationNotExistException opEx__ = new Ice.OperationNotExistException();
                                opEx__.id = current__.id;
                                opEx__.facet = current__.facet;
                                opEx__.operation = current__.operation;
                                throw opEx__;
                            }
                        }
                    }

                    public void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Context context__)
                    {
                        Ice.Current current__ = new Ice.Current();
                        initCurrent__(ref current__, "SendBuffer2", Ice.OperationMode.Normal, context__);
                        while(true)
                        {
                            IceInternal.Direct direct__ = new IceInternal.Direct(current__);
                            object servant__ = direct__.servant();
                            if(servant__ is BufferTransfer)
                            {
                                try
                                {
                                    ((InfoDTV.Multiplexer.Dynamic.Provider.BufferTransfer)servant__).SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, current__);
                                    return;
                                }
                                catch(Ice.LocalException ex__)
                                {
                                    throw new IceInternal.LocalExceptionWrapper(ex__, false);
                                }
                                finally
                                {
                                    direct__.destroy();
                                }
                            }
                            else
                            {
                                direct__.destroy();
                                Ice.OperationNotExistException opEx__ = new Ice.OperationNotExistException();
                                opEx__.id = current__.id;
                                opEx__.facet = current__.facet;
                                opEx__.operation = current__.operation;
                                throw opEx__;
                            }
                        }
                    }
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
                public abstract class BufferTransferDisp_ : Ice.ObjectImpl, BufferTransfer
                {
                    #region Slice operations

                    public void Login()
                    {
                        Login(Ice.ObjectImpl.defaultCurrent);
                    }

                    public abstract void Login(Ice.Current current__);

                    public void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq)
                    {
                        SendBuffer(aServiceName, aBufferLength, aSeq, Ice.ObjectImpl.defaultCurrent);
                    }

                    public abstract void SendBuffer(string aServiceName, int aBufferLength, byte[] aSeq, Ice.Current current__);

                    public void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq)
                    {
                        SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, Ice.ObjectImpl.defaultCurrent);
                    }

                    public abstract void SendBuffer2(string aServiceName, string aBufferGuid, int aSendIndex, int aTotalBufferLength, int aCurrentBufferLength, byte[] aSeq, Ice.Current current__);

                    #endregion

                    #region Slice type-related members

                    public static new string[] ids__ = 
                    {
                        "::Ice::Object",
                        "::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer"
                    };

                    public override bool ice_isA(string s)
                    {
                        if(IceInternal.AssemblyUtil.runtime_ == IceInternal.AssemblyUtil.Runtime.Mono)
                        {
                            // Mono bug: System.Array.BinarySearch() uses the wrong collation sequence,
                            // so we do a linear search for the time being
                            int pos = 0;
                            while(pos < ids__.Length)
                            {
                                if(ids__[pos] == s)
                                {
                                    break;
                                }
                                ++pos;
                            }
                            if(pos == ids__.Length)
                            {
                                pos = -1;
                            }
                            return pos >= 0;
                        }
                        else
                        {
                            return _System.Array.BinarySearch(ids__, s, _System.Collections.Comparer.DefaultInvariant) >= 0;
                        }
                    }

                    public override bool ice_isA(string s, Ice.Current current__)
                    {
                        if(IceInternal.AssemblyUtil.runtime_ == IceInternal.AssemblyUtil.Runtime.Mono)
                        {
                            // Mono bug: System.Array.BinarySearch() uses the wrong collation sequence,
                            // so we do a linear search for the time being
                            int pos = 0;
                            while(pos < ids__.Length)
                            {
                                if(ids__[pos] == s)
                                {
                                    break;
                                }
                                ++pos;
                            }
                            if(pos == ids__.Length)
                            {
                                pos = -1;
                            }
                            return pos >= 0;
                        }
                        else
                        {
                            return _System.Array.BinarySearch(ids__, s, _System.Collections.Comparer.DefaultInvariant) >= 0;
                        }
                    }

                    public override string[] ice_ids()
                    {
                        return ids__;
                    }

                    public override string[] ice_ids(Ice.Current current__)
                    {
                        return ids__;
                    }

                    public override string ice_id()
                    {
                        return ids__[1];
                    }

                    public override string ice_id(Ice.Current current__)
                    {
                        return ids__[1];
                    }

                    public static new string ice_staticId()
                    {
                        return ids__[1];
                    }

                    #endregion

                    #region Operation dispatch

                    public static IceInternal.DispatchStatus Login___(BufferTransfer obj__, IceInternal.Incoming inS__, Ice.Current current__)
                    {
                        checkMode__(Ice.OperationMode.Normal, current__.mode);
                        obj__.Login(current__);
                        return IceInternal.DispatchStatus.DispatchOK;
                    }

                    public static IceInternal.DispatchStatus SendBuffer___(BufferTransfer obj__, IceInternal.Incoming inS__, Ice.Current current__)
                    {
                        checkMode__(Ice.OperationMode.Normal, current__.mode);
                        IceInternal.BasicStream is__ = inS__.istr();
                        string aServiceName;
                        aServiceName = is__.readString();
                        int aBufferLength;
                        aBufferLength = is__.readInt();
                        byte[] aSeq;
                        aSeq = is__.readByteSeq();
                        obj__.SendBuffer(aServiceName, aBufferLength, aSeq, current__);
                        return IceInternal.DispatchStatus.DispatchOK;
                    }

                    public static IceInternal.DispatchStatus SendBuffer2___(BufferTransfer obj__, IceInternal.Incoming inS__, Ice.Current current__)
                    {
                        checkMode__(Ice.OperationMode.Normal, current__.mode);
                        IceInternal.BasicStream is__ = inS__.istr();
                        string aServiceName;
                        aServiceName = is__.readString();
                        string aBufferGuid;
                        aBufferGuid = is__.readString();
                        int aSendIndex;
                        aSendIndex = is__.readInt();
                        int aTotalBufferLength;
                        aTotalBufferLength = is__.readInt();
                        int aCurrentBufferLength;
                        aCurrentBufferLength = is__.readInt();
                        byte[] aSeq;
                        aSeq = is__.readByteSeq();
                        obj__.SendBuffer2(aServiceName, aBufferGuid, aSendIndex, aTotalBufferLength, aCurrentBufferLength, aSeq, current__);
                        return IceInternal.DispatchStatus.DispatchOK;
                    }

                    private static string[] all__ =
                    {
                        "ice_id",
                        "ice_ids",
                        "ice_isA",
                        "ice_ping",
                        "Login",
                        "SendBuffer",
                        "SendBuffer2"
                    };

                    public override IceInternal.DispatchStatus dispatch__(IceInternal.Incoming inS__, Ice.Current current__)
                    {
                        int pos;
                        if(IceInternal.AssemblyUtil.runtime_ == IceInternal.AssemblyUtil.Runtime.Mono)
                        {
                            // Mono bug: System.Array.BinarySearch() uses the wrong collation sequence,
                            // so we do a linear search for the time being
                            pos = 0;
                            while(pos < all__.Length)
                            {
                                if(all__[pos] == current__.operation)
                                {
                                    break;
                                }
                                ++pos;
                            }
                            if(pos == all__.Length)
                            {
                                pos = -1;
                            }
                        }
                        else
                        {
                            pos = _System.Array.BinarySearch(all__, current__.operation, _System.Collections.Comparer.DefaultInvariant);
                        }
                        if(pos < 0)
                        {
                            return IceInternal.DispatchStatus.DispatchOperationNotExist;
                        }

                        switch(pos)
                        {
                            case 0:
                            {
                                return ice_id___(this, inS__, current__);
                            }
                            case 1:
                            {
                                return ice_ids___(this, inS__, current__);
                            }
                            case 2:
                            {
                                return ice_isA___(this, inS__, current__);
                            }
                            case 3:
                            {
                                return ice_ping___(this, inS__, current__);
                            }
                            case 4:
                            {
                                return Login___(this, inS__, current__);
                            }
                            case 5:
                            {
                                return SendBuffer___(this, inS__, current__);
                            }
                            case 6:
                            {
                                return SendBuffer2___(this, inS__, current__);
                            }
                        }

                        _System.Diagnostics.Debug.Assert(false);
                        return IceInternal.DispatchStatus.DispatchOperationNotExist;
                    }

                    #endregion

                    #region Marshaling support

                    public override void write__(IceInternal.BasicStream os__)
                    {
                        os__.writeTypeId(ice_staticId());
                        os__.startWriteSlice();
                        os__.endWriteSlice();
                        base.write__(os__);
                    }

                    public override void read__(IceInternal.BasicStream is__, bool rid__)
                    {
                        if(rid__)
                        {
                            /* string myId = */ is__.readTypeId();
                        }
                        is__.startReadSlice();
                        is__.endReadSlice();
                        base.read__(is__, true);
                    }

                    public override void write__(Ice.OutputStream outS__)
                    {
                        Ice.MarshalException ex = new Ice.MarshalException();
                        ex.reason = "type InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer was not generated with stream support";
                        throw ex;
                    }

                    public override void read__(Ice.InputStream inS__, bool rid__)
                    {
                        Ice.MarshalException ex = new Ice.MarshalException();
                        ex.reason = "type InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer was not generated with stream support";
                        throw ex;
                    }

                    #endregion
                }
            }
        }
    }
}

namespace IceInternal
{
    namespace SliceChecksums
    {
        public sealed class X8F077EED_2264_41A4_A126_1BC6711C729D
        {
            public readonly static System.Collections.Hashtable map = new System.Collections.Hashtable();

            static X8F077EED_2264_41A4_A126_1BC6711C729D()
            {
                map.Add("::InfoDTV::Multiplexer::Dynamic::Provider::BufferTransfer", "e161b1d675cc57f4da3890a0cba87aca");
                map.Add("::InfoDTV::Multiplexer::Dynamic::Provider::ByteSeq", "eae189e6d7b57b6f9628e78293d6d7");
            }
        };
    }
}
