#!/bin/bash

cat linux-4.6.2-splita* | tar -zxvpf -
cat riscv-gnu-toolchain-splita* | tar -zxvpf -
tar xvjf buildroot.tar.bz2
