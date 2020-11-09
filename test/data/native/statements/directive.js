'a'; //? <+>
'a'; 'b'; //? <+>
'a'; ; 'b'; //? <+>
''; 'a'; 1; 'b'; //? <+>

function a() { 'a'; } //? <+>
function a() { 'a' } //? <+>
function a() { 'a'
} //? <+>
function a() { 'a'; 'b'; } //? <+>
function a() { 'a'; 'b' } //? <+>
function a() { 'a'
'b'; } //? <+>
function a() { 'a'
'b' } //? <+>
function a() { 'a'
'b'
} //? <+>
function a() { 'a'; 'b'; 1; } //? <+>
function a() { 'a'; 1; 'b'; } //? <+>
function a() { 1; 'a'; 'b'; } //? <+>
function a() { 'a'
+ 'b'; 'c'; } //? <+>

function a() { class b {} 'a' } //? <+>
