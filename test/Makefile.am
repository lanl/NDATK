## Process this file with automake to produce Makefile.in

ndatk_INCLUDE = -I$(top_srcdir)/src
ndatk_LIB = ../src/libndatk.a
 
noinst_PROGRAMS = test_Chart use1_Chart \
	test_Exsdir test_FileStat use0_Library use2_Library \
	test_translate_isomer test_utils

test_Chart_SOURCES = test_Chart.cc
test_Chart_LDADD = $(ndatk_LIB)
test_Chart_CXXFLAGS = $(ndatk_INCLUDE)

use0_Library_SOURCES = use0_Library.cc
use0_Library_LDADD = $(ndatk_LIB)
use0_Library_CXXFLAGS = $(ndatk_INCLUDE)

use2_Library_SOURCES = use2_Library.cc
use2_Library_LDADD = $(ndatk_LIB)
use2_Library_CXXFLAGS = $(ndatk_INCLUDE)

use1_Chart_SOURCES = use1_Chart.cc
use1_Chart_LDADD = $(ndatk_LIB)
use1_Chart_CXXFLAGS = $(ndatk_INCLUDE)

test_Exsdir_SOURCES = test_Exsdir.cc
test_Exsdir_LDADD = $(ndatk_LIB)
test_Exsdir_CXXFLAGS = $(ndatk_INCLUDE)

test_FileStat_SOURCES = test_FileStat.cc
test_FileStat_LDADD = $(ndatk_LIB)
test_FileStat_CXXFLAGS = $(ndatk_INCLUDE)

test_translate_isomer_SOURCES = test_translate_isomer.cc
test_translate_isomer_LDADD = $(ndatk_LIB)
test_translate_isomer_CXXFLAGS = $(ndatk_INCLUDE)

test_utils_SOURCES = test_utils.cc
test_utils_LDADD = $(ndatk_LIB)
test_utils_CXXFLAGS = $(ndatk_INCLUDE)
