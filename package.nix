{ stdenv, boost, cmake, cgal }:

stdenv.mkDerivation rec {
  name = "repro-${version}";
  version = "0.1.0";

  nativeBuildInputs = [
      cmake
  ];

  buildInputs = [
      boost
      cgal
  ];

  src = ./.;
}
