EXECS  = retroPower
LIBS   = -lwiringPi
CC     = gcc $(CFLAGS)

all: $(EXECS)

retrogame: retroPower/main.c
	$(CC) $< $(LIBS) -o $@

install:
	mv $(EXECS) /usr/bin

clean:
	rm -f $(EXECS)
