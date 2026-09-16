# 103Cipher

> Mathematical Message Masking Multiplying Matrices — Epitech

A Hill-cipher inspired encryption/decryption program: it turns a message and a key into ASCII-based matrices, multiplies them to encrypt, and inverts the key matrix to decrypt — without using any matrix calculus library such as numpy.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Examples](#examples)

## Overview

**Encryption**

1. The key is transcribed into numbers using the ASCII table.
2. The numbered key is converted into the smallest possible square matrix, filled line by line (padded with zeros if needed).
3. The clear message is transcribed into numbers using the ASCII table.
4. The numbered message is converted into a matrix whose number of columns matches the key matrix size, and whose number of lines is as small as possible (padded with zeros if needed).
5. The key matrix and message matrix are multiplied; the result, written linearly, is the encrypted message.

**Decryption**

Follows the reverse process, using the same key: the key matrix is inverted, then used to recover the original message matrix.

## Usage

```bash
$> ./103cipher -h
USAGE
./103cipher message key flag
DESCRIPTION
message a message, made of ASCII characters
key the encryption key, made of ASCII characters
flag 0 for the message to be encrypted, 1 to be decrypted
```

## Examples

Encryption:

```
$> ./103cipher "Just because I don't care doesn't mean I don't understand." "Homer S" 0
Key matrix:
72 111 109
101 114 32
83 0 0
Encrypted message:
26690 21552 11810 19718 16524 13668 25322 22497 14177 28422 26097 16433 12333 11874 5824
27541 23754 14452 17180 17553 7963 26387 22047 13895 18804 14859 12033 27738 23835 15331
21487 16656 13238 21696 15978 6976 20750 23307 14093 16788 11751 8981 22339 24861 15619
21295 16524 13668 26403 23610 15190 29451 25764 16106 26394 23307 14093 3312 5106 5014
```

Decryption:

```
$> ./103cipher "26690 21552 11810 19718 16524 13668 25322 22497 14177 28422 26097 16433
12333 11874 5824 27541 23754 14452 17180 17553 7963 26387 22047 13895 18804 14859 12033
27738 23835 15331 21487 16656 13238 21696 15978 6976 20750 23307 14093 16788 11751 8981
22339 24861 15619 21295 16524 13668 26403 23610 15190 29451 25764 16106 26394 23307 14093
3312 5106 5014" "Homer S" 1
Key matrix:
0.0 0.0 0.012
-0.004 0.012 -0.012
0.013 -0.013 0.004
Decrypted message:
Just because I don't care doesn't mean I don't understand.
```

Elements of the key matrix are separated by tabulations in the output. For decryption, the displayed key matrix is only indicative.