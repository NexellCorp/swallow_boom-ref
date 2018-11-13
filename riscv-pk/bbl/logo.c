#include <string.h>
#include "mtrap.h"

static const char logo[] =
"\r\n"
"                           NEXELL, INC.\r\n"
"\r\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n"
"x  xxxxxx   xx        xx  xxxxxxxxx   xx        xx   xxxxxxx   xxxxxxx\r\n"
"x   xxxxx   xx        xx   xxxxxxx   xxx        xx   xxxxxxx   xxxxxxx\r\n"
"x    xxxx   xx   xxxxxxxx   xxxxx   xxxx   xxxxxxx   xxxxxxx   xxxxxxx\r\n"
"x     xxx   xx   xxxxxxxxx   xxx   xxxxx   xxxxxxx   xxxxxxx   xxxxxxx\r\n"
"x      xx   xx       xxxxxx   x   xxxxxx       xxx   xxxxxxx   xxxxxxx\r\n"
"x   x   x   xx       xxxxxxx     xxxxxxx       xxx   xxxxxxx   xxxxxxx\r\n"
"x   xx      xx   xxxxxxxxxx   x   xxxxxx   xxxxxxx   xxxxxxx   xxxxxxx\r\n"
"x   xxx     xx   xxxxxxxxx   xxx   xxxxx   xxxxxxx   xxxxxxx   xxxxxxx\r\n"
"x   xxxx    xx        xxx   xxxxx   xxxx        xx        xx         x\r\n"
"x   xxxxx   xx        xx   xxxxxxx   xxx        xx        xx         x\r\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n"
"\r\n"
"                          Nexell RISC-V\r\n"
"\r\n";

void print_logo()
{
  putstring(logo);
}
