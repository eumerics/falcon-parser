/// decimal integer
0, 1, 12, 123; //? <+>

/// binary integer
0b0, 0b1; //? <+>
0b00, 0b01, 0b10, 0b11; //? <+>
0b01010101, 0B10101010; //? <+>

/// octal integer
0o0, 0o1, 0o2, 0o3, 0o4, 0o5, 0o6, 0o7; //? <+>
0o525, 0O252; //? <+>

/// hexadecimal integer
0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7; //? <+>
0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf; //? <+>
0xA, 0xB, 0xC, 0xD, 0xE, 0xF; //? <+>
0x55, 0XAA; //? <+>

/// real numbers
0., 1., 2.34, 5.067, 80.90, 0.e001, 2.03e+04, 56.70e-8; //? <+>
.0, .1, .23, .045, .60e+07, .8e-9; //? <+>
0e0, 1E1, 2e00, 3e+0, 4e-0, 56e78, 9e01; //? <+>

/// legacy octal
00, 007, 0123; //? <+>
/// legacy decimal like
08, 09.0; //? <+>
07.0; //? <-> -default
