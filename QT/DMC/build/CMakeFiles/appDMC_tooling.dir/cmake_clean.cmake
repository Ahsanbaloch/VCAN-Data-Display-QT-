file(REMOVE_RECURSE
  "DMC/Main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/appDMC_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
