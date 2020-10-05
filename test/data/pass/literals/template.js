let a, b, c, expr, head_expr, tail_expr;

// simple templates
``;
`template`;
`${a}`;
`head-${a}`;
`${a}-tail`;
`${a}${b}`;
`head-${a}-tail`;
`head-${a}${b}`;
`${a}-middle-${b}`;
`${a}${b}-tail`;
`${a}${b}${c}`;
`head-${a}-middle-${b}-tail`;
`head-${a}${b}-tail`;

// special characters
`$`, `{`, `}`, `\${`, `$ {`, `\``, ``, `
`, `
`;

// nesting
`${``}`, `${`${``}`}`;
`${``}-tail`, `head-${``}`;
`head-${`` - tail_expr}`;
`head-${`nested-head-${expr}` - tail_expr}`;
`head-${`${expr}-nested-tail` - tail_expr}`;
`head-${`nested-head-${expr}-nested-tail` - tail_expr}`;
`head-${head_expr - ``}`;
`head-${head_expr - `nested-head-${expr}`}`;
`head-${head_expr - `${expr}-nested-tail`}`;
`head-${head_expr - `nested-head-${expr}-nested-tail`}`;
`head-${head_expr - `` - tail_expr}`;
`head-${head_expr - `nested-head-${expr}` - tail_expr}`;
`head-${head_expr - `${expr}-nested-tail` - tail_expr}`;
`head-${head_expr - `nested-head-${expr}-nested-tail` - tail_expr}`;

// tagged templates
````, a``;
`${````}`, `${a``}}`;
`` ``, `` `\``, `\`` ``, `\`` `\``;

// special expressions / statements
`${{a}}`;
{ `${a}`; }

// tagged not-escape sequences
a`\01`, a`\1`;
a`\x`, a`\xg`, a`\x0g`;
a`\u`, a`\ug`, a`\u0g`, a`\u00g`, a`\u000g`;
a`\u{`, a`\u{g`, a`\u{0g`, a`\u{00g`, a`\u{000g`, a`\u{0000g`, a`\u{00000g`, a`\u{110000}`;
