{
  description = "OpenBomber: open-source bombing game";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };

        stb = pkgs.fetchFromGitHub {
          owner = "nothings";
          repo = "stb";
          rev = "2c980bb59875b0d32144a71867fbdebb2f77cd20";
          hash = "sha256-vA5RZLte4gf5/NkbWT3VNzGVD04kyVTHPeEZwxNnxi0=";
        };

        openbomber = pkgs.stdenv.mkDerivation {
          pname = "openbomber";
          version = "0.1.0";

          src = self;

          nativeBuildInputs = with pkgs; [
            cmake
          ];

          buildInputs = with pkgs; [
            glfw
            glm
            libGL
          ];

          cmakeFlags = [
            "-DFETCHCONTENT_FULLY_DISCONNECTED=ON"
            "-DFETCHCONTENT_TRY_FIND_PACKAGE_MODE=ALWAYS"
          ];

          env.CPATH = "${stb}";

          installPhase = ''
            runHook preInstall
            install -Dm755 openbomber $out/bin/openbomber
            runHook postInstall
          '';

          meta = {
            description = "OpenBomber: open-source bombing game";
            license = pkgs.lib.licenses.mit;
            mainProgram = "openbomber";
            platforms = pkgs.lib.platforms.unix;
          };
        };
      in
      {
        packages.default = openbomber;

        apps.default = flake-utils.lib.mkApp { drv = openbomber; };

        devShells.default = pkgs.mkShell {
          inputsFrom = [ openbomber ];

          shellHook = ''
            export CPATH="${stb}:$CPATH"
          '';
        };
      }
    );
}
