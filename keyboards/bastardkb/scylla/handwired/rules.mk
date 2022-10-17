# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
# BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
# MOUSEKEY_ENABLE = yes       # Mouse keys
# EXTRAKEY_ENABLE = yes       # Audio control and System control
# CONSOLE_ENABLE = no         # Console for debug
# COMMAND_ENABLE = no         # Commands for debug and configuration
# NKRO_ENABLE = no            # Enable N-Key Rollover
# BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
# RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
# AUDIO_ENABLE = no           # Audio output

# AUDIO_SUPPORTED = no        # Audio is not supported
# RGB_MATRIX_SUPPORTED = no   # RGB matrix is supported and enabled by default
# RGBLIGHT_SUPPORTED = no     # RGB underglow is supported, but not enabled by default
# RGB_MATRIX_ENABLE = no      # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
# RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support

# SPLIT_KEYBOARD = yes

# Space saving settings.
TAP_DANCE_ENABLE = no
QMK_SETTINGS = no
LTO_ENABLE = yes

VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = no
