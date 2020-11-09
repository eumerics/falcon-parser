break; //? <-> @1:1 -unsyntatic_break
continue; //? <-> @1:1 -unsyntatic_continue
return; //? <-> @1:1 -unsyntatic_return

/// individual for, switch, function
for(;;) break; //? <+>
for(;;) continue; //? <+>
for(;;) return; //? <-> @1:9 -unsyntatic_return
for(;;) { break; } //? <+>
for(;;) { continue; } //? <+>
for(;;) { return; } //? <-> @1:11 -unsyntatic_return
switch(a) { case 0: break; } //? <+>
switch(a) { case 0: continue; } //? <-> @1:21 -unsyntatic_continue
switch(a) { case 0: return; } //? <-> @1:21 -unsyntatic_return
switch(a) { default: break; } //? <+>
switch(a) { case 0: { break; } } //? <+>
switch(a) { default: { break; } } //? <+>
switch(a) { case 0: function a() { break; } } //? <-> @1:36 -unsyntatic_break
function a() { break; } //? <-> @1:16 -unsyntatic_break
function a() { continue; } //? <-> @1:16 -unsyntatic_continue
function a() { return; } //? <+>

/// for-switch
for(;;) switch(a) { case 0: continue; } //? <+>
for(;;) switch(a) { default: continue; } //? <+>
for(;;) switch(a) { case 0: { continue; } } //? <+>
for(;;) switch(a) { default: { continue; } } //? <+>
for(;;) { switch(a) { case 0: continue; } } //? <+>
for(;;) { switch(a) { default: continue; } } //? <+>
for(;;) { switch(a) { case 0: { continue; } } } //? <+>
for(;;) { switch(a) { default: { continue; } } } //? <+>
for(;;) { function a() { break; } } //? <-> @1:26 -unsyntatic_break
for(;;) { function a() { continue; } } //? <-> @1:26 -unsyntatic_continue
for(;;) { function a() {} return; } //? <-> @1:27 -unsyntatic_return

/// function-for, function-switch
function a() { for(;;) return; } //? <+>
function a() { for(;;) { return; } } //? <+>
function a() { switch(a) { case 0: return; } } //? <+>
function a() { switch(a) { default: return; } } //? <+>
function a() { switch(a) { case 0: { return; } } } //? <+>
function a() { switch(a) { default: { return; } } } //? <+>

/// function-for-switch
function a() { for(;;) switch(a) { case 0: return; } } //? <+>
function a() { for(;;) switch(a) { default: return; } } //? <+>
function a() { for(;;) switch(a) { case 0: { return; } } } //? <+>
function a() { for(;;) switch(a) { default: { return; } } } //? <+>
function a() { for(;;) { switch(a) { case 0: return; } } } //? <+>
function a() { for(;;) { switch(a) { default: return; } } } //? <+>
function a() { for(;;) { switch(a) { case 0: { return; } } } } //? <+>
function a() { for(;;) { switch(a) { default: { return; } } } } //? <+>
