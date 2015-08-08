#==============================================================================
TARGET		= dude
#==============================================================================
SDIR		= src
ODIR		= obj
LDIR		= lib
IDIR		= include
#==============================================================================
#DEFINES	= -D_LARGEFILE64_SOURCE -DDEBUG
DEFINES		= -DDEBUG
WARNINGS	= -Wall
CFLAGS	   += -std=c99 -Wall -O3 -s -DINI_MAX_LINE=2048
CXXFLAGS	= -std=c++11 -I$(IDIR) -L$(LDIR)
#==============================================================================
SRCS 		= $(wildcard $(SDIR)/*.cpp)
OBJS		= $(wildcard %,$(ODIR)/%.o, $(SRCS))
LIBS		= $(LDIR)/libinih.a
#==============================================================================
# -=[Release Build]=-
ifeq ($(RELEASE), 1)
  CXXFLAGS += -O3 -Os -s
else
  CXXFLAGS += -g
endif
# -=[SDL/Graphical Build]=-
ifeq ($(SDL), 1)
  LIBS += -lSDL
else
  LIBS += -lncurses
endif
#==============================================================================
CC			:= $(CROSS)$(CC)
CXX			:= $(CROSS)$(CXX)
CPPFLAGS	+= $(CXXFLAGS) $(WARNINGS) $(DEFINES)
#==============================================================================
dude: $(ODIR) $(LDIR)/libinih.a $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $(OBJS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

$(LDIR)/libinih.a: $(LDIR) $(IDIR) $(ODIR)/libini.o
	ar rcs $@ $(ODIR)/libini.o
	mkdir -p $(IDIR)/inih
	cp $(SDIR)/inih/ini.h $(IDIR)/inih/ini.h

$(ODIR)/libini.o: $(SDIR)/inih/ini.c
	$(CC) -c -o $@ $(CFLAGS) $^
#==============================================================================
$(ODIR):
	mkdir -p $(ODIR)

$(LDIR):
	mkdir -p $(LDIR)

$(IDIR):
	mkdir -p $(IDIR)
#==============================================================================
.PHONY: clean
clean:
	rm -rf $(ODIR)/ $(LDIR)/
#==============================================================================
