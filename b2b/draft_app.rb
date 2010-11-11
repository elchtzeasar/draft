# -*- coding: utf-8 -*-
require 'io/wait'

class DraftApp
  def initialize(name)
    @name = name
    @app = Kernel.open("|bin/console_draft > #{filename}", 'w')
    @file = File.open(filename, File::RDONLY | File::CREAT | File::TRUNC)
  end

  def host
    @app.write "host_draft\n"
  end

  def connect
    @app.write "connect_to_draft\n"
  end

  def read
    #ret = ''
    @file.rewind
    #while !@file.eof?
    #  ret = ret + @file.readline
    #end
    #
    #return ret
    @file.read
  end

  def close
    @app.write "exit\n"
    @file.close
  end

  def self.kill_all
    Kernel.system('pkill console_draft')
  end

private
  def filename
    "/tmp/b2b/#{@name}.log"
  end
end
