# BAEnc
A general purpose encryption library targetted at smaller microprocessors with limited memory and program space.

This library provides a simple means of securely transmitting messages between small microprocessors
and a central processor over an insecure transmission path..

The upside of this library is its very small footprint, around 150 program bytes and around 20 bytes of RAM.

The down side is that it is a shared key, non-symmetric cipher.

All up, the BAEnc library is great for situations where you have a small microprocessor that needs to communicate
with a larger processor over a non-secure comunications channel.

Make no mistake, BAEnc is not in the same league as AES and co. when it comes to secure communications. It is not designed to be like that.

It is designed to be small, reasonably fast, and hard for a casual eaves-dropper to break.

You can think of BAEnc as being somewhere between a simple shared-key XOR entryption and the AES's of the world.
