#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([p4-build], [0.1], [antonin@barefootnetworks.com])
# This prevents autotools from automatically adding -O2 flag.
: ${CXXFLAGS=""}
AM_INIT_AUTOMAKE([foreign subdir-objects])
# TODO(antonin): had to comment this out, because I am using a GNU make
# extension in bmv2/Makefile.am
# AM_INIT_AUTOMAKE([-Wportability -Werror foreign subdir-objects])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

# will abort if there is no Python interpreter >= 2.7
AM_PATH_PYTHON([2.7])

want_bmv2=no
AC_ARG_WITH([bmv2],
    AS_HELP_STRING([--with-bmv2], [Build for bmv2 target]),
    [want_bmv2=yes], [])

AM_CONDITIONAL([WITH_BMV2], [test "$want_bmv2" = yes])

AC_ARG_VAR([P4_NAME], [Name of the P4 program])
AS_IF([test "$P4_NAME" = ""], [
  AC_MSG_ERROR([Environment variable P4_NAME needs to be set])
])

AC_ARG_VAR([P4_PATH], [Path to the P4 program])
AS_IF([test "$P4_PATH" = ""], [
  AC_MSG_ERROR([Environment variable P4_PATH needs to be set])
])
check_abs_path=$($PYTHON $srcdir/tools/check_p4_path.py $P4_PATH)
AS_IF([test "$check_abs_path" != yes], [
  AC_MSG_ERROR([The P4_PATH you provided does not exist or is not absolute])
])

AC_ARG_VAR([P4_PREFIX], [Prefix for the PD APIs])
AS_IF([test "$P4_PREFIX" = ""], [
  AC_MSG_NOTICE([Environment variable P4_PREFIX not set, using P4_NAME])
  P4_PREFIX="$P4_NAME"
  AC_SUBST([P4_PREFIX])
])

AC_ARG_VAR([P4C_BM_FLAGS], [Options to pass to the p4c-bm compiler])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
LT_INIT

# enforce -std=c++11
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# Checks for header files.
AC_LANG_PUSH(C)
AC_LANG_PUSH(C++)

AC_CHECK_HEADERS([algorithm array cassert cmath queue \
cstdio string sys/stat.h sys/types.h ctime tuple unistd.h unordered_map \
utility vector], [], [AC_MSG_ERROR([Missing header file])])

# To simplify usage, we will update PATH, CPPFLAGS,.. to include the 'prefix'
# ones
adl_RECURSIVE_EVAL([$bindir], [BIN_DIR])
adl_RECURSIVE_EVAL([$includedir], [INCLUDE_DIR])
adl_RECURSIVE_EVAL([$pythondir], [PYTHON_DIR])
adl_RECURSIVE_EVAL([$libdir], [LIB_DIR])

AS_IF([test "$want_bmv2" = yes], [
    AC_PATH_PROG([P4C_BM], [p4c-bmv2], [], [$PATH$PATH_SEPARATOR$BIN_DIR])
    AS_IF([test x"$P4C_BM" = x], AC_MSG_ERROR([cannot find p4c-bmv2 compiler]))

    AX_SAVE_FLAGS(SAVE_1)

    CPPFLAGS="$CPPFLAGS -I$INCLUDE_DIR"
    AC_CHECK_HEADER([bm/pdfixed/pd_common.h], [],
      [AC_MSG_ERROR([bmv2 pdfixed headers not found])])

    # Locate res.thrift needed to run the thrift compiler on the PD IDL
    # Quite nasty, but I don't see another way
    ab_FIND_HEADER_PATH(["bm/pdfixed/thrift/res.thrift"],
                        [pdfixedthrift_path])
    AC_SUBST([BM_THRIFT_INCLUDE], ["$pdfixedthrift_path"])

    AC_CHECK_HEADER([bm/Standard.h], [],
      [AC_MSG_ERROR([bmv2 Thrift headers not found])])

    AX_RESTORE_FLAGS(SAVE_1)
])

# Thrift
AC_WITH([p4thrift],
    [
        AC_PATH_PROG([THRIFT], [p4thrift], [])
        AC_SUBST([THRIFT_LIB], ["-lp4thrift"])
        WITH_P4THRIFT="true"
        AC_CHECK_HEADER([p4thrift/P4Thrift.h], [], [AC_MSG_ERROR([P4Thrift headers not found. Install P4Thrift from http://github.com/p4lang/thrift/])])
    ],
    [
        AC_PATH_PROG([THRIFT], [thrift], [])
        AC_SUBST([THRIFT_LIB], ["-lthrift"])
        AC_CHECK_HEADER([thrift/Thrift.h], [], [AC_MSG_ERROR([Thrift headers not found. Install Thrift from http://thrift.apache.org/docs/install/])])
    ])
AM_CONDITIONAL([P4THRIFT], [test "x$WITH_P4THRIFT" != "x"])
AS_IF([test x"$THRIFT" = x],
[AC_MSG_ERROR([cannot find thrift])])

# Check for libjudy, libnanomsg, pthread
AC_CHECK_LIB([Judy], [Judy1Next], [], [AC_MSG_ERROR([Missing libJudy])])
AC_CHECK_LIB([nanomsg], [nn_errno], [], [AC_MSG_ERROR([Missing libnanomsg])])
AC_CHECK_LIB([pthread], pthread_create, [], [AC_MSG_ERROR([required library pthread missing])])

# Checks for typedefs, structures, and compiler characteristics.
# introduced in autoconf 2.69
# AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_LANG_POP(C++)

AC_PROG_SED

AC_SUBST([MY_PYTHONPATH], ["$PYTHON_DIR"])

# Generate makefiles
AC_CONFIG_FILES([Makefile
                 bmv2/Makefile])

# Generate other files
AC_CONFIG_FILES([tools/produce_deps.py], [chmod +x tools/produce_deps.py])
AC_CONFIG_FILES([bmv2/.gitignore])

AS_IF([test "$want_bmv2" != yes], [
  AC_MSG_WARN([You did not use --with-bmv2 but bmv2 is the only target supported
               for now])
])

AC_OUTPUT

AS_ECHO("")
AS_ECHO("Features recap ......................")
AS_ECHO("P4_PATH ....................... : $P4_PATH")
AS_ECHO("P4_NAME ....................... : $P4_NAME")
AS_ECHO("P4_PREFIX ..................... : $P4_PREFIX")
AS_ECHO("Compile for bmv2 .............. : $want_bmv2")
