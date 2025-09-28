use std::num::NonZeroU32;

#[derive(Clone, Copy, PartialEq, Eq)]
pub struct NonMaxU32(NonZeroU32);

impl NonMaxU32 {
    pub fn new(n: u32) -> Option<Self> {
        match NonZeroU32::new(n.wrapping_add(1)) {
            Some(non_zero) => Some(NonMaxU32(non_zero)),
            None => None,
        }
    }
    pub fn get(self) -> u32 {
        self.0.get() - 1
    }
}

#[cfg(test)]
mod tests {
    use crate::utils::NonMaxU32;

    #[test]
    fn test_new() {
        let x = NonMaxU32::new(2);
        assert!(x.is_some());
        assert_eq!(x.unwrap().get(), 2);
    }
}
