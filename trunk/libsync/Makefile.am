AM_CFLAGS = $(OPT) $(DEFINE) -Wall
AM_CPPFLAGS = -I.
AM_LDFLAGS  = -L.

MYCFLAGS = $(AM_CFLAGS) 
MYCFLAGS_THREADS = $(AM_CFLAGS) 


lib_LTLIBRARIES = libsync.la

libsync_la_SOURCES = sync.c md5.c adler32.c hashtable.c
libsync_la_CFLAGS = $(MYCFLAGS_THREADS)
libsync_la_LIBADD =

bin_PROGRAMS = synctest

synctest_SOURCES = synctest.c 
synctest_CFLAGS = $(MYCFLAGS_THREADS)
synctest_LDADD = .libs/libsync.a

