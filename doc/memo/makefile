memo.pdf: memo.tex ndatk.10 class.pdf package.pdf
	pdflatex memo.tex
	pdflatex memo.tex

view: memo.pdf
	acroread memo.pdf

ndatk.10: ndatk.mp
	mpost ndatk.mp

class.pdf: class.dot
	dot -Teps -o class.eps class.dot
	epstopdf class.eps

package.pdf: package.dot
	dot -Teps -o package.eps package.dot
	epstopdf package.eps
