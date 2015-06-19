# Adventures on Rasperry Pi
Random Raspberry Pi bare metal code I've been working on my spare time.

My codes were inspired mostly by the Baking Pi tutorial
(https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/).
Other general references include the ARM instruction set
(http://www.ic.unicamp.br/~ranido/mc404/arm/arm-instructionset.pdf)
and the BCM2835 peripherals guide (https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/downloads/SoC-Peripherals.pdf).
More specific references are shown in each section.

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
