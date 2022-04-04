{ stdenv
, cmake
, ragel
, nix-gitignore
} :
stdenv.mkDerivation {
  name = "incavead";
  version = "20220404";
  src = nix-gitignore.gitignoreSourcePure [ ./.gitignore ] ./.;
  nativeBuildInputs = [ cmake ragel ];
}
