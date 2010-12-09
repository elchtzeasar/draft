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

  should 'change state to ListentingForConnections in server when it listens' do
    @server.host
  
    assert_includes '-> Server::ListeningForConnections', @server
  end

  should 'change state to WaitingForConnection as it tries to connect' do
    @client.connect

    assert_includes '-> Client::WaitingForConnection', @client
  end

  should 'change state to Configuring in server when client connects' do
    host_and_wait
    connect_and_wait
  
    assert_includes '-> Server::ClientStateMachine::Configuring', @server
  end
  
  should 'change change state to Configuring in client when it successfully connects' do
    host_and_wait
    connect_and_wait
  
    assert_includes '-> Client::Configuring', @client
  end
  
  should 'send message from server to client upon connection' do
    host_and_wait
    connect_and_wait
  
    assert_includes 'This is server speaking...', @client
  end
  
  def host_and_wait
    @server.host

    @server.wait_for_log('-> Server::ClientStateMachine::Configuring')
  end

  def connect_and_wait
    @client.connect

    @client.wait_for_log('-> Client::Configuring')
  end
end
