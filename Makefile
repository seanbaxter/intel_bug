bug:
	spirv-link vert1.spv frag.spv -o linked_good.spv
	spirv-link vert1.spv vert2.spv frag.spv -o linked_bad.spv
	clang++ -DBAD bug.cxx -lGL -lglfw -lgl3w -o bad
	clang++ -DGOOD bug.cxx -lGL -lglfw -lgl3w -o good
