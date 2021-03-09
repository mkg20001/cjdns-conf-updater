# cjdns-conf-updater

C payload for updating your remote devices' CJDNS config

Simply place your nodes in `src/nodes.ipv4.conf` and `src/nodes.ipv6.conf` and build the executable either by running cmake in src/ or running `nix build .#out` for cross-compiled binaries

(ignoring files makes nix ignore them)
