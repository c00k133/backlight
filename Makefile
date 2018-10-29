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
		sudo chown root $(EXECUTABLE);\
		sudo chmod 4754 $(EXECUTABLE);\
		sudo mv $(EXECUTABLE) $(EXECFILE);\
	else\
		echo "BRIGHT ALREADY EXISTS";\
	fi
