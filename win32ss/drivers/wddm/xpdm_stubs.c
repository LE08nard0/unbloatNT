/*
 * PROJECT:     LiberNT Display Driver Model - Win32k/dxgkrnl Bridge
 * LICENSE:     GPL-3.0-or-later (https://spdx.org/licenses/GPL-3.0-or-later)
 * PURPOSE:     XPDM link stubs for the always-built win32k D3DKMT thunks
 * COPYRIGHT:   Copyright 2026 LiberNT Contributors
 */

#include <ntifs.h>
#include <windef.h>
#include <d3dkmthk.h>

/*
 * XPDM does not have a dxgkrnl bridge. Keep only the symbols referenced by
 * win32k and avoid pulling the full WDDM implementation or its selected
 * WDDM 3.x layouts into an XPDM build.
 */

typedef struct _REACTOS_WIN32K_DXGKRNL_INTERFACE
    *PREACTOS_WIN32K_DXGKRNL_INTERFACE;

/*
 * These structures belong to DDI levels newer than XPDM's header selection.
 * Their contents are deliberately unavailable here; pointer declarations are
 * sufficient to preserve the callers' C ABI without importing newer layouts.
 */
struct _D3DKMT_ACQUIREKEYEDMUTEX2;
/* The doubled "M" is the public WDK tag spelling; keep tag identity exact. */
struct _D3DKMT_CHANGEVIDEOMMEMORYRESERVATION;
struct _D3DKMT_CREATEHWQUEUE;
struct _D3DKMT_CREATEKEYEDMUTEX2;
struct _D3DKMT_DESTROYALLOCATION2;
struct _D3DKMT_DESTROYHWQUEUE;
struct _D3DKMT_ENUMADAPTERS;
struct _D3DKMT_ENUMADAPTERS2;
struct _D3DKMT_ENUMADAPTERS3;
struct _D3DKMT_ISFEATUREENABLED;
struct _D3DKMT_LOCK2;
struct _D3DKMT_OPENADAPTERFROMLUID;
struct _D3DKMT_OPENKEYEDMUTEX2;
struct _D3DKMT_QUERYCLOCKCALIBRATION;
struct _D3DKMT_REGISTERTRIMNOTIFICATION;
struct _D3DKMT_RELEASEKEYEDMUTEX2;
struct _D3DKMT_SETVIDPNSOURCEOWNER2;
struct _D3DKMT_SUBMITCOMMANDTOHWQUEUE;
struct _D3DKMT_SUBMITWAITFORSYNCOBJECTSTOHWQUEUE;
struct _D3DKMT_SUBMITSIGNALSYNCOBJECTSTOHWQUEUE;
struct _D3DKMT_SUBMITPRESENTBLTTOHWQUEUE;
struct _D3DKMT_SUBMITPRESENTTOHWQUEUE;
struct _D3DKMT_UNLOCK2;
struct _D3DKMT_UNREGISTERTRIMNOTIFICATION;

#define DEFINE_XPDM_D3DKMT_STUB(Name, Annotation, Type) \
    NTSTATUS                                             \
    APIENTRY                                             \
    Name(                                                \
        Annotation Type *pData)                          \
    {                                                    \
        UNREFERENCED_PARAMETER(pData);                   \
        return STATUS_NOT_SUPPORTED;                     \
    }

