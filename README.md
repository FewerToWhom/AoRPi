# Adventures on Rasperry Pi
Random Raspberry Pi bare metal code I've been working on my spare time.

Parts of my codes were inspired mostly by the Baking Pi tutorial
(https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/).
Other, more specific, references are shown in each section.

memory/

Contais my implementations of memcpy and memset for the RPi.
Both have the same signature as the standard C ones.
They have been written in assembly in order to check for alignment and benefit from it when possible.

gpio/

Contains a small library to deal with GPIO and its pins. It's able to
switch the GPIO on and control the pins' levels.

mailbox/

Deals with sending/receiving messages to/from the GPU via the mailbox system.
Based on https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
