solution = Solution.new("hake")
project = Project.new("hake")

solution:cmd()

project:addExclude(".git/**")
project:addExclude("build/**")

project:addFile("Sources/**")

solution:addProject(project)
