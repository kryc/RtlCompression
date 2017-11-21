#pragma once

#include <windows.h>

typedef NTSTATUS(__stdcall *_RtlCompressBuffer)(
	USHORT CompressionFormatAndEngine,
	PUCHAR UncompressedBuffer,
	ULONG UncompressedBufferSize,
	PUCHAR CompressedBuffer,
	ULONG CompressedBufferSize,
	ULONG UncompressedChunkSize,
	PULONG FinalCompressedSize,
	PVOID WorkSpace
	);

typedef NTSTATUS(__stdcall *_RtlDecompressBuffer)(
	USHORT CompressionFormat,
	PUCHAR UncompressedBuffer,
	ULONG UncompressedBufferSize,
	PUCHAR CompressedBuffer,
	ULONG CompressedBufferSize,
	PULONG FinalUncompressedSize
	);

typedef NTSTATUS(__stdcall *_RtlDecompressBufferEx)(
	_In_  USHORT CompressionFormat,
	_Out_ PUCHAR UncompressedBuffer,
	_In_  ULONG  UncompressedBufferSize,
	_In_  PUCHAR CompressedBuffer,
	_In_  ULONG  CompressedBufferSize,
	_Out_ PULONG FinalUncompressedSize,
	_In_  PVOID  WorkSpace
	);

typedef NTSTATUS(__stdcall *_RtlGetCompressionWorkSpaceSize)(
	USHORT CompressionFormatAndEngine,
	PULONG CompressBufferWorkSpaceSize,
	PULONG CompressFragmentWorkSpaceSize
	);

typedef struct _RtlCompression {
	_RtlCompressBuffer RtlCompressBuffer;
	_RtlDecompressBuffer RtlDecompressBuffer;
	_RtlDecompressBufferEx RtlDecompressBufferEx;
	_RtlGetCompressionWorkSpaceSize RtlGetCompressionWorkSpaceSize;
} RtlCompressionFuncs;

int GetCompressionFunctions(RtlCompressionFuncs *funcs);
