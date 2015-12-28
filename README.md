# Image Writer Hacks
Playing around old Apple Image Writer printer and appletalk.

# Disclaimer
This code doesn't work for now (and it's not likely to change anytime soon).

However this project does contain some interesting parts, mainly the **goodies/** directory, the modified version of **bin/pap/pap.c** (disable checks that make pap fail on image writer) and **bin/pap/papstatus.c** (return human readable string and not an ugly binary code), and this general documentation.

# Description
This repository contains the necessary stuff to access and 
print on an Apple Image Writer through appletalk.

# Acknowledge
This repository is derived from the netatalk project.

# License
This work is licensed under the GPLv2

# How to use
## Hardware requirements

* An Apple Image Writer with it's localtalk addon card
* The localtalk adapter and cables
* A Localtalk <-> Ethertalk adapter (Asantetalk adapter for example)
* A Linux PC running Cups

## Compiling the tools

Dependencies:
* libacl
* cmake

Building:
```
cmake .
make
```

Generated binaries:
* iwh-atalkd: daemon managing name, registration and routing on the appletalk network
* iwh-nbplkup: utility scanning the appletalk network for available devices
* iwh-papstatus: utility displaying a printer status
* iwh-pap: utility sending stuff for the printer to print

## Setting up the appletalk network

Enable appletalk module in Linux kernel:
```
modprobe appletalk
```

Change configuration:
```
vim conf/atalkd.conf
```

Start iwh-atalkd:
```
./iwh-atalkd -f conf/atalkd.conf
```

Scan the network:
```
./iwh-nbplkup
```
It should display your printer name.

Get printer status:
```
./iwh-papstatus -p "<printer name>:ImageWriter"
```

## Configuring cups

Put **goodies/cups-backend/pap** in **/usr/lib/cups/backend** (or the appropriate cups backend dir on your system).

Create a printer in cups with the following uri: 
* **pap://<printer name>** (replace spaces with %20)

If the image writer ppd is not provided, use the ppd file in directory **goodies/**
