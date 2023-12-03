
#ifndef POWER_EXPORT_H
#define POWER_EXPORT_H

#ifdef POWER_STATIC_DEFINE
#  define POWER_EXPORT
#  define POWER_NO_EXPORT
#else
#  ifndef POWER_EXPORT
#    ifdef MauiCorePower_EXPORTS
        /* We are building this library */
#      define POWER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define POWER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef POWER_NO_EXPORT
#    define POWER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef POWER_DEPRECATED
#  define POWER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef POWER_DEPRECATED_EXPORT
#  define POWER_DEPRECATED_EXPORT POWER_EXPORT POWER_DEPRECATED
#endif

#ifndef POWER_DEPRECATED_NO_EXPORT
#  define POWER_DEPRECATED_NO_EXPORT POWER_NO_EXPORT POWER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef POWER_NO_DEPRECATED
#    define POWER_NO_DEPRECATED
#  endif
#endif

#endif /* POWER_EXPORT_H */
