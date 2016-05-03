#!/bin/bash
set -e
git clone https://github.com/p4lang/p4c-bm.git p4c-bmv2
cd p4c-bmv2
pip install --user -r requirements.txt
python setup.py install --user \
    --single-version-externally-managed \
    --record install_files.txt
cd ..
