#!/usr/bin/ruby

require 'b2b/draft_app'

require 'b2b/test_helper'

SLEEP_TIME = 0.5

class B2BTest < Test::Unit::TestCase
  def setup
    Dir.mkdir('/tmp/b2b') unless FileTest.exists?('/tmp/b2b')
    DraftApp.kill_all

    @server = DraftApp.new('server')
    @client = DraftApp.new('client')
  end

  def teardown
    @server.close
    @client.close
  end

  should 'log in server when it listens' do
    @server.host

    sleep(SLEEP_TIME)

    assert_includes 'Waiting for connections...', @server.read
  end

  should 'log in client when it connects' do
    @client.connect

    sleep(SLEEP_TIME)

    assert_includes 'Connecting to server at localhost on port 10001', @client.read
  end

  should 'log in server when client connects' do
    host_and_wait
    connect_and_wait
  
    sleep(SLEEP_TIME)

    assert_includes 'Received incomming connection from client.', @server.read
  end

  should 'log in client when client connects' do
    host_and_wait
    connect_and_wait
  
    sleep(SLEEP_TIME)

    assert_includes 'Connected to server.', @client.read
  end

  should 'send message from server to client upon connection' do
    host_and_wait
    connect_and_wait
  
    sleep(SLEEP_TIME)

    assert_includes 'This is server speaking...', @client.read
  end

  def host_and_wait
    @server.host

    waits = 0
    while not(@server.read[/Received incomming connection from client/] or waits > 10)
      waits = waits + 1
      sleep(0.1)
    end
  end

  def connect_and_wait
    @client.connect

    waits = 0
    while not(@server.read[/Connected to server/] or waits > 10)
      waits = waits + 1
      sleep(0.1)
    end
  end

  def assert_includes(substring, actual, message=nil)
    full_message = build_message(message, "<?> was expected to contain\n<?>.\n", actual, substring)
    assert_block(full_message) { actual.include? substring }
  end
end
