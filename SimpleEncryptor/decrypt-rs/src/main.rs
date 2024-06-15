use std::ops::BitXorAssign;

fn main() {
    let mut encrypted_data = std::fs::read("rev_simpleencryptor/flag.enc")
        .expect("flag.enc file with encrypted data is required");

    // First four bytes of the data is a seed for libc srand() function,
    // remove it from encrypted data and transform to unsigned integer
    let seed_bytes: Vec<_> = encrypted_data.drain(..4).collect();
    let mut seed: [u8; 4] = [0; 4];
    seed.copy_from_slice(&seed_bytes[..]);
    let seed = u32::from_le_bytes(seed);

    println!("Seed: {}", seed);

    // Seed the C random generator with required seed value
    unsafe {
        libc::srand(seed);
    }

    let mut flag = String::new();
    // During encrypt, each byte of plain data:
    // * XORed with rand() value;
    // * next rand() value is ANDed with 7;
    // * XORed plain byte is cyclically rotated to left by this
    //   (rand() & 7) and the result is actual encrypted byte.
    //
    // We have to perform these actions in reverse, keeping in mind
    // that we have to use rand() in the same order as for encryption
    // in order to get the right rand() values.
    for mut encrypted_byte in encrypted_data {
        let rnd_value_to_xor_plain_byte;
        let rnd_value_rotate;
        unsafe {
            rnd_value_to_xor_plain_byte = libc::rand();
            rnd_value_rotate = libc::rand() & 7;
        }

        encrypted_byte = encrypted_byte.rotate_right(rnd_value_rotate as u32);
        encrypted_byte.bitxor_assign(rnd_value_to_xor_plain_byte as u8);

        flag.push(encrypted_byte as char);
    }

    println!("Flag: {}", flag);
}
