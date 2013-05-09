## Process this file with automake to produce Makefile.in

ndatk_INCLUDE = -I$(top_srcdir)/src
ndatk_LIB = ../src/libndatk.a
 
noinst_PROGRAMS = test_Chart test_Exsdir \
	test_translate_Isomer test_utils

test_Chart_SOURCES = test_Chart.cc
test_Chart_LDADD = $(ndatk_LIB)
test_Chart_CXXFLAGS = $(ndatk_INCLUDE)

test_Exsdir_SOURCES = test_Exsdir.cc
test_Exsdir_LDADD = $(ndatk_LIB)
test_Exsdir_CXXFLAGS = $(ndatk_INCLUDE)

test_translate_Isomer_SOURCES = test_translate_Isomer.cc
test_translate_Isomer_LDADD = $(ndatk_LIB)
test_translate_Isomer_CXXFLAGS = $(ndatk_INCLUDE)

test_utils_SOURCES = test_utils.cc
test_utils_LDADD = $(ndatk_LIB)
test_utils_CXXFLAGS = $(ndatk_INCLUDE)
