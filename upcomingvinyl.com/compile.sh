#!/bin/bash

gcc -o fuzzy_match fuzzy_match11f.c -lxml2 -lfuzzy -lfstrcmp -I/usr/include/libxml2
