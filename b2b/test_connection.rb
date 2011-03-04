#!/usr/bin/ruby

require 'b2b/draft_app'

require 'b2b/test_helper'

class Connection < Test::Unit::TestCase
  def setup
    @server = DraftApp.new("#{app_name}-server")
    @client = DraftApp.new("#{app_name}-client")
  end

  def teardown
    @server.close
    @client.close
  end

  # TODO: Change this to use folders instead of just a log file name
  def app_name
    return self.name.gsub(/test: |\.|\([^\)]*\)/, '').gsub(' ', '_')
  end

  should 'log in client when it is connected to the server' do
    host_and_wait
    connect_and_wait

    assert_includes('Connected to server', @client)
  end

  should 'log in server when a client is connected' do
    @client.set_name 'Client'
    host_and_wait
    connect_and_wait

    assert_includes("Client connected", @server)
  end
  
  def host_and_wait
    @server.host

    @server.wait_for_state_change('Server::ClientStateMachine::Configuring')
  end

  def connect_and_wait
    @client.connect

    @client.wait_for_state_change('Client::Configuring')
  end
end
