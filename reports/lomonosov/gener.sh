#! /bin/bash

pdflatex -synctex=1 -interaction=nonstopmode "Nikiforov".tex -shell-escape
evince Nikiforov.pdf
