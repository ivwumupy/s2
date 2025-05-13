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
s2_syntax_node(function_item)
s2_syntax_node(param_list)
s2_syntax_node(param)
s2_syntax_node(return_type)

s2_syntax_node(block_expr)
s2_syntax_node(group_expr)
s2_syntax_node(call_expr)
s2_syntax_node(literal_expr)

s2_syntax_node(name)
s2_syntax_node(type)

s2_syntax_node(placeholder_)

#undef s2_syntax_leaf
#undef s2_syntax_node
