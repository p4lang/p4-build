ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

pd_files = \
@P4_NAME@/src/pd.cpp \
@P4_NAME@/src/pd_learning.cpp \
@P4_NAME@/src/pd_meters.cpp \
@P4_NAME@/src/pd_counters.cpp \
@P4_NAME@/src/pd_registers.cpp \
@P4_NAME@/src/pd_tables.cpp \
@P4_NAME@/src/pd_ageing.cpp \
@P4_NAME@/src/pd_mirroring.cpp

pd_headers = \
@P4_NAME@/pd/pd.h \
@P4_NAME@/pd/pd_learning.h \
@P4_NAME@/pd/pd_meters.h \
@P4_NAME@/pd/pd_counters.h \
@P4_NAME@/pd/pd_registers.h \
@P4_NAME@/pd/pd_tables.h \
@P4_NAME@/pd/pd_types.h \
@P4_NAME@/pd/pd_mirroring.h

pd_p4_IDL = @P4_NAME@/thrift/p4_pd_rpc.thrift
pd_p4_src = \
$(builddir)/@P4_NAME@/thrift-src/p4_pd_rpc_server.ipp \
$(builddir)/@P4_NAME@/thrift-src/pd_rpc_server.cpp \
$(builddir)/@P4_NAME@/thrift-src/pd_rpc_server.h

P4_JSON_OUTPUT = $(P4_NAME).json

# TODO(antonin):
# this is not portable (GNU make extension), but this is the only think I can
# think of right now to keep track of dependencies
# anyone with a better solution is welcome to change this
refdeps := $(shell ../tools/produce_deps.py @P4_PATH@)

pd_files.ts : $(P4_PATH) $(refdeps)
	@rm -f pd_files.tmp
	@touch pd_files.tmp
	PYTHONPATH=$$PYTHONPATH:$(MY_PYTHONPATH) $(P4C_BM) --pd $(builddir)/$(P4_NAME)/ --p4-prefix $(P4_PREFIX) $(P4C_BM_FLAGS) --json $(builddir)/$(P4_JSON_OUTPUT) $(P4_PATH)
	@mv -f pd_files.tmp $@
$(pd_files) $(pd_p4_IDL) $(pd_p4_src) : pd_files.ts
## Recover from the removal of $@
	@if test -f $@; then :; else \
	  trap 'rm -rf pd_files.lock pd_files.ts' 1 2 13 15; \
## mkdir is a portable test-and-set
	if mkdir pd_files.lock 2>/dev/null; then \
## This code is being executed by the first process.
	  rm -f pd_files.ts; \
	  $(MAKE) $(AM_MAKEFLAGS) pd_files.ts; \
	  result=$$?; rm -rf pd_files.lock; exit $$result; \
	else \
## This code is being executed by the follower processes.
## Wait until the first process is done.
	  while test -d pd_files.lock; do sleep 1; done; \
## Succeed if and only if the first process succeeded.
	    test -f pd_files.ts; \
	  fi; \
	fi

pd_p4_thrift_cxx = \
pd_thrift_gen/gen-cpp/p4_prefix0.cpp \
pd_thrift_gen/gen-cpp/p4_prefix1.cpp \
pd_thrift_gen/gen-cpp/p4_prefix2.cpp \
pd_thrift_gen/gen-cpp/p4_prefix.h \
pd_thrift_gen/gen-cpp/p4_pd_rpc_constants.cpp \
pd_thrift_gen/gen-cpp/p4_pd_rpc_constants.h \
pd_thrift_gen/gen-cpp/p4_pd_rpc_types.cpp \
pd_thrift_gen/gen-cpp/p4_pd_rpc_types.h

pd_p4_thrift_py = \
pd_thrift_gen/gen-py/p4_pd_rpc/constants.py \
pd_thrift_gen/gen-py/p4_pd_rpc/__init__.py \
pd_thrift_gen/gen-py/p4_pd_rpc/ttypes.py \
pd_thrift_gen/gen-py/p4_pd_rpc/@P4_PREFIX@.py \
pd_thrift_gen/gen-py/p4_pd_rpc/@P4_PREFIX@-remote
p4pythondir = @pythondir@/bmpd/@P4_NAME@/p4_pd_rpc
p4python_PYTHON = $(pd_p4_thrift_py)

