#! /bin/bash

xelatex $1.tex
bibtex $1
xelatex $1.tex

evince $1.pdf
