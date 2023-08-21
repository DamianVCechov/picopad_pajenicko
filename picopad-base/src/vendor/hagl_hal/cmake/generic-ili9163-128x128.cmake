#
# Generic 128x128 ILI9163
#
target_compile_definitions(firmware PRIVATE
    MIPI_DISPLAY_PIN_DC=8
    MIPI_DISPLAY_PIN_CS=9
    MIPI_DISPLAY_PIN_CLK=10
    MIPI_DISPLAY_PIN_MOSI=11
    MIPI_DISPLAY_PIN_RST=12
    MIPI_DISPLAY_PIN_BL=13
    MIPI_DISPLAY_PIN_MISO=-1
    MIPI_DISPLAY_PIN_POWER=-1
    MIPI_DISPLAY_PIN_TE=-1

    MIPI_DISPLAY_SPI_PORT=spi1
    MIPI_DISPLAY_SPI_CLOCK_SPEED_HZ=62500000
    MIPI_DISPLAY_PIXEL_FORMAT=MIPI_DCS_PIXEL_FORMAT_16BIT

    MIPI_DISPLAY_ADDRESS_MODE=MIPI_DCS_ADDRESS_MODE_BGR|MIPI_DCS_ADDRESS_MODE_MIRROR_Y|MIPI_DCS_ADDRESS_MODE_MIRROR_X
    MIPI_DISPLAY_WIDTH=128
    MIPI_DISPLAY_HEIGHT=128
    MIPI_DISPLAY_OFFSET_X=0
    MIPI_DISPLAY_OFFSET_Y=32

    # MIPI_DISPLAY_ADDRESS_MODE=MIPI_DCS_ADDRESS_MODE_BGR|MIPI_DCS_ADDRESS_MODE_SWAP_XY|MIPI_DCS_ADDRESS_MODE_MIRROR_Y
    # MIPI_DISPLAY_WIDTH=128
    # MIPI_DISPLAY_HEIGHT=128
    # MIPI_DISPLAY_OFFSET_X=32
    # MIPI_DISPLAY_OFFSET_Y=0

    MIPI_DISPLAY_INVERT=0
)