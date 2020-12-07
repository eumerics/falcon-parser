/// code points are choosen to cover all possible coding scenarios in UTF8
a, À, ἀ, 𝛃; //? <+>
aa, aÀ, aἀ, a𝛃; //? <+>
Àa, ÀÀ, Àἀ, À𝛃; //? <+>
ἀa, ἀÀ, ἀἀ, ἀ𝛃; //? <+>
𝛃a, 𝛃À, 𝛃ἀ, 𝛃𝛃; //? <+>
a‌, À‌, ἀ‌, 𝛃‌; // invisible ZWJ as IdentifierPart //? <+>
a‍, À‍, ἀ‍, 𝛃‍; // invisible ZWNJ as IdentifierPart //? <+>
aÀἀ𝛃‌‍aÀἀ𝛃‌‍; //? <+>

𞸊, 𞸋, 𞸊𞸋; // surrogates (only valid as characters, not escape sequences) //? <+>

//- surrogate_in_identifier
\ud835; //? <-> @1:1
\udec3; //? <-> @1:1
\ud835\udec3; //? <-> @1:1
\u0061\ud835\udec3; //? <-> @1:7
\ud835\udec3\u00c0; //? <-> @1:1

/// unicode escaped versions of above tests
\u0061, \u00c0, \u1f00, \u{1d6c3}; //? <+>
\u0061\u0061, \u0061\u00c0, \u0061\u1f00, \u0061\u{1d6c3}; //? <+>
\u00c0\u0061, \u00c0\u00c0, \u00c0\u1f00, \u00c0\u{1d6c3}; //? <+>
\u1f00\u0061, \u1f00\u00c0, \u1f00\u1f00, \u1f00\u{1d6c3}; //? <+>
\u{1d6c3}\u0061, \u{1d6c3}\u00c0, \u{1d6c3}\u1f00, \u{1d6c3}\u{1d6c3}; //? <+>
\u0061\u200c, \u00c0\u200c, \u1f00\u200c, \u{1d6c3}\u200c; //? <+>
\u0061\u200d, \u00c0\u200d, \u1f00\u200d, \u{1d6c3}\u200d; //? <+>
\u0061\u00c0\u1f00\u{1d6c3}\u200c\u200d\u0061\u00c0\u1f00\u{1d6c3}\u200c\u200d; //? <+>

 a   À   ἀ   𝛃  //? <+>
 a  À  ἀ  𝛃  //? <+>

  //? <+>
  //? <+>
