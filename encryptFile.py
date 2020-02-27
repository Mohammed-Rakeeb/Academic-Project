##Mohammed Rakeeb
##30019515

import sys
import os
from cryptography.hazmat.primitives.ciphers import (
    Cipher, algorithms, modes
)
from   cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives import padding
from   cryptography.hazmat.backends import default_backend


def get_bytes_from_file(filename):
    return open(filename, "rb").read()

def write_bytes_to_file(filename,mode,content):
    with open(filename, mode) as f:
        f.write(content)

def pad_it(B):
    padder = padding.PKCS7(128).padder()
    pad = padder.update(B)
    pad += padder.finalize()
    return pad

def encrypt_message():
    msg = get_bytes_from_file(sys.argv[1])

    B = bytearray()
    for i in msg:
        B.append(i)


    #B = msg.encode('utf-8')
    #print(B[0])


    digest = hashes.Hash(hashes.SHA1(), backend=default_backend())
    t = digest.update(B)
    t = digest.finalize()

    B_t = B + t

    password = sys.argv[3].encode('utf-8')
    pass_digest =  hashes.Hash(hashes.SHA1(), backend=default_backend())
    key = pass_digest.update(password)
    key = pass_digest.finalize()
    key = key[:16]
    #print(key)

    iv = os.urandom(16)

    write_bytes_to_file(sys.argv[2], "wb", iv)

    cipher_ob = Cipher(algorithms.AES(key),modes.CBC(iv), backend=default_backend())


    if(len(B_t)%16 !=0):
        pad = pad_it(bytes(B_t))
        enc = cipher_ob.encryptor()
        ctext = enc.update(pad)
        ctext += enc.finalize()

        write_bytes_to_file(sys.argv[2], "ab" , ctext)
    else:
        enc = cipher_ob.encryptor()
        ctext = enc.update(B_t)
        ctext += enc.finalize()
        write_bytes_to_file(sys.argv[2], "ab" , ctext)


encrypt_message()
##https://people.ucalgary.ca/~rscheidl/418/handouts/Tutorial/pyca-crypto.pdf
