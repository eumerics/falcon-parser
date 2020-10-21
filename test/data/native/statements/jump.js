break; //? <->
continue; //? <->
return; //? <->

/// individual for, switch, function
for(;;) break; //? <+>
for(;;) continue; //? <+>
for(;;) return; //? <->
for(;;) { break; } //? <+>
for(;;) { continue; } //? <+>
for(;;) { return; } //? <->
switch(a) { case 0: break; } //? <+>
switch(a) { case 0: continue; } //? <->
switch(a) { case 0: return; } //? <->
switch(a) { default: break; } //? <+>
switch(a) { case 0: { break; } } //? <+>
switch(a) { default: { break; } } //? <+>
switch(a) { case 0: function a() { break; } } //? <->
function a() { break; } //? <->
function a() { continue; } //? <->
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
for(;;) { function a() { break; } } //? <->
for(;;) { function a() { continue; } } //? <->
for(;;) { function a() {} return; } //? <->

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
