#!/usr/bin/python
import subprocess
import os
code_dir = "code"
title = "UPB ISC Team Notebook"

def get_sections():
    sections = []
    section_name = None
    with open('contents.txt', 'r') as f:
        for line in f:
            if '#' in line: line = line[:line.find('#')]
            line = line.strip()
            if len(line) == 0: continue
            if line[0] == '[':
                section_name = line[1:-1]
                subsections = []
                if section_name is not None:
                    sections.append((section_name, subsections))
            else:
                tmp = line.split('\t', 1)
                if len(tmp) == 1:
                    raise ValueError('Subsection parse error: %s' % line)
                filename = tmp[0]
                subsection_name = tmp[1]
                if section_name is None:
                    raise ValueError('Subsection given without section')
                subsections.append((filename, subsection_name))
    return sections

def get_style(filename):
    ext = filename.lower().split('.')[-1]
    if ext in ['c', 'cc', 'cpp']:
        return 'cpp'
    elif ext in ['java']:
        return 'java'
    elif ext in ['py']:
        return 'py'
    else:
        return 'txt'

# TODO: check if this is everything we need
def texify(s):
    # Escape LaTeX special characters in section/subsection titles
    # We purposely do NOT escape file paths passed to lstinputlisting.
    repl = {
        '&': r'\&',
        '%': r'\%',
        '$': r'\$',
        '#': r'\#',
        '_': r'\_',
        '{': r'\{',
        '}': r'\}',
        '~': r'\\textasciitilde{}',
        '^': r'\\^{}',
    }
    return ''.join(repl.get(ch, ch) for ch in s)

def get_tex(sections):
    tex = ''
    first = True
    for (section_name, subsections) in sections:
        # Force a new physical page at the start of each section.
        # In a two-column multicols environment, one \newpage advances a column;
        # two successive \newpage advance to the next page's first column.
        if not first:
            tex += '\\newpage\n\\newpage\n'
        first = False
        tex += '\\section{%s}\n' % texify(section_name)
        for (filename, subsection_name) in subsections:
            tex += '\\subsection{%s}\n' % texify(subsection_name)
            caption = texify('%s (%s)' % (subsection_name, filename))
            tex += '\\raggedbottom\\lstinputlisting[style=%s,caption={%s}]{%s/%s}\n' % (get_style(filename), caption, code_dir, filename)
            tex += '\\hrulefill\n'
        tex += '\n'
    return tex

if __name__ == "__main__":
    sections = get_sections()
    tex = get_tex(sections)
    with open('contents.tex', 'w') as f:
        f.write(tex)
    # Build two variants: print and read
    # Print mode is enabled by presence of 'printmode.flag'
    # 1) Print version
    try:
        with open('printmode.flag', 'w'):
            pass
        subprocess.call(["latexmk", "-pdf", "-jobname=notebook_print", "notebook.tex"])
    finally:
        if os.path.exists('printmode.flag'):
            os.remove('printmode.flag')
    # 2) Read (screen) version
    subprocess.call(["latexmk", "-pdf", "-jobname=notebook_read", "notebook.tex"])
