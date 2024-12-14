import random
import string
import base64
import time

# from secret import FLAG


def unxor_cipher(cipher, xor_key):
    return "".join(chr(b ^ xor_key) for b in cipher)


def polyalphabetic_decryption(ciphertext, key):
    ciphertext = str(ciphertext)
    ciphertext = ciphertext.encode()
    ciphertext = base64.b64decode(ciphertext)
    ciphertext = ciphertext.decode()

    key_length = len(key)
    plaintext_chars = []
    for i, char in enumerate(ciphertext):
        key_char = key[i % key_length]
        original_char = chr((ord(char) - ord(key_char)) % 256)
        plaintext_chars.append(original_char)

    return "".join(plaintext_chars)


def generate_key(seed, length=16):
    random.seed(seed)
    key = "".join(
        random.choice(string.ascii_letters + string.digits) for _ in range(length)
    )
    return key


def polyalphabetic_encrypt(plaintext, key):
    key_length = len(key)
    ciphertext = []
    for i, char in enumerate(plaintext):
        key_char = key[i % key_length]
        encrypted_char = chr((ord(char) + ord(key_char)) % 256)
        ciphertext.append(encrypted_char)
    return base64.b64encode("".join(ciphertext).encode()).decode()


def xor_cipher(text, key):
    return bytes([ord(c) ^ key for c in text])


def get_timestamp_based_keys():
    timestamp = int(time.time())
    if timestamp % 2 == 0:
        print(1)
        key_seed = random.randint(1, 1000)
        xor_key = 42
    else:
        print(2)
        key_seed = 42
        xor_key = random.randint(1, 255)
    return key_seed, xor_key


def main():
    # Split the flag
    FLAG = "Pedro Hanna Luiz 2024"

    flag_half1 = FLAG[: len(FLAG) // 2]
    flag_half2 = FLAG[len(FLAG) // 2 :]
    key = list()
    xor_key = list()
    encrypted_flags = []

    for i in range(2):
        key_seed, xor_aux = get_timestamp_based_keys()
        xor_key.append(xor_aux)
        key_aux = generate_key(key_seed)
        key.append(key_aux)
        encrypted_half = polyalphabetic_encrypt(
            flag_half1 if len(encrypted_flags) == 0 else flag_half2, key_aux
        )
        print(encrypted_half)
        encrypted_half = xor_cipher(encrypted_half, xor_aux)
        print(encrypted_half)
        encrypted_flags.append(encrypted_half.hex())
        time.sleep(1)

    # Save encrypted flags to output.txt
    with open("output2.txt", "w") as f:
        f.write(f"{encrypted_flags[0]}\n{encrypted_flags[1]}\n")

    encrypted_flags[0] = (
        "00071134013a3c1c00423f330704382d00420d331d04383d00420134044f383300062f34063a383e0006443310043839004315340314382f004240331c043815004358331b4f3830"
    )

    encrypted_flags[1] = (
        "5d1f486e4d49611a5d1e7e6e4067611f5d5b196e5b5961405d1f7a695b12614e5d58506e4212654b5d5b196e4067611d5d5b726e4649657c5d5872695f12654d5d5b4c6e4749611b"
    )

    cipher1 = list(bytes.fromhex(encrypted_flags[0]))
    print(cipher1)
    cipher1 = unxor_cipher(cipher1, xor_key[0])
    print(cipher1)
    cipher1 = polyalphabetic_decryption(cipher1, key[0])
    print(cipher1)

    cipher2 = list(bytes.fromhex(encrypted_flags[1]))
    print(cipher2)
    cipher2 = unxor_cipher(cipher2, xor_key[1])
    print(cipher2)
    cipher2 = polyalphabetic_decryption(cipher2, key[1])
    print(cipher2)


if __name__ == "__main__":
    main()
