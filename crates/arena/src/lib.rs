pub mod utils;

use std::marker::PhantomData;

use crate::utils::NonMaxU32;

pub struct Arena<T> {
    storage: Vec<T>,
}

type Index = NonMaxU32;

#[derive(Clone, Copy, PartialEq, Eq)]
pub struct Handle<T> {
    index: Index,
    marker: PhantomData<T>,
}

impl<T> Arena<T> {
    pub fn new() -> Self {
        Arena {
            storage: Vec::new(),
        }
    }

    pub fn clear(&mut self) {
        self.storage.clear();
    }

    pub fn get(&self, handle: Handle<T>) -> &T {
        &self.storage[handle.index.get() as usize]
    }
}
