#!/usr/bin/ruby

require 'b2b/draft_app'

require 'b2b/test_helper'

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

    wait_for_log(@server, 'Waiting for connections...')

    assert_includes 'Waiting for connections...', @server.read
  end

  should 'log in client when it connects' do
    @client.connect

    wait_for_log(@client, 'Connecting to server at localhost on port 10001')

    assert_includes 'Connecting to server at localhost on port 10001', @client.read
  end

  should 'log in server when client connects' do
    host_and_wait
    connect_and_wait
  
    wait_for_log(@server, 'Received incomming connection from client.')

    assert_includes 'Received incomming connection from client.', @server.read
  end

  should 'log in client when client connects' do
    host_and_wait
    connect_and_wait
  
    wait_for_log(@client, 'Connected to server')

    assert_includes 'Connected to server.', @client.read
  end

  should 'send message from server to client upon connection' do
    host_and_wait
    connect_and_wait
  
    wait_for_log(@client, 'This is server speaking...')

    assert_includes 'This is server speaking...', @client.read
  end

  def host_and_wait
    @server.host

    wait_for_log(@server, 'Received incomming connection from client')
  end

  def connect_and_wait
    @client.connect

    wait_for_log(@client, 'Connected to server')
  end

  def wait_for_log(draftApp, logLine)
    waits = 0
    while not(draftApp.read[logLine] or waits > 10)
      waits = waits + 1
      sleep(0.05)
    end
  end

  def assert_includes(substring, actual, message=nil)
    full_message = build_message(message, "<?> was expected to contain\n<?>.\n", actual, substring)
    assert_block(full_message) { actual.include? substring }
  end
end
