CC = g++
CFLAGS = -O3 -Wall -g

OBJDIR 		= obj
INCDIR		= include

INCLUDES 	= -I $(INCDIR)
LIBS		=

.PHONY: clean

$(OBJDIR):
	mkdir ./$(OBJDIR)

all: $(OBJDIR) assignment2.out

$(OBJDIR)/%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

assignment2.out: $(OBJDIR)/assignment2.o $(OBJDIR)/map.o ../utils/utimer/obj/utimer.o ../utils/logger/logger.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJDIR)/*.o assignment2.out
