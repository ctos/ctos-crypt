CC= gcc
LDFLAGS= -lmcrypt
ctos_crypt: example.c crypt.c
	    $(CC) $(LDFLAGS)  -o $@ $^

.PHONY:

clean:
	-rm ctos_crypt
