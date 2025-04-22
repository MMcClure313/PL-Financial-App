CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCS     = main.cpp user.cpp expense.cpp expense_manager.cpp budget.cpp utils.cpp
OBJS     = $(SRCS:.cpp=.o)
TARGET   = expense_tracker

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
