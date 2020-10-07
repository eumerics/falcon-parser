function* a(b,,c) {}
//<>
function* a(...b,) {}
//<>
function* a(...b, c) {}
//<>
function* a(yield) {}
//<>
function* a([yield]) {}
//<>
function* a(b = yield) {}
//<>
function* a(b = yield.a) {}
//<>
function* a(b = [yield]) {}
//<>
function* a(b = [...yield]) {}
//<>
function* a(b = {[yield]: 0}) {}
//<>
function* a(){ yield.a; }
//<>
function* a(){ ({yield}); }
//<>
function* a(){ ({yield = 0}); }
//<>
function* a(){ yield => {}; }
//<>
function* a(){ (yield) => {}; }
//[TODO]<>
//function* a(){ (b = yield) => {}; }
//<>
function* a(){ new yield; }
//<>
function* a(){ var yield; }
//<>
function* a(){ let yield; }
//<>
function* a(){ yield: ; }
