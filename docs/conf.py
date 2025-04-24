"""Documentation for DE-Book."""

from pathlib import Path
from shutil import copyfile, copytree, rmtree
from sphinxcontrib.collections.drivers import Driver
from sphinxcontrib.collections.api import register_driver

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
    "sphinxcontrib.bibtex",
    "breathe",
    "sphinx_proof",
    "sphinxcontrib.inkscapeconverter",
    "sphinx_material",
    "sphinxcontrib.collections",
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

# -- Bibtex settings ---------------------------------------------------
bibtex_bibfiles = ["./refs/zotero.bib", "./refs/manual.bib"]

# -- Breathe settings ---------------------------------------------------
breathe_projects = {"Core_Libraries": "./.build/doxygen/xml"}
breathe_default_project = "Core_Libraries"

# -- MyST settings ---------------------------------------------------
myst_fence_as_directive = ["mermaid"]

myst_enable_extensions = [
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
myst_enable_checkboxes = True
myst_substitutions = {
    "role": "[role](#syntax/roles)",
    "directive": "[directive](#syntax/directives)",
}

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output
# user starts in dark mode
default_dark_mode = True
html_theme = "sphinx_material"

# Material theme options (see theme.conf for more information)
html_theme_options = {
    # Set the name of the project to appear in the navigation.
    "nav_title": "The Tanglenomicon: Core Libraries",
    # Set the color and the accent color
    "theme_color": "001f3f",
    "color_primary": "#001f3f",
    "color_accent": "#7FDBFF",
    # Set the repo location to get a badge with stats
    "repo_url": "https://github.com/Uiowa-Applied-Topology/tanglenomicon_core_libraries",
    "repo_name": "tanglenomicon_core_libraries",
    "html_minify": True,
    "css_minify": True,
    "logo_icon": "",
}
html_sidebars = {
    "**": [
        "globaltoc.html",
        "localtoc.html",
    ]
}
html_show_sourcelink = False
# -- Mermaid settings ---------------------------------------------------

mermaid_d3_zoom = True
mermaid_init_js = """mermaid.initialize({
  securityLevel: 'loose',
  theme: 'dark',
});"""

# -- LaTex settings ---------------------------------------------------

latex_engine = "lualatex"
latex_theme = "howto"
latex_elements = {
    "preamble": r"""
    \usepackage{xcolor}
    \usepackage[twitter]{coloremoji}

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

# -- Misc settings ---------------------------------------------------

autosummary_generate = True
autoclass_content = "both"
autodoc_inherit_docstrings = True


class CopyDocsDriver(Driver):
    def run(self):
        self.info("Copy folder...")
        source = Path(self.config['source'])
        target = Path(self.config['target'])
        print(source)
        if not source.exists():
            self.error("Source {} does not exist".format(source))
            return
        try:
            for use_case in source.glob(f"**/{self.config['file-name']}.md"):
                dest = target.joinpath(
                    use_case.relative_to(source))
                dest.parent.mkdir(parents=True, exist_ok=True)
                copyfile(use_case, str(dest))
                ...
            for use_case in source.glob(f"**/{self.config['file-name']}"):
                dest = target.joinpath(
                    use_case.relative_to(source))
                dest.parent.mkdir(parents=True, exist_ok=True)
                copytree(use_case, str(dest))
                ...
        except IOError as e:
            self.error("Problems during copying folder.", e)

    def clean(self):
        target = Path(self.config['target'])
        try:
            for dir in Path(target).glob("./**/"):
                rmtree(dir)
                self.info("Folder deleted: {}".format(dir))
            for file in Path(target).glob(
                    f"./**/{self.config['file-name']}.md"):
                file.unlink()
                self.info("File deleted: {}".format(file))
        except FileNotFoundError:
            pass  # Already cleaned? I'm okay with it.
        except IOError as e:
            self.error("Problems during cleaning for collection {}".format(
                self.config["name"]), e)


register_driver('my_driver', CopyDocsDriver)

collections = {
    'use-cases': {
        'driver': 'my_driver',
        'source': 'source',
        'target': '../use_cases/.cp_from_source',
        'active': True,
        'file-name': "use-case",
    },
    'unit-descriptions': {
        'driver': 'my_driver',
        'source': 'source',
        'target': '../unit_description/.cp_from_source',
        'active': True,
        'file-name': "unit-description",
    },

}
