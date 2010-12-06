namespace 'test' do
  desc 'Run unit tests'
  task :unit do
    Kernel.system('bin/unit_tests')
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
task :test => ['test:unit', 'test:system']

namespace 'statemachine' do
  desc 'Generate state machine graph'
  task :generate do
    Kernel.system('dot -Tjpg state/graph.dot -o state/graph.jpg')
    puts 'state/graph.jpg file generated'
  end
end