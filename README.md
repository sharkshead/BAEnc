# BAEnc
A general purpose encryption library targetted at smaller microprocessors with limited memory and program space.

This library provides a simple means of securely transmitting messages between small microprocessors
and a central processor over an insecure transmission path.

The upside of this library is its very small footprint, around 150 program bytes and around 20 bytes of RAM.

The down side is that it is a shared key, non-symmetric cipher.

All up, the BAEnc library is great for situations where you have a small microprocessor that needs to communicate
with a larger processor over a non-secure comunications channel.

Make no mistake, BAEnc is not in the same league as AES and co. when it comes to secure communications. It is not designed to be like that.

It is designed to be small, fast, and hard for a casual eaves-dropper to break.

You can think of BAEnc's security as being somewhere between a simple shared-key XOR encryption and the AES's of the world.


# Overview

BAEnc consists of two functions, called BAEncA() and BAEncB(). A message encrypted by "A" can only be decrypted by "B", and vice versa.

If you are using this library because of its small footprint, then I'd suggest you put the "A" function on your smallest microprocessor
and "B" on the largest or the one collecting all the data from your satellite micros. This is because "A" is slightly smaller and faster than "B".
You can, however, use them in whatever configuration suits your needs.

The number of (Feistel) rounds and the key length are customisable in the BAEnc.h file. Defaults are 7 rounds and a key length of 32 nibbles (16 bytes.)

Both "A" and "B" can encrypt and decrypt in-situ, meaning you don't need to allocate a separate chunk of memory to hold the encrypted/decrypted message.
They can produce their output in a separate buffer if you so desire, its just that this choice is not forced on you.

Then there's the issue of the shared key. You could store this in non-volatile memory, such as the EEPROM on most micros or in a database
if you're running on a Pi or similar. This definitely has simplicity on its side, and is possibly good enough security if you're in an
environment with other hackers and you don't want them simply snooping your messages. It may not pass muster if you're in a more hostile environment,
for which you'll need a more secure method of storing or transmitting keys.

This has been developed using g++ and the Arduino IDE, which is why the source is in a BAEnc.cpp file. There is, however,
no C++ code here. If you're in a C environment then simply change the file name to BAEnc.c and carry on as usual.

The Makefile at the top of the repository is for a Raspberry Pi running Linux.
Two examples are included that use the BAEnc library, one for a Pi and one for an Arduino. Both do the same job and have the same output -
they allocate a random message and random key, then pass this through "A" then "B" and then "B" then "A", so you can see that the original
message is restored after each function has been used, and then it performs a speed test usng the same random message and key, reporting the
time in nanoseconds to encrypt a single byte.