DEFINE_XPDM_D3DKMT_STUB(D3DKMTAcquireKeyedMutex,
                        _Inout_,
                        struct _D3DKMT_ACQUIREKEYEDMUTEX)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTAcquireKeyedMutex2,
                        _Inout_,
                        struct _D3DKMT_ACQUIREKEYEDMUTEX2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTChangeVideoMemoryReservation,
                        _In_,
                        CONST struct _D3DKMT_CHANGEVIDEOMMEMORYRESERVATION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCheckVidPnExclusiveOwnership,
                        _In_,
                        CONST struct _D3DKMT_CHECKVIDPNEXCLUSIVEOWNERSHIP)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateHwQueue,
                        _Inout_,
                        struct _D3DKMT_CREATEHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateKeyedMutex,
                        _Inout_,
                        struct _D3DKMT_CREATEKEYEDMUTEX)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateKeyedMutex2,
                        _Inout_,
                        struct _D3DKMT_CREATEKEYEDMUTEX2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTDestroyAllocation2,
                        _In_,
                        CONST struct _D3DKMT_DESTROYALLOCATION2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTDestroyHwQueue,
                        _In_,
                        CONST struct _D3DKMT_DESTROYHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTDestroyKeyedMutex,
                        _In_,
                        CONST struct _D3DKMT_DESTROYKEYEDMUTEX)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTEnumAdapters,
                        _Inout_,
                        CONST struct _D3DKMT_ENUMADAPTERS)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTEnumAdapters2,
                        _Inout_,
                        CONST struct _D3DKMT_ENUMADAPTERS2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTEnumAdapters3,
                        _Inout_,
                        struct _D3DKMT_ENUMADAPTERS3)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTIsFeatureEnabled,
                        _Inout_,
                        struct _D3DKMT_ISFEATUREENABLED)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTLock2,
                        _Inout_,
                        struct _D3DKMT_LOCK2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenAdapterFromDeviceName,
                        _Inout_,
                        struct _D3DKMT_OPENADAPTERFROMDEVICENAME)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenAdapterFromLuid,
                        _Inout_,
                        CONST struct _D3DKMT_OPENADAPTERFROMLUID)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenKeyedMutex,
                        _Inout_,
                        struct _D3DKMT_OPENKEYEDMUTEX)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenKeyedMutex2,
                        _Inout_,
                        struct _D3DKMT_OPENKEYEDMUTEX2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryClockCalibration,
                        _Inout_,
                        struct _D3DKMT_QUERYCLOCKCALIBRATION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTRegisterTrimNotification,
                        _Inout_,
                        struct _D3DKMT_REGISTERTRIMNOTIFICATION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTReleaseKeyedMutex,
                        _Inout_,
                        struct _D3DKMT_RELEASEKEYEDMUTEX)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTReleaseKeyedMutex2,
                        _Inout_,
                        struct _D3DKMT_RELEASEKEYEDMUTEX2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSetVidPnSourceOwner2,
                        _In_,
                        CONST struct _D3DKMT_SETVIDPNSOURCEOWNER2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSubmitCommandToHwQueue,
                        _In_,
                        CONST struct _D3DKMT_SUBMITCOMMANDTOHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSubmitWaitForSyncObjectsToHwQueue,
                        _In_,
                        CONST struct _D3DKMT_SUBMITWAITFORSYNCOBJECTSTOHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSubmitSignalSyncObjectsToHwQueue,
                        _In_,
                        CONST struct _D3DKMT_SUBMITSIGNALSYNCOBJECTSTOHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSubmitPresentBltToHwQueue,
                        _In_,
                        CONST struct _D3DKMT_SUBMITPRESENTBLTTOHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSubmitPresentToHwQueue,
                        _Inout_,
                        struct _D3DKMT_SUBMITPRESENTTOHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTUnlock2,
                        _In_,
                        CONST struct _D3DKMT_UNLOCK2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTUnregisterTrimNotification,
                        _Inout_,
                        struct _D3DKMT_UNREGISTERTRIMNOTIFICATION)

/*
 * Newer win32k thunks that are always built. XPDM has no kernel graphics
 * runtime behind them, so they report the operation as unsupported.
 */
