require 'rainbow'
require 'cucumber/rake/task'
success = true

namespace 'test' do
  desc 'Run unit tests'
  task :unit do
    success = success && Kernel.system("env LD_LIBRARY_PATH=$LD_LIBRARY_PATH:#{pwd}/libs bin/unit_tests")
  end

  desc 'Run component tests'
  task :component do
    success = success && Kernel.system("env LD_LIBRARY_PATH=$LD_LIBRARY_PATH:#{pwd}/libs bin/component_tests")
  end
  
  namespace 'system' do
    Cucumber::Rake::Task.new(:verified, 'Run non-wip system tests') do |task|
      task.cucumber_opts = %w{--tags ~@wip features}
    end

    Cucumber::Rake::Task.new(:wip, 'Run wip system tests') do |task|
      task.cucumber_opts = %w{--tags @wip features}
    end
  end
  
  desc 'Run system tests'
  task :system => 'test:system:verified' do
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
