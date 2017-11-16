#pragma once
#include "Logger.h"


#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;

#define INVALID_GL_VALUE 0xffffffff
#define INVALID_UNIFORM_LOCATION 0xffffffff

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;


//log helpers
template<typename T>
inline void LOG_DEBUG(const T& msg)
{
	Common::Logger::GetInstance().LogDebug(msg);
}

template <typename Arg1, typename... Args>
inline void LOG_DEBUG(const char* fmt, const Arg1 &arg1, const Args&... args)
{
	Common::Logger::GetInstance().LogDebugFormated(fmt, arg1, args...);
}

template<typename T>
inline void LOG_ERROR(const T& msg)
{
	Common::Logger::GetInstance().LogError(msg);
}

template <typename Arg1, typename... Args>
inline void LOG_ERROR(const char* fmt, const Arg1 &arg1, const Args&... args)
{
	Common::Logger::GetInstance().LogErrorFormated(fmt, arg1, args...);
}

template<typename T>
inline void LOG_WARNING(const T& msg)
{
	Common::Logger::GetInstance().LogWarning(msg);
}

template <typename Arg1, typename... Args>
inline void LOG_WARNING(const char* fmt, const Arg1 &arg1, const Args&... args)
{
	Common::Logger::GetInstance().LogWarningFormated(fmt, arg1, args...);
}

template<typename T>
inline void LOG_INFO(const T& msg)
{
	Common::Logger::GetInstance().LogInfo(msg);
}

template <typename Arg1, typename... Args>
inline void LOG_INFO(const char* fmt, const Arg1 &arg1, const Args&... args)
{
	Common::Logger::GetInstance().LogInfoFormatted(fmt, arg1, args...);
}
