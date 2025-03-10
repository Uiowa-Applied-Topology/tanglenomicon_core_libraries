"""Documentation for DE-Book."""

import os
import sys

# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information


project = "Tanglenomicon Core Libraries"
copyright = "2023, temp"
author = "temp"
release = "0.0.1"

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinx.ext.napoleon",
    "sphinx.ext.todo",
    "sphinx.ext.viewcode",
    "sphinx.ext.autodoc",
    "sphinx.ext.autosummary",
    "myst_parser",
    "sphinxcontrib.mermaid",
    # "autodoc2",
    "sphinx_rtd_dark_mode",
    "sphinxcontrib.bibtex",
    "breathe",
    "sphinx_proof",
    "sphinx_togglebutton",
    "sphinxcontrib.inkscapeconverter",
    "sphinx_material"
]
templates_path = ["_templates"]
exclude_patterns = []
source_suffix = {".rst": "restructuredtext"}

suppress_warnings = ["myst.strikethrough", "misc.highlighting_failure"]

intersphinx_mapping = {
    "python": ("https://docs.python.org/3.7", None),
    "sphinx": ("https://www.sphinx-doc.org/en/master", None),
    "markdown_it": ("https://markdown-it-py.readthedocs.io/en/latest", None),
}

# -- Autodoc settings ---------------------------------------------------
#
# autodoc2_packages = [
#     {
#         "path": "../tanglenomicon_data_api",
#         "exclude_files": ["_docs.py"],
#     }
# ]
# autodoc2_hidden_objects = ["dunder", "private", "inherited"]
# autodoc2_replace_annotations = [
#     ("re.Pattern", "typing.Pattern"),
#     ("markdown_it.MarkdownIt", "markdown_it.main.MarkdownIt"),
# ]
# autodoc2_replace_bases = [
#     ("sphinx.directives.SphinxDirective", "sphinx.util.docutils.SphinxDirective"),
# ]
# autodoc2_render_plugin = "myst"
#
# nitpicky = False


# -- Bibtex settings ---------------------------------------------------
bibtex_bibfiles = ["./refs/zotero.bib", "./refs/manual.bib"]

# -- Breathe settings ---------------------------------------------------
breathe_projects = {"Core_Libraries": "./build/doxygen/xml"}
breathe_default_project = "Core_Libraries"

# -- MyST settings ---------------------------------------------------
myst_fence_as_directive = ["mermaid"]

myst_enable_extensions = [
    "dollarmath",
    # "amsmath",
    "deflist",
    "fieldlist",
    "html_admonition",
    "html_image",
    "colon_fence",
    "smartquotes",
    "replacements",
    "linkify",
    "strikethrough",
    "substitution",
    "tasklist",
    "attrs_inline",
    "attrs_block",
]
myst_url_schemes = {
    "http": None,
    "https": None,
    "mailto": None,
    "ftp": None,
    "wiki": "https://en.wikipedia.org/wiki/{{path}}#{{fragment}}",
    "doi": "https://doi.org/{{path}}",
    "gh-pr": {
        "url": "https://github.com/executablebooks/MyST-Parser/pull/{{path}}#{{fragment}}",
        "title": "PR #{{path}}",
        "classes": ["github"],
    },
    "gh-issue": {
        "url": "https://github.com/executablebooks/MyST-Parser/issue/{{path}}#{{fragment}}",
        "title": "Issue #{{path}}",
        "classes": ["github"],
    },
    "gh-user": {
        "url": "https://github.com/{{path}}",
        "title": "@{{path}}",
        "classes": ["github"],
    },
}
myst_number_code_blocks = ["typescript"]
myst_heading_anchors = 2
myst_footnote_transition = True
# myst_dmath_double_inline = True
myst_enable_checkboxes = True
myst_substitutions = {
    "role": "[role](#syntax/roles)",
    "directive": "[directive](#syntax/directives)",
}

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output
# user starts in dark mode
default_dark_mode = True
html_theme = "sphinx-material"
# The name of the Pygments (syntax highlighting) style to use.
pygments_style = "dracula"
# html_static_path = ["_static"]

mermaid_d3_zoom = True
mermaid_init_js = """mermaid.initialize({
  securityLevel: 'loose',
  theme: 'dark',
});"""

autosummary_generate = True
autoclass_content = "both"
html_show_sourcelink = False
autodoc_inherit_docstrings = True

