#!/bin/bash

function Main () {
  local COMMAND="${1}"; shift
  local FILES=("${@}")
  local PASS=$(cat project_euler/passphrase.txt)
  local OPENSSL_OPTS=(enc -base64 -aes-256-cbc -md sha256 -pbkdf2 -nosalt -pass pass:${PASS})

  case "${COMMAND}" in
    encrypt)
      for FILE in "${FILES[@]}"; do
        echo ":: [Encrypt] ${FILE} => ${FILE}.base64"
        openssl "${OPENSSL_OPTS[@]}" -in "${FILE}" -out "${FILE}.base64"
      done
    ;;
    decrypt)
      for FILE in "${FILES[@]}"; do
        echo ":: [Decrypt] ${FILE} => ${FILE%.base64}"
        openssl "${OPENSSL_OPTS[@]}" -in "${FILE}" -out "${FILE%.base64}" -d
      done
    ;;
    *)
      echo 'Usage: <program> (encrypt|decrypt) <file1> <file2> ...'
    ;;
  esac
}

Main "${@}"
