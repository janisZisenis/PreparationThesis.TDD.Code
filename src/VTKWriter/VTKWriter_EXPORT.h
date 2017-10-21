
#ifndef VTKWriter_EXPORT_H
#define VTKWriter_EXPORT_H

#ifdef VTKWriter_BUILT_AS_STATIC
#  define VTKWriter_EXPORT
#  define VTKWRITER_NO_EXPORT
#else
#  ifndef VTKWriter_EXPORT
#    ifdef VTKWriter_EXPORTS
        /* We are building this library */
#      define VTKWriter_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKWriter_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKWRITER_NO_EXPORT
#    define VTKWRITER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKWRITER_DEPRECATED
#  define VTKWRITER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VTKWRITER_DEPRECATED_EXPORT
#  define VTKWRITER_DEPRECATED_EXPORT VTKWriter_EXPORT VTKWRITER_DEPRECATED
#endif

#ifndef VTKWRITER_DEPRECATED_NO_EXPORT
#  define VTKWRITER_DEPRECATED_NO_EXPORT VTKWRITER_NO_EXPORT VTKWRITER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKWRITER_NO_DEPRECATED
#    define VTKWRITER_NO_DEPRECATED
#  endif
#endif

#endif
