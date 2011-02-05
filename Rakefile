namespace 'test' do
  desc 'Run unit tests'
  task :unit do
    Kernel.system("env LD_LIBRARY_PATH=#{pwd}/libs bin/unit_tests")
  end

  desc 'Run component tests'
  task :component do
    Kernel.system("env LD_LIBRARY_PATH=#{pwd}/libs bin/component_tests")
  end

  desc 'Run systems tests'
  task :system do
    require 'rake/runtest'

    logdir = "/tmp/b2b.#{Etc.getlogin}"
    Dir.mkdir(logdir) unless File.exist? logdir

    Rake.run_tests('b2b/test*.rb')
  end
end

desc 'Run unit and system tests'
task :test => ['test:unit', 'test:component', 'test:system']

namespace 'statemachine' do
  desc 'Generate state machine graph'
  task :generate do
    Kernel.system('dot -Tjpg state/graph.dot -o state/graph.jpg')
    puts 'state/graph.jpg file generated'
  end
end

desc 'Clean all generated files'
task :clean do
  puts 'Removing moc files'
  `find . -name moc_* | xargs rm`

  puts 'Removing .o files'
  `find . -name *.o | xargs rm`

  puts 'Removing binaries'
  `rm bin/*`

  puts 'Removing libs'
  `rm libs/*`

  puts 'make clean...'
  `make clean`
end
