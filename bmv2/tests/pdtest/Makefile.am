check_PROGRAMS = pdtest

pdtest_SOURCES = pdtest.cpp

pdtest_CPPFLAGS = -I$(includedir)
pdtest_CPPFLAGS += -I$(srcdir)/../thrift_endpoint
pdtest_CPPFLAGS += -I$(builddir)/../../pdtest
pdtest_CPPFLAGS += -I$(top_srcdir)/pdfixed

if P4THRIFT
    pdtest_CPPFLAGS += -DP4THRIFT
endif

pdtest_LDFLAGS = -L$(libdir)
pdtest_LDFLAGS += -pthread

noinst_LTLIBRARIES = libthrift_endpoint.la
libthrift_endpoint_la_SOURCES = ../thrift_endpoint/src/server.cpp

pdtest_LDADD = libthrift_endpoint.la
pdtest_LDADD += $(builddir)/../../libpd.la -lbmpdfixed
# TODO(antonin): is there a way to avoid having to do this?
pdtest_LDADD += -lruntimestubs -lsimpleswitch_thrift
pdtest_LDADD += $(THRIFT_LIB)

TESTS = ./run_tests.sh
