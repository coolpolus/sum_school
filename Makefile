all:
	make --directory Day1/dz1
	make --directory Day1/pr1
	make --directory Day2/dz2_1
	make --directory Day2/dz2_2 #нечего очищать(bash)
	make --directory Day3/dz3_2
clean:
	make clean --directory Day1/dz1
	make clean --directory Day1/pr1
	make clean --directory Day2/dz2_1
	make clean --directory Day3/dz3_2