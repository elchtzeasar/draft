# -*- coding: utf-8 -*-
require 'etc'
require 'fileutils'
require 'io/wait'

require 'rainbow'

class DraftApp
  def initialize(name, scenario_name)
    @name = name
    @app = Kernel.open("|GLOG_logtostderr=1 bin/console_draft > #{filename(scenario_name)} 2>&1", 'w')
    @file = File.open(filename(scenario_name), File::RDONLY | File::CREAT | File::TRUNC)
  end

  attr_reader :name

  def host
    @app.write "host_draft\n"
  end

  def connect
    @app.write "connect_to_draft\n"
  end

  def set_name(name)
    @name = name
    configure_name
  end

  def configure_name
    @app.write "set_name #{@name}\n"
  end

  def get_name
    @app.write "get_name\n"
  end

  def read
    @file.rewind

    @file.read
  end

  def close
    begin
      @app.write "exit\n"
    rescue
      puts "Error when closing application: #{@name}, killing all console_drafts".color(:red)
      Kernel.system('pkill console_draft')
    end
    @file.close

    @app.close
  end

  def wait_for_state_change(new_state)
    wait_for_log(/STATE CHANGE [[:alpha:]*:{0,2}]+ -> #{new_state}/)
  end

  def wait_for_log(log_line)
    waits = 0
    while not(read[log_line])
      if waits > 25
        puts("Timed out waiting for log: '#{log_line}'")
        return read
      end
      waits = waits + 1
      sleep(0.05)
    end

    return read
  end

private
  def filename(scenario_name)
    logdir = "/tmp/b2b.#{`whoami`.gsub("\n", '')}/#{scenario_name.gsub(' ', '_')}"
    FileUtils.mkdir_p logdir
    return "#{logdir}/draft_app_#{@name.gsub(' ', '_')}.log"
  end
end
