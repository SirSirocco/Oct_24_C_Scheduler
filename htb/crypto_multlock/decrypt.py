import random
import string
import base64


def generate_key(seed, length=16):
    random.seed(seed)
    key = "".join(
        random.choice(string.ascii_letters + string.digits) for _ in range(length)
    )
    return key


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


ciphers1 = open("ciphers1.txt", "w")
ciphers2 = open("ciphers2.txt", "w")

first_half_hex = "00071134013a3c1c00423f330704382d00420d331d04383d00420134044f383300062f34063a383e0006443310043839004315340314382f004240331c043815004358331b4f3830"
first_half = bytes.fromhex(first_half_hex)
first_half = list(first_half)

second_half_hex = "5d1f486e4d49611a5d1e7e6e4067611f5d5b196e5b5961405d1f7a695b12614e5d58506e4212654b5d5b196e4067611d5d5b726e4649657c5d5872695f12654d5d5b4c6e4749611b"
second_half = bytes.fromhex(second_half_hex)
second_half = list(second_half)

xor_key = ""
teste = "12345678"
teste = (teste, xor_key)

# Gera uma chave polialfabética fixa a partir do seed 42
poly_key = generate_key(42)

# Primeiro loop: tenta XOR keys de 1 a 255 com a mesma chave polialfabética
for xor_key in range(1, 256):
    try:
        cipher1 = unxor_cipher(first_half, xor_key)
        cipher1 = polyalphabetic_decryption(cipher1, poly_key)
        print(cipher1)

        cipher2 = unxor_cipher(second_half, xor_key)
        cipher2 = polyalphabetic_decryption(cipher2, poly_key)

        ciphers1.write(cipher1 + cipher2 + "\n")
        print(cipher1, cipher2)
    except:
        pass


# Segundo loop: tenta variar a chave polialfabética gerando-a a partir de seeds de 1 a 1000,
# usando xor_key fixo em 42
xor_key = 42
for seed in range(1, 1001):
    try:
        test_key = generate_key(seed)
        cipher1 = unxor_cipher(first_half, xor_key)
        cipher1 = polyalphabetic_decryption(cipher1, test_key)
        print(cipher1)
    except:
        pass

    try:
        cipher2 = unxor_cipher(second_half, xor_key)
        cipher2 = polyalphabetic_decryption(cipher2, test_key)

        ciphers2.write(cipher1 + cipher2 + "\n")
        print(cipher1, cipher2)
    except:
        pass

ciphers1.close()
ciphers2.close()
