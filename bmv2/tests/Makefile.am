if BMV2_TEST_ENV

check_PROGRAMS = test

test_SOURCES = test.cpp \
thrift_endpoint/src/server.cpp

test_CPPFLAGS = -I$(includedir)
test_CPPFLAGS += -I$(srcdir)/thrift_endpoint
test_CPPFLAGS += -I$(builddir)/../test
test_CPPFLAGS += -I$(top_srcdir)/pdfixed

if P4THRIFT
    test_CPPFLAGS += -DP4THRIFT
endif

test_LDFLAGS = -L$(libdir)
test_LDFLAGS += -pthread
test_LDADD = $(builddir)/../libpd.la -lbmpdfixed
# TODO(antonin): is there a way to avoid having to do this?
test_LDADD += -lruntimestubs -lsimpleswitch_thrift
test_LDADD += $(THRIFT_LIB)

TESTS = ./run_tests.sh

else

check-local:
	@echo "================================================="
	@echo "No bmv2 tests can run if configure was not run with the \
	appropriate environment."
	@echo "================================================="

endif
