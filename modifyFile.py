##Mohammed Rakeeb
##30019515

import sys
import os
import cryptography.hazmat.primitives.ciphers
from   cryptography.hazmat.primitives import hashes
from   cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import (
    Cipher, algorithms, modes
)
from cryptography.hazmat.primitives import padding
from datetime import timedelta, date


def get_bytes_from_file(filename):
    return open(filename, "rb").read()
def write_bytes_to_file(filename,mode,content):
    with open(filename, mode) as f:
        f.write(content)


dictionary = []

start_dt = date(1984, 1, 1)
end_dt = date(2020, 2, 12)
Secret="FOXHOUND"
token = Secret.encode('utf-8')
ctext = get_bytes_from_file(sys.argv[1])
ciphT = ctext[16:]
iv = ctext[:16]
text = bytearray()



def daterange(date1, date2):
    for n in range(int ((date2 - date1).days)+1):
        yield date1 + timedelta(n)

for dt in daterange(start_dt, end_dt):
    dictionary.append(dt.strftime("%Y%m%d"))



def unpad(cipht):
    unpadder = padding.PKCS7(128).unpadder()
    data = unpadder.update(cipht)
    data += unpadder.finalize()
    return data


def Brute_force():
    global text
    p = ""

    for i in dictionary:
        possible_key = i.encode('utf-8')
        pass_digest =  hashes.Hash(hashes.SHA1(), backend=default_backend())
        key = pass_digest.update(possible_key)
        key = pass_digest.finalize()
        key = key[:16]
        cipher = Cipher(algorithms.AES(key),modes.CBC(iv), backend=default_backend())
        dec = cipher.decryptor()
        msg = dec.update(ciphT) + dec.finalize()
        if(token in msg):
            p = str(i)
            for i in msg:
                text.append(i)
    return p


def pad_it(B):
    padder = padding.PKCS7(128).padder()
    pad = padder.update(B)
    pad += padder.finalize()
    return pad



def tamper_it(text, passkey):

    digest = hashes.Hash(hashes.SHA1(), backend=default_backend())
    t = digest.update(text)
    t = digest.finalize()
    B = text + t
    p = passkey.encode('utf-8')
    pass_digest =  hashes.Hash(hashes.SHA1(), backend=default_backend())
    key = pass_digest.update(p)
    key = pass_digest.finalize()
    key = key[:16]

    iv = os.urandom(16)

    write_bytes_to_file(sys.argv[1], "wb", iv)

    cipher_ob = Cipher(algorithms.AES(key),modes.CBC(iv), backend=default_backend())

    if(len(B)%16 !=0):
        pad = pad_it(bytes(B))
        enc = cipher_ob.encryptor()
        ctext = enc.update(pad)
        ctext += enc.finalize()
        write_bytes_to_file(sys.argv[1], "ab" , ctext)
    else:
        enc = cipher_ob.encryptor()
        ctext = enc.update(B)
        ctext += enc.finalize()
        write_bytes_to_file(sys.argv[1], "ab" , ctext)





def main():
    global text
    password = Brute_force()
    print("The password is :", password)
    text = unpad(bytes(text))
    text = text[:len(text)-20]
    target= "CODE-RED"
    tar_p= target.encode('utf-8')
    tamper= "CODE-BLUE"
    tam_p = tamper.encode('utf-8')
    if (tar_p in text):
        print("the previous secret message:", text )
        text = text.replace(tar_p, tam_p)
        print(text)
        tamper_it(text, password)
        print("tampared message:", text)
    else:
        print("The secret message is:", text)


if __name__ == '__main__':
    main()
##https://people.ucalgary.ca/~rscheidl/418/handouts/Tutorial/pyca-crypto.pdf
