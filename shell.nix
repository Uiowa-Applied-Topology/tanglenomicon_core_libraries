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
    export PATH=":$HOME/.local/share/JetBrains/Toolbox/scripts:$HOME/.local/share/JetBrains/Toolbox/:$PATH"
    unset SOURCE_DATE_EPOCH
  '';
}

