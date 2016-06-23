check_PROGRAMS = oftest

oftest_SOURCES = oftest.c

nodist_EXTRA_oftest_SOURCES = dummy.cxx

oftest_CPPFLAGS = -I$(includedir)
oftest_CPPFLAGS += -I$(srcdir)/../thrift_endpoint
oftest_CPPFLAGS += -I$(builddir)/../../oftest
oftest_CPPFLAGS += -I$(top_srcdir)/pdfixed
oftest_CPPFLAGS += -D_BMV2_

if P4THRIFT
    oftest_CPPFLAGS += -DP4THRIFT
endif

oftest_LDFLAGS = -L$(libdir)
oftest_LDFLAGS += -pthread

noinst_LTLIBRARIES = libthrift_endpoint.la
libthrift_endpoint_la_SOURCES = ../thrift_endpoint/src/server.cpp

oftest_LDADD = libthrift_endpoint.la
oftest_LDADD += $(builddir)/../../libof.la -lp4ofagent $(builddir)/../../libpd.la -lbmpdfixed
oftest_LDADD += -lruntimestubs -lsimpleswitch_thrift -lrt
oftest_LDADD += $(THRIFT_LIB)

TESTS = ./run_tests.sh
