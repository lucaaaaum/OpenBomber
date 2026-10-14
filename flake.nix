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

        # Compila o jogo para a plataforma alvo de targetPkgs (nativo ou cross).
        mkOpenbomber =
          targetPkgs:
          let
            inherit (targetPkgs.stdenv.hostPlatform) isWindows;
            exe = "openbomber${targetPkgs.stdenv.hostPlatform.extensions.executable}";
            # O GLM é só cabeçalhos, mas o nixpkgs não o marca como disponível
            # para Windows.
            glm = targetPkgs.glm.overrideAttrs (old: {
              meta = old.meta // {
                platforms = pkgs.lib.platforms.all;
              };
            });
          in
          targetPkgs.stdenv.mkDerivation {
            pname = "openbomber";
            version = "0.1.0";

            src = self;

            nativeBuildInputs = [
              pkgs.cmake
            ];

            buildInputs = [
              targetPkgs.glfw
              glm
            ]
            ++ pkgs.lib.optional (!isWindows) targetPkgs.libGL;

            cmakeFlags = [
              "-DFETCHCONTENT_FULLY_DISCONNECTED=ON"
              "-DFETCHCONTENT_TRY_FIND_PACKAGE_MODE=ALWAYS"
            ];

            env.CPATH = "${stb}";

            installPhase = ''
              runHook preInstall
              install -Dm755 ${exe} $out/bin/${exe}
              runHook postInstall
            '';

            meta = {
              description = "OpenBomber: open-source bombing game";
              license = pkgs.lib.licenses.mit;
              mainProgram = "openbomber";
              platforms = pkgs.lib.platforms.unix ++ pkgs.lib.platforms.windows;
            };
          };

        openbomber = mkOpenbomber pkgs;
      in
      {
        packages.default = openbomber;
        packages.windows = mkOpenbomber pkgs.pkgsCross.mingwW64;

        apps.default = flake-utils.lib.mkApp { drv = openbomber; };

        devShells.default = pkgs.mkShell {
          inputsFrom = [ openbomber ];

          packages = with pkgs; [
            clang-tools
          ];

          shellHook = ''
            export CPATH="${stb}:$CPATH"
          '';
        };
      }
    );
}
