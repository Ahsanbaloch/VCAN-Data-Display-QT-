TARGET = speed_feeder

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) -lncurses

%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re



