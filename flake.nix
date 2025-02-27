{
  description = "Flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    {
      self,
      nixpkgs,
    }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      tex = pkgs.texlive.combine {
        inherit (pkgs.texlive)
          scheme-medium
          latexmk
          ifoddpage
          relsize
          mdframed
          zref
          needspace
          xcharter
          xstring
          xetex
          fontaxes
          amsmath
          lipsum
          enumitem
          glossaries
          listings
          tcolorbox
          environ
          tikzfill
          pdfcol
          sauerj
          adjustbox
          datetime
          fmtcount
          framed
          doi
          graphbox
          ;
      };
    in
    {

      devShells.${system}.default = pkgs.mkShell {
        NIX_LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
          pkgs.stdenv.cc.cc
          pkgs.libz
        ];

        buildInputs = with pkgs; [
          stdenv.cc.cc.lib

          git-crypt
          stdenv.cc.cc # jupyter lab needs
          just
          tex
          rsync
          python3
          act
          zip
          uv
          ruff
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
        ];

        shellHook = ''
          export PATH=":$HOME/.local/share/JetBrains/Toolbox/scripts:$HOME/.local/share/JetBrains/Toolbox/:$PATH"
          unset SOURCE_DATE_EPOCH
          echo done!
        '';
      };
    };
}
