# vtlock

Simple virtual terminal locker.

## Building

`linux/vt.h` is the only platform-specific dependency.  Edit **config.mk** to
match your setup before building (default target is /usr/local).

Run the following to compile and install (as root if necessary):

    make clean install

## Usage

    vtlock <command ...>

The virtual terminal will stay locked until the given command exits.
You can wrap X screen lockers, a kiosk program, or whatever you like.

## Legal

See LICENSE.

