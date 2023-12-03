
#ifndef NOTIFICATIONS_EXPORT_H
#define NOTIFICATIONS_EXPORT_H

#ifdef NOTIFICATIONS_STATIC_DEFINE
#  define NOTIFICATIONS_EXPORT
#  define NOTIFICATIONS_NO_EXPORT
#else
#  ifndef NOTIFICATIONS_EXPORT
#    ifdef MauiCoreNotifications_EXPORTS
        /* We are building this library */
#      define NOTIFICATIONS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define NOTIFICATIONS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef NOTIFICATIONS_NO_EXPORT
#    define NOTIFICATIONS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef NOTIFICATIONS_DEPRECATED
#  define NOTIFICATIONS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef NOTIFICATIONS_DEPRECATED_EXPORT
#  define NOTIFICATIONS_DEPRECATED_EXPORT NOTIFICATIONS_EXPORT NOTIFICATIONS_DEPRECATED
#endif

#ifndef NOTIFICATIONS_DEPRECATED_NO_EXPORT
#  define NOTIFICATIONS_DEPRECATED_NO_EXPORT NOTIFICATIONS_NO_EXPORT NOTIFICATIONS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef NOTIFICATIONS_NO_DEPRECATED
#    define NOTIFICATIONS_NO_DEPRECATED
#  endif
#endif

#endif /* NOTIFICATIONS_EXPORT_H */
