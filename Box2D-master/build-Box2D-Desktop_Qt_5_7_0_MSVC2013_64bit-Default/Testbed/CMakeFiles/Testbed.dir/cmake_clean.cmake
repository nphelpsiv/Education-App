file(REMOVE_RECURSE
  "Testbed.pdb"
  "Testbed.exe"
  "Testbed.exe.manifest"
  "Testbed.lib"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Testbed.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
