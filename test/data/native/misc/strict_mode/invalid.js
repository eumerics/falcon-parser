/// template
!{ a(){ 'use strict'; } } //? <+>
!{ set b(c){ 'use strict'; }} //? <+>
!function(){ 'use strict'; } //? <+>
!class{ a(){ 'use strict'; } } //? <+>
() => { 'use strict'; }; //? <+>
async () => { 'use strict'; }; //? <+>
function a(){ 'use strict'; } //? <+>
class a{ b(){ 'use strict'; } } //? <+>

//- invalid_strict_mode
!{ a(b = 0){ 'use strict'; } } //? <-> @1:14
!{ set a(b = 0){ 'use strict'; } } //? <-> @1:18
!function(a = 0){ 'use strict'; } //? <-> @1:19
!class{ a(b = 0){ 'use strict'; } } //? <-> @1:19
(a = 0) => { 'use strict'; }; //? <-> @1:14
async (a = 0) => { 'use strict'; }; //? <-> @1:20
function a(b = 0){ 'use strict'; } //? <-> @1:20
class a{ b(c = 0){ 'use strict'; } } //? <-> @1:20
///
!{ a([b]){ 'use strict'; } } //? <-> @1:12
!{ set a([b]){ 'use strict'; } } //? <-> @1:16
!function([a]){ 'use strict'; } //? <-> @1:17
!class{ a([b]){ 'use strict'; } } //? <-> @1:17
([a]) => { 'use strict'; }; //? <-> @1:12
async ([a]) => { 'use strict'; }; //? <-> @1:18
function a([b]){ 'use strict'; } //? <-> @1:18
class a{ b([c]){ 'use strict'; } } //? <-> @1:18
///
!{ a({b}){ 'use strict'; } } //? <-> @1:12
!{ set a({b}){ 'use strict'; } } //? <-> @1:16
!function({a}){ 'use strict'; } //? <-> @1:17
!class{ a({b}){ 'use strict'; } } //? <-> @1:17
({a}) => { 'use strict'; }; //? <-> @1:12
async ({a}) => { 'use strict'; }; //? <-> @1:18
function a({b}){ 'use strict'; } //? <-> @1:18
class a{ b({c}){ 'use strict'; } } //? <-> @1:18
///
!{ a(...b){ 'use strict'; } } //? <-> @1:13
!{ set a(...b){ 'use strict'; } } //? <-> @1:10 -default
!function(...a){ 'use strict'; } //? <-> @1:18
!class{ a(...b){ 'use strict'; } } //? <-> @1:18
(...a) => { 'use strict'; }; //? <-> @1:13
async (...a) => { 'use strict'; }; //? <-> @1:19
function a(...b){ 'use strict'; } //? <-> @1:19
class a{ b(...c){ 'use strict'; } } //? <-> @1:19
///
function a([eval]) { 'use strict'; } //? <-> @1:22
