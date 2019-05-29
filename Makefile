EXECS  = retropower
LIBS   = -lwiringPi
CC     = gcc $(CFLAGS)

all: $(EXECS)

retropower: retroPower/main.c
	$(CC) $< $(LIBS) -o $@

install:
	mv $(EXECS) $(DESTDIR)/usr/bin

clean:
	rm -f $(EXECS)
