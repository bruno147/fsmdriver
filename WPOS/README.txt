A brief explanation on how to use this folder:

First of all, "WPOS" folder will contain only the files needed for inclusion in the ".tex" file of the conference article for submission.
That is, all images files that are to be included in the publication should be archived in the WPOS folder.

The file "fsmdriver.tex" contains the article itself, and should not be altered without previous warning to the other members.

A substitute option for writing in ".tex" is write a text file, such as ".doc(x)" or ".txt", containing what is wished to be inserted in
the final article. Example: If you want to add the "Conclusions" section to the article, and do not wish to write it in LaTeX, you can write a ".txt" file containing your text and information and place it in the WPOS folder, then it will be further added to the article.

TeX style: [IEEEtran](http://www.ctan.org/tex-archive/macros/latex/contrib/IEEEtran/)

Compiling:

    pdflatex WPOS.tex
    bibtex WPOS
    pdflatex WPOS.tex
