
#ifndef CrossViews_EXPORT_H
#define CrossViews_EXPORT_H

#ifdef CrossViews_BUILT_AS_STATIC
#  define CrossViews_EXPORT
#  define CROSSVIEWS_NO_EXPORT
#else
#  ifndef CrossViews_EXPORT
#    ifdef CrossViews_EXPORTS
        /* We are building this library */
#      define CrossViews_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CrossViews_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef CROSSVIEWS_NO_EXPORT
#    define CROSSVIEWS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef CROSSVIEWS_DEPRECATED
#  define CROSSVIEWS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CROSSVIEWS_DEPRECATED_EXPORT
#  define CROSSVIEWS_DEPRECATED_EXPORT CrossViews_EXPORT CROSSVIEWS_DEPRECATED
#endif

#ifndef CROSSVIEWS_DEPRECATED_NO_EXPORT
#  define CROSSVIEWS_DEPRECATED_NO_EXPORT CROSSVIEWS_NO_EXPORT CROSSVIEWS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CROSSVIEWS_NO_DEPRECATED
#    define CROSSVIEWS_NO_DEPRECATED
#  endif
#endif

#endif
