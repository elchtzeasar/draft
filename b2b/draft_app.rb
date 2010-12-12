# -*- coding: utf-8 -*-
require 'etc'
require 'io/wait'

class DraftApp
  def initialize(name)
    @name = name
    @app = Kernel.open("|bin/console_draft > #{filename} 2>&1", 'w')
    @file = File.open(filename, File::RDONLY | File::CREAT | File::TRUNC)
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
    @app.write "set_name #{name}\n"
  end

  def get_name
    @app.write "get_name\n"
  end

  def read
    @file.rewind

    @file.read
  end

  def close
    @app.write "exit\n"
    @file.close

    @app.close
  end

  def wait_for_state_change(new_state)
    wait_for_log(/STATE CHANGE [[:alpha:]*:{0,2}]+ -> #{new_state}/)
  end

  def wait_for_log(log_line)
    waits = 0
    while not(read[log_line])
      return false if waits > 10
      waits = waits + 1
      sleep(0.05)
    end

    return true
  end

private
  def filename
    logdir = "/tmp/b2b.#{`whoami`.gsub("\n", '')}"
    return "#{logdir}/draft_app_#{@name}.log"
  end
end
