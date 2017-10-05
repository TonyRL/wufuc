#pragma once

#include <phnt_windows.h>

#define DLL_PROCESS_VERIFIER 4

typedef VOID(NTAPI *RTL_VERIFIER_DLL_LOAD_CALLBACK)(PWSTR DllName, PVOID DllBase, SIZE_T DllSize, PVOID Reserved);
typedef VOID(NTAPI *RTL_VERIFIER_DLL_UNLOAD_CALLBACK)(PWSTR DllName, PVOID DllBase, SIZE_T DllSize, PVOID Reserved);
typedef VOID(NTAPI *RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK)(PVOID AllocationBase, SIZE_T AllocationSize);

typedef struct tagRTL_VERIFIER_THUNK_DESCRIPTOR
{
        PCHAR ThunkName;
        PVOID ThunkOldAddress;
        PVOID ThunkNewAddress;
} RTL_VERIFIER_THUNK_DESCRIPTOR, *PRTL_VERIFIER_THUNK_DESCRIPTOR;

typedef struct tagRTL_VERIFIER_DLL_DESCRIPTOR
{
        PWCHAR DllName;
        DWORD DllFlags;
        PVOID DllAddress;
        PRTL_VERIFIER_THUNK_DESCRIPTOR DllThunks;
} RTL_VERIFIER_DLL_DESCRIPTOR, *PRTL_VERIFIER_DLL_DESCRIPTOR;

typedef struct tagRTL_VERIFIER_PROVIDER_DESCRIPTOR
{
        DWORD Length;
        PRTL_VERIFIER_DLL_DESCRIPTOR ProviderDlls;
        RTL_VERIFIER_DLL_LOAD_CALLBACK ProviderDllLoadCallback;
        RTL_VERIFIER_DLL_UNLOAD_CALLBACK ProviderDllUnloadCallback;
        PWSTR VerifierImage;
        DWORD VerifierFlags;
        DWORD VerifierDebug;
        PVOID RtlpGetStackTraceAddress;
        PVOID RtlpDebugPageHeapCreate;
        PVOID RtlpDebugPageHeapDestroy;
        RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK ProviderNtdllHeapFreeCallback;
} RTL_VERIFIER_PROVIDER_DESCRIPTOR, *PRTL_VERIFIER_PROVIDER_DESCRIPTOR;

extern RTL_VERIFIER_THUNK_DESCRIPTOR g_vfADVAPIThunkDescriptors[];
extern RTL_VERIFIER_THUNK_DESCRIPTOR g_vfK32ThunkDescriptors[];
extern RTL_VERIFIER_DLL_DESCRIPTOR g_vfDllDescriptors[];
extern RTL_VERIFIER_PROVIDER_DESCRIPTOR g_vfProviderDescriptor;
