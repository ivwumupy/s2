pub mod token;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct ValueRef(u32);

pub enum TypeKind {
    Unit,
    Int32,
}

pub struct Module {
    pub functions: Vec<Function>,
}

pub struct Function {
    pub name: String,
    pub values: Vec<ValueData>,
}

pub enum ValueData {
    BasicBlock(BasicBlock),
    Integer(Integer),
    Instruction(Instruction),
}

pub struct Integer {
    pub value: i32,
}

pub enum Instruction {
    Trap,
}

pub struct BasicBlock {}
