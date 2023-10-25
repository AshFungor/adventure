#bin/sh

target_dir="../game/bin"
for _lib in *.so; do
	test -f "$target_dir/$_lib" && rm -f "$target_dir/$_lib";
	cp $_lib $target_dir;
	printf "moving lib: $_lib";
done

