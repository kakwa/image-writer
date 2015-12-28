# Image Writer Hacks
Playing around old Apple Image Writer printer and appletalk.

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
* A Localtalk <-> Ethertalk adapter
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
