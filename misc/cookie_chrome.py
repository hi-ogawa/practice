#
# Read cookies from chrome/chromium's storage
#
# Cf.
#  - https://source.chromium.org/chromium/chromium/src/+/master:components/os_crypt/os_crypt_linux.cc;l=158
#  - https://www.openssl.org/docs/man1.1.0/man3/PKCS5_PBKDF2_HMAC_SHA1.html
#  - https://specifications.freedesktop.org/secret-service/latest/
#  - https://github.com/n8henrie/pycookiecheat/blob/master/src/pycookiecheat/pycookiecheat.py
#


kSalt = b"saltysalt"
kDerivedKeySizeInBits = 128
kEncryptionIterations = 1
kIVBlockSizeAES128 = 16

kVersion = b"v11"
kApplicationName = "chromium"
kCookieFile = "~/.config/chromium/Default/Cookies"
kCookieFields = "name, value, encrypted_value, creation_utc, expires_utc, path, is_secure, is_httponly, has_expires, is_persistent".split(", ")


def get_password():
  # Assume system installation of "dbus" (dbus-send cli is not enough since this requires alive connection)
  import dbus
  dbus_conn = dbus.SessionBus()
  dbus_obj = dbus_conn.get_object('org.freedesktop.secrets', '/org/freedesktop/secrets')
  dbus_iface = dict(dbus_interface='org.freedesktop.Secret.Service')
  resp = dbus_obj.SearchItems({'application': kApplicationName}, **dbus_iface)
  assert len(resp[0]) >= 1, "Password not found"
  key_path = resp[0][0]
  resp = dbus_obj.OpenSession('plain', '', **dbus_iface)
  session_path = resp[1]
  resp = dbus_obj.GetSecrets([key_path], session_path, **dbus_iface)
  password = bytes(resp[key_path][2])
  return password


def get_encryption_key(password, salt, iteration, keylen):
  # Directly invoke C api since openssl CLI only supports "standard" salt (i.e. Salt_xxx).
  import ctypes
  libcrypto = ctypes.cdll.LoadLibrary('libcrypto.so')
  key = b' ' * keylen
  libcrypto.PKCS5_PBKDF2_HMAC_SHA1(
      password, len(password),
      salt, len(salt),
      iteration, keylen, key)
  return key


def to_hex_str(bs): # bytes -> str
  return ''.join(hex(b)[2:] for b in bs)


def decrypt(encryption_key, ciphertext):
  # Use openssl CLI since it's much simpler
  import subprocess
  hex_encryption_key = to_hex_str(encryption_key)
  hex_iv = to_hex_str(b' ' * kIVBlockSizeAES128)
  command = f"openssl enc -d -aes-128-cbc -K {hex_encryption_key} -iv {hex_iv}"
  proc = subprocess.run(command.split(), input=ciphertext, capture_output=True, check=True)
  return proc.stdout


def decrypt_cookie(encryption_key, encrypted_value):
  if len(encrypted_value) == 0:
    return b''
  assert encrypted_value[:3] == kVersion
  ciphertext = encrypted_value[3:]
  plaintext = decrypt(encryption_key, ciphertext)
  return plaintext


def get_cookies(hostname):
  import sqlite3, os
  password = get_password()
  encryption_key = get_encryption_key(password, kSalt, kEncryptionIterations, kDerivedKeySizeInBits // 8)
  conn = sqlite3.connect(os.path.expanduser(kCookieFile))
  cursor = conn.cursor()
  query = f"""
    SELECT {', '.join(kCookieFields)} FROM cookies WHERE host_key LIKE ?
    ORDER BY LENGTH(path) DESC, creation_utc ASC
  """
  rows = cursor.execute(query, ('%' + hostname,))
  cookies = [dict(zip(kCookieFields, row)) for row in rows]
  for c in cookies:
    c['value'] = decrypt_cookie(encryption_key, c['encrypted_value']).decode()
    c['encrypted_value'] = ''
  return cookies


def main(hostname, format):
  import json
  cookies = get_cookies(hostname)
  if format == 'json':
    print(json.dumps(cookies, indent=2))
  if format == 'header':
    print('; '.join(c['name'] + '=' + c['value'] for c in cookies))


def main_cli():
  import argparse, sys
  parser = argparse.ArgumentParser()
  parser.add_argument("hostname", type=str)
  parser.add_argument("--format", type=str, choices=['json', 'header'], default='json')
  sys.exit(main(**parser.parse_args().__dict__))


if __name__ == '__main__':
  main_cli()
