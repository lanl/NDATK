CXXFLAGS = -g

test_library: test_library.cc library.o utils.o

test_chart: test_chart.cc chart.o utils.o

test_utils: test_utils.cc utils.o

library.o: library.cc library.hh utils.hh  
chart.o: chart.cc chart.hh utils.hh
utils.o: utils.cc utils.hh
