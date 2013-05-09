## Process this file with automake to produce Makefile.in

include_INCLUDES = ndatk.hh Chart.hh Exsdir.hh translate_Isomer.hh utils.hh
lib_LIBRARIES = libndatk.a
libndatk_a_SOURCES = CuratedData.cc CuratedData.hh \
	Chart.cc Chart.hh Exsdir.cc Exsdir.hh \
	translate_Isomer.cc translate_Isomer.hh \
	utils.cc utils.hh

check_PROGRAMS = TestRunner
TestRunner_SOURCES = TestRunner.cc \
	ChartTest.cc ChartTest.hh \
	UnitTest.cc UnitTest.hh ExsdirTest.cc ExsdirTest.hh \
	utilsTest.cc utilsTest.hh

TestRunner_LDADD = libndatk.a

TESTS = TestRunner
