# cjdns-conf-updater

Small C binary to update your cjdns configuration to include the latest nodes

Simply place your nodes in `src/nodes.ipv4.conf` and `src/nodes.ipv6.conf` and build the executable either by running cmake in src/ or running `nix build .#out` for cross-compiled binaries

(ignoring files makes nix ignore them)