struct _D3DKMT_ADJUSTFULLSCREENGAMMA;
struct _D3DKMT_CONFIGURESHAREDRESOURCE;
struct _D3DKMT_CONNECT_DOORBELL;
struct _D3DKMT_CREATEHWCONTEXT;
struct _D3DKMT_CREATENATIVEFENCE;
struct _D3DKMT_CREATEPROTECTEDSESSION;
struct _D3DKMT_CREATE_DOORBELL;
struct _D3DKMT_DESTROYHWCONTEXT;
struct _D3DKMT_DESTROYPROTECTEDSESSION;
struct _D3DKMT_DESTROY_DOORBELL;
struct _D3DKMT_FLUSHHEAPTRANSITIONS;
struct _D3DKMT_GETCONTEXTINPROCESSSCHEDULINGPRIORITY;
struct _D3DKMT_GETNATIVEFENCELOGDETAIL;
struct _D3DKMT_GETPROCESSDEVICEREMOVALSUPPORT;
struct _D3DKMT_GET_POST_COMPOSITION_CAPS;
struct _D3DKMT_MARKDEVICEASERROR;
struct _D3DKMT_NOTIFY_WORK_SUBMISSION;
struct _D3DKMT_OPENKEYEDMUTEXFROMNTHANDLE;
struct _D3DKMT_OPENNATIVEFENCEFROMNTHANDLE;
struct _D3DKMT_OPENPROTECTEDSESSIONFROMNTHANDLE;
struct _D3DKMT_OUTPUTDUPLPRESENTTOHWQUEUE;
struct _D3DKMT_PRESENT_REDIRECTED;
struct _D3DKMT_QUERYFSEBLOCK;
struct _D3DKMT_QUERYPROCESSOFFERINFO;
struct _D3DKMT_QUERYPROTECTEDSESSIONINFOFROMNTHANDLE;
struct _D3DKMT_QUERYPROTECTEDSESSIONSTATUS;
struct _D3DKMT_QUERYREMOTEVIDPNSOURCEFROMGDIDISPLAYNAME;
struct _D3DKMT_SETCONTEXTINPROCESSSCHEDULINGPRIORITY;
struct _D3DKMT_SETFSEBLOCK;
struct _D3DKMT_SETHWPROTECTIONTEARDOWNRECOVERY;
struct _D3DKMT_SETVIDPNSOURCEHWPROTECTION;
struct _D3DKMT_SET_COLORSPACE_TRANSFORM;
struct _D3DKMT_TRIMPROCESSCOMMITMENT;

