break; //<>
continue; //<>
return; //<>

for(;;) return; //<>
for(;;) { return; } //<>
switch(a) { case a: continue; } //<>
switch(a) { case a: return; } //<>
function a() { break; } //<>
function a() { continue; } //<>

for(;;) { function a() { break; } } //<>
for(;;) { function a() { continue; } } //<>
for(;;) { function a() {} return; } //<>

switch(a) { case 0: function a() { break; } } //<>
