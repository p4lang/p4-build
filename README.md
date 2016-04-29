# p4-build
Infrastructure needed to generate, build and install the PD library for a given P4 program

## Dependencies

[bmv2] (https://github.com/p4lang/behavioral-model) **with pdfixed** needs to be
installed. When compiling bmv2, pdfixed can be installed with `--with-pdfixed`.

The [bmv2 compiler] (https://github.com/p4lang/p4c-bm) also needs to be
installed.

## Building and installing the code

This repository is meant to be used to compile (and install) the PD library for
a given P4 program. As a result the full absolute path to the P4 program, as
well as the P4 program name, needs to be provided to `configure`.
When running `configure` the folllowing environment variables need to be
defined: `P4_PATH`, `P4_NAME` and possibly `P4_PREFIX`. You can run `configure
-h` for more details.

    1. ./autogen.sh
    2. ./configure --with-bmv2 P4_NAME=<name of P4 program> P4_PATH=<absolute
    path to P4 program> [P4_PREFIX=<prefix to use for PD APIs>]
    3. make
    4. make install

If `P4_PREFIX` is missing, we will use `P4_NAME` by default.

The following describes what can potentially be installed by this package, for a
given P4 program for which `P4_NAME=test`.

```
.
├── bin
├── include
│   └── bmpd
│       └── test
│           └── pd
│               ├── pd_counters.h
│               ├── pd.h
│               ├── pd_learning.h
│               ├── pd_meters.h
│               ├── pd_mirroring.h
│               ├── pd_registers.h
│               ├── pd_rpc_server.h
│               ├── pd_tables.h
│               └── pd_types.h
├── lib
│   ├── bmpd
│   │   └── test
│   │       ├── libpd.a
│   │       ├── libpd.la
│   │       ├── libpd.so -> libpd.so.0.0.0
│   │       ├── libpd.so.0 -> libpd.so.0.0.0
│   │       ├── libpd.so.0.0.0
│   │       ├── libpdthrift.a
│   │       ├── libpdthrift.la
│   │       ├── libpdthrift.so -> libpdthrift.so.0.0.0
│   │       ├── libpdthrift.so.0 -> libpdthrift.so.0.0.0
│   │       └── libpdthrift.so.0.0.0
│   └── python2.7
│       └── site-packages
│           └── bmpd
│               └── test
│                   ├── p4_pd_rpc
│                   │   ├── constants.py
│                   │   ├── __init__.py
│                   │   ├── test.py
│                   │   ├── test-remote
│                   │   └── ttypes.py
│                   └── res_pd_rpc
│                       ├── constants.py
│                       ├── __init__.py
│                       └── ttypes.py
└── share
    └── bmpd
        └── test
            └── test.json
```
