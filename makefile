CXXFLAGS = -g

test_chart: test_chart.cc chart.o utils.o

test_utils: test_utils.cc utils.o
 
chart.o: chart.cc chart.hh utils.hh
utils.o: utils.cc utils.hh
