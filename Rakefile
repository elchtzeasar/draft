namespace 'test' do
  desc 'Run unit tests'
  task :unit do
    Kernel.system('bin/unit_tests')
  end

  desc 'Run systemt tests'
  task :system do
    require 'rake/runtest'
    Rake.run_tests('b2b/test*.rb')
  end
end

desc 'Run unit and system tests'
task :test => ['test:unit', 'test:system']