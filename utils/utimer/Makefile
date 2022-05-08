CC = g++
CFLAGS = -O3 -Wall -g
OUTDIR = out

.PHONY: clean

$(OUTDIR):
	mkdir ./$(OUTDIR)

utimer: $(OUTDIR) ./$(OUTDIR)/utimer.o
	@printf ""

./$(OUTDIR)/utimer.o: utimer.cpp utimer.h
	$(CC) $(CFLAGS) -c utimer.cpp -o ./$(OUTDIR)/utimer.o

clean:
	rm -f ./$(OUTDIR)/*.o
