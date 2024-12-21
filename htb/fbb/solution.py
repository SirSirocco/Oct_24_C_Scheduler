import base64

def remove_as(input_string):
    """
    Removes all occurrences of 'A' and 'a' from the input string.

    :param input_string: The string to process.
    :return: A new string without 'A' or 'a'.
    """
    return input_string.replace('A', '')

def string_to_hex(input_string):
    """
    Converts a string to its hexadecimal representation.

    :param input_string: The string to convert.
    :return: A hexadecimal string.
    """
    return input_string.encode('utf-8').hex()

def bytes_to_hex(byte_data):
    """
    Converts a bytes object to a hexadecimal string.

    :param byte_data: The bytes object to convert.
    :return: A hexadecimal string.
    """
    if not isinstance(byte_data, (bytes, bytearray)):
        raise TypeError("Input must be a bytes or bytearray object")
    return byte_data.hex()

def hex_to_char_string(hex_string):
    """
    Converts a hexadecimal string to a character string.

    :param hex_string: The hexadecimal string to convert.
    :return: A decoded character string.
    """
    if not isinstance(hex_string, str):
        raise TypeError("Input must be a hexadecimal string")
    
    # Ensure the string length is even (hexadecimal pairs)
    if len(hex_string) % 2 != 0:
        raise ValueError("Hex string length must be even")

    # Convert the hex string to bytes
    byte_data = bytes.fromhex(hex_string)
    
    # Decode bytes to string (assuming UTF-8 encoding)
    return byte_data.decode('utf-8')

# Replace 'your_base64_string' with the binary content provided
base64_string = """
AQAAABQAAAAAAAAAJgAAACcAAAA=
"""

# Decode the Base64 string
image_data = base64.b64decode(base64_string)
string_hex = bytes_to_hex(image_data)
char_string = hex_to_char_string(string_hex)

print(string_hex)
print(char_string)

# Save the binary data as an image file
with open("icon.bmp", "wb") as image_file:
    image_file.write(image_data)

with open("icon.png", "wb") as image_file:
    image_file.write(image_data)

with open("icon.jpg", "wb") as image_file:
    image_file.write(image_data)

with open("icon.jpeg", "wb") as image_file:
    image_file.write(image_data)

with open("icon.ico", "wb") as image_file:
    image_file.write(image_data)