latex_engine = 'lualatex'
latex_theme = 'howto'
latex_elements = {
    "preamble": r"""
    \usepackage{xcolor}
    \usepackage[twitter]{coloremoji}


    \definecolor{draculabg}      {RGB} {40,   42,   54}
    \definecolor{draculacl}      {RGB} {68,   71,   90}
    \definecolor{draculafg}      {RGB} {248,  248,  242}
    \definecolor{draculacomment} {RGB} {98,   114,  164}
    \definecolor{draculacyan}    {RGB} {139,  233,  253}
    \definecolor{draculagreen}   {RGB} {80,   250,  123}
    \definecolor{draculaorange}  {RGB} {255,  184,  108}
    \definecolor{draculapink}    {RGB} {255,  121,  198}
    \definecolor{draculapurple}  {RGB} {189,  147,  249}
    \definecolor{draculared}     {RGB} {255,  85,   85}
    \definecolor{draculayellow}  {RGB} {241,  250,  140}

    \pagecolor{draculabg}
    \color{draculafg}

    \sphinxsetup{%
         verbatimwithframe=true,
         VerbatimColor={named}{draculabg},
         VerbatimBorderColor={named}{draculapurple},
         TitleColor={named}{draculapurple},
         hintBorderColor={named}{draculapink},
         attentionborder=3pt,
         attentionBorderColor={named}{draculared},
         attentionBgColor={named}{draculabg},
         noteborder=2pt,
         noteBorderColor={named}{draculagreen},
         InnerLinkColor={named}{draculacyan},
         OuterLinkColor={named}{draculaorange},
         cautionborder=3pt,
         cautionBorderColor={named}{draculacyan},
         cautionBgColor={named}{draculacyan},
         div.topic_background-TeXcolor={named}{draculabg},
         div.topic_background-TeXcolor={named}{draculabg},
         div.topic_title-background-TeXcolor={named}{draculabg},
         }

    \newcommand{\N}{\mathbb{N}}
    \newcommand{\Z}{\mathbb{Z}}
    \newcommand{\Q}{\mathbb{Q}}
    \newcommand{\R}{\mathbb{R}}
    \newcommand{\LN}{\left.}
    \newcommand{\RN}{\right.}
    \newcommand{\LP}{\left(}
    \newcommand{\RP}{\right)}
    \newcommand{\LS}{\left\lbrace}
    \newcommand{\RS}{\right\rbrace}
    \newcommand{\LA}{\left\langle}
    \newcommand{\RA}{\right\rangle}
    \newcommand{\LB}{\left[}
    \newcommand{\RB}{\right]}
    \newcommand{\MM}{\ \middle|\ }
    \newcommand{\abs}[1]{\left\vert#1\right\vert}
    \newcommand{\msr}[1]{m\left(#1\right)}
    \newcommand{\inv}[1]{ #1^{-1}}
    \newcommand{\bkt}[1]{\LA \img{ #1}\RA}

\renewenvironment{sphinxnote}[1]
  {\begin{sphinxlightbox}\sphinxstrong{#1} }
  {\end{sphinxlightbox}}
\renewenvironment{sphinxhint}[1]
  {\begin{sphinxlightbox}\sphinxstrong{#1} }
  {\end{sphinxlightbox}}
\renewenvironment{sphinximportant}[1]
  {\begin{sphinxlightbox}\sphinxstrong{#1} }
  {\end{sphinxlightbox}}
\renewenvironment{sphinxtip}[1]
  {\begin{sphinxlightbox}\sphinxstrong{#1} }
  {\end{sphinxlightbox}}
\renewenvironment{sphinxseealso}[1]
  {\sphinxcolorlet{spx@notice@bordercolor}{sphinxseealsoBorderColor}%
   \csname spx@notice@border\endcsname=
   \dimexpr\csname spx@seealso@border@top\endcsname\relax
  \begin{sphinxlightbox}\sphinxstrong{#1} }
  {\end{sphinxlightbox}}
\renewenvironment{sphinxtodo}[1]
  {\sphinxcolorlet{spx@notice@bordercolor}{sphinxtodoBorderColor}%
   \csname spx@notice@border\endcsname=
   \dimexpr\csname spx@todo@border@top\endcsname\relax
  \begin{sphinxlightbox}\sphinxstrong{#1} }
  {\end{sphinxlightbox}}""",
}
