[...a, ] = [];
//<>
[...a, b] = [];
//<>
[...a, ...b] = [];
//<>
[...a, b, ...c] = [];
//<>
z = {...a, } = {};
//<>
z = {...a, b} = {};
//<>
z = {...a, ...b} = {};
//<>
z = {...a, b, ...c} = {};
//<>
z = {a(){}} = {};
//<>
z = {*a(){}} = {};
//<>
z = {async a(){}} = {};
//<>
z = {async* a(){}} = {};
//<>
z = {get a(){}} = {};
//<>
z = {set a(b){}} = {};
//<>
([a]) = 1;
//<>
z = {a = 0};
