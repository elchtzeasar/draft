#!/usr/bin/ruby

require 'b2b/draft_app'

require 'b2b/test_helper'

class Connection < Test::Unit::TestCase
  def setup
    Dir.mkdir('/tmp/b2b') unless FileTest.exists?('/tmp/b2b')

    @server = DraftApp.new("#{app_name}-server")
    @client = DraftApp.new("#{app_name}-client")
  end

  def teardown
    @server.close
    @client.close
  end

  def app_name
    return self.name.gsub(/test: |\.|\([^\)]*\)/, '').gsub(' ', '_')
  end

  should 'log in server when it listens' do
    @server.host
  
    assert_includes 'Waiting for connections...', @server
  end

  should 'log in client when it connects' do
    @client.connect

    assert_includes 'Connecting to server at localhost on port 10001', @client
  end

  should 'log in server when client connects' do
    host_and_wait
    connect_and_wait
  
    assert_includes 'Received incomming connection from client.', @server
  end
  
  should 'log in client when client connects' do
    host_and_wait
    connect_and_wait
  
    assert_includes 'Connected to server.', @client
  end
  
  should 'send message from server to client upon connection' do
    host_and_wait
    connect_and_wait
  
    assert_includes 'This is server speaking...', @client
  end
  
  def host_and_wait
    @server.host

    @server.wait_for_log('Received incomming connection from client')
  end

  def connect_and_wait
    @client.connect

    @client.wait_for_log('Connected to server')
  end
end
