#ifndef CC_ASYNCDOWNLOADER_H
#define CC_ASYNCDOWNLOADER_H
#include "Constants.h"
#include "Utils.h"
/* Downloads images, texture packs, skins, etc in async manner.
   Copyright 2014-2017 ClassicalSharp | Licensed under BSD-3
*/
struct IGameComponent;
struct ScheduledTask;

enum REQUEST_TYPE { REQUEST_TYPE_DATA, REQUEST_TYPE_CONTENT_LENGTH };
enum ASYNC_PROGRESS {
	ASYNC_PROGRESS_NOTHING = -3,
	ASYNC_PROGRESS_MAKING_REQUEST = -2,
	ASYNC_PROGRESS_FETCHING_DATA = -1,
};

struct AsyncRequest {
	char URL[STRING_SIZE];
	char ID[STRING_SIZE];

	UInt64 TimeAdded, TimeDownloaded;
	Int32  StatusCode;
	ReturnCode Result;

	void* ResultData;
	UInt32 ResultSize;

	UInt64 LastModified;    /* Time item cached at (if at all) */
	char Etag[STRING_SIZE]; /* ETag of cached item (if any) */
	UInt8 RequestType;
};

void ASyncRequest_Free(struct AsyncRequest* request);

void AsyncDownloader_MakeComponent(struct IGameComponent* comp);
void AsyncDownloader_GetSkin(const String* id, const String* skinName);
void AsyncDownloader_GetData(const String* url, bool priority, const String* id);
void AsyncDownloader_GetContentLength(const String* url, bool priority, const String* id);
/* TODO: Implement post */
/* void AsyncDownloader_PostString(const String* url, bool priority, const String* id, const String* contents); */
void AsyncDownloader_GetDataEx(const String* url, bool priority, const String* id, UInt64* lastModified, const String* etag);

bool AsyncDownloader_Get(const String* id, struct AsyncRequest* item);
bool AsyncDownloader_GetCurrent(struct AsyncRequest* request, Int32* progress);
void AsyncDownloader_PurgeOldEntriesTask(struct ScheduledTask* task);
#endif