# TODO(antonin): really necessary to install this again (pdfixed has it)?
pd_res_thrift_py = \
pd_thrift_gen/gen-py/res_pd_rpc/constants.py \
pd_thrift_gen/gen-py/res_pd_rpc/__init__.py \
pd_thrift_gen/gen-py/res_pd_rpc/ttypes.py
respythondir = @pythondir@/bmpd/@P4_NAME@/res_pd_rpc
respython_PYTHON = $(pd_res_thrift_py)

pd_thrift_files = $(pd_p4_thrift_cxx) $(pd_p4_thrift_py) $(pd_res_thrift_py)

pd_thrift_files.ts: $(pd_files) $(pd_p4_IDL) $(pd_res_IDL)
	@rm -f pd_thrift_files.tmp
	@touch pd_thrift_files.tmp
	$(THRIFT) -o $(builddir)/pd_thrift_gen/ -I $(BM_THRIFT_INCLUDE) --gen cpp -r $(pd_p4_IDL)
	$(THRIFT) -o $(builddir)/pd_thrift_gen/ -I $(BM_THRIFT_INCLUDE) --gen py -r $(pd_p4_IDL)
	mv -f pd_thrift_gen/gen-cpp/$(P4_PREFIX).h pd_thrift_gen/gen-cpp/p4_prefix.h
	sed --in-place 's/include "$(P4_PREFIX).h"/include "p4_prefix.h"/' pd_thrift_gen/gen-cpp/$(P4_PREFIX).cpp
	$(PYTHON) $(top_srcdir)/tools/split_pd_thrift.py pd_thrift_gen/gen-cpp/$(P4_PREFIX).cpp pd_thrift_gen/gen-cpp/ 3
	@mv -f pd_thrift_files.tmp $@
$(pd_thrift_files): pd_thrift_files.ts
## Recover from the removal of $@
	@if test -f $@; then :; else \
	  trap 'rm -rf pd_thrift_files.lock pd_thrift_files.ts' 1 2 13 15; \
## mkdir is a portable test-and-set
	if mkdir pd_thrift_files.lock 2>/dev/null; then \
## This code is being executed by the first process.
	  rm -f pd_thrift_files.ts; \
	  $(MAKE) $(AM_MAKEFLAGS) pd_thrift_files.ts; \
	  result=$$?; rm -rf pd_thrift_files.lock; exit $$result; \
	else \
## This code is being executed by the follower processes.
## Wait until the first process is done.
	  while test -d pd_thrift_files.lock; do sleep 1; done; \
## Succeed if and only if the first process succeeded.
	    test -f pd_thrift_files.ts; \
	  fi; \
	fi

BUILT_SOURCES = \
$(pd_files) \
$(pd_thrift_files)

pdincludedir = $(includedir)/bmpd/@P4_NAME@/pd
pdinclude_HEADERS = \
$(pd_headers) \
@P4_NAME@/thrift-src/pd_rpc_server.h

pdlibdir = $(libdir)/bmpd/@P4_NAME@
pdlib_LTLIBRARIES = libpd.la libpdthrift.la

libpd_la_SOURCES = \
$(pd_files)

libpdthrift_la_SOURCES = \
$(pd_thrift_files) \
@P4_NAME@/thrift-src/pd_rpc_server.cpp

AM_CPPFLAGS = -I$(includedir)
AM_CPPFLAGS += -I$(builddir)/@P4_NAME@/
AM_CPPFLAGS += -I$(builddir)/pd_thrift_gen/gen-cpp/
AM_CPPFLAGS += -DHOST_BYTE_ORDER_CALLER

if P4THRIFT
    AM_CPPFLAGS += -DP4THRIFT
endif

pddatadir = $(datadir)/bmpd/@P4_NAME@
pddata_DATA = $(P4_JSON_OUTPUT)

CLEANFILES = $(BUILT_SOURCES) \
pd_files.ts pd_thrift_files.ts \
$(P4_JSON_OUTPUT)
