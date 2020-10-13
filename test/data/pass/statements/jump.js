// individual for, switch, function
for(;;) break;
for(;;) continue;
for(;;) { break; }
for(;;) { continue; }
switch(a) { case 0: break; }
switch(a) { default: break; }
switch(a) { case 0: { break; } }
switch(a) { default: { break; } }
function a() { return; }
b: break b;
c: for(;;) break c;
d: for(;;) continue d;

// for-switch
for(;;) switch(a) { case 0: continue; }
for(;;) switch(a) { default: continue; }
for(;;) switch(a) { case 0: { continue; } }
for(;;) switch(a) { default: { continue; } }
for(;;) { switch(a) { case 0: continue; } }
for(;;) { switch(a) { default: continue; } }
for(;;) { switch(a) { case 0: { continue; } } }
for(;;) { switch(a) { default: { continue; } } }

// function-for, function-switch
function a() { for(;;) return; }
function a() { for(;;) { return; } }
function a() { switch(a) { case 0: return; } }
function a() { switch(a) { default: return; } }
function a() { switch(a) { case 0: { return; } } }
function a() { switch(a) { default: { return; } } }

// function-for-switch
function a() { for(;;) switch(a) { case 0: return; } }
function a() { for(;;) switch(a) { default: return; } }
function a() { for(;;) switch(a) { case 0: { return; } } }
function a() { for(;;) switch(a) { default: { return; } } }
function a() { for(;;) { switch(a) { case 0: return; } } }
function a() { for(;;) { switch(a) { default: return; } } }
function a() { for(;;) { switch(a) { case 0: { return; } } } }
function a() { for(;;) { switch(a) { default: { return; } } } }
