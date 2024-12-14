from hashlib import md5
import json

users = {
    'teste' : [md5(b'HTBUser132').hexdigest(), 'secure123!']
}

print(users)

# {"username":"teste", "password":["cdf16ba040ec2b7ecf2d1cda3289bba9", "secure123!"]}

# # Login 
# {"option":"login"}

# User
# {"username": "HTBUser132", "password": "secure123!"}

print(len("cdf16ba040ec2b7ecf2d1cda3289bba9"))
print(md5(b'JohnMarcus').hexdigest())
print(md5(b'test123').hexdigest())