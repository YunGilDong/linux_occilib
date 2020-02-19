#
# Environment
#
OCCI_INC = /usr/include/oracle/19.5/client64/
OCCI_LIB = /usr/lib/oracle/19.5/client64/lib
CPPVER = -std=c++11
CCOPTS = $(CPPVER) -c -Wno-write-strings -I$(OCCI_INC)
LDOPTS = -L$(OCCI_LIB)
GCCVER =-4.8

#CC = g++ $(CCOPTS)
CC = g++-4.8 $(CCOPTS)
#LINK = g++ $(LDOPTS)
LINK = g++-4.8 $(LDOPTS)
.cpp.o:	; $(CC) $<
LIBS = -locci -lclntsh
#LIBS = 

OBJS = ClsDB.o ClsOcci.o

TARGET = ClsDB

default:	$(TARGET)

$(TARGET):	$(OBJS)
	$(LINK) $(OBJS) -o $@ $(LIBS)