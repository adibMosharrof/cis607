CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		main3E.o image.o sink.o source.o PNMreader.o PNMwriter.o filter.o

LIBS =

TARGET =	proj3E

$(TARGET):	$(OBJS)
	g++ -o $(TARGET) $(OBJS) $(LIBS)

prog:	$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)
