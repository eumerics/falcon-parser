function a(b, b) {} //? <+>
function a(b, b = 0) {} //? <->
function a(b, [b]) {} //? <->
function a(b, {b}) {} //? <->
function a(b, ...b) {} //? <->
function a(b = 0, b) {} //? <->
function a([b], b) {} //? <->
function a({b}, b) {} //? <->
function a(b, b, c = 0) {} //? <->
function a(b, b, [c]) {} //? <->
function a(b, b, {c}) {} //? <->
function a(b) { var b; } //? <+>
function a(b) { let b; } //? <->
function a([b]) { var b; } //? <+>
function a([b]) { let b; } //? <->
function a({b}) { var b; } //? <+>
function a({b}) { let b; } //? <->
function a(...b) { var b; } //? <+>
function a(...b) { let b; } //? <->
function a(b = 0) { var b; } //? <+>
function a(b = 0) { let b; } //? <->

!function a(b, b = 0) {} //? <->
!function a(b, [b]) {} //? <->
!function a(b, {b}) {} //? <->
!function a(b, ...b) {} //? <->
!function a(b = 0, b) {} //? <->
!function a([b], b) {} //? <->
!function a({b}, b) {} //? <->
!function a(b, b, c = 0) {} //? <->
!function a(b, b, [c]) {} //? <->
!function a(b, b, {c}) {} //? <->
!function a(b) { let b; } //? <->
!function a([b]) { let b; } //? <->
!function a({b}) { let b; } //? <->
