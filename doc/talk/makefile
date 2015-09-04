%.pdf: %.dot
	dot -Teps -o $*.eps $<
	epstopdf $*.eps

talk.pdf: talk.tex ndatk.10 class.pdf package.pdf w7.pdf nds.pdf
	pdflatex talk.tex
	pdflatex talk.tex

view: talk.pdf
	acroread talk.pdf

ndatk.10: ndatk.mp
	mpost ndatk.mp

class.pdf: class.dot

package.pdf: package.dot

nds.pdf: nds.dot

w7.pdf: w7.dot
