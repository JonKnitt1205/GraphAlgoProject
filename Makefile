# paths and names for building
exe_name1 = CaseCreator
exe_name2 = test
o_dir = Objects
s_dir = src
output_dir = Output

# compiler options
comp_flags = -std=c++11 -I src/BellmanFord -I src/CaseCreator -O3 -pedantic -Wall -Wextra 
comp_cmd = g++ $(comp_flags)
link_cmd = ${comp_cmd} $^ -o $@
build_objects_cmd = $(comp_cmd) -c $< -o $@

all: ${exe_name1} ${exe_name2}

# link object files
${exe_name1}: ${o_dir}/CaseCreatorMain.o ${o_dir}/CaseCreator.o
	${link_cmd}

# todo
${exe_name2}: 

# create object files
${o_dir}/CaseCreatorMain.o: ${s_dir}/CaseCreator/main.cpp ${s_dir}/CaseCreator/CaseCreator.hpp
	${build_objects_cmd}

${o_dir}/CaseCreator.o: ${s_dir}/CaseCreator/CaseCreator.cpp ${s_dir}/CaseCreator/CaseCreator.hpp
	${build_objects_cmd}

# clean and remove temp files
clean:
	@rm -f ${output_dir}/*.txt
	@rm -f ${o_dir}/*.o
	@rm -f ${exe_name1} ${exe_name2}
	@rm -rf .vscode
	@rm -rf .DS_Store
	@echo "Cleaned"