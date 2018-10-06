#ifndef CC_CORE_H
#define CC_CORE_H
/* Core fixed-size integer and floating point types, and common small structs.
   Copyright 2017 ClassicalSharp | Licensed under BSD-3
*/

#if _MSC_VER
typedef unsigned __int8  UInt8;
typedef unsigned __int16 UInt16;
typedef unsigned __int32 UInt32;
typedef unsigned __int64 UInt64;
#ifdef _WIN64
typedef unsigned __int64 UIntPtr;
#else
typedef unsigned int     UIntPtr;
#endif

typedef signed __int8  Int8;
typedef signed __int16 Int16;
typedef signed __int32 Int32;
typedef signed __int64 Int64;
#define NOINLINE_ __declspec(noinline)
#elif __GNUC__
#include <stdint.h>
typedef uint8_t  UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;
typedef uintptr_t UIntPtr;

typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;
#define NOINLINE_ __attribute__((noinline))
#else
#error "I don't recognise this compiler. You'll need to add required definitions in Core.h!"
#endif

typedef UInt8 bool;
#define true 1
#define false 0
#define NULL ((void*)0)

#define EXTENDED_BLOCKS
#ifdef EXTENDED_BLOCKS
typedef UInt16 BlockID;
#else
typedef UInt8 BlockID;
#endif

#define EXTENDED_TEXTURES
#ifdef EXTENDED_TEXTURES
typedef UInt16 TextureLoc;
#else
typedef UInt8 TextureLoc;
#endif

typedef UInt8 BlockRaw;
typedef UInt8 EntityID;
typedef UInt8 Face;
typedef UInt32 ReturnCode;
typedef UInt64 TimeMS;

typedef struct Rect2D_  { Int32 X, Y, Width, Height; } Rect2D;
typedef struct Point2D_ { Int32 X, Y; } Point2D;
typedef struct Size2D_  { Int32 Width, Height; } Size2D;
typedef struct FontDesc_ { void* Handle; UInt16 Size, Style; } FontDesc;
typedef struct TextureRec_ { float U1, V1, U2, V2; } TextureRec;
typedef struct Bitmap_ { UInt8* Scan0; Int32 Width, Height; } Bitmap;

/*#define CC_BUILD_GL11*/
#define CC_BUILD_D3D9
#define CC_BUILD_WIN
/*#define CC_BUILD_OSX*/
/*#define CC_BUILD_NIX*/
/*#define CC_BUILD_SOLARIS*/

#ifdef CC_BUILD_D3D9
typedef void* GfxResourceID;
#else
typedef UInt32 GfxResourceID;
#endif
#endif
