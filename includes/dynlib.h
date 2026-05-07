#ifndef DYNLIB_H_
#define DYNLIB_H_

#if defined(_WIN32)
#   include <minwindef.h>
#   include <libloaderapi.h>

#   define DynLib HINSTANCE
#   define DynFunc FARPROC

#   define dynLibOpen(libname) LoadLibraryW(L ## libname)
#   define dynLibLoadFunction(lib, fn) GetProcAddress((lib), (fn))
#   define dynLibClose(lib) FreeLibrary((lib))
#else
#   include <dlfcn.h>

#   define DynLib void*
#   define DynFunc void*

#   define dynLibOpen(libname) dlopen((libname), RTLD_LAZY)
#   define dynLibLoadFunction(lib, fn) dlsym((lib), (fn))
#   define dynLibClose(lib) dlclose((lib))

#endif // defined(_WIN32)

#endif // DYNLIB_H_
