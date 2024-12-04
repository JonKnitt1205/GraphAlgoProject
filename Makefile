# paths and names for building
exe_name1 = CaseCreator
exe_name2 = test
o_dir = Objects
s_dir = src
output_dir = Output

# compiler options
comp_flags = -std=c++11 -I src/BellmanFord -I src/CaseCreator -I src/CaseParser -I src/Util -O3 -pedantic -Wall -Wextra 
comp_cmd = g++ $(comp_flags)
link_cmd = ${comp_cmd} $^ -o $@
build_objects_cmd = $(comp_cmd) -c $< -o $@

all: ${exe_name1} ${exe_name2}

# link object files
${exe_name1}: ${o_dir}/CaseCreatorMain.o ${o_dir}/CaseCreator.o
	${link_cmd}

${exe_name2}: ${o_dir}/main.o ${o_dir}/CaseCreator.o ${o_dir}/CaseParser.o ${o_dir}/BellmanFord.o
	${link_cmd}

# create object files
${o_dir}/main.o: ${s_dir}/main.cpp ${s_dir}/CaseCreator/CaseCreator.hpp ${s_dir}/CaseParser/CaseParser.hpp
	${build_objects_cmd}

${o_dir}/CaseCreatorMain.o: ${s_dir}/CaseCreator/main.cpp ${s_dir}/CaseCreator/CaseCreator.hpp ${s_dir}/Util/GraphTypes.hpp
	${build_objects_cmd}

${o_dir}/CaseParser.o: ${s_dir}/CaseParser/CaseParser.cpp ${s_dir}/CaseParser/CaseParser.hpp ${s_dir}/Util/GraphTypes.hpp
	${build_objects_cmd}

${o_dir}/CaseCreator.o: ${s_dir}/CaseCreator/CaseCreator.cpp ${s_dir}/CaseCreator/CaseCreator.hpp
	${build_objects_cmd}

${o_dir}/BellmanFord.o: ${s_dir}/BellmanFord/BellmanFord.cpp ${s_dir}/BellmanFord/BellmanFord.hpp ${s_dir}/Util/GraphTypes.hpp
	${build_objects_cmd}

${o_dir}/AStar.o: ${s_dir}/AStar/AStar.cpp ${s_dir}/AStar/AStar.hpp ${s_dir}/Util/GraphTypes.hpp
	${build_objects_cmd}

# clean and remove temp files
clean:
	@rm -f ${output_dir}/*.txt
	@rm -f ${o_dir}/*.o
	@rm -f ${exe_name1} ${exe_name2}
	@rm -rf .vscode
	@rm -rf .DS_Store
	@echo "Cleaned"