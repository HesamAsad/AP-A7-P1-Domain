CXX = g++
CXXFLAGS = -std=c++11

SRCS = Filter.cpp Interface.cpp Reservation.cpp Rooms.cpp Utrip.cpp Hotel.cpp   main.cpp Reservation_date.cpp User.cpp
OBJS = $(SRCS:.cpp=.o) # Replace .cpp with .o
MAIN = utrip

# Not related to a file
.PHONY: clean all

all: $(MAIN)
	@echo Compiled $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

# Suffix replacement $< = .cpp, $@ = .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) *.o .*~ $(MAIN)
