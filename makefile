CXXFLAGS = -g

TestRunner: TestRunner.cc UnitTest.o \
	UtilsTest.hh ChartTest.o LibraryTest.o chart.o library.o \
	provendata.o utils.o 	

test_library: test_library.cc library.o provendata.o utils.o

test_chart: test_chart.cc chart.o provendata.o utils.o

test_utils: test_utils.cc utils.o

library.o: library.cc library.hh provendata.hh utils.hh  
chart.o: chart.cc chart.hh provendata.hh utils.hh
provendata.o: provendata.cc provendata.hh 
utils.o: utils.cc utils.hh
UnitTest.o: UnitTest.cc UnitTest.hh
ChartTest.o: ChartTest.cc ChartTest.hh chart.hh
LibraryTest.o: LibraryTest.cc LibraryTest.hh library.hh
