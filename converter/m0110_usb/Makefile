# Target file name (without extension).
TARGET = m0110

# Directory common source filess exist
TOP_DIR = ../..

# Directory keyboard dependent files exist
TARGET_DIR = .

# keyboard dependent files
SRC =	main.c \
	keymap.c \
	matrix.c \
	led.c \
	m0110.c

CONFIG_H = config.h


# MCU name, you MUST set this to match the board you are using
# type "make clean" after changing this, so all files will be rebuilt
#MCU = at90usb162       # Teensy 1.0
MCU = atmega32u4       # Teensy 2.0
#MCU = at90usb646       # Teensy++ 1.0
#MCU = at90usb1286      # Teensy++ 2.0


# Processor frequency.
#   Normally the first thing your program should do is set the clock prescaler,
#   so your program will run at the correct speed.  You should also set this
#   variable to same clock speed.  The _delay_ms() macro uses this, and many
#   examples use this variable to calculate timings.  Do not add a "UL" here.
F_CPU = 16000000


# Build Options
#   *Comment out* to disable the options.
#
MOUSEKEY_ENABLE = yes	# Mouse keys
#PS2_MOUSE_ENABLE = yes	# PS/2 mouse(TrackPoint) support
EXTRAKEY_ENABLE = yes	# Audio control and System control
#NKRO_ENABLE = yes	# USB Nkey Rollover



#---------------- Programming Options --------------------------
PROGRAM_CMD = teensy_loader_cli -mmcu=$(MCU) -w -v $(TARGET).hex



include $(TOP_DIR)/protocol/pjrc.mk
include $(TOP_DIR)/protocol.mk
include $(TOP_DIR)/common.mk
include $(TOP_DIR)/rules.mk

hasu: EXTRAFLAGS += -DHASU
hasu: all
