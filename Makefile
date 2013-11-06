CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic
LDFLAGS=-lpthread
OBJ=$(SRC:.c=.o)
SRC=$(addprefix $(CDIR), $(CFILES))
CDIR=src/
CFILES=destroy.c myHTTPd.c parseSocket.c daemon.c socket.c errors.c \
	string.c parser.c signal.c threads.c send.c server_errors.c
EXEC=myHTTPd
ARCHIVE=gatine_v-myHTTPd

-include Make.rules

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ)
	rm -rf $(EXEC)
	rm -rf $(EXEC).core
	rm -rf $(ARCHIVE).tar.bz2

distclean: clean
	rm -rf Make.rules

export:
	git archive HEAD --prefix=$(ARCHIVE)/ | bzip2 > $(ARCHIVE).tar.bz2

check: all
	check/check.sh $(EXEC)

doc:
	doxygen Doxyfile

.PHONY: all clean export debug check doc distclean
