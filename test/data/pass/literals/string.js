'', "", 'a', 'bc', "d", "ef";
// SinglEscapeCharacter
'\'', "\"", '\"', "\'";
'\\', '\r', '\n', '\t', '\v', '\b', '\f';
// NonEscapeCharacter
'\p';
// null character
'\0';
// HexEscapeSequence
'\x00', '\x80', '\xff';
// UnicodeEscapeSequence
'\u2028', '\u{0}', '\u{1}', '\u{12}', '\u{123}', '\u{1234}';
'\u{10000}', '\u{10ffff}', `\u{00000020}`;
// LineContinuation
'\
', '\ ', ' '; // line and paragraph separators
///*
// legacy octal
'\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7';
'\00', '\77', '\000', '\377';
// legacy non-octal
'\8', '\9';
//*/
