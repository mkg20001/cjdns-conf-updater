{
  description = "cjdns config updater";

  inputs.nixcrpkgs.url = "github:mkg20001/nixcrpkgs/flake";

  outputs = { self, nixpkgs, nixcrpkgs }:
    let
      cr = nixcrpkgs.lib.nixcrpkgs { nixpkgs = (import nixpkgs { system = "x86_64-linux"; }); macos_sdk = null; };
      pkg = import ./cr.nix;
    in
      {
        out = cr.bundle {
          win32 = pkg cr.win32;
          # linux-x86 = linux-x86;
          # linux-rpi = linux-rpi;
          # macos = macos;
        };
      };
}
