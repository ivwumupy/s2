#ifndef s2_syntax_leaf
#define s2_syntax_leaf(x)
#endif

#ifndef s2_syntax_node
#define s2_syntax_node(x)
#endif

s2_syntax_leaf(end_of_input)
s2_syntax_leaf(unknown_character)

s2_syntax_leaf(whitespace)
s2_syntax_leaf(line_comment)

s2_syntax_leaf(l_paren)
s2_syntax_leaf(r_paren)
s2_syntax_leaf(l_brace)
s2_syntax_leaf(r_brace)

s2_syntax_leaf(semicolon)
s2_syntax_leaf(equal)

s2_syntax_leaf(ident)

s2_syntax_leaf(kw_def)

s2_syntax_node(source_file)
s2_syntax_node(group_expr)

#undef s2_syntax_leaf
#undef s2_syntax_node
