solution = Solution.new("hake")
project = Project.new("hake")

solution:cmd()

project:addExclude(".git/**")
project:addExclude("build/**")

project:addFile("Sources/**")
project:addExclude("kmdlib/.git/**")
project:addFile("kmdlib/**")
project:addIncludeDir("kmdlib")

solution:addProject(project)
