# --------- build german_english_dictionary plugin ----------- #
add_library(german_english_dictionary-objs
  OBJECT
    german_english_dictionary.cpp
  )

set_target_properties(german_english_dictionary-objs
  PROPERTIES
    POSITION_INDEPENDENT_CODE 1
  )

add_library(german_english_dictionary-shared
  SHARED
    $<TARGET_OBJECTS:german_english_dictionary-objs>
  )

set_target_properties(german_english_dictionary-shared
  PROPERTIES
  OUTPUT_NAME "german_english_dictionary"
  )

# --------- build german_french_dictionary plugin ----------- #
add_library(german_french_dictionary-objs
  OBJECT
    german_french_dictionary.cpp
  )

set_target_properties(german_french_dictionary-objs
  PROPERTIES
    POSITION_INDEPENDENT_CODE 1
  )

add_library(german_french_dictionary-shared
  SHARED
    $<TARGET_OBJECTS:german_french_dictionary-objs>
  )

set_target_properties(german_french_dictionary-shared
  PROPERTIES
  OUTPUT_NAME "german_french_dictionary"
  )

