function a() { 'use strict'; eval; } //<>
function a() { 'use strict'; arguments; } //<>
function a() { 'use strict'; function a(b = eval) {} } //<>
function a() { 'use strict'; function a(b = arguments) {} } //<>
!{eval: 0}; //<>
!{arguments: 0}; //<>
function a() { 'use strict'; !{eval: 0}; } //<>
function a() { 'use strict'; !{arguments: 0}; } //<>
function a(){ eval; } //<>
function a(){ arguments; } //<>
function a(){ 'use strict'; eval; } //<>
function a(){ 'use strict'; arguments; } //<>
function a(){ 'use strict'; !{eval}; } //<>
function a(){ 'use strict'; !{arguments}; } //<>
function a(){ 'use strict'; !{eval: 0}; } //<>
function a(){ 'use strict'; !{arguments: 0}; } //<>
