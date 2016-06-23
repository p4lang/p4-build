ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

if BMV2_OFTEST_ENV
SUBDIRS = openflow 
endif

if BMV2_PDTEST_ENV
SUBDIRS = pdtest
endif

if !BMV2_OFTEST_ENV
if !BMV2_PDTEST_ENV
check-local:
	@echo "================================================="
	@echo "No bmv2 tests can run if configure was not run with the \
	appropriate environment."
	@echo "================================================="
endif
endif

