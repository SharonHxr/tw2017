INC = .
SRCS = BillingRule.cpp \
       main.cpp	\
	   Schedule.cpp \
	   InputOutput.cpp \
	   PlayGround.cpp

OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = $(addprefix -I,$(INC))

test: $(OBJS)
	c++ -o $@ $^
#*.o : *.cpp
#	c++ -c $(CXXFLAGS) -o $@ $<

.phony :clean
clean:
	-rm -f $(OBJS)
	-rm -f test
