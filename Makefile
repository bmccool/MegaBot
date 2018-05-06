CC = g++
CFLAGS = -c -g -Wall `pkg-config --cflags opencv` -std=c++11
LDFLAGS = `pkg-config --libs opencv` -lX11 -lpthread -ldl
SOURCES = main.cpp HW_camera.cpp CS_time.cpp CT_window_manager.cpp FCEUX.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = MegaBot 

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) *.o *~
