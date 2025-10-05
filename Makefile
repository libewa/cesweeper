# ----------------------------
# Makefile Options
# ----------------------------

NAME = MINESWEP
ICON = icon.png
DESCRIPTION = "CE Minesweeper"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

upload: all
	tilp -n bin/$(NAME).8xp