DEFINE_XPDM_D3DKMT_STUB(D3DKMTAdjustFullscreenGamma,
                        _In_,
                        struct _D3DKMT_ADJUSTFULLSCREENGAMMA)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTConfigureSharedResource,
                        _In_,
                        CONST struct _D3DKMT_CONFIGURESHAREDRESOURCE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTConnectDoorbell,
                        _In_,
                        struct _D3DKMT_CONNECT_DOORBELL)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateDoorbell,
                        _In_,
                        struct _D3DKMT_CREATE_DOORBELL)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateHwContext,
                        _Inout_,
                        struct _D3DKMT_CREATEHWCONTEXT)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateNativeFence,
                        _Inout_,
                        struct _D3DKMT_CREATENATIVEFENCE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTCreateProtectedSession,
                        _Inout_,
                        struct _D3DKMT_CREATEPROTECTEDSESSION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTDestroyDoorbell,
                        _In_,
                        struct _D3DKMT_DESTROY_DOORBELL)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTDestroyHwContext,
                        _In_,
                        CONST struct _D3DKMT_DESTROYHWCONTEXT)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTDestroyProtectedSession,
                        _Inout_,
                        struct _D3DKMT_DESTROYPROTECTEDSESSION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTFlushHeapTransitions,
                        _In_,
                        struct _D3DKMT_FLUSHHEAPTRANSITIONS)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTGetContextInProcessSchedulingPriority,
                        _Inout_,
                        struct _D3DKMT_GETCONTEXTINPROCESSSCHEDULINGPRIORITY)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTGetNativeFenceLogDetail,
                        _Inout_,
                        struct _D3DKMT_GETNATIVEFENCELOGDETAIL)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTGetPostCompositionCaps,
                        _Inout_,
                        struct _D3DKMT_GET_POST_COMPOSITION_CAPS)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTGetProcessDeviceRemovalSupport,
                        _Inout_,
                        struct _D3DKMT_GETPROCESSDEVICEREMOVALSUPPORT)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTMarkDeviceAsError,
                        _In_,
                        struct _D3DKMT_MARKDEVICEASERROR)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTNotifyWorkSubmission,
                        _In_,
                        struct _D3DKMT_NOTIFY_WORK_SUBMISSION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenKeyedMutexFromNtHandle,
                        _Inout_,
                        struct _D3DKMT_OPENKEYEDMUTEXFROMNTHANDLE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenNativeFenceFromNtHandle,
                        _Inout_,
                        struct _D3DKMT_OPENNATIVEFENCEFROMNTHANDLE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenProtectedSessionFromNtHandle,
                        _Inout_,
                        struct _D3DKMT_OPENPROTECTEDSESSIONFROMNTHANDLE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOutputDuplPresentToHwQueue,
                        _In_,
                        CONST struct _D3DKMT_OUTPUTDUPLPRESENTTOHWQUEUE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTPresentRedirected,
                        _In_,
                        struct _D3DKMT_PRESENT_REDIRECTED)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryFSEBlock,
                        _Inout_,
                        struct _D3DKMT_QUERYFSEBLOCK)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryProcessOfferInfo,
                        _Inout_,
                        struct _D3DKMT_QUERYPROCESSOFFERINFO)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryProtectedSessionInfoFromNtHandle,
                        _Inout_,
                        struct _D3DKMT_QUERYPROTECTEDSESSIONINFOFROMNTHANDLE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryProtectedSessionStatus,
                        _Inout_,
                        struct _D3DKMT_QUERYPROTECTEDSESSIONSTATUS)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryRemoteVidPnSourceFromGdiDisplayName,
                        _Inout_,
                        struct _D3DKMT_QUERYREMOTEVIDPNSOURCEFROMGDIDISPLAYNAME)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSetContextInProcessSchedulingPriority,
                        _In_,
                        CONST struct _D3DKMT_SETCONTEXTINPROCESSSCHEDULINGPRIORITY)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSetFSEBlock,
                        _In_,
                        CONST struct _D3DKMT_SETFSEBLOCK)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSetHwProtectionTeardownRecovery,
                        _In_,
                        struct _D3DKMT_SETHWPROTECTIONTEARDOWNRECOVERY)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSetMonitorColorSpaceTransform,
                        _In_,
                        struct _D3DKMT_SET_COLORSPACE_TRANSFORM)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTSetVidPnSourceHwProtection,
                        _In_,
                        struct _D3DKMT_SETVIDPNSOURCEHWPROTECTION)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTTrimProcessCommitment,
                        _Inout_,
                        struct _D3DKMT_TRIMPROCESSCOMMITMENT)

struct _D3DDDI_GETRESOURCEPRESENTPRIVATEDRIVERDATA;
struct _D3DKMT_GETSHAREDRESOURCEADAPTERLUID;
struct _D3DKMT_INVALIDATECACHE;
struct _D3DKMT_OPENADAPTERFROMHDC;
struct _D3DKMT_OPENRESOURCE;
struct _D3DKMT_QUERYRESOURCEINFO;
struct _D3DKMT_RECLAIMALLOCATIONS2;
struct D3DDDI_UPDATEALLOCPROPERTY;

