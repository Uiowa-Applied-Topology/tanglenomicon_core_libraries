with import <nixpkgs> { };

let
  pythonPackages = python310Packages; # Change to Python 3.10
in pkgs.mkShell rec {
  name = "impurePythonEnv";
  venvDir = "./.venv";
  buildInputs = [

    pkgs.stdenv.cc.cc.lib


    git-crypt
    stdenv.cc.cc # jupyter lab needs

    pythonPackages.python
    pythonPackages.venvShellHook
    pythonPackages.pip


    # sometimes you might need something additional like the following - you will get some useful error if it is looking for a binary in the environment.
    taglib
    openssl
    git
    libxml2
    libxslt
    libzip
    zlib
    clang
    cmake
    ninja
    doxygen
    emscripten
    gdb
    just
  ];

  # Run this command, only after creating the virtual environment
  postVenvCreation = ''
    unset SOURCE_DATE_EPOCH

    pip install -r requirements.txt
  '';

  # Now we can execute any commands within the virtual environment.
  # This is optional and can be left out to run pip manually.
  postShellHook = ''
    # allow pip to install wheels
    export PATH="$PWD/node_modules/.bin/:$HOME/.local/share/JetBrains/Toolbox/scripts:$HOME/.local/share/JetBrains/Toolbox/:$PATH"
    unset SOURCE_DATE_EPOCH
  '';
}

# {
#   tinypkgs ? import (fetchTarball {
#     url = "https://gitlab.inria.fr/nix-tutorial/packages-repository/-/archive/master/packages-repository-8e43243635cd8f28c7213205b08c12f2ca2ac74d.tar.gz";
#     sha256 = "sha256:09l2w3m1z0308zc476ci0bsz5amm536hj1n9xzpwcjm59jxkqpqa";
#   }) {}
# }:

# with tinypkgs; # Put tinypkgs's attributes in the current scope.
# with pkgs; # Same for pkgs.

# mkShell {
#   name = "impurePythonEnv";
#   venvDir = "./.venv";
#   buildInputs = [
#     chord
#     taglib
#     openssl
#     git
#     libxml2
#     libxslt
#     libzip
#     zlib
#     git-crypt
#     stdenv.cc.cc # jupyter lab needs
#     stdenv.cc.cc.lib
#     # Defines a python + set of packages.
#     (python3.withPackages (ps: with ps; with python3Packages; [
#       jupyter
#       # jupyterlab
#       ipython
#       ipykernel
#       venvShellHook
#       pip
#       pandas
#       numpy
#       matplotlib
#     ]))
#   ];

#   # Automatically run jupyter when entering the shell.
#   # shellHook = "jupyter notebook";

# #   # Run this command, only after creating the virtual environment
#   postVenvCreation = ''
#     unset SOURCE_DATE_EPOCH

#     python -m ipykernel install --user --name=myenv4 --display-name="myenv4"
#     pip install -r requirements.txt
#   '';

#   # Now we can execute any commands within the virtual environment.
#   # This is optional and can be left out to run pip manually.
#   postShellHook = ''
#     # allow pip to install wheels
#     unset SOURCE_DATE_EPOCH
#   '';
# }