CC = g++
CFLAGS = -O3 -Wall -g
OBJDIR = obj

.PHONY: clean

$(OBJDIR):
	mkdir ./$(OBJDIR)

utimer: $(OBJDIR) $(OBJDIR)/utimer.o
	@printf ""

$(OBJDIR)/utimer.o: utimer.cpp utimer.h
	$(CC) $(CFLAGS) -c utimer.cpp -o $(OBJDIR)/utimer.o

clean:
	rm -f ./$(OBJDIR)/*.o
