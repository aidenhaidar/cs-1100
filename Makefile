CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread
TARGET = guess_the_output
SRCS = main.cpp game.cpp questions.cpp leaderboard.cpp utils.cpp pages.cpp
OBJS = main.o questions.o leaderboard.o utils.o pages.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp httplib.h questions.h leaderboard.h pages.h utils.h
	$(CXX) $(CXXFLAGS) -c main.cpp

questions.o: questions.cpp questions.h
	$(CXX) $(CXXFLAGS) -c questions.cpp

leaderboard.o: leaderboard.cpp leaderboard.h
	$(CXX) $(CXXFLAGS) -c leaderboard.cpp

utils.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

pages.o: pages.cpp pages.h questions.h leaderboard.h
	$(CXX) $(CXXFLAGS) -c pages.cpp

clean:
	rm -f $(OBJS) $(TARGET)
