#!/usr/bin/env bash

# @file     install_llvm_toolchain.sh
# @author   Ignacio Vizzo [ivizzo@uni-bonn.de]
# @author   Hayat Rajani  [hayatrajani@gmail.com]   
#
# Original Copyright (c) 2019 Ignacio Vizzo, all rights reserved

# Remove all existing alternatives
update-alternatives --remove-all clang

# exit on first error
set -e

# Pick here your clang and gcc version
LLVM_VERSION=10

# Install Modern GCC version
apt-get install software-properties-common -yqq
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt update && apt install -yy gcc-${GCC_VERSION} g++-${GCC_VERSION}

# Add latest stable release to Ubuntu
bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

# Intsall clang-tools and friends
# Clang and co
apt-get install -yy clang-${LLVM_VERSION} \
  clang-tools-${LLVM_VERSION} \
  clang-tidy-${LLVM_VERSION} \
  clang-${LLVM_VERSION}-doc \
  libclang-common-${LLVM_VERSION}-dev \
  libclang-${LLVM_VERSION}-dev \
  libclang1-${LLVM_VERSION} \
  clang-format-${LLVM_VERSION} \
  python3-clang-${LLVM_VERSION} \
  clangd-${LLVM_VERSION}
# lldb
apt-get install -yy lldb-${LLVM_VERSION}
# lld (linker)
apt-get install -yy lld-${LLVM_VERSION}
# libc++
apt-get install -yy libc++-${LLVM_VERSION}-dev libc++abi-${LLVM_VERSION}-dev
# OpenMP
apt-get install -yy libomp-${LLVM_VERSION}-dev

update-alternatives \
  --install /usr/bin/clang clang /usr/bin/clang-${LLVM_VERSION} 20 \
  --slave /usr/bin/clang++ clang++ /usr/bin/clang++-${LLVM_VERSION} \
  --slave /usr/bin/lld lld /usr/bin/lld-${LLVM_VERSION} \
  --slave /usr/bin/clang-format clang-format /usr/bin/clang-format-${LLVM_VERSION} \
  --slave /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${LLVM_VERSION} \
  --slave /usr/bin/clang-tidy-diff.py clang-tidy-diff.py /usr/bin/clang-tidy-diff-${LLVM_VERSION}.py \
  --slave /usr/bin/run-clang-tidy run-clang-tidy /usr/bin/run-clang-tidy-${LLVM_VERSION} \
  --slave /usr/bin/clang-include-fixer clang-include-fixer /usr/bin/clang-include-fixer-${LLVM_VERSION} \
  --slave /usr/bin/clang-offload-bundler clang-offload-bundler /usr/bin/clang-offload-bundler-${LLVM_VERSION} \
  --slave /usr/bin/clangd clangd /usr/bin/clangd-${LLVM_VERSION} \
  --slave /usr/bin/clang-check clang-check /usr/bin/clang-check-${LLVM_VERSION} \
  --slave /usr/bin/scan-view scan-view /usr/bin/scan-view-${LLVM_VERSION} \
  --slave /usr/bin/clang-apply-replacements clang-apply-replacements /usr/bin/clang-apply-replacements-${LLVM_VERSION} \
  --slave /usr/bin/clang-query clang-query /usr/bin/clang-query-${LLVM_VERSION} \
  --slave /usr/bin/modularize modularize /usr/bin/modularize-${LLVM_VERSION} \
  --slave /usr/bin/sancov sancov /usr/bin/sancov-${LLVM_VERSION} \
  --slave /usr/bin/c-index-test c-index-test /usr/bin/c-index-test-${LLVM_VERSION} \
  --slave /usr/bin/clang-reorder-fields clang-reorder-fields /usr/bin/clang-reorder-fields-${LLVM_VERSION} \
  --slave /usr/bin/clang-change-namespace clang-change-namespace /usr/bin/clang-change-namespace-${LLVM_VERSION} \
  --slave /usr/bin/clang-import-test clang-import-test /usr/bin/clang-import-test-${LLVM_VERSION} \
  --slave /usr/bin/scan-build scan-build /usr/bin/scan-build-${LLVM_VERSION} \
  --slave /usr/bin/scan-build-py scan-build-py /usr/bin/scan-build-py-${LLVM_VERSION} \
  --slave /usr/bin/clang-cl clang-cl /usr/bin/clang-cl-${LLVM_VERSION} \
  --slave /usr/bin/clang-rename clang-rename /usr/bin/clang-rename-${LLVM_VERSION} \
  --slave /usr/bin/find-all-symbols find-all-symbols /usr/bin/find-all-symbols-${LLVM_VERSION} \
  --slave /usr/bin/lldb lldb /usr/bin/lldb-${LLVM_VERSION} \
  --slave /usr/bin/lldb-server lldb-server /usr/bin/lldb-server-${LLVM_VERSION}

# LLVM
update-alternatives --install /usr/bin/cc cc /usr/bin/clang 40 \
  --slave /usr/bin/c++ c++ /usr/bin/clang++ \
  --slave /usr/bin/ld ld /usr/bin/lld

# Update -- For some reason the LLVM installation had broken links
LLVM_FILES=$(find /usr/bin -name "llvm-*$LLVM_VERSION")
for LLVM_FILE in $LLVM_FILES
do
 LINK=${LLVM_FILE%-*}
 CMD=${LINK##*/}
 update-alternatives --install $LINK $CMD $LLVM_FILE 100
done

# Set clang as default compiler system wide
update-alternatives --set cc /usr/bin/clang

