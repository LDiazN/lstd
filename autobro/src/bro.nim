import ./utils

proc sup(args: seq[string]): int =
  echo "sup bro"
  return 0

proc update(): int = 
  let r =  runcs(@[
    "cd autobro",
    "nimble build -d:release"
    ])
  
  if r == 0:
    echo "Build successful"
    echo "Run: "
    echo "\tcp autobro/bro.exe ."

proc build(g: bool = false): int = 
  const generate_cmake = "cmake -B build"
  const build_program = "cmake --build build" 
  if g:
    return runcs(@[
      generate_cmake,
      build_program
    ])
  else:
    return runc(build_program)

proc test(g: bool = false, c: bool = false): int = 
  return runcs(@[
    if g: "cmake -B build" else: "",
    if g or c: "cmake --build build --target tests" else: "",
    "ctest --test-dir build"
  ])

proc clean():int = 
  return runcs(@[
    "echo 'About to delete builds directory...'",
    "rmdir /S build",
    "echo 'About to delete autobro/bro.exe...",
    "del autobro\\bro.exe"
  ])


when isMainModule:
  import cligen; dispatchMulti([sup], [update], [build], [test], [clean])
