UPB ICPC Team Notebook (based on Stanford)
=========================================

This is the Universidad Privada Boliviana (UPB) ICPC team notebook, adapted and extended from the original Stanford ACM-ICPC notebook. It keeps the spirit and structure of the Stanford repo while adding:

- UPB branding (logo, headers) and improved PDF UI/UX (line numbers, captions, list of algorithms, dual themes).
- Expanded algorithms and data structures across graphs, strings, DP, number theory, geometry, etc.
- A modernized LaTeX build that produces both “read” (screen) and “print” PDFs.

The original upstream Stanford repository remains the foundational source of many implementations and ideas. See Credits below.

Generating the notebook
=======================
The included Python scripts can generate the notebook in PDF or HTML format. Both scripts read the contents from `contents.txt`.

PDF version
-----------
Requires: [Python 3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/), a LaTeX distribution (macOS: MacTeX).

Build both themed PDFs:

```
python3 generate_pdf.py
```

Outputs:

- `notebook_read.pdf`  (screen theme)
- `notebook_print.pdf` (print-friendly, grayscale)

The LaTeX template is `notebook.tex`. Syntax highlighting is provided by `listings`. To tweak styles or add languages, edit `notebook.tex` and/or `generate_pdf.py`.

HTML version
------------
Requires: [Python 2/3](https://www.python.org/), [enscript](https://www.gnu.org/software/enscript/)

Script for generating the HTML file is `generate_html.py`.
Syntax highlighting is handled solely by enscript, and in order to change the color schemes, either the default options of enscript or `generate_html.py` should be edited accordingly.

Links
=====
* UPB ISC — Competitive Programming resources (internal)
* ICPC official site: https://icpc.global/
* Kattis: https://open.kattis.com/ — Codeforces: https://codeforces.com/

Credits
=======
- Original base: Stanford ACM-ICPC team notebook (this repository is a derivative work). Many implementations and the initial structure come from the Stanford team and contributors over the years.
- UPB adaptations: branding, dual-theme PDFs, expanded algorithm set, and general UX improvements.

Notes
=====
- LIS variants: `code/LongestIncreasingSubsequence.cpp` provides two functions:
  - `LongestIncreasingSubsequence(v)`: strictly increasing LIS.
  - `LongestIncreasingSubsequenceNonStrict(v)`: non-decreasing LIS.

macOS notes
===========
- After installing MacTeX, ensure `latexmk` is on your PATH. If needed:

```
export PATH="/Library/TeX/texbin:$PATH"
```
