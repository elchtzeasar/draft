require 'rainbow'

success = true

namespace 'test' do
  desc 'Run unit tests'
  task :unit do
    success = success && Kernel.system("bin/unit_tests")
  end

  desc 'Run component tests'
  task :component do
    success = success && Kernel.system("bin/component_tests")
  end

  desc 'Run systems tests'
  task :system do
    require 'rake/runtest'

    logdir = "/tmp/b2b.#{Etc.getlogin}"
    Dir.mkdir(logdir) unless File.exist? logdir

    Rake.run_tests('b2b/test*.rb')
  end
end

desc 'Run unit, component and system tests'
task :test => ['test:unit', 'test:component', 'test:system'] do
  puts 'Component or unit tests failed'.color(:red) unless success
end

namespace 'statemachine' do
  desc 'Generate state machine graph'
  task :generate do
    Kernel.system('dot -Tjpg state/graph.dot -o state/graph.jpg')
    puts 'state/graph.jpg file generated'
  end
end

namespace 'clean' do
  desc 'remove mocs'
  task :moc do
    puts 'Removing moc files'
    `find . -name moc_* | xargs rm`
  end

  desc 'remote object (.o) files'
  task :object do
    puts 'Removing .o files'
    `find . -name *.o | xargs rm`
  end

  desc 'remove binary files'
  task :binaries do
    puts 'Removing binaries'
    `rm bin/*`
  end

  desc 'remove library files'
  task :library do
    puts 'Removing libs'
    `rm libs/*`
  end

  desc 'make clean'
  task :make do
    puts 'make clean...'
    `make clean`
  end

  desc 'remove Makefiles'
  task :makefiles do
    puts 'Removing Makefiles'
    puts `find . -name Makefile | xargs rm`
  end
end

desc 'Clean all generated files'
task :clean => ['clean:moc', 'clean:object', 'clean:binaries', 'clean:library', 'clean:make', 'clean:makefiles'] do
end
