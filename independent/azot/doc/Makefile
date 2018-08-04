all: document

azot.toc:
	latex azot.tex

document: azot.toc
	latex azot.tex

clean:
	rm -f *.aux
	rm -f *.dvi
	rm -f *.log
	rm -f *.toc
