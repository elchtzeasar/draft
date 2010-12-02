# -*- coding: utf-8 -*-
require 'etc'
require 'io/wait'

class DraftApp
  def initialize(name)
    @name = name
    @app = Kernel.open("|bin/console_draft > #{filename} 2>&1", 'w')
    @file = File.open(filename, File::RDONLY | File::CREAT | File::TRUNC)
  end

  def host
    @app.write "host_draft\n"
  end

  def connect
    @app.write "connect_to_draft\n"
  end

  def set_name(name)
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

  def wait_for_log(logLine)
    waits = 0
    while not(read[logLine]) and waits < 10
      waits = waits + 1
      sleep(0.05)
    end
  end

private
  def filename
    logdir = "/tmp/b2b.#{`whoami`.gsub("\n", '')}"
    return "#{logdir}/draft_app_#{@name}.log"
  end
end
