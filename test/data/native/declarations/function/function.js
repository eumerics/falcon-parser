/// different types of function declarations
function a(){} //? <+>
function* a(){} //? <+>
async function a(){} //? <+>
async function* a(){} //? <+>
async
function a(){} //? <+>

/// contextual keywords
function* a() { yield; } //? <+>
async function a() { await 0; } //? <+>
async function* a() { yield; await 0; } //? <+>
async function a(){ function b(){ await 0; } } //? <-> @1:41

/// pedantic contextual keywords
function* yield(){}; //? <+?>
async function await(){}; //? <+?>
async function* yield(){}; //? <+?>
async function* await(){}; //? <+?>

/// formal parameters
function a(b) {} //? <+>
function a(b = 2) {} //? <+>
function a(...b) {} //? <+>
function a(b, ...c) {} //? <+>
function a(b, c = 2, ...d) {} //? <+>
