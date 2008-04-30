#!/bin/sh

g++ dblp-grep.c -o dblp-grep `xml2-config --libs --cflags`
