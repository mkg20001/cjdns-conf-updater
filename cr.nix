env:

env.make_derivation {
  builder = ./builder.sh;
  src = ./src;
  # cross_inputs = [ env.cmake ];
}
