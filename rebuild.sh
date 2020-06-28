#!/bin/bash

rm -rf test_package/build ~/.conan/data/ssge-client;
conan create . demo/testing;
