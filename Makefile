all: object.c header/object.h map.gv map.png lilcave

C = object.c misc.c noun.c location.c move.c inventory.c \
	inventory2.c openclose.c reach.c toggle.c parsexec.c match.c \
	main.c onoff.c expand.c talk.c attack.c damage.c turn.c social.c \
	server.c break.c client.c outbuf.c print.c tcp.c telnet.c
H = header/object.h header/misc.h header/noun.h header/location.h \
	header/move.h header/inventory.h header/parsexec.h header/openclose.h \
	header/reach.h header/toggle.h header/match.h header/inventory2.h \
	header/onoff.h header/expand.h header/talk.h header/attack.h \
	header/damage.h header/turn.h header/social.h header/server.h \
	header/break.h header/client.h header/print.h header/tcp.h header/telnet.h \
	header/outbuf.h

lilcave: $(C) $(H)
	gcc -Wall -Wextra $(C) -o $@

header/object.h: object.awk object.txt
	awk -v pass=h -f object.awk object.txt > $@

object.c: object.awk object.txt
	awk -v pass=c1 -f object.awk object.txt > $@
	awk -v pass=c2 -f object.awk object.txt >> $@

map.png: map.gv
	dot -Tpng -o $@ $<

map.gv: map.awk object.txt
	awk -f map.awk object.txt > $@

success.txt: lilcave testscript.txt baseline.txt
	./lilcave testscript.txt > transcript.txt
	cmp baseline.txt transcript.txt
	mv -f transcript.txt success.txt

clean:
	rm object.c header/object.h lilcave map.gv map.png