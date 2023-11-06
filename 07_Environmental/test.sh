#!/bin/env bash

./bin/rhasher > test.out << @@@
    md5 "hello"
    sha1 "hello"
    tth "hello"
    MD5 "hello"
    SHA1 "hello"
    TTH "hello"
    md5 testfile
    sha1 testfile
    tth testfile
    MD5 testfile
    SHA1 testfile
    TTH testfile
@@@

if cmp -s test.out test.ref ; then
    echo "OK"
else
    echo "FAILED"
fi