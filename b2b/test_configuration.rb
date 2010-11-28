#!/usr/bin/ruby

require 'b2b/draft_app'

require 'b2b/test_helper'

class Configuration < Test::Unit::TestCase
  def setup
    Dir.mkdir('/tmp/b2b') unless FileTest.exists?('/tmp/b2b')

    create_configuration_file

    @app = DraftApp.new(app_name)
  end

  def teardown
    @app.close

    remove_configuration_file
  end

  def app_name
    return self.name.gsub(/test: |\.|\([^\)]*\)/, '').gsub(' ', '_')
  end

  def create_configuration_file
    File.open('configuration.xml', File::CREAT|File::TRUNC|File::WRONLY)
  end

  def remove_configuration_file
    File.delete('configuration.xml')
  end

  should 'have same player name as was set' do
    @app.set_name("player-name")
    @app.get_name

    assert_includes "Player name: player-name", @app
  end

  should 'have the last set name upon restarting app' do
    first_app = DraftApp.new('first-configuration-app')
    first_app.set_name("player-name")
    first_app.wait_for_log('Configuration saved')
    first_app.close

    second_app = DraftApp.new('second-configuration-app')
    second_app.get_name
    
    assert_includes "Player name: player-name", second_app

    second_app.close
  end
end
