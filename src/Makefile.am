## Process this file with automake to produce Makefile.in

AM_CXXFLAGS = -ansi -pedantic -Wall -fPIC
include_HEADERS = ndatk.hh Library.hh Chart.hh Exsdir.hh \
	CuratedData.hh translate_isomer.hh utils.hh constants.hh

lib_LIBRARIES = libndatk.a
libndatk_a_SOURCES = CuratedData.cc CuratedData.hh \
	Chart.cc Chart.hh Exsdir.cc Exsdir.hh Library.cc Library.hh \
	translate_isomer.cc translate_isomer.hh \
	utils.cc utils.hh constants.hh

check_PROGRAMS = TestRunner
TestRunner_SOURCES = TestRunner.cc \
	LibraryTest.cc LibraryTest.hh \
	ChartTest.cc ChartTest.hh \
	ExsdirTest.cc ExsdirTest.hh \
	translate_isomerTest.cc translate_isomer.hh \
	utilsTest.cc utilsTest.hh \
	UnitTest.cc UnitTest.hh 

TestRunner_LDADD = libndatk.a

TESTS = TestRunner
