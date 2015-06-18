include ../settings.mk

all: $(BUILD) $(BUILD)malloc.o $(BUILD)memcpy.o $(BUILD)memset.o

$(BUILD)malloc.o: malloc.c
	$(ARMGNU)-gcc $(CFLAGS) $< -o $@

$(BUILD)memcpy.o: memcpy.s
	$(ARMGNU)-as $(ASFLAGS) $< -o $@

$(BUILD)memset.o: memset.s
	$(ARMGNU)-as $(ASFLAGS) $< -o $@

include ../settings2.mk
