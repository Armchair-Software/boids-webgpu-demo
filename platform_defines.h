#pragma once

/// A preprocessor-only header file to simplify platform-dependent defines

#if defined _WIN32 || defined WIN32 || defined OS_WIN64 || defined _WIN64 || defined WIN64 || defined WINNT
  #define PLATFORM_WINDOWS
#elif defined __APPLE__ || defined macintosh || defined Macintosh
  #define PLATFORM_MACOS
#elif defined __linux__ || defined linux || defined __linux || defined __gnu_linux__ || defined __FreeBSD_kernel__ || defined __GNU__ || defined __unix__ || defined __unix || defined __OpenBSD__ || defined BSD || defined __NetBSD__ || defined __FreeBSD__
  #define PLATFORM_LINUX
#endif

#ifdef __EMSCRIPTEN__
  // note this is NOT mutually exclusive with the platforms above; PLATFORM_LINUX will usually also be defined
  #define PLATFORM_EMSCRIPTEN
#endif

#if defined(__x86_64__) || defined(_M_X64)
  #define PLATFORM_64BIT
#else
  #define PLATFORM_32BIT
#endif

#if defined __BIG_ENDIAN && __BYTE_ORDER == __BIG_ENDIAN
  #define PLATFORM_BIGENDIAN
#else
  #define PLATFORM_LITTLEENDIAN
#endif
