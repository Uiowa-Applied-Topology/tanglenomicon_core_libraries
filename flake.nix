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
      systemfontdirs =
        with pkgs;
        map toString [
          noto-fonts
          noto-fonts-cjk-sans
          noto-fonts-emoji
          liberation_ttf
          fira-code
          fira-code-symbols
          mplus-outline-fonts.githubRelease
          dina-font
          proggyfonts
          freefont_ttf
        ];

      tex = pkgs.texlive.combine {
        inherit (pkgs.texlive)
          scheme-tetex
          collection-luatex
          adjustbox
          amsmath
          bbm
          biblatex
          capt-of
          catchfile
          datetime
          doi
          enumitem
          environ
          fancyhdr
          fmtcount
          fncychap
          fontaxes
          fontspec
          framed
          glossaries
          graphbox
          graphics
          hyperref
          ifoddpage
          import
          latexmk
          lipsum
          listings
          mdframed
          needspace
          pdfcol
          relsize
          sauerj
          silence
          svg
          tabulary
          tcolorbox
          tikzfill
          titlesec
          transparent
          upquote
          varwidth
          wrapfig
          xcharter
          xetex
          xstring
          xurl
          zref
          commonunicode
          newunicodechar
          gnu-freefont
          ;
      };
    in
    {

      devShells.${system}.default = pkgs.mkShell {
        NIX_LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
          # For sure not all of these are needed. I don't want to figure out which ones are.
          pkgs.alsa-lib
          pkgs.at-spi2-atk
          pkgs.at-spi2-core
          pkgs.atk
          pkgs.bzip2
          pkgs.cairo
          pkgs.cups
          pkgs.curl
          pkgs.curlWithGnuTls
          pkgs.dbus
          pkgs.dbus-glib
          pkgs.desktop-file-utils
          pkgs.e2fsprogs
          pkgs.expat
          pkgs.expat
          pkgs.flac
          pkgs.fontconfig
          pkgs.freeglut
          pkgs.freetype
          pkgs.fribidi
          pkgs.fuse
          pkgs.fuse
          pkgs.fuse3
          pkgs.fuse3
          pkgs.gdk-pixbuf
          pkgs.glew110
          pkgs.glib
          pkgs.glib
          pkgs.gmp
          pkgs.gst_all_1.gst-plugins-ugly
          pkgs.gst_all_1.gstreamer
          pkgs.gtk2
          pkgs.harfbuzz
          pkgs.icu
          pkgs.icu
          pkgs.keyutils.lib
          pkgs.libappindicator-gtk2
          pkgs.libcaca
          pkgs.libcanberra
          pkgs.libcap
          pkgs.libclang.lib
          pkgs.libdbusmenu
          pkgs.libdrm
          pkgs.libgcrypt
          pkgs.libGL
          pkgs.libGLU
          pkgs.libgpg-error
          pkgs.libidn
          pkgs.libjack2
          pkgs.libjpeg
          pkgs.libmikmod
          pkgs.libogg
          pkgs.libpng12
          pkgs.libpulseaudio
          pkgs.librsvg
          pkgs.libsamplerate
          pkgs.libthai
          pkgs.libtheora
          pkgs.libtiff
          pkgs.libudev0-shim
          pkgs.libusb1
          pkgs.libuuid
          pkgs.libvdpau
          pkgs.libvorbis
          pkgs.libvpx
          pkgs.libxcrypt-legacy
          pkgs.libxkbcommon
          pkgs.libxml2
          pkgs.libzip
          pkgs.mesa
          pkgs.nspr
          pkgs.nss
          pkgs.openssl
          pkgs.p11-kit
          pkgs.pango
          pkgs.pixman
          pkgs.python3
          pkgs.SDL
          pkgs.SDL_image
          pkgs.SDL_mixer
          pkgs.SDL2
          pkgs.SDL2_image
          pkgs.SDL2_mixer
          pkgs.SDL2_ttf
          pkgs.speex
          pkgs.stdenv.cc.cc
          pkgs.stdenv.cc.cc.lib
          pkgs.tbb
          pkgs.udev
          pkgs.vulkan-loader
          pkgs.wayland
          pkgs.xorg.libICE
          pkgs.xorg.libpciaccess
          pkgs.xorg.libSM
          pkgs.xorg.libX11
          pkgs.xorg.libxcb
          pkgs.xorg.libXcomposite
          pkgs.xorg.libXcursor
          pkgs.xorg.libXdamage
          pkgs.xorg.libXext
          pkgs.xorg.libXfixes
          pkgs.xorg.libXft
          pkgs.xorg.libXi
          pkgs.xorg.libXinerama
          pkgs.xorg.libXmu
          pkgs.xorg.libXrandr
          pkgs.xorg.libXrender
          pkgs.xorg.libXScrnSaver
          pkgs.xorg.libXt
          pkgs.xorg.libXtst
          pkgs.xorg.libXxf86vm
          pkgs.xorg.xcbutil
          pkgs.xorg.xcbutilimage
          pkgs.xorg.xcbutilkeysyms
          pkgs.xorg.xcbutilrenderutil
          pkgs.xorg.xcbutilwm
          pkgs.xorg.xkeyboardconfig
          pkgs.xz
          pkgs.zlib
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
          wget
          rip2
          ninja
          clang
          graphviz
          imagemagick
          inkscape
          svg2pdf
          twemoji-color-font
          dejavu_fonts
          lmodern
          nodePackages.prettier
          freefont_ttf
          dos2unix
        ];
        # used by xetex and mtx-fonts (context)
        FONTCONFIG_FILE = pkgs.makeFontsConf { fontDirectories = systemfontdirs ++ [ tex.fonts ]; };
        # used by luaotfload (lualatex)
        OSFONTDIR = pkgs.lib.concatStringsSep "//:" systemfontdirs;
        LOCALE_ARCHIVE = "${pkgs.glibcLocales}/lib/locale/locale-archive";

        shellHook = ''
          export LD_LIBRARY_PATH="$NIX_LD_LIBRARY_PATH"
          export PATH=":$HOME/.local/share/JetBrains/Toolbox/scripts/:$HOME/.local/share/JetBrains/Toolbox/:$PATH"
          unset SOURCE_DATE_EPOCH
          wget -q --spider https://google.com

          if [ $? -eq 0 ]; then
              echo "Online"
              rip .venv
          else
              echo "Offline"
          fi

          just bootstrap
          luaotfload-tool --cache=erase --flush-lookups --force
          source .venv/bin/activate
          echo done!
        '';
      };
    };
}
