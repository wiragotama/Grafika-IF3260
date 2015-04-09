#ifndef COLOR_PICKER_CONTROLLER_H
#define COLOR_PICKER_CONTROLLER_H

#include <linux/fb.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "../3D_Perspective/canvas.h"
#include "gradientPalette.h"
#include "rainbowPalette.h"
#include "../core/graphicsio.h"

uint32_t colorPicker(Canvas *canvas);

#endif
