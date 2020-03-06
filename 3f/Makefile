SRC=main3F.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3F

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3F




#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
#
#OBJS =		3f.o
#
#LIBS =
#
#TARGET =	3f.exe
#
#$(TARGET):	$(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
#
#all:	$(TARGET)
#
#clean:
#	rm -f $(OBJS) $(TARGET)
