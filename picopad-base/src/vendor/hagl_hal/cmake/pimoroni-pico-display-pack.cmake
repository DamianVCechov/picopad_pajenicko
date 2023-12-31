#
# Pimoroni Pico Display Pack (135x240 ST7789)
# https://shop.pimoroni.com/products/pico-display-pack
# https://botland.store/search?s=769894017081
#
target_compile_definitions(firmware PRIVATE
    MIPI_DISPLAY_PIN_CS=17
    MIPI_DISPLAY_PIN_DC=16
    MIPI_DISPLAY_PIN_RST=-1
    MIPI_DISPLAY_PIN_BL=20
    MIPI_DISPLAY_PIN_CLK=18
    MIPI_DISPLAY_PIN_MOSI=19
    MIPI_DISPLAY_PIN_MISO=-1
    MIPI_DISPLAY_PIN_POWER=-1
    MIPI_DISPLAY_PIN_TE=-1

    MIPI_DISPLAY_SPI_PORT=spi0
    MIPI_DISPLAY_SPI_CLOCK_SPEED_HZ=62500000

    MIPI_DISPLAY_PIXEL_FORMAT=MIPI_DCS_PIXEL_FORMAT_16BIT
    MIPI_DISPLAY_ADDRESS_MODE=MIPI_DCS_ADDRESS_MODE_RGB
    MIPI_DISPLAY_WIDTH=135
    MIPI_DISPLAY_HEIGHT=240
    MIPI_DISPLAY_OFFSET_X=52
    MIPI_DISPLAY_OFFSET_Y=40
    # MIPI_DISPLAY_ADDRESS_MODE=MIPI_DCS_ADDRESS_MODE_RGB|MIPI_DCS_ADDRESS_MODE_SWAP_XY|MIPI_DCS_ADDRESS_MODE_MIRROR_Y
    # MIPI_DISPLAY_WIDTH=240
    # MIPI_DISPLAY_HEIGHT=135
    # MIPI_DISPLAY_OFFSET_X=40
    # MIPI_DISPLAY_OFFSET_Y=52
    MIPI_DISPLAY_INVERT=1
)