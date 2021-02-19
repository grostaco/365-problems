static signed subtable[] = {-2, -1, 1, 2};
static unsigned table[] = {0b0001, 0b0010, 0b0100, 0b0111, 0b1000,
                           0b1011, 0b1101, 0b1110, 42};
static unsigned ktables[8][2];
#define kmoves(xoffset, yoffset)                                               \
  ({                                                                           \
    for (unsigned *dx = table; *dx != 42; ++dx) {                              \
      ktables[dx - table][0] = xoffset + subtable[*dx >> 2];                   \
      ktables[dx - table][1] = yoffset + subtable[*dx & 0x3];                  \
    }                                                                          \
    ktables;                                                                   \
  })
