#!/bin/bash

if [ $# -ne 1 ]; then
    echo parameter error!
    exit 1
fi

if [ $1 == "i" ]; then
    cp arch/arm/configs/qin2440_defconfig .config
elif [ $1 == "m" ]; then 
    make ARCH=arm menuconfig
elif [ $1 == "u" ]; then
    make ARCH=arm CROSS_COMPILE=/home/sam/Work/arm-linux-gcc-3.4.5/gcc-3.4.5-glibc-2.3.6/bin/arm-linux- uImage
else
    echo parameter error!
fi

