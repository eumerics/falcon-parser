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
'\', '\
', '\
', '\ ', ' '; // line and paragraph separators
///*
// legacy octal
'\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7';
'\00', '\01', '\77', '\000', '\001', '\377';
// legacy non-octal
'\8', '\9';
// mixed octal
'\08', '\78', '\81', '\91', '\378', '\381', '\401';
//*/
