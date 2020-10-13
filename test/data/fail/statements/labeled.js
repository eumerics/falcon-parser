do a: function b(){} while(0); //<>
while(0) a: function b(){} //<>
for(;false;) a: function b(){} //<>
for(a in b) c: function d(){} //<>
for(a of b) c: function d(){} //<>
async function a() { for await(b in c) d: function e(){} } //<>
async function a() { for await(b of c) d: function e(){} } //<>
a: function* b(){} //<>
a: async function b(){} //<>
a: async function* b(){} //<>
'use strict'; a: function b(){} //<>
