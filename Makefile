EXECUTABLE = bright
CFILE = bright.c
EXECFILE = /usr/bin/bright

C = gcc
CFLAGS = -g -Wall -std=c99

.PHONY: main install

main:
	$(C) $(CFLAGS) -o $(EXECUTABLE) $(CFILE)

install:
	make main
	@if [ ! -f $(EXECFILE) ]; then\
		sudo chown root bright;\
		sudo chmod 4754 bright;\
		sudo mv bright $(EXECFILE);\
	else\
		echo "BRIGHT ALREADY EXISTS";\
	fi
