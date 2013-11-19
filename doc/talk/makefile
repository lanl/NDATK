talk.pdf: talk.tex ndatk.10 class.pdf package.pdf w7.pdf
	pdflatex talk.tex
	pdflatex talk.tex

view: talk.pdf
	acroread talk.pdf

ndatk.10: ndatk.mp
	mpost ndatk.mp

class.pdf: class.dot
	dot -Teps -o class.eps class.dot
	epstopdf class.eps

package.pdf: package.dot
	dot -Teps -o package.eps package.dot
	epstopdf package.eps

w7.pdf: w7.dot
	dot -Teps -o w7.eps w7.dot
	epstopdf w7.eps

