EXECS  = retropower
LIBS   = -lwiringPi
CC     = gcc $(CFLAGS)

all: $(EXECS)

retropower:
	$(CC) retroPower/libs/ini.c retroPower/checkBat.c retroPower/debugLogger.c retroPower/powerConfig.c retroPower/powerOff.c retroPower/main.c $(LIBS) -o $@

install:
	mv $(EXECS) $(DESTDIR)/usr/bin

clean:
	rm -f $(EXECS)
