#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "RtlCompression.h"

int main(int argc, char *argv[]) {
	DWORD Status = ERROR_SUCCESS;
	RtlCompressionFuncs Functions;
	UCHAR Source[4096];
	UCHAR Destination[4096];
	ULONG WorkspaceSize;
	ULONG FragWorkspaceSize;
	PVOID Workspace = NULL;
	ULONG FinalCompressedSize;
	ULONG FinalUncompressedSize;

	for (ULONG i = 0; i < sizeof(Source); i++)
		Source[i] = (UCHAR)(i & 0xff);

	/* Get the Rtl compression functions */
	Status = GetCompressionFunctions(&Functions);
	if (Status != ERROR_SUCCESS)
		goto exit;

	/* Work out how much workspace size we need */
	Status = Functions.RtlGetCompressionWorkSpaceSize(
		COMPRESSION_FORMAT_XPRESS | COMPRESSION_ENGINE_MAXIMUM,	// CompressionFormatAndEngine
		&WorkspaceSize,											// CompressBufferWorkSpaceSize
		&FragWorkspaceSize										// CompressFragmentWorkSpaceSize
	);

	printf("[+] Workspace sizes required: %d | %d (Frag)\n", WorkspaceSize, FragWorkspaceSize);
	
	Workspace = malloc((size_t)WorkspaceSize);

	Status = Functions.RtlCompressBuffer(
		COMPRESSION_FORMAT_XPRESS | COMPRESSION_ENGINE_MAXIMUM,	// CompressionFormatAndEngine
		Source,													// UncompressedBuffer
		sizeof(Source),											// UncompressedBufferSize
		Destination,											// CompressedBuffer
		sizeof(Destination),									// CompressedBufferSize
		4096,													// UncompressedChunkSize
		&FinalCompressedSize,									// FinalCompressedSize
		Workspace												// WorkSpace
	);
	printf("[+] Compressed Size: %u\n", FinalCompressedSize);

	Status = Functions.RtlDecompressBufferEx(
		COMPRESSION_FORMAT_XPRESS,		// CompressionFormat
		Source,							// UncompressedBuffer
		sizeof(Source),					// UncompressedBufferSize
		Destination,					// CompressedBuffer
		FinalCompressedSize,			// CompressedBufferSize
		&FinalUncompressedSize,			// FinalUncompressedSize
		Workspace						// WorkSpace
	);

	printf("[+] Uncompressed Size: %u\n", FinalUncompressedSize);

exit:
	printf("[+] Press return to continue\n");
	getchar();
	return Status;
}