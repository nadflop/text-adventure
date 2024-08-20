all: map.png

C = object.c misc.c noun.c location.c move.c inventory.c parsexec.c main.c
H = header/object.h header/misc.h header/noun.h header/location.h header/move.h header/inventory.h header/parsexec.h

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

clean:
	$(RM) object.c object.h lilcave map.gv map.png