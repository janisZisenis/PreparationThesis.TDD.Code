
#ifndef QtViews_EXPORT_H
#define QtViews_EXPORT_H

#ifdef QtViews_BUILT_AS_STATIC
#  define QtViews_EXPORT
#  define QTVIEWS_NO_EXPORT
#else
#  ifndef QtViews_EXPORT
#    ifdef QtViews_EXPORTS
        /* We are building this library */
#      define QtViews_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define QtViews_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef QTVIEWS_NO_EXPORT
#    define QTVIEWS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef QTVIEWS_DEPRECATED
#  define QTVIEWS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef QTVIEWS_DEPRECATED_EXPORT
#  define QTVIEWS_DEPRECATED_EXPORT QtViews_EXPORT QTVIEWS_DEPRECATED
#endif

#ifndef QTVIEWS_DEPRECATED_NO_EXPORT
#  define QTVIEWS_DEPRECATED_NO_EXPORT QTVIEWS_NO_EXPORT QTVIEWS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QTVIEWS_NO_DEPRECATED
#    define QTVIEWS_NO_DEPRECATED
#  endif
#endif

#endif
