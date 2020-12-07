for(;;){ continue } //? <+>
for(;;){ break } //? <+>
function a(){ return } //? <+>
function* a(){ yield } //? <+>
async function a(){ await 0 } //? <+>
debugger
{1
 2} 3 //? <+>
do ; while(false) //? <+>
for(;;){
   continue
1
} //? <+>
for(;;){
   break
   1
} //? <+>
function a(){
   return
   1;
} //? <+>
function* a(){
   yield
   1;
} //? <+>
a = b //? <+>
++a //? <+>
a = b + c //? <+>
(a + b).print() //? <+>
function a() {
   return /* inline */ 1;
} //? <+>
function a() {
   return /* multi-line
   */ 1;
} //? <+>
function a() {
   return /* inline */ /* multi-line
   */1;
} //? <+>
function a() {
   return /* multi-line
   */ /* inline */ 1;
} //? <+>
function a() {
   return /* inline */ /* multi-line
   */ /* inline */ 1;
} //? <+>
