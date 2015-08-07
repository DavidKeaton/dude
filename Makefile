#==============================================================================
TARGET		= dude
#==============================================================================
SDIR		= src
ODIR		= obj
LDIR		= lib
IDIR		= include
#==============================================================================
#DEFINES		= -D_LARGEFILE64_SOURCE -DDEBUG
DEFINES		= -DDEBUG
WARNINGS	= -Wall -Wno-multichar -Wno-switch -Wno-unused-label
CCFLAGS		= -std=c99 -Wall
CXXFLAGS	= -std=c++11 -I$(IDIR) -L$(LDIR)
#==============================================================================
SOURCES 	= $(wildcard $(SDIR)/%.cpp)
OBJECTS		= $(wildcard %,$(ODIR)/%.o, $(SOURCES))
LIBS		= $(LDIR)/libinih.a
#==============================================================================
ifeq ($(RELEASE), 1)
  CXXFLAGS 	+= -O3 -Os -s
else
  CXXFLAGS 	+= -g
endif
CFLAGS		+= $(CCFLAGS) $(WARNINGS) $(DEFINES)
CPPFLAGS	+= $(CXXFLAGS) $(WARNINGS) $(DEFINES)
#==============================================================================
dude: $(ODIR) $(LDIR)/libinih.a $(OBJECTS)
	$(CXX) -o $@ $(CPPFLAGS) $(OBJECTS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

$(LDIR)/libinih.a: src/inih/ini.c
	$(CC) -o $@ $(CFLAGS) $^
#==============================================================================
$(ODIR):
	mkdir -p $(ODIR)
#==============================================================================
.PHONY: clean
clean:
	rm -rf $(ODIR)/
#==============================================================================
