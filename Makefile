RM = /bin/rm 
CFLAGS = -D_FILE_OFFSET_BITS=64
all:	libsync.a libsync.so synctest
libsync.a:
	gcc -c  $(CFLAGS) adler32.c hashtable.c md5.c sync.c
	ar -rsv libsync.a *.o 
	chmod +x libsync.a
libsync.so:
	gcc -fPIC -g $(CFLAGS) -c adler32.c hashtable.c md5.c sync.c
	gcc $(CFLAGS) -g -shared -W1,-soname,libsync.so -o libsync.so *.o

synctest:
	gcc -o synctest synctest.c -L. -lsync

install:
	cp -rf libsync.* /usr/local/lib/
	ln -sf /usr/local/lib/libsync.so  /usr/local/lib/libsync.so.1

uninstall:
	rm -rf /usr/local/lib/libsync.*

clean: 
	$(RM) -rf *.o  libsync.a libsync.so synctest

