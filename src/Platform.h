#ifndef CC_PLATFORM_H
#define CC_PLATFORM_H
#include "Utils.h"
#include "PackedCol.h"
/* Abstracts platform specific memory management, I/O, etc.
   Copyright 2017 ClassicalSharp | Licensed under BSD-3
*/
struct DrawTextArgs;
struct AsyncRequest;

enum SOCKET_SELECT { SOCKET_SELECT_READ, SOCKET_SELECT_WRITE };
#ifdef CC_BUILD_WIN
typedef UIntPtr SocketPtr;
#else
typedef Int32 SocketPtr;
#endif

extern char* Platform_NewLine; /* Newline for text */
extern char Directory_Separator;
extern ReturnCode ReturnCode_FileShareViolation;
extern ReturnCode ReturnCode_FileNotFound;
extern ReturnCode ReturnCode_NotSupported;
extern ReturnCode ReturnCode_SocketInProgess;
extern ReturnCode ReturnCode_SocketWouldBlock;
extern ReturnCode ReturnCode_InvalidArg;

void Platform_ConvertString(void* dstPtr, const String* src);
void Platform_Init(void);
void Platform_Free(void);
void Platform_SetWorkingDir(void);
void Platform_Exit(ReturnCode code);
Int32 Platform_GetCommandLineArgs(int argc, STRING_REF const char** argv, String* args);
ReturnCode Platform_StartShell(const String* args);

NOINLINE_ void* Mem_Alloc(UInt32 numElems, UInt32 elemsSize, const char* place);
NOINLINE_ void* Mem_AllocCleared(UInt32 numElems, UInt32 elemsSize, const char* place);
NOINLINE_ void* Mem_Realloc(void* mem, UInt32 numElems, UInt32 elemsSize, const char* place);
NOINLINE_ void  Mem_Free(void* mem);
void Mem_Set(void* dst, UInt8 value, UInt32 numBytes);
void Mem_Copy(void* dst, void* src, UInt32 numBytes);

void Platform_Log(const String* message);
void Platform_LogConst(const char* message);
void Platform_Log1(const char* format, const void* a1);
void Platform_Log2(const char* format, const void* a1, const void* a2);
void Platform_Log3(const char* format, const void* a1, const void* a2, const void* a3);
void Platform_Log4(const char* format, const void* a1, const void* a2, const void* a3, const void* a4);

TimeMS DateTime_CurrentUTC_MS(void);
void DateTime_CurrentUTC(DateTime* time);
void DateTime_CurrentLocal(DateTime* time);
void Stopwatch_Measure(UInt64* timer);
Int32 Stopwatch_ElapsedMicroseconds(UInt64* timer);

bool Directory_Exists(const String* path);
ReturnCode Directory_Create(const String* path);
typedef void Directory_EnumCallback(const String* filename, void* obj);
ReturnCode Directory_Enum(const String* path, void* obj, Directory_EnumCallback callback);
bool File_Exists(const String* path);
ReturnCode File_GetModifiedTime_MS(const String* path, TimeMS* ms);

ReturnCode File_Create(void** file, const String* path);
ReturnCode File_Open(void** file, const String* path);
ReturnCode File_Append(void** file, const String* path);
ReturnCode File_Read(void* file, UInt8* buffer, UInt32 count, UInt32* bytesRead);
ReturnCode File_Write(void* file, UInt8* buffer, UInt32 count, UInt32* bytesWrote);
ReturnCode File_Close(void* file);
ReturnCode File_Seek(void* file, Int32 offset, Int32 seekType);
ReturnCode File_Position(void* file, UInt32* position);
ReturnCode File_Length(void* file, UInt32* length);

void Thread_Sleep(UInt32 milliseconds);
typedef void Thread_StartFunc(void);
void* Thread_Start(Thread_StartFunc* func, bool detach);
void Thread_Detach(void* handle);
void Thread_Join(void* handle);

void* Mutex_Create(void);
void  Mutex_Free(void* handle);
void  Mutex_Lock(void* handle);
void  Mutex_Unlock(void* handle);

void* Waitable_Create(void);
void  Waitable_Free(void* handle);
void  Waitable_Signal(void* handle);
void  Waitable_Wait(void* handle); 
void  Waitable_WaitFor(void* handle, UInt32 milliseconds);

NOINLINE_ void Font_GetNames(StringsBuffer* buffer);
NOINLINE_ void Font_Make(FontDesc* desc, const String* fontName, UInt16 size, UInt16 style);
NOINLINE_ void Font_Free(FontDesc* desc);
NOINLINE_ Size2D Platform_TextMeasure(struct DrawTextArgs* args);
NOINLINE_ Size2D Platform_TextDraw(struct DrawTextArgs* args, Bitmap* bmp, Int32 x, Int32 y, PackedCol col);

void Socket_Create(SocketPtr* socket);
ReturnCode Socket_Available(SocketPtr socket, UInt32* available);
ReturnCode Socket_SetBlocking(SocketPtr socket, bool blocking);
ReturnCode Socket_GetError(SocketPtr socket, ReturnCode* result);

ReturnCode Socket_Connect(SocketPtr socket, const String* ip, Int32 port);
ReturnCode Socket_Read(SocketPtr socket, UInt8* buffer, UInt32 count, UInt32* modified);
ReturnCode Socket_Write(SocketPtr socket, UInt8* buffer, UInt32 count, UInt32* modified);
ReturnCode Socket_Close(SocketPtr socket);
ReturnCode Socket_Select(SocketPtr socket, Int32 selectMode, bool* success);

void Http_Init(void);
ReturnCode Http_Do(struct AsyncRequest* req, volatile Int32* progress);
ReturnCode Http_Free(void);

#define AUDIO_MAX_CHUNKS 4
struct AudioFormat { UInt16 Channels, BitsPerSample; Int32 SampleRate; };
#define AudioFormat_Eq(a, b) ((a)->Channels == (b)->Channels && (a)->BitsPerSample == (b)->BitsPerSample && (a)->SampleRate == (b)->SampleRate)
typedef Int32 AudioHandle;

void Audio_Init(AudioHandle* handle, Int32 buffers);
ReturnCode Audio_Free(AudioHandle handle);
ReturnCode Audio_StopAndFree(AudioHandle handle);
struct AudioFormat* Audio_GetFormat(AudioHandle handle);
ReturnCode Audio_SetFormat(AudioHandle handle, struct AudioFormat* format);
ReturnCode Audio_BufferData(AudioHandle handle, Int32 idx, void* data, UInt32 dataSize);
ReturnCode Audio_Play(AudioHandle handle);
ReturnCode Audio_Stop(AudioHandle handle);
ReturnCode Audio_IsCompleted(AudioHandle handle, Int32 idx, bool* completed);
ReturnCode Audio_IsFinished(AudioHandle handle, bool* finished);
#endif
