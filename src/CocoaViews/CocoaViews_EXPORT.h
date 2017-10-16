
#ifndef CocoaViews_EXPORT_H
#define CocoaViews_EXPORT_H

#ifdef CocoaViews_BUILT_AS_STATIC
#  define CocoaViews_EXPORT
#  define COCOAVIEWS_NO_EXPORT
#else
#  ifndef CocoaViews_EXPORT
#    ifdef CocoaViews_EXPORTS
        /* We are building this library */
#      define CocoaViews_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CocoaViews_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef COCOAVIEWS_NO_EXPORT
#    define COCOAVIEWS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef COCOAVIEWS_DEPRECATED
#  define COCOAVIEWS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef COCOAVIEWS_DEPRECATED_EXPORT
#  define COCOAVIEWS_DEPRECATED_EXPORT CocoaViews_EXPORT COCOAVIEWS_DEPRECATED
#endif

#ifndef COCOAVIEWS_DEPRECATED_NO_EXPORT
#  define COCOAVIEWS_DEPRECATED_NO_EXPORT COCOAVIEWS_NO_EXPORT COCOAVIEWS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COCOAVIEWS_NO_DEPRECATED
#    define COCOAVIEWS_NO_DEPRECATED
#  endif
#endif

#endif
