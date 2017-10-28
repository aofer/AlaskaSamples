#pragma once
#include "Logger.h"

#define LOG_DEBUG(msg) Common::Logger::GetInstance().LogDebug(msg)
#define LOG_ERROR(msg) Common::Logger::GetInstance().LogError(msg)
#define LOG_WARNING(msg) Common::Logger::GetInstance().LogWarning(msg)
#define LOG_INFO(msg)	Common::Logger::GetInstance().LogInfo(msg)

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;

#define INVALID_GL_VALUE 0xffffffff
#define INVALID_UNIFORM_LOCATION 0xffffffff

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;