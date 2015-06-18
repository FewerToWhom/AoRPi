include ../settings.mk

all: $(BUILD) $(BUILD)gpio.o

$(BUILD)gpio.o: gpio.c
	$(ARMGNU)-gcc $(CFLAGS) $< -o $@

include ../settings2.mk
