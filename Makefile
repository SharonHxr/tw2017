INC = src/include
SRCS = src/BillingRule.cpp \
       src/main.cpp	\
	   src/Schedule.cpp \
	   src/InputOutput.cpp \
	   src/PlayGround.cpp

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
