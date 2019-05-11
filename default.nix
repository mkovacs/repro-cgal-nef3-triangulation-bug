with import <nixpkgs> { };

callPackage ./package.nix {
  cgal = callPackage ./CGAL {};
}
