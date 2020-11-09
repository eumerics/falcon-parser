switch(a) {} //? <+>
switch(a) { case 0: } //? <+>
switch(a) { default: } //? <+>
switch(a) { case 0: default: } //? <+>
switch(a) { default: case 0: } //? <+>
switch(a)
{
   case 0: {}
   case 1: a;
   case 2: b; break;
   default: break;
} //? <+>
switch(a) { default: default: } //? <-> @1:22 -duplicate_default_clause
