with (import <nixpkgs> {}); stdenv.mkDerivation {
  name = "cjdns-conf-updater";

  src = ./src;

  nativeBuildInputs = [
    cmake
  ];
}
