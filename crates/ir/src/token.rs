pub enum TokenKind {
    Literal(i32),
    Keyword(Keyword),
    Symbol(String),
    Other(char),
    EndOfFile,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Keyword {
    /// `i32`
    I32,

    // Control flow
    /// `jump`
    Jump,
    /// `br`
    Br,
    /// `call`
    Call,
    /// `ret`
    Ret,

    // Memory ops
    /// `load`
    Load,
    /// `store`
    Store,
    /// `alloc`
    Alloc,

    // Syntax
    /// `def`
    Def,
}
