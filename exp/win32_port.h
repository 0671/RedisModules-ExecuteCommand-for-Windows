/*
 * Unification of type definitions with the ones used in Redis for Windows.
 * Based on:
 * - https://github.com/tporadowski/redis/blob/win-4.0.2/src/Win32_Interop/win32_types_hiredis.h
 * - https://github.com/tporadowski/redis/blob/win-4.0.2/src/Win32_Interop/Win32_Portability.h
 */
#ifndef WIN32_PORT_H
#define WIN32_PORT_H

#ifdef _WIN32

typedef __int64 PORT_LONGLONG;
typedef unsigned __int64 PORT_ULONGLONG;
typedef double PORT_LONGDOUBLE;

#define IF_WIN32(x, y) x
#define WIN32_ONLY(x) x
#define POSIX_ONLY(x)
#define inline __inline

#ifdef _WIN64
typedef __int64 ssize_t;
typedef __int64 PORT_LONG;
typedef unsigned __int64 PORT_ULONG;
#else
typedef long ssize_t;
typedef long PORT_LONG;
typedef unsigned long PORT_ULONG;
#endif

#ifdef _WIN64
#define PORT_LONG_MAX _I64_MAX
#define PORT_LONG_MIN _I64_MIN
#define PORT_ULONG_MAX _UI64_MAX
#else
#define PORT_LONG_MAX LONG_MAX
#define PORT_LONG_MIN LONG_MIN
#define PORT_ULONG_MAX ULONG_MAX
#endif

#else //not(_WIN32)

typedef long long PORT_LONGLONG;
typedef unsigned long long PORT_ULONGLONG;
typedef double PORT_LONGDOUBLE;
typedef long PORT_LONG;
typedef unsigned long PORT_ULONG;

#define IF_WIN32(x, y) y
#define WIN32_ONLY(x)
#define POSIX_ONLY(x) x

#endif

#endif