
#ifndef AUDIO_EXPORT_H
#define AUDIO_EXPORT_H

#ifdef AUDIO_STATIC_DEFINE
#  define AUDIO_EXPORT
#  define AUDIO_NO_EXPORT
#else
#  ifndef AUDIO_EXPORT
#    ifdef MauiCoreAudio_EXPORTS
        /* We are building this library */
#      define AUDIO_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define AUDIO_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef AUDIO_NO_EXPORT
#    define AUDIO_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef AUDIO_DEPRECATED
#  define AUDIO_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef AUDIO_DEPRECATED_EXPORT
#  define AUDIO_DEPRECATED_EXPORT AUDIO_EXPORT AUDIO_DEPRECATED
#endif

#ifndef AUDIO_DEPRECATED_NO_EXPORT
#  define AUDIO_DEPRECATED_NO_EXPORT AUDIO_NO_EXPORT AUDIO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef AUDIO_NO_DEPRECATED
#    define AUDIO_NO_DEPRECATED
#  endif
#endif

#endif /* AUDIO_EXPORT_H */
