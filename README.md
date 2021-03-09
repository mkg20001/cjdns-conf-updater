# cjdns-conf-updater

Small C binary to update your cjdns configuration to include the latest nodes

Simply place your nodes in `src/nodes.ipv4.conf` and `src/nodes.ipv6.conf` and build the executable either by running cmake in src/ or running `nix build .#out` for cross-compiled binaries

NOTE: To prevent git from accidently commiting your nodes, use

```
git update-index --assume-unchanged src/nodes.ipv4.conf
git update-index --assume-unchanged src/nodes.ipv6.conf
```

(ignoring files makes nix ignore them)
