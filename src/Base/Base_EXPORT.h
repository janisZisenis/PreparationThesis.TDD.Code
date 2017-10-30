
#ifndef Base_EXPORT_H
#define Base_EXPORT_H

#ifdef Base_BUILT_AS_STATIC
#  define Base_EXPORT
#  define BASE_NO_EXPORT
#else
#  ifndef Base_EXPORT
#    ifdef Base_EXPORTS
        /* We are building this library */
#      define Base_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define Base_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef BASE_NO_EXPORT
#    define BASE_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef BASE_DEPRECATED
#  define BASE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef BASE_DEPRECATED_EXPORT
#  define BASE_DEPRECATED_EXPORT Base_EXPORT BASE_DEPRECATED
#endif

#ifndef BASE_DEPRECATED_NO_EXPORT
#  define BASE_DEPRECATED_NO_EXPORT BASE_NO_EXPORT BASE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BASE_NO_DEPRECATED
#    define BASE_NO_DEPRECATED
#  endif
#endif

#endif
