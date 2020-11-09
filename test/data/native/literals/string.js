'', "", 'a', 'bc', "d", "ef"; //? <+>
/// SinglEscapeCharacter
'\'', "\"", '\"', "\'"; //? <+>
'\\', '\r', '\n', '\t', '\v', '\b', '\f'; //? <+>
/// NonEscapeCharacter
'\p'; //? <+>
///
'\0'; //null character //? <+>
' '; //line separator //? <+>
' '; //paragraph separator //? <+>
/// HexEscapeSequence
'\x00', '\x80', '\xff'; //? <+>
/// UnicodeEscapeSequence
'\u2028', '\u{0}', '\u{1}', '\u{12}', '\u{123}', '\u{1234}'; //? <+>
'\u{10000}', '\u{10ffff}', `\u{00000020}`; //? <+>
// LineContinuation
'\
'; //? <+>
'\'; //? <+>
'\
'; //? <+>
'\ '; // line separator //? <+>
'\ '; // paragraph separator //? <+>
/// legacy octal
'\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7'; //? <+&>
'\00', '\01', '\77', '\000', '\001', '\377'; //? <+&>
/// legacy non-octal
'\8', '\9'; //? <+&>
/// mixed octal
'\08', '\78', '\81', '\91', '\378', '\381', '\401'; //? <+&>

//- invalid_escape_sequence
'use strict'; '\1'; //? <-> @1:16
'use strict'; '\8'; //? <-> @1:16
'use strict'; '\01'; //? <-> @1:16
'use strict'; '\377'; //? <-> @1:16
//- octal_in_strict
'\1'
'use strict' //? <-?> @1:2
'\1'
'use strict'; //? <-?> @1:2
''
'\1'
'use strict' //? <-?> @2:2
//- unicode_range
'\u{110000}'; //? <-> @1:2

/// line terminators
//- newline_in_string_literal
'
'; //? <-> @1:2
''; //? <-> @1:2
'
'; //? <-> @1:2
' '; //? <+>
' '; //? <+>
'\
'; //? <+>
'\'; //? <+>
'\
'; //? <+>
'\ '; //? <+>
'\ '; //? <+>