DEFINE_XPDM_D3DKMT_STUB(D3DKMTGetResourcePresentPrivateDriverData,
                        _Inout_,
                        struct _D3DDDI_GETRESOURCEPRESENTPRIVATEDRIVERDATA)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTGetSharedResourceAdapterLuid,
                        _Inout_,
                        struct _D3DKMT_GETSHAREDRESOURCEADAPTERLUID)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTInvalidateCache,
                        _In_,
                        CONST struct _D3DKMT_INVALIDATECACHE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenAdapterFromHdc,
                        _Inout_,
                        struct _D3DKMT_OPENADAPTERFROMHDC)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTOpenResource,
                        _Inout_,
                        struct _D3DKMT_OPENRESOURCE)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTQueryResourceInfo,
                        _Inout_,
                        struct _D3DKMT_QUERYRESOURCEINFO)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTReclaimAllocations2,
                        _Inout_,
                        struct _D3DKMT_RECLAIMALLOCATIONS2)
DEFINE_XPDM_D3DKMT_STUB(D3DKMTUpdateAllocationProperty,
                        _Inout_,
                        struct D3DDDI_UPDATEALLOCPROPERTY)

NTSTATUS
APIENTRY
D3DKMTPresentWithOverlays(
    _In_ const VOID *Overlays,
    _In_ const VOID *Present)
{
    UNREFERENCED_PARAMETER(Overlays);
    UNREFERENCED_PARAMETER(Present);
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
APIENTRY
D3DKMTRegisterVailProcess(
    _In_ GUID *Guid)
{
    UNREFERENCED_PARAMETER(Guid);
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
APIENTRY
D3DKMTSetProcessSchedulingPriorityClass(
    _In_ HANDLE Process,
    _In_ D3DKMT_SCHEDULINGPRIORITYCLASS PriorityClass)
{
    UNREFERENCED_PARAMETER(Process);
    UNREFERENCED_PARAMETER(PriorityClass);
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
APIENTRY
D3DKMTGetProcessSchedulingPriorityClass(
    _In_ HANDLE Process,
    _Out_ D3DKMT_SCHEDULINGPRIORITYCLASS *PriorityClass)
{
    UNREFERENCED_PARAMETER(Process);
    UNREFERENCED_PARAMETER(PriorityClass);
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
WddmBridgeInit(VOID)
{
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
WddmBridgeRequireReady(VOID)
{
    return STATUS_NOT_SUPPORTED;
}

VOID
WddmBridgeInitCallbacks(
    _Out_ PREACTOS_WIN32K_DXGKRNL_INTERFACE Interface)
{
    UNREFERENCED_PARAMETER(Interface);
}

NTSTATUS
WddmBridgeSendIoctl(
    _In_ ULONG IoControlCode,
    _In_opt_ PVOID InputBuffer,
    _In_ ULONG InputSize,
    _Out_opt_ PVOID OutputBuffer,
    _In_ ULONG OutputSize)
{
    UNREFERENCED_PARAMETER(IoControlCode);
    UNREFERENCED_PARAMETER(InputBuffer);
    UNREFERENCED_PARAMETER(InputSize);
    UNREFERENCED_PARAMETER(OutputBuffer);
    UNREFERENCED_PARAMETER(OutputSize);
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
WddmBridgeSendIoctlWithInformation(
    _In_ ULONG IoControlCode,
    _In_opt_ PVOID InputBuffer,
    _In_ ULONG InputSize,
    _Out_opt_ PVOID OutputBuffer,
    _In_ ULONG OutputSize,
    _Out_opt_ PULONG_PTR Information)
{
    UNREFERENCED_PARAMETER(IoControlCode);
    UNREFERENCED_PARAMETER(InputBuffer);
    UNREFERENCED_PARAMETER(InputSize);
    UNREFERENCED_PARAMETER(OutputBuffer);
    UNREFERENCED_PARAMETER(OutputSize);
    UNREFERENCED_PARAMETER(Information);
    return STATUS_NOT_SUPPORTED;
}

NTSTATUS
WddmBridgeValidateSharedResourceOwner(
    _In_ const LUID *AdapterLuid,
    _In_ ULONG GlobalShare)
{
    UNREFERENCED_PARAMETER(AdapterLuid);
    UNREFERENCED_PARAMETER(GlobalShare);
    return STATUS_NOT_SUPPORTED;
}
