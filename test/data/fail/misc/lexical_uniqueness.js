function a(b, b = 0) {} //<>
function a(b, [b]) {} //<>
function a(b, {b}) {} //<>
function a(b, ...b) {} //<>
function a(b = 0, b) {} //<>
function a([b], b) {} //<>
function a({b}, b) {} //<>
function a(b, b, c = 0) {} //<>
function a(b, b, [c]) {} //<>
function a(b, b, {c}) {} //<>
function a(b) { let b; } //<>
function a([b]) { let b; } //<>
function a({b}) { let b; } //<>

!function a(b, b = 0) {} //<>
!function a(b, [b]) {} //<>
!function a(b, {b}) {} //<>
!function a(b, ...b) {} //<>
!function a(b = 0, b) {} //<>
!function a([b], b) {} //<>
!function a({b}, b) {} //<>
!function a(b, b, c = 0) {} //<>
!function a(b, b, [c]) {} //<>
!function a(b, b, {c}) {} //<>
!function a(b) { let b; } //<>
!function a([b]) { let b; } //<>
!function a({b}) { let b; } //<>

//for(let a;;) { var a; } //<

'use strict'; function a(b, b) {} //<>
