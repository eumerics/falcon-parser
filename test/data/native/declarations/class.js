/// empty declarations
class a {} //? <+>
class a {;} //? <+>
class a { ''(){} } //? <+^>
class a extends b {} //? <+>

/// class declarations are always in strict mode
class eval {} //? <->
class arguments {} //? <->
class a extends eval {} //? <+>
class a extends arguments {} //? <+>
class a extends eval = b {} //? <->
class a extends arguments = b {} //? <->

/// constructors
class a { constructor(){} } //? <+>
class a { 'constructor'(){} } //? <+>
class a { ['constructor'](){} } //? <+>
class a { static constructor(){} } //? <+>

/// early errors
class a { constructor(){ super(); } } //? <->
///class a { constructor(){} constructor(){} } //? <->
class a extends b { c(){ super(); } } //? <->
class a { * constructor(){} } //? <->
class a { async constructor(){} } //? <->
class a { async* constructor(){} } //? <->
class a { get constructor(){} } //? <->
class a { set constructor(b){} } //? <->
class a { static b(){ super(); } } //? <->
///class a { static prototype(){} } //? <->

/// method definitions
///   regular methods
class a { b(c){} } //? <+>
class a { 'a'(b, c){} } //? <+>
class a { [b](...c){} } //? <+>
class a { [(b)](c, ...d){} } //? <+>
class a { 0(b,){} } //? <+>
///   generator methods
class a { * b([c]){} } //? <+>
class a { * 'a'({b}){} } //? <+>
class a { * [b](...[c]){} } //? <+>
class a { * [(b)](...{c}){} } //? <+>
class a { * 0([b], {c}, ...[d]){} } //? <+>
///   async methods
class a { async b(c = 0){} } //? <+>
class a { async 'a'([b = 0]){} } //? <+>
class a { async [b]({c = 0}){} } //? <+>
class a { async [(b)](...[c = 0]){} } //? <+>
class a { async 0(...{b = 0}){} } //? <+>
///   async generator methods
class a { async* b(){} } //? <+>
class a { async* 'a'(b){} } //? <+>
class a { async* [b](c,d){} } //? <+>
class a { async* [(b)](...c){} } //? <+>
class a { async* 1(b, ...c){} } //? <+>
///   getters
class a { get b(){} } //? <+>
class a { get 'a'(){} } //? <+>
class a { get [b](){} } //? <+>
class a { get [(b)](){} } //? <+>
class a { get 0(){} } //? <+>
///   setters
class a { set b(c){} } //? <+>
class a { set 'a'(b){} } //? <+>
class a { set [b](c){} } //? <+>
class a { set [(b)](c){} } //? <+>
class a { set 0(b){} } //? <+>

/// static method definitions
///   static methods
class a { static b(c){} } //? <+>
class a { static 'a'(b, c){} } //? <+>
class a { static [b](...c){} } //? <+>
class a { static [(b)](c, ...d){} } //? <+>
class a { static 0(b,){} } //? <+>
///   static generator methods
class a { static * b([c]){} } //? <+>
class a { static * 'a'({b}){} } //? <+>
class a { static * [b](...[c]){} } //? <+>
class a { static * [(b)](...{c}){} } //? <+>
class a { static * 0([b], {c}, ...[d]){} } //? <+>
///   static async methods
class a { static async b(c = 0){} } //? <+>
class a { static async 'a'([b = 0]){} } //? <+>
class a { static async [b]({c = 0}){} } //? <+>
class a { static async [(b)](...[c = 0]){} } //? <+>
class a { static async 0(...{b = 0}){} } //? <+>
///   static async generator methods
class a { static async* b(){} } //? <+>
class a { static async* 'a'(b){} } //? <+>
class a { static async* [b](c,d){} } //? <+>
class a { static async* [(b)](...c){} } //? <+>
class a { static async* 1(b, ...c){} } //? <+>
///   static getters
class a { static get b(){} } //? <+>
class a { static get 'a'(){} } //? <+>
class a { static get [b](){} } //? <+>
class a { static get [(b)](){} } //? <+>
class a { static get 0(){} } //? <+>
///   static setters
class a { static set b(c){} } //? <+>
class a { static set 'a'(b){} } //? <+>
class a { static set [b](c){} } //? <+>
class a { static set [(b)](c){} } //? <+>
class a { static set 0(b){} } //? <+>

/// keyword method definitions
class a { get(){} } //? <+>
class a { set(){} } //? <+>
class a { async(){} } //? <+>
class a { static(){} } //? <+>
/// get
class a { get(){} } //? <+>
class a { * get(){} } //? <+>
class a { async get(){} } //? <+>
class a { async* get(){} } //? <+>
class a { get get(){} } //? <+>
class a { set get(b){} } //? <+>
class a { static get(){} } //? <+>
/// set
class a { set(b){} } //? <+>
class a { * set(b){} } //? <+>
class a { async set(b){} } //? <+>
class a { async* set(b){} } //? <+>
class a { get set(){} } //? <+>
class a { set set(b){} } //? <+>
class a { static set(b){} } //? <+>
/// async
class a { async(){} } //? <+>
class a { * async(){} } //? <+>
class a { async async(){} } //? <+>
class a { async* async(){} } //? <+>
class a { get async(){} } //? <+>
class a { set async(b){} } //? <+>
class a { static async(){} } //? <+>
/// static
class a { static(){} } //? <+>
class a { * static(){} } //? <+>
class a { async static(){} } //? <+>
class a { async* static(){} } //? <+>
class a { get static(){} } //? <+>
class a { set static(b){} } //? <+>
class a { static static(){} } //? <+>
