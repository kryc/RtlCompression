#include <windows.h>
#include "RtlCompression.h"

int GetCompressionFunctions(RtlCompressionFuncs *funcs) {
	DWORD Status = ERROR_SUCCESS;
	HMODULE WINAPI Ntdll;

	/* Open up a handle to ntdll so that we can find the compression API fucntions */
	if ((Ntdll = LoadLibraryA("ntdll.dll")) == NULL) {
		perror("[!] Unable to loadlibrary ntdll.dll");
		Status = GetLastError();
		goto exit;
	}

	/* Get the addresses of the compression functions */
	if (((funcs->RtlCompressBuffer = (_RtlCompressBuffer)GetProcAddress(Ntdll, "RtlCompressBuffer")) == NULL) ||
		((funcs->RtlDecompressBuffer = (_RtlDecompressBuffer)GetProcAddress(Ntdll, "RtlDecompressBuffer")) == NULL) ||
		((funcs->RtlDecompressBufferEx = (_RtlDecompressBufferEx)GetProcAddress(Ntdll, "RtlDecompressBufferEx")) == NULL) ||
		((funcs->RtlGetCompressionWorkSpaceSize = (_RtlGetCompressionWorkSpaceSize)GetProcAddress(Ntdll, "RtlGetCompressionWorkSpaceSize")) == NULL)) {
		perror("[!] Unable to locate Rtl Compression functions\n");
		Status = GetLastError();
		goto exit;
	}

exit:
	return Status;
}
